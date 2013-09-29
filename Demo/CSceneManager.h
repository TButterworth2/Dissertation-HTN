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
		// The function return -1 (n_max) if there are no templates or if the given template does not exist.
		TUInt32 CreateModel(TUInt32 templateID);

		// Creates a new model template. The UID of the template is returned.
		TUInt32 CreateTemplate(const char* meshFileName, bool tangents=false);

		// Creates a new render device. The SceneManager can only have 1 render device at a time.
		bool CreateRenderDevice(HWND hWnd);

		// Destroys the render device.
		void DeleteDevice();

		// Renders the scene.
		void Render(const CVector4& clearColour);

		// Deletes a template in the scene. The ID must be passed.
		void DeleteTemplate(TUInt32 templateID);

		// Deletes all templates in the scene.
		void DeleteAllTemplates();

		// Deletes a model in the scene. Returns true if the model was deleted. Returns false if the model
		// did not exist in the scene.
		bool DeleteModel(TUInt32 modelID);

		// Deletes all models in the scene.
		void DeleteAllModels();

		//==========================================================================================
		// Model Control
		//==========================================================================================

		// Load a texture and associate it with a model.
		void SetTexture(const char* texFileName, TUInt32 modelID);


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

		vector<CTemplate*>		m_TemplateList;
		map<TUInt32, TUInt32>	m_ModelList;// Maps the ModelUID with the TemplateUID. Used to make Model Controls more efficient.

		vector<ID3D10ShaderResourceView*>	m_TextureList;

		CRender*		m_pRender;
		CRenderDevice*	m_pRenderDevice;

		TUInt32 m_NumTemplates;
		TUInt32 m_NumModels;

	};

}// namespace DX

#endif// _DEMO__DX_CSCENEMANAGER_H_
