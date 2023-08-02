//float4 ToonShading(float4 color)
//{
//    return smoothstep(0.38f, 0.42f, color);
//}

//float RimLight(float3 eyedir, float3 normal, float3 lightcolor)
//{
//    float rim = 1.0 - saturate(dot(normalize(eyedir), normal));
//    float emission = lightcolor * pow(rim, rimpower);
//    if (rimseparate)
//    {
//        emission = step(0.3f, emission);
//    }
//    return emission;
//}

float2 randomVec(float2 fact)
{
    float2 angle = float2(
        dot(fact, float2(127.1, 311.7)),
        dot(fact, float2(269.5, 183.3))
    );
    return frac(sin(angle) * 43758.5453123) * 2 - 1;
}

// �m�C�Y�̖��x��density�Őݒ�Auv��i.uv����
float PerlinNoise(float density, float2 uv)
{
    float2 uvFloor = floor(uv * density);
    float2 uvFrac = frac(uv * density);
    float v[2][2], c[2][2];

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            // �e���_�̃����_���ȃx�N�g�����擾
            v[i][j] = randomVec(uvFloor + float2(i, j));
            // �����_���ȃx�N�g���ƒ��_�Ɍ������x�N�g���̓��ς��Ƃ��āA�e���_�̐F���쐬
            c[i][j] = dot(v[i][j], uvFrac - float2(i, j));
        }
    }

    float2 u = uvFrac * uvFrac * (3 - 2 * uvFrac);
    // �`�悷��s�N�Z������s�N�Z���F�����߂�
    float v0010 = lerp(c[0][0], c[1][0], u.x);
    float v0111 = lerp(c[0][1], c[1][1], u.x);
    return lerp(v0010, v0111, u.y) / 2 + 0.5;
}

float FractalSumNoise(float density, float2 uv)
{
    float fn;
    for (float i = 1; i < 16; i *= 2)
    {
        fn += PerlinNoise(density * i, uv) * 1.0 / (i * 2);
    }
    return fn;
}
