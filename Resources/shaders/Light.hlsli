struct DirLight
{
    float3 lightv; // ���C�g�ւ̕����̒P�ʃx�N�g��
    float3 lightcolor; // ���C�g�̐F(RGB)
    uint active;
};

struct PointLight
{
    float3 lightpos; // ���C�g���W
    float3 lightcolor; // ���C�g�̐F(RGB)
    float3 lightatten; // ���C�g���������W��
    uint active;
};

struct SpotLight
{
    float3 lightv; // ���C�g�̌��������̋t�x�N�g��
    float3 lightpos; // ���C�g���W
    float3 lightcolor; // ���C�g�̐F(RGB)
    float3 lightatten; // ���C�g���������W��
    float2 lightfactoranglecos; // ���C�g�����p�x��cos
    uint active;
};

struct CircleShadow
{
    float3 dir; // ���e�����̋t�x�N�g��(�P�ʃx�N�g��)
    float3 casterPos; // �L���X�^�[���W
    float distanceCasterLight; // �L���X�^�[�ƃ��C�g�̋���
    float3 atten; // ���������W��
    float2 factorAngleCos; // �����p�x��cos
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
    float3 ambient; // �A���r�G���g�W��
    float3 diffuse; // �f�B�t���[�Y�W��
    float3 specular; // �X�y�L�����[�W��
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
		// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
        float3 dotlightnormal = dot(dirLight.lightv, normal);
		// ���ˌ��x�N�g��
        float3 reflect = normalize(-dirLight.lightv + 2 * dotlightnormal * normal);
		// �g�U���ˌ�
        float3 diffuse = saturate(dotlightnormal * diffuse);
		// ���ʔ��ˌ�
        float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * specular;
		// �S�ĉ��Z����
        sumColor += (diffuse + specular) * dirLight.lightcolor;
    }
    return sumColor;
}