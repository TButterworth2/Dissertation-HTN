
#include "CSceneManager.h"

#include <D3DX10.h>

namespace Scene {

	ISceneManager* CreateSceneManager()
	{
		return new DX::CSceneManager();
	}

}// namespace Scene

namespace DX {

	// Basic Constructor.
	CSceneManager::CSceneManager()
	{
		m_pRender = NULL;
		m_pRenderDevice = new CRenderDevice();

		m_NumTemplates = 0;
		m_NumModels = 0;

		m_ClearColour = CVector4( 0.0f, 0.0f, 0.0f, 0.0f );

		// Insert Placeholders for the future implementation of the model + template creation.
		CTemplate* baseTemplate = new CTemplate( m_NumTemplates++ );
		CModel* baseModel = new CModel( m_NumModels, baseTemplate->GetUID() );
		m_TemplateList.push_back( baseTemplate );
		m_ModelList.insert( pair< TUInt32, TUInt32 >( m_NumModels++, baseTemplate->GetUID() ) );
	}

	// Basic Destructor.
	CSceneManager::~CSceneManager()
	{
		DeleteAllTemplates();

		m_pRender->ReleaseResources();
		m_pRenderDevice->DeleteDevice();

		delete m_pRender;
		delete m_pRenderDevice;
	}

	//==========================================================================================
	// Scene Control
	//==========================================================================================

	// Creates a new model. Returns the UID of the model. Requires the UID of the template to use.
	TUInt32 CSceneManager::CreateModel(TUInt32 templateID)
	{
		if( m_TemplateList.empty() || m_TemplateList.size() <= templateID )
		{
			return -1;
		}

		m_TemplateList[templateID]->CreateModel( m_NumModels );

		m_ModelList.insert( pair<TUInt32, TUInt32>( m_NumModels, templateID ) );

		return m_NumModels++;
	}

	// Creates a new model template. The UID of the template is returned.
	TUInt32 CSceneManager::CreateTemplate(const char* meshFileName, bool tangents/*=false*/)
	{
		CTemplate* temp = new CTemplate( m_NumTemplates );

		temp->Load( m_pRenderDevice->GetDevice(), m_pRender->GetTechnique(), meshFileName, tangents );

		m_TemplateList.push_back( temp );

		return m_NumTemplates++;
	}

	// Creates a new render device. The SceneManager can only have 1 render device at a time.
	bool CSceneManager::CreateRenderDevice(HWND hWnd, const char* FXFile, const char* techniqueName)
	{
		if( m_pRenderDevice->SetupDevice( hWnd ) )
		{
			m_pRender = new CRender( m_pRenderDevice->GetDevice(), FXFile, techniqueName );

			return m_pRender->IsValid();
		}


		return false;
	}

	// Destroys the render device.
	void CSceneManager::DeleteDevice()
	{
		m_pRenderDevice->DeleteDevice();
	}

	// Renders the scene.
	void CSceneManager::Render()
	{
		m_pRenderDevice->ClearScreen( m_ClearColour );

		CVector3 camPos = m_pCamera->GetPosition();

		m_pRender->RenderStart( &camPos );// place holder only.

		CTemplate* temp = 0;
		for(TUInt32 i = 0; i < m_TemplateList.size(); i++)
		{
			temp = m_TemplateList[i];

			temp->Render( m_pRenderDevice->GetDevice() );

			ID3D10ShaderResourceView* tex = temp->GetTexture();

			for(TUInt32 model=0; model < temp->ModelCount(); model++)
			{
				CModel* current = temp->GetModelByIndex( model );
				m_pRender->RenderModel( current->GetWorldMatrix(), tex );

				m_pRenderDevice->DrawIndexed( temp->IndexCount() );
			}
		}


		m_pRenderDevice->Present();
	}

	// Deletes a template in the scene. The ID must be passed.
	void CSceneManager::DeleteTemplate(TUInt32 templateID)
	{
		vector<CTemplate*>::iterator P;
		P = m_TemplateList.begin();

		while( P != m_TemplateList.end() )
		{
			if( (*P)->GetUID() == templateID )
			{
				P = m_TemplateList.erase( P );
				return;
			}

			P++;
		}
	}

	// Deletes all templates in the scene. WARNING: This will deleta all models as well.
	void CSceneManager::DeleteAllTemplates()
	{
		vector<CTemplate*>::iterator P;
		P = m_TemplateList.begin();

		while( P != m_TemplateList.end() )
		{
			(*P)->DeleteAllModels();

			delete (*P);

			P = m_TemplateList.erase( P );
		}
	}

	// Deletes a model in the scene. Returns true if the model was deleted. Returns false if the model
	// did not exist in the scene.
	bool CSceneManager::DeleteModel(TUInt32 modelID)
	{
		TUInt32 templateID = m_ModelList.at( modelID );

		return m_TemplateList[templateID]->DeleteModel( modelID );
	}

	// Deletes all models in the scene.
	void CSceneManager::DeleteAllModels()
	{
		for(TUInt32 templateID=0; templateID < m_TemplateList.size(); templateID++)
		{
			CTemplate* temp = m_TemplateList[templateID];

			temp->DeleteAllModels();
		}
	}

	// Set the colour for the screen to clear to.
	void CSceneManager::SetClearColour(float fR, float fG, float fB, float fA)
	{
		m_ClearColour.Set( fR, fG, fB, fA );
	}

	// Set the colour of the ambient light in the scene.
	void CSceneManager::SetAmbientColour(float fR, float fG, float fB)
	{
		m_pRender->SetAmbientLight( fR, fG, fB );
	}

	// Set the colour of the specular light to be used in rendering.
	void CSceneManager::SetSpecularColour(float fR, float fG, float fB)
	{
		m_pRender->SetSpecularColour( fR, fG, fB );
	}

	Scene::IRTSCamera* CSceneManager::CreateCamera(float fX/*=0.0f*/, float fY/*=0.0f*/, float fZ/*=0.0f*/)
	{
		m_pCamera = new CRTSCamera( CVector3( 0.0f, 1.0f, 0.0f ), (-1), (-1), fX, fY, fZ );

		return m_pCamera;
	}

	void CSceneManager::DeleteCamera()
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	Scene::ILight* CSceneManager::CreateLight()
	{
//		Scene::ILight* light = new CLight();
//		m_LightList.push_back( light );

//		return light;
		return 0;
	}

	void CSceneManager::DeleteLight(Scene::ILight* light)
	{
	}

	//==========================================================================================
	// Model Control
	//==========================================================================================

	// Load a texture and associate it with a template.
	bool CSceneManager::SetTexture(const char* texFileName, TUInt32 templateID)
	{
		if( templateID < m_TemplateList.size() )
		{
			return m_TemplateList[templateID]->SetTexture( m_pRenderDevice->GetDevice(), texFileName );
		}

		return false;
	}

	// Moves a model in the local X direction by the specified amount.
	void CSceneManager::MoveLocalX(float amount, TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		m_TemplateList[temp]->GetModelByUID( modelID )->MoveLocalX( amount );
	}

	// Moves a model in the local X direction by the specified amount.
	void CSceneManager::MoveLocalY(float amount, TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		m_TemplateList[temp]->GetModelByUID( modelID )->MoveLocalY( amount );
	}

	// Moves a model in the local X direction by the specified amount.
	void CSceneManager::MoveLocalZ(float amount, TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		m_TemplateList[temp]->GetModelByUID( modelID )->MoveLocalZ( amount );
	}



	// Moves a model in the world X direction by the specified amount.
	void CSceneManager::MoveWorldX(float amount, TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		m_TemplateList[temp]->GetModelByUID( modelID )->MoveX( amount );
	}

	// Moves a model in the world X direction by the specified amount.
	void CSceneManager::MoveWorldY(float amount, TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		m_TemplateList[temp]->GetModelByUID( modelID )->MoveY( amount );
	}

	// Moves a model in the world X direction by the specified amount.
	void CSceneManager::MoveWorldZ(float amount, TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		m_TemplateList[temp]->GetModelByUID( modelID )->MoveZ( amount );
	}



	// Rotates a model in the local X direction by the specified amount.
	void CSceneManager::RotateX(float amount, TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		m_TemplateList[temp]->GetModelByUID( modelID )->RotateX( amount );
	}

	// Rotates a model in the local X direction by the specified amount.
	void CSceneManager::RotateY(float amount, TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		m_TemplateList[temp]->GetModelByUID( modelID )->RotateY( amount );
	}

	// Rotates a model in the local X direction by the specified amount.
	void CSceneManager::RotateZ(float amount, TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		m_TemplateList[temp]->GetModelByUID( modelID )->RotateZ( amount );
	}


	// Returns the X position of a model.
	float CSceneManager::GetX(TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		return m_TemplateList[temp]->GetModelByUID( modelID )->GetX();
	}

	// Returns the X position of a model.
	float CSceneManager::GetY(TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		return m_TemplateList[temp]->GetModelByUID( modelID )->GetY();
	}

	// Returns the X position of a model.
	float CSceneManager::GetZ(TUInt32 modelID)
	{
		TUInt32 temp = m_ModelList.at( modelID );

		return m_TemplateList[temp]->GetModelByUID( modelID )->GetZ();
	}

}// namespace DX
