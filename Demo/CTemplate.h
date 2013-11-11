#ifndef _DEMO__DX_CTEMPLATE_H_
#define _DEMO__DX_CTEMPLATE_H_

#include <d3d10.h>

#include <vector>
#include <map>
using std::vector;
using std::map;

#include "MSDefines.h"
using gen::TUInt32;

#include "CModel.h"

namespace Scene{

	class ITemplate
	{

	public:

		// Basic Constructor.
		ITemplate(TUInt32 ID) {}

		// Basic Destructor. Will release all resources that are left including
		// the model list.
		virtual ~ITemplate() {}


		// Load the mesh (vertices and indices) of the model. The filename and
		// full path of the model file must be passed as the parameter.
		virtual bool Load(ID3D10Device* p_d3dDevice, ID3D10EffectTechnique* p_Technique, const char* meshFile, bool tangents=false) = 0;

		// Sends the necessary data to the GPU ready for the models to be drawn.
		virtual void Render(ID3D10Device* p_d3dDevice) = 0;

		// This function clears all of the data stored for the mesh.
		virtual void ReleaseResources() = 0;

		// Returns the UID of this template. Used by the SceneManager to perform
		// model creation and rendering.
		virtual TUInt32 GetUID() = 0;

		// Set the texture associate with this template. This will replace any
		// texture currently loaded.
		virtual bool SetTexture(ID3D10Device* device, const char* texFile) = 0;

		// Returns the texture associated with this template. Will return 0 if
		// none exists.
		virtual ID3D10ShaderResourceView* GetTexture() = 0;


		// Creates a new model of this template. Must provide the ID of the model.
		// Can specify a location for the model to be created at.
		virtual void CreateModel(TUInt32 modelID, float fX=0.0f, float fY=0.0f, float fZ=0.0f) = 0;

		// Removes a model from the scene. Must pass the UID of the model.
		// Returns true if the model was removed.
		virtual bool DeleteModel(TUInt32 modelID) = 0;

		// Removes all models associated with this template from the scene.
		virtual void DeleteAllModels() = 0;

		// Returns a pointer to a model with a given UID.
		virtual DX::CModel* GetModelByUID(TUInt32 modelID) = 0;

		// Returns a pointer to a model at the specified position in the model list.
		virtual DX::CModel* GetModelByIndex(TUInt32 modelIndex) = 0;

		// Returns the number of models currently associated with this template.
		virtual TUInt32 ModelCount() = 0;

		virtual TUInt32 IndexCount() = 0;
	};

}// namespace Scene

namespace DX {

	// This class will act as the template for the models to be made from.
	class CTemplate : public Scene::ITemplate
	{

	public:

		// Basic Constructor.
		CTemplate(TUInt32 ID);

		// Basic Destructor. Will release all resources that are left including
		// the model list.
		~CTemplate();


		// Load the mesh (vertices and indices) of the model. The filename and
		// full path of the model file must be passed as the parameter.
		bool Load(ID3D10Device* p_d3dDevice, ID3D10EffectTechnique* p_Technique, const char* meshFile, bool tangents=false);

		// Sends the necessary data to the GPU ready for the models to be drawn.
		void Render(ID3D10Device* p_d3dDevice);

		// This function clears all of the data stored for the mesh.
		void ReleaseResources();

		// Returns the UID of this template. Used by the SceneManager to perform
		// model creation and rendering.
		TUInt32 GetUID()
		{ return m_TemplateID; }

		// Set the texture associate with this template. This will replace any
		// texture currently loaded.
		bool SetTexture(ID3D10Device* device, const char* texFile);

		// Returns the texture associated with this template. Will return 0 if
		// none exists.
		ID3D10ShaderResourceView* GetTexture();


		// Creates a new model of this template. Must provide the ID of the model.
		// Can specify a location for the model to be created at.
		void CreateModel(TUInt32 modelID, float fX=0.0f, float fY=0.0f, float fZ=0.0f);

		// Removes a model from the scene. Must pass the UID of the model.
		// Returns true if the model was removed.
		bool DeleteModel(TUInt32 modelID);

		// Removes all models associated with this template from the scene.
		void DeleteAllModels();

		// Returns a pointer to a model with a given UID.
		CModel* GetModelByUID(TUInt32 modelID);

		// Returns a pointer to a model at the specified position in the model list.
		CModel* GetModelByIndex(TUInt32 modelIndex);

		// Returns the number of models currently associated with this template.
		TUInt32 ModelCount();

		TUInt32 IndexCount();

	private:

		// Geometry data

		// Does this model have any geometry to render
		bool                     mHasGeometry;

		// Vertex data for the model stored in a vertex buffer and the number of the vertices in the buffer
		ID3D10Buffer*            mVertexBuffer;
		unsigned int             mNumVertices;

		// Description of the elements in a single vertex (position, normal, UVs etc.)
		static const int         MAX_VERTEX_ELTS = 64;
		D3D10_INPUT_ELEMENT_DESC mVertexElts[MAX_VERTEX_ELTS];
		ID3D10InputLayout*       mVertexLayout; // Layout of a vertex (derived from above)
		unsigned int             mVertexSize;   // Size of vertex calculated from contained elements

		// Index data for the model stored in a index buffer and the number of indices in the buffer
		ID3D10Buffer*            mIndexBuffer;
		unsigned int             mNumIndices;

		TUInt32 m_TemplateID;

		vector<CModel*>			m_ModelList;

		ID3D10ShaderResourceView*	m_pTexture;

	};

}// namespace DX

#endif// _DEMO__DX_CTEMPLATE_H_
