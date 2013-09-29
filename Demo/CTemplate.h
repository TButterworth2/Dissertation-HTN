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

namespace DX {

	// This class will act as the template for the models to be made from.
	class CTemplate
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
		CModel* GetModelByLocation(TUInt32 modelNumber);

		// Returns the number of models currently associated with this template.
		TUInt32 ModelCount();

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

	};

}// namespace DX

#endif// _DEMO__DX_CTEMPLATE_H_
