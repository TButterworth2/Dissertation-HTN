
#include "CRender.h"

#include <new>

namespace DX {

	// The basic contructor of the CRender class.
	// The render setup will be performed here.
	CRender::CRender(ID3D10Device* device, const char* FXFileName, const char* techniqueName)
	{
		m_SpecularPower = 0.0f;

		m_pLastTex = NULL;
		m_pAmbientColour = new D3DXCOLOR();
		m_pSpecularColour = new D3DXCOLOR();
		m_pEffect = NULL;
		m_pEffectTechnique = NULL;
		m_pLastTex = NULL;
		m_pCameraPosVar = NULL;
		m_pAmbientLightVar = NULL;
		m_pSpecularLightVar = NULL;
		m_pSpecularPowerVar = NULL;
		m_pModelTextureVar = NULL;
		m_pWorldMatrixVar = NULL;




		ID3D10Blob* pErrors = NULL;
		DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_DEBUG;

		HRESULT hr = D3DX10CreateEffectFromFile
						(
							FXFileName,
							0,
							0,
							"fx_4_1",
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
		}
		
		if ( m_pEffect->IsValid() )
		{
			m_pEffectTechnique = m_pEffect->GetTechniqueByName( techniqueName );

			//if( m_pEffectTechnique->IsValid() == false )
			//{
			//	MessageBox( 0, "Error: Failed to create technique", 0, 0 );
			//}
			//else
			//{
				m_pAmbientLightVar = m_pEffect->GetVariableByName( "AmbientLight" )->AsVector();

				m_pSpecularLightVar = m_pEffect->GetVariableByName( "SpecularLight" )->AsVector();
				m_pSpecularPowerVar = m_pEffect->GetVariableByName( "SpecularPower" )->AsScalar();

				m_pModelTextureVar = m_pEffect->GetVariableByName( "ModelTex" )->AsShaderResource();

				m_pWorldMatrixVar = m_pEffect->GetVariableByName( "WorldMatrix" )->AsMatrix();

				m_pCameraPosVar = m_pEffect->GetVariableByName( "CameraPos" )->AsVector();
			//}
		}
	}

	// Basic destructor. Checks to see if the render variables have been released.
	// If not then they will be released and cleaned up here.
	CRender::~CRender()
	{
		ReleaseResources();

		if( m_pAmbientColour )
			delete m_pAmbientColour;

		if( m_pSpecularColour )
			delete m_pSpecularColour;
	}

	void CRender::ReleaseResources()
	{
		if( m_pLastTex ) m_pLastTex->Release();	m_pLastTex = NULL;

		if( m_pEffect ) m_pEffect->Release();	m_pEffect = NULL;
	}

	// Start the render sequence.
	void CRender::RenderStart(const CVector3* cameraPos)
	{
		if( m_pAmbientColour )
			m_pAmbientLightVar->SetFloatVector( (float*)m_pAmbientColour );

		if( m_pSpecularColour )
			m_pSpecularLightVar->SetFloatVector( (float*)m_pSpecularColour );

		m_pSpecularPowerVar->SetFloat( m_SpecularPower );
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
		m_pAmbientColour->a = 0;
		m_pAmbientColour->r = fR;
		m_pAmbientColour->g = fG;
		m_pAmbientColour->b = fB;
	}

	// Sets the colour of the specular light. The old colour will be overwritten.
	void CRender::SetSpecularColour(float fR, float fG, float fB)
	{
		m_pSpecularColour->a = 0;
		m_pSpecularColour->r = fR;
		m_pSpecularColour->g = fG;
		m_pSpecularColour->b = fB;
	}

	// Sets the specular power. The old value will be overwritten.
	void CRender::SetSpecularPower(float fPower)
	{
		m_SpecularPower = fPower;
	}

	// Returns the current specular power that is to be used.
	float CRender::GetSpecularPower()
	{
		return m_SpecularPower;
	}

	// Return the colour of the ambient light in the three variables pR, pG and pB.
	void CRender::GetAmbientLight(float* pR, float* pG, float* pB)
	{
		*pR = m_pAmbientColour->r;
		*pG = m_pAmbientColour->g;
		*pB = m_pAmbientColour->b;
	}

	// Return the colour of the specular light in the three variables pR, pG and pB.
	void CRender::GetSpecularLight(float* pR, float* pG, float* pB)
	{
		*pR = m_pSpecularColour->r;
		*pG = m_pSpecularColour->g;
		*pB = m_pSpecularColour->b;
	}

	// Check if CRender is ready to be used.
	bool CRender::IsValid()
	{
		if( m_pEffect->IsValid() &&	m_pEffectTechnique->IsValid() &&	m_pAmbientLightVar->IsValid() &&	m_pSpecularLightVar->IsValid() &&
			m_pSpecularPowerVar->IsValid() &&	m_pModelTextureVar->IsValid() &&	m_pWorldMatrixVar->IsValid()	
		  )
		{
			return true;
		}

		return false;
	}

}// namespace DX
