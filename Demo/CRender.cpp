
#include "CRender.h"

namespace DX {

	// The basic contructor of the CRender class.
	// The render setup will be performed here.
	CRender::CRender(ID3D10Device* device, const char* FXFileName, const char* techniqueName)
	{
		m_pLastTex = 0;

		ID3D10Blob* pErrors;
		DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG;

		HRESULT hr = D3DX10CreateEffectFromFile
						(
							FXFileName,
							0,
							0,
							"fx_4_0",
							shaderFlags,
							0,
							device,
							0,
							0,
							&m_pEffect,
							&pErrors,
							0
						);

		if( FAILED( hr ) )
		{
			if( pErrors )
			{
				MessageBoxA( 0, (char*)pErrors->GetBufferPointer(), 0, 0 );
			}
			else
			{
				MessageBoxA( NULL, "Failed to create effect from file", "Error", NULL );
			}

			pErrors->Release();
		}

		if( m_pEffect->IsValid() )
		{
			m_pEffectTechnique = m_pEffect->GetTechniqueByName( techniqueName );

			if( m_pEffectTechnique->IsValid() == false )
			{
				MessageBox( 0, "Error: Failed to create technique", 0, 0 );
			}
		}

		m_pAmbientLightVar = m_pEffect->GetVariableByName( "AmbientLight" )->AsVector();

		m_pSpecularLightVar = m_pEffect->GetVariableByName( "AmbientLight" )->AsVector();
		m_pSpecularPowerVar = m_pEffect->GetVariableByName( "AmbientLight" )->AsScalar();

		m_pModelTextureVar = m_pEffect->GetVariableByName( "AmbientLight" )->AsShaderResource();

		m_pWorldMatrixVar = m_pEffect->GetVariableByName( "AmbientLight" )->AsMatrix();
	}

	// Basic destructor. Checks to see if the render variables have been released.
	// If not then they will be released and cleaned up here.
	CRender::~CRender()
	{
	}

	// Start the render sequence.
	void CRender::RenderStart()
	{
	}

	// This is the main render function. Only one model can be rendered at a time. The world matrix of the model to be
	// rendered is required as a parameter. Also the texture ID needs to be passed in for the model.
	void CRender::RenderModel(const CMatrix4x4* worldMatrix, ID3D10ShaderResourceView* texture)
	{
		m_pWorldMatrixVar->SetMatrix( D3DXMATRIX( &worldMatrix->e00 ) );

		m_pModelTextureVar->SetRawValue( texture, 0, 1 );
	}



	// Sets the colour of the ambient light. The old colour will be overwritten.
	void CRender::SetAmbientLight(float fR, float fG, float fB)
	{
	}

	// Sets the colour of the specular light. The old colour will be overwritten.
	void CRender::SetSpecularColour(float fR, float fG, float fB)
	{
	}

	// Sets the specular power. The old value will be overwritten.
	void CRender::SetSpecularPower(float fPower)
	{
	}

	// Returns the current specular power that is to be used.
	float CRender::GetSpecularPower()
	{
		return 0.0f;
	}

	// Return the colour of the ambient light in the three variables pR, pG and pB.
	void CRender::GetAmbientLight(float* pR, float* pG, float* pB)
	{
	}

	// Return the colour of the specular light in the three variables pR, pG and pB.
	void CRender::GetSpecularLight(float* pR, float* pG, float* pB)
	{
	}

}// namespace DX
