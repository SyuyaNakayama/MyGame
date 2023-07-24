#include "Obj.hlsli"

Texture2D<float4> mainTex : register(t0); // 0番スロットに設定されたテクスチャ
Texture2D<float4> subTex : register(t1); // 1番スロットに設定されたテクスチャ
Texture2D<float4> blendMask : register(t2); // 2番スロットに設定されたテクスチャ
Texture2D<float4> specularMask : register(t3); // 3番スロットに設定されたテクスチャ
Texture2D<float4> dissolveMask : register(t4); // 4番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	// テクスチャマッピング
    float4 mainTexColor = mainTex.Sample(smp, texTrans[0].GetUV(input.uv)) * color[0];
    float4 subTexColor = subTex.Sample(smp, texTrans[1].GetUV(input.uv)) * color[1];
    
    // マスク値の取得
    float blendMaskVal = blendMask.Sample(smp, texTrans[2].GetUV(input.uv)).r * maskPow[0];
    float specularMaskVal = specularMask.Sample(smp, texTrans[3].GetUV(input.uv)).r * maskPow[1];
    float dissolveMaskVal = dissolveMask.Sample(smp, input.uv).r;
    
    // テクスチャブレンド
    float4 texcolor = lerp(mainTexColor, subTexColor, blendMaskVal);
    
	// 環境反射光
    float3 ambient = material.ambient;
	// 光計算関数へ送るデータ
    LightData lightData;
    lightData.normal = input.normal;
    lightData.worldpos = input.worldpos.xyz;
	// 頂点から視点への方向ベクトル
    lightData.eyedir = normalize(cameraPos - input.worldpos.xyz);
	// 光沢度
    lightData.shininess = 4.0f;
	// シェーディングによる色
    float4 shadecolor = float4(lightGroup.ambientColor * ambient, 1.0f);
    shadecolor.rgb += lightGroup.ComputeLightEffect(lightData, material);

    shadecolor.a = 1.0f;
    return shadecolor * texcolor;
}