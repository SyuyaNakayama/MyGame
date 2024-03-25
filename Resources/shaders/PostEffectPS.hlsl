#include "PostEffectFunctions.hlsli"

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv);
    
    // �P�x��ύX
    texcolor = ChangeBrightness(texcolor, brightness);
    // UV���炵
    texcolor = ChangeUV(input, uvOffset);
    
    switch (effectType)
    {
        case 1: // �F���]
            texcolor = ColorFlip(texcolor);
            break;
        case 2: // �O���[�X�P�[��
            texcolor = GrayScale(texcolor);
            break;
        case 3: // ���P�x���o
            texcolor = GetHighLumi(input);
            break;
        case 4: // ���ςڂ���
            texcolor = Blur(input, 3);
            break;
        case 5: // �K�E�V�A���u���[
            texcolor = GaussianBlur(input);
            break;
        case 6: // �P�����̃K�E�V�A���u���[
            texcolor = GaussianBlurLinear(input);
            break;
        case 7: // �N���X�t�B���^
            texcolor *= CreateDotFilter(input);
            break;
        case 8: // �u���[��
            texcolor = Bloom(input);
            break;
    }
    texcolor.a = 1;
    return texcolor;
}