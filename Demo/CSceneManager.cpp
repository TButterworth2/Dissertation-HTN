
#include "CSceneManager.h"

namespace DX {

	// Basic Constructor.
	CSceneManager::CSceneManager()
	{
	}

	// Basic Destructor.
	CSceneManager::~CSceneManager()
	{
	}

	//==========================================================================================
	// Scene Control
	//==========================================================================================

	// Creates a new model. Returns the UID of the model. Requires the UID of the template to use.
	TUInt32 CSceneManager::CreateModel(TUInt32 templateID)
	{
		return 0;
	}

	// Creates a new model template. The UID of the template is returned.
	TUInt32 CSceneManager::CreateTemplate(const char* meshFileName, bool tangents/*=false*/)
	{
		return 0;
	}

	// Creates a new render device. The SceneManager can only have 1 render device at a time.
	bool CSceneManager::CreateRenderDevice()
	{
		return false;
	}

	// Destroys the render device.
	void CSceneManager::DeleteDevice()
	{
	}

	// Renders the scene.
	void CSceneManager::Render()
	{
	}

	// Deletes a template in the scene. The ID must be passed.
	void CSceneManager::DeleteTemplate(TUInt32 templateID)
	{
	}

	// Deletes all templates in the scene.
	void CSceneManager::DeleteAllTemplates()
	{
	}

	// Deletes a model in the scene.
	void CSceneManager::DeleteModel(TUInt32 modelID)
	{
	}

	// Deletes all models in the scene.
	void CSceneManager::DeleteAllModels()
	{
	}

	//==========================================================================================
	// Model Control
	//==========================================================================================

	// Moves a model in the local X direction by the specified amount.
	void CSceneManager::MoveLocalX(float amount, TUInt32 modelID)
	{
	}

	// Moves a model in the local X direction by the specified amount.
	void CSceneManager::MoveLocalY(float amount, TUInt32 modelID)
	{
	}

	// Moves a model in the local X direction by the specified amount.
	void CSceneManager::MoveLocalZ(float amount, TUInt32 modelID)
	{
	}



	// Moves a model in the world X direction by the specified amount.
	void CSceneManager::MoveWorldX(float amount, TUInt32 modelID)
	{
	}

	// Moves a model in the world X direction by the specified amount.
	void CSceneManager::MoveWorldY(float amount, TUInt32 modelID)
	{
	}

	// Moves a model in the world X direction by the specified amount.
	void CSceneManager::MoveWorldZ(float amount, TUInt32 modelID)
	{
	}



	// Rotates a model in the local X direction by the specified amount.
	void CSceneManager::RotateX(float amount, TUInt32 modelID)
	{
	}

	// Rotates a model in the local X direction by the specified amount.
	void CSceneManager::RotateY(float amount, TUInt32 modelID)
	{
	}

	// Rotates a model in the local X direction by the specified amount.
	void CSceneManager::RotateZ(float amount, TUInt32 modelID)
	{
	}


	// Returns the X position of a model.
	float CSceneManager::GetX(TUInt32 modelID)
	{
		return 0.0f;
	}

	// Returns the X position of a model.
	float CSceneManager::GetY(TUInt32 modelID)
	{
		return 0.0f;
	}

	// Returns the X position of a model.
	float CSceneManager::GetZ(TUInt32 modelID)
	{
		return 0.0f;
	}

}// namespace DX
