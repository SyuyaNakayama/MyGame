struct DirLight
{
    float3 lightv; // ライトへの方向の単位ベクトル
    float3 lightcolor; // ライトの色(RGB)
    uint active;
};

struct PointLight
{
    float3 lightpos; // ライト座標
    float3 lightcolor; // ライトの色(RGB)
    float3 lightatten; // ライト距離減衰係数
    uint active;
};

struct SpotLight
{
    float3 lightv; // ライトの光線方向の逆ベクトル
    float3 lightpos; // ライト座標
    float3 lightcolor; // ライトの色(RGB)
    float3 lightatten; // ライト距離減衰係数
    float2 lightfactoranglecos; // ライト減衰角度のcos
    uint active;
};

struct CircleShadow
{
    float3 dir; // 投影方向の逆ベクトル(単位ベクトル)
    float3 casterPos; // キャスター座標
    float distanceCasterLight; // キャスターとライトの距離
    float3 atten; // 距離減衰係数
    float2 factorAngleCos; // 減衰角度のcos
    uint active;
};

static const uint DIRLIGHT_NUM = 3;
static const uint POINTLIGHT_NUM = 3;
static const uint SPOTLIGHT_NUM = 3;
static const uint CIRCLESHADOW_NUM = 1;

struct LightGroup
{
    float3 ambientColor;
    DirLight dirLights[DIRLIGHT_NUM];
    PointLight pointLights[POINTLIGHT_NUM];
    SpotLight spotLights[SPOTLIGHT_NUM];
    CircleShadow circleShadows[CIRCLESHADOW_NUM];
};

struct Material
{
    float3 ambient; // アンビエント係数
    float3 diffuse; // ディフューズ係数
    float3 specular; // スペキュラー係数
};

float3 ComputeDirLight(LightGroup lightGroup, float3 normal, float3 eyedir, const float shininess, Material material)
{
    float3 sumColor;
    for (int i = 0; i < DIRLIGHT_NUM; i++)
    {
        DirLight dirLight = lightGroup.dirLights[i];
        if (!dirLight.active)
        {
            continue;
        }
		// ライトに向かうベクトルと法線の内積
        float3 dotlightnormal = dot(dirLight.lightv, normal);
		// 反射光ベクトル
        float3 reflect = normalize(-dirLight.lightv + 2 * dotlightnormal * normal);
		// 拡散反射光
        float3 diffuse = saturate(dotlightnormal * diffuse);
		// 鏡面反射光
        float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * specular;
		// 全て加算する
        sumColor += (diffuse + specular) * dirLight.lightcolor;
    }
    return sumColor;
}