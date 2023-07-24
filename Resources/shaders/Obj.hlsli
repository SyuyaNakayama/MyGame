#include "Light.hlsli"

cbuffer cbuff0 : register(b0)
{
	matrix world; // ワールド行列
};

cbuffer cbuff1 : register(b1)
{
    Material material;
	float2 uvOffset;
	float2 tiling;
	float4 color;
}

cbuffer cbuff2 : register(b2)
{
    LightGroup lightGroup;
}

cbuffer cbuff3 : register(b3)
{
	matrix viewproj; // ビュープロジェクション行列
	float3 cameraPos; // カメラ座標(ワールド座標)
};

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; // システム用頂点座標
	float4 worldpos : POSITION; // ワールド座標
	float3 normal : NORMAL; // 法線
	float2 uv : TEXCOORD; // uv値
};