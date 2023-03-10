// Description: Simple shader that does transform.

cbuffer TransformBuffer : register(b0)
{
	matrix world;
	matrix wvp;
	float3 viewPosition;
	float displacementWeight;
}

cbuffer LightBuffer : register(b1)
{
	float3 lightDirection;
	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
}

cbuffer SettingsBuffer : register(b2)
{
    int useDisplacementMap = 1;
    int useSpecularMap = 1;
    int useDiffuseMap = 1;
    int useNormalMap = 1;
}

Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);
Texture2D displacementMap : register(t2);
Texture2D specularMap : register(t3);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float3 worldNormal : NORMAL;
	float3 worldTangent : TANGENT;
	float3 dirToLight : TEXCOORD0;
	float3 dirToView : TEXCOORD1;
	float2 texCoord : TEXCOORD2;
};

static matrix Identity =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	matrix toWorld = world;
	matrix toNDC = wvp;
	
    float3 localPosition = input.position;
	
	if(useDisplacementMap)
	{
		float displacementColor = displacementMap.SampleLevel(textureSampler, input.texCoord, 0.0f).r;
		localPosition += (input.normal * displacementColor * displacementWeight);		
    }

    output.position = mul(float4(localPosition, 1.0f), toNDC);
	output.worldNormal = mul(input.normal, (float3x3)toWorld);
	output.worldTangent = mul(input.tangent, (float3x3)toWorld);
	output.dirToLight = -lightDirection;
    output.dirToView = normalize(viewPosition - mul(float4(localPosition, 1.0f), world).xyz);
	output.texCoord = input.texCoord;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 n = normalize(input.worldNormal);
	
	if(useNormalMap)
    {
        float3 t = normalize(input.worldTangent);
        float3 b = normalize(cross(n, t));
        float tbnw = float3x3(t, b, n);
        float4 normalMapColor = normalMap.Sample(textureSampler, input.texCoord);
        float3 unpackedNormalMap = normalize(float3((normalMapColor.xy * 2.0f) - 1.0f, normalMapColor.z));
        n = mul(unpackedNormalMap, tbnw);
    }
    float3 light = normalize(input.dirToLight);
    float3 view = normalize(input.dirToView);
	
    float4 ambient = lightAmbient;
	
    float d = saturate(dot(light, n));
    float4 diffuse = d * lightDiffuse;
	
    float3 r = reflect(-light, n);
    float base = saturate(dot(r, view));
    float s = pow(base, 12.0f);
    float4 specular = s * lightSpecular;
	
	float4 diffuseMapColor = (useDiffuseMap)?  diffuseMap.Sample(textureSampler, input.texCoord) : 1.0f;
    float4 specularMapColor = (useSpecularMap)?  specularMap.Sample(textureSampler, input.texCoord).r : 1.0f;
	
    float4 finalColor = (ambient + diffuse) * diffuseMapColor + (specular * specularMapColor);

    return finalColor;
}