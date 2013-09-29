
#include "CSceneManager.h"

#include <D3DX10.h>

namespace DX {

	// Basic Constructor.
	CSceneManager::CSceneManager()
	{
		//m_pRender = new CRender();
		m_pRenderDevice = new CRenderDevice();

		m_NumTemplates = 0;
		m_NumModels = 0;
	}

	// Basic Destructor.
	CSceneManager::~CSceneManager()
	{
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
	bool CSceneManager::CreateRenderDevice(HWND hWnd)
	{
		return m_pRenderDevice->SetupDevice( hWnd );
	}

	// Destroys the render device.
	void CSceneManager::DeleteDevice()
	{
		m_pRenderDevice->DeleteDevice();
	}

	// Renders the scene.
	void CSceneManager::Render(const CVector4& clearColour)
	{
		m_pRenderDevice->ClearScreen( clearColour );

		m_pRender->RenderStart();

		CTemplate* temp = 0;
		for(TUInt32 i = 0; i < m_TemplateList.size(); i++)
		{
			temp = m_TemplateList[i];

			temp->Render( m_pRenderDevice->GetDevice() );

			for(TUInt32 model=0; model < temp->ModelCount(); model++)
			{
				CModel* current = temp->GetModelByLocation( model );
				m_pRender->RenderModel( current->GetWorldMatrix(), m_TextureList[current->GetTextureID()] );
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

	//==========================================================================================
	// Model Control
	//==========================================================================================

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
