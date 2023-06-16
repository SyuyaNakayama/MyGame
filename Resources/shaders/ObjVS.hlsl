#include "Obj.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	// 法線にワールド行列によるスケーリング・回転を適用
	float4 wnormal = normalize(mul(world, float4(normal, 0)));

	VSOutput output;
	output.svpos = mul(mul(viewproj, world), pos);
	output.worldpos = mul(world, pos);
	output.normal = wnormal.xyz;
	output.uv = uv * tiling + uvOffset;
	return output;
}