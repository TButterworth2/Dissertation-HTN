#ifndef _DEMO__DX_CSCENEMANAGER_H_
#define _DEMO__DX_CSCENEMANAGER_H_

#include <vector>
#include <map>
using std::vector;
using std::map;	using std::pair;

#include <d3d10.h>

#include "MSDefines.h"
using gen::TUInt32;

#include "CVector4.h"
using gen::CVector4;

#include "CTemplate.h"
#include "CModel.h"

#include "CRenderDevice.h"

#include "CRender.h"

namespace Gen {

	class ISceneManager
	{

	public:
		// Basic Constructor.
		ISceneManager() {}

		// Basic Destructor.
		virtual ~ISceneManager() {};

		//==========================================================================================
		// Scene Control
		//==========================================================================================

		// Creates a new model. Returns the UID of the model. Requires the UID of the template to use.
		// The function return -1 (n_max) if there are no templates or if the given template does not exist.
		virtual TUInt32 CreateModel(TUInt32 templateID) = 0;

		// Creates a new model template. The UID of the template is returned.
		virtual TUInt32 CreateTemplate(const char* meshFileName, bool tangents=false) = 0;

		// Set/Change the texture associated with a template.
		virtual void SetTemplateTexture(const char* textureFile, TUInt32 templateID) = 0;

		// Creates a new render device. The SceneManager can only have 1 render device at a time.
		virtual bool CreateRenderDevice(HWND hWnd) = 0;

		// Destroys the render device.
		virtual void DeleteDevice() = 0;

		// Renders the scene.
		virtual void Render(const CVector4& clearColour) = 0;

		// Deletes a template in the scene. The ID must be passed.
		virtual void DeleteTemplate(TUInt32 templateID) = 0;

		// Deletes all templates in the scene.
		virtual void DeleteAllTemplates() = 0;

		// Deletes a model in the scene. Returns true if the model was deleted. Returns false if the model
		// did not exist in the scene.
		virtual bool DeleteModel(TUInt32 modelID) = 0;

		// Deletes all models in the scene.
		virtual void DeleteAllModels() = 0;

		//==========================================================================================
		// Model Control
		//==========================================================================================


		// Moves a model in the local X direction by the specified amount.
		virtual void MoveLocalX(float amount, TUInt32 modelID) = 0;

		// Moves a model in the local X direction by the specified amount.
		virtual void MoveLocalY(float amount, TUInt32 modelID) = 0;

		// Moves a model in the local X direction by the specified amount.
		virtual void MoveLocalZ(float amount, TUInt32 modelID) = 0;



		// Moves a model in the world X direction by the specified amount.
		virtual void MoveWorldX(float amount, TUInt32 modelID) = 0;

		// Moves a model in the world X direction by the specified amount.
		virtual void MoveWorldY(float amount, TUInt32 modelID) = 0;

		// Moves a model in the world X direction by the specified amount.
		virtual void MoveWorldZ(float amount, TUInt32 modelID) = 0;



		// Rotates a model in the local X direction by the specified amount.
		virtual void RotateX(float amount, TUInt32 modelID) = 0;

		// Rotates a model in the local X direction by the specified amount.
		virtual void RotateY(float amount, TUInt32 modelID) = 0;

		// Rotates a model in the local X direction by the specified amount.
		virtual void RotateZ(float amount, TUInt32 modelID) = 0;


		// Returns the X position of a model.
		virtual float GetX(TUInt32 modelID) = 0;

		// Returns the X position of a model.
		virtual float GetY(TUInt32 modelID) = 0;

		// Returns the X position of a model.
		virtual float GetZ(TUInt32 modelID) = 0;
	};

	ISceneManager* CreateSceneManager();

}// namespace gen

namespace DX {

	class CSceneManager : public Gen::ISceneManager
	{

	public:

		// Basic Constructor.
		CSceneManager();

		// Basic Destructor.
		virtual ~CSceneManager();

		//==========================================================================================
		// Scene Control
		//==========================================================================================

		// Creates a new model. Returns the UID of the model. Requires the UID of the template to use.
		// The function return -1 (n_max) if there are no templates or if the given template does not exist.
		virtual TUInt32 CreateModel(TUInt32 templateID);

		// Creates a new model template. The UID of the template is returned.
		virtual TUInt32 CreateTemplate(const char* meshFileName, bool tangents=false);

		// Set/Change the texture associated with a template.
		virtual void SetTemplateTexture(const char* textureFile, TUInt32 templateID);

		// Creates a new render device. The SceneManager can only have 1 render device at a time.
		virtual bool CreateRenderDevice(HWND hWnd);

		// Destroys the render device.
		virtual void DeleteDevice();

		// Renders the scene.
		virtual void Render(const CVector4& clearColour);

		// Deletes a template in the scene. The ID must be passed.
		virtual void DeleteTemplate(TUInt32 templateID);

		// Deletes all templates in the scene.
		virtual void DeleteAllTemplates();

		// Deletes a model in the scene. Returns true if the model was deleted. Returns false if the model
		// did not exist in the scene.
		virtual bool DeleteModel(TUInt32 modelID);

		// Deletes all models in the scene.
		virtual void DeleteAllModels();

		//==========================================================================================
		// Model Control
		//==========================================================================================


		// Moves a model in the local X direction by the specified amount.
		virtual void MoveLocalX(float amount, TUInt32 modelID);

		// Moves a model in the local X direction by the specified amount.
		virtual void MoveLocalY(float amount, TUInt32 modelID);

		// Moves a model in the local X direction by the specified amount.
		virtual void MoveLocalZ(float amount, TUInt32 modelID);



		// Moves a model in the world X direction by the specified amount.
		virtual void MoveWorldX(float amount, TUInt32 modelID);

		// Moves a model in the world X direction by the specified amount.
		virtual void MoveWorldY(float amount, TUInt32 modelID);

		// Moves a model in the world X direction by the specified amount.
		virtual void MoveWorldZ(float amount, TUInt32 modelID);



		// Rotates a model in the local X direction by the specified amount.
		virtual void RotateX(float amount, TUInt32 modelID);

		// Rotates a model in the local X direction by the specified amount.
		virtual void RotateY(float amount, TUInt32 modelID);

		// Rotates a model in the local X direction by the specified amount.
		virtual void RotateZ(float amount, TUInt32 modelID);


		// Returns the X position of a model.
		virtual float GetX(TUInt32 modelID);

		// Returns the X position of a model.
		virtual float GetY(TUInt32 modelID);

		// Returns the X position of a model.
		virtual float GetZ(TUInt32 modelID);

	private:

		vector<CTemplate*>		m_TemplateList;
		map<TUInt32, TUInt32>	m_ModelList;// Maps the ModelUID with the TemplateUID. Used to make Model Controls more efficient.

		CRender*		m_pRender;
		CRenderDevice*	m_pRenderDevice;

		TUInt32 m_NumTemplates;
		TUInt32 m_NumModels;

	};

}// namespace DX

#endif// _DEMO__DX_CSCENEMANAGER_H_
