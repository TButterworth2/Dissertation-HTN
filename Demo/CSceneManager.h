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

#include "CRTSCamera.h"

#include "CLight.h"

namespace Scene {

	class ISceneManager
	{

	public:

		// Basic Constructor.
		ISceneManager() {}

		// Basic Destructor.
		virtual ~ISceneManager() {}

		//==========================================================================================
		// Scene Control
		//==========================================================================================

		// Creates a new model. Returns the UID of the model. Requires the UID of the template to use.
		// The function return -1 (n_max) if there are no templates or if the given template does not exist.
		virtual TUInt32 CreateModel(TUInt32 templateID) = 0;

		// Creates a new model template. The UID of the template is returned.
		virtual TUInt32 CreateTemplate(const char* meshFileName, bool tangents=false) = 0;

		// Creates a new render device. The SceneManager can only have 1 render device at a time.
		virtual bool CreateRenderDevice(HWND hWnd, const char* FXFile, const char* techniqueName) = 0;

		// Destroys the render device.
		virtual void DeleteDevice() = 0;

		// Renders the scene.
		virtual void Render() = 0;

		// Deletes a template in the scene. The ID must be passed.
		virtual void DeleteTemplate(TUInt32 templateID) = 0;

		// Deletes all templates in the scene.
		virtual void DeleteAllTemplates() = 0;

		// Deletes a model in the scene. Returns true if the model was deleted. Returns false if the model
		// did not exist in the scene.
		virtual bool DeleteModel(TUInt32 modelID) = 0;

		// Deletes all models in the scene.
		virtual void DeleteAllModels() = 0;

		// Set the colour for the screen to clear to.
		virtual void SetClearColour(float fR, float fG, float fB, float fA) = 0;

		// Set the colour of the ambient light in the scene.
		virtual void SetAmbientColour(float fR, float fG, float fB) = 0;

		// Set the colour of the specular light to be used in rendering.
		virtual void SetSpecularColour(float fR, float fG, float fB) = 0;

		virtual IRTSCamera* CreateCamera(float fX=0.0f, float fY=0.0f, float fZ=0.0f) = 0;

		virtual void DeleteCamera() = 0;

		virtual ILight* CreateLight() = 0;
		virtual void DeleteLight(ILight* light) = 0;

		//==========================================================================================
		// Model Control
		//==========================================================================================

		// Load a texture and associate it with a model.
		virtual bool SetTexture(const char* texFileName, TUInt32 modelID) = 0;


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

}// namespace Scene

namespace DX {

	class CSceneManager : public Scene::ISceneManager
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
		bool CreateRenderDevice(HWND hWnd, const char* FXFile, const char* techniqueName);

		// Destroys the render device.
		void DeleteDevice();

		// Renders the scene.
		void Render();

		// Deletes a template in the scene. The ID must be passed.
		void DeleteTemplate(TUInt32 templateID);

		// Deletes all templates in the scene.
		void DeleteAllTemplates();

		// Deletes a model in the scene. Returns true if the model was deleted. Returns false if the model
		// did not exist in the scene.
		bool DeleteModel(TUInt32 modelID);

		// Deletes all models in the scene.
		void DeleteAllModels();

		// Set the colour for the screen to clear to.
		void SetClearColour(float fR, float fG, float fB, float fA);

		// Set the colour of the ambient light in the scene.
		void SetAmbientColour(float fR, float fG, float fB);

		// Set the colour of the specular light to be used in rendering.
		void SetSpecularColour(float fR, float fG, float fB);
		
		
		virtual Scene::IRTSCamera* CreateCamera(float fX=0.0f, float fY=0.0f, float fZ=0.0f);

		virtual void DeleteCamera();


		virtual Scene::ILight* CreateLight();

		virtual void DeleteLight(Scene::ILight* light);

		//==========================================================================================
		// Model Control
		//==========================================================================================

		// Load a texture and associate it with a template.
		bool SetTexture(const char* texFileName, TUInt32 templateID);


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
//		vector<ILight*> m_LightList;

		CRender*		m_pRender;
		CRenderDevice*	m_pRenderDevice;

		TUInt32 m_NumTemplates;
		TUInt32 m_NumModels;

		CVector4	m_ClearColour;

		CRTSCamera*	m_pCamera;

	};

}// namespace DX

#endif// _DEMO__DX_CSCENEMANAGER_H_
