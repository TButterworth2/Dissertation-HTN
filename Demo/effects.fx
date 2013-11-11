
struct VS_STANDARD_INPUT
{
	float3 Pos		: POSITION;
	float3 Normal	: NORMAL;
	float2 UV		: TEXCOORD;
};

struct PS_BASIC_INPUT
{
	float4 ProjPos	: POSITION;
	float2 UV		: TEXCOORD0;
};

struct PS_LIGHTING_INPUT
{
	float4 ProjPos		: SV_POSITION;
	float3 WorldPos		: POSITION;
	float3 WorldNormal	: NORMAL;
	float2 UV			: TEXCOORD0;
};



SamplerState TrilinearWrap
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

RasterizerState CullNone
{
	CullMode = None;
};
RasterizerState CullBack
{
	CullMode = Back;
};

BlendState AdditiveBlending
{
	BlendEnable[0] = TRUE;
	SrcBlend = ONE;
	DestBlend = ONE;
	BlendOp = ADD;
};
BlendState MultiplicativeBlending
{
	BlendEnable[0] = TRUE;
	SrcBlend = DEST_COLOR;
	DestBlend = ZERO;
	BlendOp = ADD;
};

DepthStencilState DepthWritesOn
{
	DepthWriteMask = ALL;
};
DepthStencilState DepthWritesOff
{
	DepthWriteMask = ZERO;
};


float4x4	ViewProjMatrix;
float3		CameraPos;

float3	LightPos;
float3	LightColour;
float3	AmbientLight;
float3	SpecularLight;
float	SpecularPower;

Texture2D	ModelTexture;
float4x4	WorldMatrix;

PS_BASIC_INPUT VSBasicVertex(VS_STANDARD_INPUT vIn)
{
	PS_BASIC_INPUT vOut;

	vOut.ProjPos = float4(0.0f, 0.0f, 0.0f, 0.0f);
	vOut.UV = vIn.UV;

	return vOut;
}

PS_LIGHTING_INPUT VSPixelLit(VS_STANDARD_INPUT vIn)
{
	PS_LIGHTING_INPUT vOut;

	float4 worldPos = mul( float4(vIn.Pos, 1.0f), WorldMatrix );
	vOut.WorldPos = worldPos.xyz;

	vOut.ProjPos = mul( worldPos, ViewProjMatrix );

	vOut.WorldNormal = mul( float4( vIn.Normal, 0.0f ), WorldMatrix ).xyz;

	vOut.UV = vIn.UV;

	return vOut;
}

float4 PSBasicPixel(PS_BASIC_INPUT pIn) : SV_Target
{
	return float4( 1.0f, 1.0f, 1.0f, 1.0f );
}

float4 PSPixelLit(PS_LIGHTING_INPUT pIn) : SV_Target
{
	float4 diffuseMaterial = ModelTexture.Sample( TrilinearWrap, pIn.UV );

	float3 worldNormal = normalize( pIn.WorldNormal );

	float3 cameraDir = normalize( CameraPos - pIn.WorldPos.xyz );

	float3 lightDir = normalize( LightPos - pIn.WorldPos.xyz );
	float3 lightDist = length( LightPos - pIn.WorldPos.xyz );
	float3 diffuseLight = LightColour * max( dot( worldNormal.xyz, lightDir ), 0 ) / lightDist;
	float3 halfway = normalize( lightDir + cameraDir );
	float3 specularLight = diffuseLight * pow( max( dot( worldNormal.xyz, halfway ), 0 ), SpecularPower );

	float3 specularMaterial = 1.0f;

	float4 combinedColour;
	combinedColour.rgb =  diffuseMaterial.rgb * diffuseLight + specularMaterial * specularLight;
	combinedColour.a = 1.0f;

	return combinedColour;
}

technique10 BasicRender
{
	pass p0
	{
		SetVertexShader( CompileShader( vs_4_1, VSBasicVertex() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_1, PSBasicPixel() ) );

		SetRasterizerState( CullNone );
		SetBlendState( AdditiveBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		SetDepthStencilState( DepthWritesOn, 0 );
	}
}

technique11 PixelLighting
{
	pass p0
	{
		SetVertexShader( CompileShader( vs_4_1, VSBasicVertex() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_1, PSBasicPixel() ) );

		SetRasterizerState( CullNone );
		SetBlendState( AdditiveBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		SetDepthStencilState( DepthWritesOn, 0 );
	}
}
