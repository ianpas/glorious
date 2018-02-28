struct Material
{
	float4 m_Diffuse;
};

struct Light
{
	float3 m_Pos;
	float  m_Reserved0;
};

struct VSInput
{
	float3 m_Pos	: POSITION;
	float3 m_Normal	: NORMAL;
	float2 m_Tex	: TEXCOORD;

};

struct PSInput
{
	float4 m_HPos	: SV_POSITION;
	float3 m_VPos	: POSITION;
	float3 m_VNrm	: NORMAL0;
	float3 m_WNrm   : NORMAL1;
	float2 m_Tex	: TEXCOORD;

};

cbuffer cbObject:register(b0)
{
	float4x4 g_World;
	Material g_Material;
}

cbuffer cbCamera : register(b1)
{
	float3x3		g_View;
	float3			g_ViewPos;
	float			g_Reserved0;
	float4x4		g_Proj;
};

cbuffer cbLight : register(b2)
{
	Light g_Light;
}

SamplerState	    ssAni : register(s0);//Sampler State Anisotropic
Texture2D<float4>	texObjectDiffuse	: register(t0);

PSInput VSMain(VSInput vsi)
{
	float3 LPos = vsi.m_Pos;
	float3 LNrm = vsi.m_Normal;

	float3 WPos = mul(float4(LPos, 1), g_World).xyz;
	float3 WNrm = mul(float4(LNrm, 0), g_World).xyz;

	float3 VPos = mul(WPos - g_ViewPos, g_View);
	float3 VNrm = mul(WNrm, g_View);

	float4 HPos = mul(float4(VPos, 1), g_Proj);

	PSInput psi;
	psi.m_HPos = HPos;
	psi.m_VPos = VPos;
	psi.m_VNrm = VNrm;
	psi.m_WNrm = WNrm;
	psi.m_Tex = vsi.m_Tex;

	return psi;
}

float4 PSMain(PSInput psi) : SV_TARGET
{
	float3 VPos = mul(g_Light.m_Pos - g_ViewPos, g_View);

	float3 L = normalize(VPos - psi.m_VPos);
	float NdotL = saturate(dot(psi.m_VNrm, L));

	float4 diffuse = g_Material.m_Diffuse * NdotL;
	float4 ambient = 0.2f * g_Material.m_Diffuse;

	// texture is keyword?..
	float4 __texture = texObjectDiffuse.Sample(ssAni, psi.m_Tex);

	float4 color = __texture * (ambient + diffuse);

	return color;
}
