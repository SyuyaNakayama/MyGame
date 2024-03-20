#include "PostEffect.hlsli"
SamplerState smp : register(s0);
Texture2D<float4> tex : register(t0);

float4 ChangeBrightness(float4 col, float brightness)
{
    return float4(col.rgb * brightness, 1);
}

float4 ColorFlip(float4 col)
{
    return float4(float3(1, 1, 1) - col.rgb, 1);
}

float4 ChangeUV(VSOutput i, float2 uvOffset)
{
    return float4(tex.Sample(smp, i.uv + uvOffset).rgb, 1);
}

float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
    float d = distance(drawUV, pickUV);
    return exp(-(d * d) / (2 * sigma * sigma));
}

float GrayScale(float4 col)
{
    return col.r * 0.299 + col.g * 0.587 + col.b * 0.114;
}

float4 GetHighLumi(VSOutput i)
{
    float4 col = tex.Sample(smp, i.uv);
    float grayScale = GrayScale(col);
    float extract = smoothstep(0.6, 0.9, grayScale);
    return col * extract;
}

float4 Blur(VSOutput i, float blurRange)
{
    float4 col = float4(0, 0, 0, 0);
    float num = 0;
    float2 texSize;
    tex.GetDimensions(texSize.x, texSize.y);

    for (float py = -blurRange; py <= blurRange; py++)
    {
        for (float px = -blurRange; px <= blurRange; px++)
        {
            float2 pickUV = i.uv + float2(px / texSize.x, py / texSize.y);
            col += tex.Sample(smp, pickUV);
            num++;
        }
    }
    col.rgb /= num; // �������u�d�݁v���A���ʂ��犄��
    col.a = 1;
    return col;
}

float4 GaussianBlur(VSOutput i)
{
    float totalWeight = 0, sigma = 0.005, stepWidth = 0.001;
    float4 col = float4(0, 0, 0, 0);

    for (float py = -sigma * 2; py <= sigma * 2; py += stepWidth)
    {
        for (float px = -sigma * 2; px <= sigma * 2; px += stepWidth)
        {
            float2 pickUV = i.uv + float2(px, py);
            float weight = Gaussian(i.uv, pickUV, sigma);
			// Gaussian�Ŏ擾�����u�d�݁v��F�ɂ�����
            col += tex.Sample(smp, pickUV) * weight;
			// �������u�d�݁v�̍��v�l���T���Ă���
            totalWeight += weight;
        }
    }
    col.rgb = col.rgb / totalWeight; // �������u�d�݁v���A���ʂ��犄��
    col.a = 1;
    return col;
}

// �����̃K�E�V�A���u���[
float4 GaussianBlurLinear(VSOutput i)
{
    float totalWeight = 0;
    float4 color = float4(0, 0, 0, 0);
    float pickRange = 0.06; // �K�E�X�֐����ł�����

    // �����Ȃ̂�for���͈��
    for (float j = -pickRange; j <= pickRange; j += 0.005)
    {
        float x = cos(angle) * j; // �p�x������W���w��
        float y = sin(angle) * j;
        float2 pickUV = i.uv + float2(x, y); // �F�擾������W
        // ����̃K�E�X�֐��Ōv�Z
        float weight = Gaussian(i.uv, pickUV, pickRange);
		// �擾����F��weight���|����
        color += tex.Sample(smp, pickUV) * weight;
		// �|����weight�̍��v�l���T���Ă���
        totalWeight += weight;
    }
    color /= totalWeight; // �������킹���F��weight�̍��v�l�Ŋ���
    return color;
}

float4 CreateDotFilter(VSOutput i)
{
    float2 texSize = float2(0, 0);
    float level = 0;
    tex.GetDimensions(0, texSize.x, texSize.y, level);
    float2 st = i.uv / texSize.x * 20;
    st = frac(st * texSize.xy);
    float l = distance(st, float2(0.5, 0.5));
    float4 col = float4(1, 1, 1, 1) * 1 - step(0.3, l);
    col.a = 1.0;
    return col;
}

float4 Bloom(VSOutput i)
{
    float4 highLumi = GetHighLumi(i); // ���P�x���o
    float4 blur = GaussianBlur(i); // �ڂ���
    return tex.Sample(smp, i.uv) + highLumi + blur; // �e�N�X�`������
}