#ifndef _DEMO__DX_CSCENEMANAGER_H_
#define _DEMO__DX_CSCENEMANAGER_H_

#include <list>
using std::list;

#include "MSDefines.h"
using gen::TUInt32;

#include "CTemplate.h"
#include "CModel.h"

#include "CRender.h"

namespace DX {

	class CSceneManager
	{

	public:

		// Basic Constructor.
		CSceneManager();

		// Basic Destructor.
		~CSceneManager();

		//==========================================================================================
		// Scene Control
		//==========================================================================================

		// Creates a new model. Returns the UID of the model. Requires the UID of the template to use.
		TUInt32 CreateModel(TUInt32 templateID);

		// Creates a new model template. The UID of the template is returned.
		TUInt32 CreateTemplate(const char* meshFileName, bool tangents=false);

		// Creates a new render device. The SceneManager can only have 1 render device at a time.
		bool CreateRenderDevice();

		// Destroys the render device.
		void DeleteDevice();

		// Renders the scene.
		void Render();

		// Deletes a template in the scene. The ID must be passed.
		void DeleteTemplate(TUInt32 templateID);

		// Deletes all templates in the scene.
		void DeleteAllTemplates();

		// Deletes a model in the scene.
		void DeleteModel(TUInt32 modelID);

		// Deletes all models in the scene.
		void DeleteAllModels();

		//==========================================================================================
		// Model Control
		//==========================================================================================

		// Moves a model in the local X direction by the specified amount.
		void MoveLocalX(float amount, TUInt32 modelID);

		// Moves a model in the local X direction by the specified amount.
		void MoveLocalY(float amount, TUInt32 modelID);

		// Moves a model in the local X direction by the specified amount.
		void MoveLocalZ(float amount, TUInt32 modelID);



		// Moves a model in the world X direction by the specified amount.
		void MoveWorldX(float amount, TUInt32 modelID);

		// Moves a model in the world X direction by the specified amount.
		void MoveWorldY(float amount, TUInt32 modelID);

		// Moves a model in the world X direction by the specified amount.
		void MoveWorldZ(float amount, TUInt32 modelID);



		// Rotates a model in the local X direction by the specified amount.
		void RotateX(float amount, TUInt32 modelID);

		// Rotates a model in the local X direction by the specified amount.
		void RotateY(float amount, TUInt32 modelID);

		// Rotates a model in the local X direction by the specified amount.
		void RotateZ(float amount, TUInt32 modelID);


		// Returns the X position of a model.
		float GetX(TUInt32 modelID);

		// Returns the X position of a model.
		float GetY(TUInt32 modelID);

		// Returns the X position of a model.
		float GetZ(TUInt32 modelID);

	private:

		list<CTemplate*>	m_TemplateList;
		list<CModel*>		m_ModelList;

		CRender*	m_pRender;
		void*		m_pRenderDevice;

	};

}// namespace DX

#endif// _DEMO__DX_CSCENEMANAGER_H_
