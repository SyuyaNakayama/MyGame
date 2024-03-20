#include "PostEffectFunctions.hlsli"

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv);
    
    switch (effectType)
    {
        case 1: // 高輝度抽出
            texcolor = GetHighLumi(input);
            break;
        case 2: // ガウシアンブラー
            texcolor = GaussianBlur(input);
            break;
        case 3: // 単方向のガウシアンブラー
            texcolor = GaussianBlurLinear(input);
            break;
        case 4: // クロスフィルタ
            texcolor *= CreateDotFilter(input);
            break;
        case 5: // 色反転
            texcolor = ColorFlip(texcolor);
            break;
        case 6: // 平均ぼかし
            texcolor = Blur(input, 3);
            break;
    }
    texcolor.a = 1;
    return texcolor;
}