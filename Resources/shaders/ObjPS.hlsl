#include "Obj.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	// テクスチャマッピング
    float4 texcolor = tex.Sample(smp, input.uv);
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
    return shadecolor * texcolor * color;
}