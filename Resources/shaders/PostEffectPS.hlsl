#include "PostEffectFunctions.hlsli"

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv);
    
    switch (effectType)
    {
        case 1: // ���P�x���o
            texcolor = GetHighLumi(input);
            break;
        case 2: // �K�E�V�A���u���[
            texcolor = GaussianBlur(input);
            break;
        case 3: // �P�����̃K�E�V�A���u���[
            texcolor = GaussianBlurLinear(input);
            break;
        case 4: // �N���X�t�B���^
            texcolor *= CreateDotFilter(input);
            break;
        case 5: // �F���]
            texcolor = ColorFlip(texcolor);
            break;
        case 6: // ���ςڂ���
            texcolor = Blur(input, 3);
            break;
    }
    texcolor.a = 1;
    return texcolor;
}