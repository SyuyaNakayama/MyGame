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

struct Material
{
    float3 ambient; // �A���r�G���g�W��
    float3 diffuse; // �f�B�t���[�Y�W��
    float3 specular; // �X�y�L�����[�W��
};

struct LightData
{
    float3 normal;
    float3 worldpos;
    float3 eyedir;
    float shininess;
    float3 texcolor;
    float specularMaskVal;
};

struct LightGroup
{
    float3 ambientColor;
    DirLight dirLights[DIRLIGHT_NUM];
    PointLight pointLights[POINTLIGHT_NUM];
    SpotLight spotLights[SPOTLIGHT_NUM];
    CircleShadow circleShadows[CIRCLESHADOW_NUM];

    float3 ComputeDirLight(LightData lightData, Material material);
    float3 ComputePointLight(LightData lightData, Material material);
    float3 ComputeSpotLight(LightData lightData, Material material);
    float3 ComputeCircleShadow(float3 worldpos, Material material);
    float3 ComputeLightEffect(LightData lightData, Material material);
};

float3 ComputeDiffuseSpecular(float3 lightv, LightData lightData, Material material)
{
    // ���C�g�Ɍ������x�N�g���Ɩ@���̓���
    float3 dotlightnormal = dot(lightv, lightData.normal);
    // ���ˌ��x�N�g��
    float3 reflect = normalize(-lightv + 2 * dotlightnormal * lightData.normal);
	// �g�U���ˌ�
    float3 diffuse = saturate(dotlightnormal * material.diffuse);
	// ���ʔ��ˌ�
    float3 specular = pow(saturate(dot(reflect, lightData.eyedir)), lightData.shininess) * material.specular;
    return diffuse * lightData.texcolor + specular * lightData.specularMaskVal;
}

float3 LightGroup::ComputeDirLight(LightData lightData, Material material)
{
    float3 sumColor;
    for (int i = 0; i < DIRLIGHT_NUM; i++)
    {
        DirLight dirLight = dirLights[i];
        if (!dirLight.active)
        {
            continue;
        }
		// �S�ĉ��Z����
        sumColor += ComputeDiffuseSpecular(dirLight.lightv, lightData, material) * dirLight.lightcolor;
    }
    return sumColor;
}

float3 LightGroup::ComputePointLight(LightData lightData, Material material)
{
    float3 sumColor;
    // �_����
    for (int i = 0; i < POINTLIGHT_NUM; i++)
    {
        PointLight pointLight = pointLights[i];
        if (!pointLight.active)
        {
            continue;
        }
		// ���C�g�ւ̃x�N�g��
        float3 lightv = pointLight.lightpos - lightData.worldpos;
		// �x�N�g���̒���
        float d = length(lightv);
		// ���K�����A�P�ʃx�N�g���ɂ���
        lightv = normalize(lightv);
		// ���������W��
        float atten = 1.0f / (pointLight.lightatten.x + pointLight.lightatten.y * d + pointLight.lightatten.z * d * d);
		// �S�ĉ��Z����
        sumColor += atten * ComputeDiffuseSpecular(lightv, lightData, material) * pointLight.lightcolor;
    }
    return sumColor;
}

float3 LightGroup::ComputeSpotLight(LightData lightData, Material material)
{
    float3 sumColor;
    for (int i = 0; i < SPOTLIGHT_NUM; i++)
    {
        SpotLight spotLight = spotLights[i];
        if (!spotLight.active)
        {
            continue;
        }
		// ���C�g�ւ̕����x�N�g��
        float3 lightv = spotLight.lightpos - lightData.worldpos;
        float d = length(lightv);
        lightv = normalize(lightv);
		// ���������W��
        float atten = saturate(1.0f / (spotLight.lightatten.x + spotLight.lightatten.y * d + spotLight.lightatten.z * d * d));
		// �p�x����
        float cos = dot(lightv, spotLight.lightv);
		// �����J�n�p�x����A�����I���p�x�ɂ����Č���
		// �����J�n�p�x�̓�����1�{�A�����I���p�x�̊O����0�{�̋P�x
        float angleatten = smoothstep(spotLight.lightfactoranglecos.y, spotLight.lightfactoranglecos.x, cos);
		// �p�x��������Z
        atten *= angleatten;
		// �S�ĉ��Z����
        sumColor += atten * ComputeDiffuseSpecular(lightv, lightData, material) * spotLight.lightcolor;
    }
    return sumColor;
}

float3 LightGroup::ComputeCircleShadow(float3 worldpos, Material material)
{
    float3 sumColor = float3(0, 0, 0);
    for (int i = 0; i < CIRCLESHADOW_NUM; i++)
    {
        CircleShadow circleShadow = circleShadows[i];
        if (!circleShadow.active)
        {
            continue;
        }
		// �I�u�W�F�N�g�\�ʂ���L���X�^�[�ւ̃x�N�g��
        float3 casterv = circleShadow.casterPos - worldpos;
		// ���e�����ł̋���
        float d = dot(casterv, circleShadow.dir);
		// ���������W��
        float atten = saturate(1.0f / (circleShadow.atten.x + circleShadow.atten.y * d + circleShadow.atten.z * d * d));
		// �������}�C�i�X�Ȃ�0�ɂ���
        atten *= step(0, d);
		// ���z���C�g�̍��W
        float3 lightpos = circleShadow.casterPos + circleShadow.dir * circleShadow.distanceCasterLight;
		// �I�u�W�F�N�g�\�ʂ��烉�C�g�ւ̃x�N�g��(�P�ʃx�N�g��)
        float3 lightv = normalize(lightpos - worldpos);
		// �p�x����
        float cos = dot(lightv, circleShadow.dir);
		// �����J�n�p�x����A�����I���p�x�ɂ����Č���
		// �����J�n�p�x�̓�����1�{�A�����I���p�x�̊O����0�{�̋P�x
        float angleatten = smoothstep(circleShadow.factorAngleCos.y, circleShadow.factorAngleCos.x, cos);
		// �p�x��������Z
        atten *= angleatten;
		// �S�Č��Z����
        sumColor -= atten;
    }
    return sumColor;
}

// ���C�g�v�Z
float3 LightGroup::ComputeLightEffect(LightData lightData, Material material)
{
	// ���s����
    float3 sumColor = ComputeDirLight(lightData, material);
    // �_����
    sumColor += ComputePointLight(lightData, material);
	// �X�|�b�g���C�g
    sumColor += ComputeSpotLight(lightData, material);
	// �ۉe
    sumColor += ComputeCircleShadow(lightData.worldpos, material);
    return sumColor;
}