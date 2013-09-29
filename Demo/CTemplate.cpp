
#include "CImportXFile.h"
using gen::CImportXFile;

#include "CTemplate.h"

using std::pair;

namespace DX {

	// Basic Constructor.
	CTemplate::CTemplate(UINT ID)
	{
		mHasGeometry = false;

		mVertexBuffer = 0;
		mNumVertices = 0;

		mVertexLayout = 0; // Layout of a vertex (derived from above)

		mIndexBuffer = 0;
		mNumIndices = 0;

		m_TemplateID = ID;
	}

	// Basic Destructor.
	CTemplate::~CTemplate()
	{
		if( mHasGeometry )
		{
			ReleaseResources();
		}

		if( m_ModelList.empty() != true )
		{
			vector<CModel*>::iterator P;
			P = m_ModelList.begin();

			while( P != m_ModelList.end() )
			{
				delete (*P);

				P++;
			}
		}
	}


	// Load the mesh (vertices and indices) of the model. The filename and
	// full path of the model file must be passed as the parameter.
	bool CTemplate::Load(ID3D10Device* p_d3dDevice, ID3D10EffectTechnique* p_Technique, const char* meshFile, bool tangents/*=false*/)
	{
		// Release any existing geometry in this object
		if( mHasGeometry )
			ReleaseResources();

		// Use CImportXFile class (from another application) to load the given file. The import code is wrapped in the namespace 'gen'
		gen::CImportXFile mesh;
		if (mesh.ImportFile( meshFile ) != gen::kSuccess)
		{
			return false;
		}

		// Get first sub-mesh from loaded file
		gen::SSubMesh subMesh;
		if (mesh.GetSubMesh( 0, &subMesh, tangents ) != gen::kSuccess)
		{
			return false;
		}


		// Create vertex element list & layout. We need a vertex layout to say what data we have per vertex in this model (e.g. position, normal, uv, etc.)
		// In previous projects the element list was a manually typed in array as we knew what data we would provide. However, as we can load models with
		// different vertex data this time we need flexible code. The array is built up one element at a time: ask the import class if it loaded normals, 
		// if so then add a normal line to the array, then ask if it loaded UVS...etc
		unsigned int numElts = 0;
		unsigned int offset = 0;
		// Position is always required
		mVertexElts[numElts].SemanticName = "POSITION";   // Semantic in HLSL (what is this data for)
		mVertexElts[numElts].SemanticIndex = 0;           // Index to add to semantic (a count for this kind of data, when using multiple of the same type, e.g. TEXCOORD0, TEXCOORD1)
		mVertexElts[numElts].Format = DXGI_FORMAT_R32G32B32_FLOAT; // Type of data - this one will be a float3 in the shader. Most data communicated as though it were colours
		mVertexElts[numElts].AlignedByteOffset = offset;  // Offset of element from start of vertex data (e.g. if we have position (float3), uv (float2) then normal, the normal's offset is 5 floats = 5*4 = 20)
		mVertexElts[numElts].InputSlot = 0;               // For when using multiple vertex buffers (e.g. instancing - an advanced topic)
		mVertexElts[numElts].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA; // Use this value for most cases (only changed for instancing)
		mVertexElts[numElts].InstanceDataStepRate = 0;                     // --"--

		offset += 12;
		++numElts;


		// Repeat for each kind of vertex data
		if (subMesh.hasNormals)
		{
			mVertexElts[numElts].SemanticName = "NORMAL";
			mVertexElts[numElts].SemanticIndex = 0;
			mVertexElts[numElts].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			mVertexElts[numElts].AlignedByteOffset = offset;
			mVertexElts[numElts].InputSlot = 0;
			mVertexElts[numElts].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
			mVertexElts[numElts].InstanceDataStepRate = 0;

			offset += 12;
			++numElts;
		}
		if (subMesh.hasTangents)
		{
			mVertexElts[numElts].SemanticName = "TANGENT";
			mVertexElts[numElts].SemanticIndex = 0;
			mVertexElts[numElts].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			mVertexElts[numElts].AlignedByteOffset = offset;
			mVertexElts[numElts].InputSlot = 0;
			mVertexElts[numElts].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
			mVertexElts[numElts].InstanceDataStepRate = 0;

			offset += 12;
			++numElts;
		}
		if (subMesh.hasTextureCoords)
		{
			mVertexElts[numElts].SemanticName = "TEXCOORD";
			mVertexElts[numElts].SemanticIndex = 0;
			mVertexElts[numElts].Format = DXGI_FORMAT_R32G32_FLOAT;
			mVertexElts[numElts].AlignedByteOffset = offset;
			mVertexElts[numElts].InputSlot = 0;
			mVertexElts[numElts].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
			mVertexElts[numElts].InstanceDataStepRate = 0;

			offset += 8;
			++numElts;
		}
		if (subMesh.hasVertexColours)
		{
			mVertexElts[numElts].SemanticName = "COLOR";
			mVertexElts[numElts].SemanticIndex = 0;
			mVertexElts[numElts].Format = DXGI_FORMAT_R8G8B8A8_UNORM; // A RGBA colour with 1 byte (0-255) per component
			mVertexElts[numElts].AlignedByteOffset = offset;
			mVertexElts[numElts].InputSlot = 0;
			mVertexElts[numElts].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
			mVertexElts[numElts].InstanceDataStepRate = 0;

			offset += 4;
			++numElts;
		}
		mVertexSize = offset;

		// Given the vertex element list, pass it to DirectX to create a vertex layout. We also need to pass an example of a technique that will
		// render this model. We will only be able to render this model with techniques that have the same vertex input as the example we use here
		D3D10_PASS_DESC PassDesc;
		ID3D10EffectPass* pass = p_Technique->GetPassByIndex( 0 );
		if( !pass->IsValid() )
			return false;
		HRESULT hr = pass->GetDesc( &PassDesc );
		if( FAILED( hr ) )
			return false;

		hr = p_d3dDevice->CreateInputLayout( mVertexElts, numElts, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &mVertexLayout );
		if( FAILED( hr ) )
			return false;


		// Create the vertex buffer and fill it with the loaded vertex data
		mNumVertices = subMesh.numVertices;
		D3D10_BUFFER_DESC bufferDesc;
		bufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D10_USAGE_DEFAULT; // Not a dynamic buffer
		bufferDesc.ByteWidth = mNumVertices * mVertexSize; // Buffer size
		bufferDesc.CPUAccessFlags = 0;   // Indicates that CPU won't access this buffer at all after creation
		bufferDesc.MiscFlags = 0;
		D3D10_SUBRESOURCE_DATA initData; // Initial data
		initData.pSysMem = subMesh.vertices;   
		if (FAILED( p_d3dDevice->CreateBuffer( &bufferDesc, &initData, &mVertexBuffer )))
		{
			return false;
		}


		// Create the index buffer - assuming 2-byte (WORD) index data
		mNumIndices = static_cast<unsigned int>(subMesh.numFaces) * 3;
		bufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
		bufferDesc.Usage = D3D10_USAGE_DEFAULT;
		bufferDesc.ByteWidth = mNumIndices * sizeof(WORD);
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		initData.pSysMem = subMesh.faces;   
		if (FAILED( p_d3dDevice->CreateBuffer( &bufferDesc, &initData, &mIndexBuffer )))
		{
			return false;
		}

		mHasGeometry = true;

		return true;
	}

	// Sends the necessary data to the GPU ready for the models to be drawn.
	void CTemplate::Render(ID3D10Device* p_d3dDevice)
	{
		UINT offset = 0;

		p_d3dDevice->IASetVertexBuffers
			(
				0,
				1,
				&mVertexBuffer,
				&mVertexSize,
				&offset
			);

		p_d3dDevice->IASetInputLayout( mVertexLayout );
		p_d3dDevice->IASetIndexBuffer( mIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
		p_d3dDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	}

	// This function clears all of the data stored for the mesh.
	void CTemplate::ReleaseResources()
	{
		mIndexBuffer->Release();	mIndexBuffer = 0;
		mVertexBuffer->Release();	mVertexBuffer = 0;
		mVertexLayout->Release();	mVertexLayout = 0;

		mHasGeometry = false;
	}

	// Creates a new model of this template. Must provide the ID of the model.
		// Can specify a location for the model to be created at.
	void CTemplate::CreateModel(TUInt32 modelID, float fX/*=0.0f*/, float fY/*=0.0f*/, float fZ/*=0.0f*/)
	{
		CModel* model = new CModel( modelID, m_TemplateID, fX, fY, fZ );

		m_ModelList.push_back( model );
	}

	// Removes a model from the scene. Must pass the UID of the model.
	bool CTemplate::DeleteModel(TUInt32 modelID)
	{
		vector<CModel*>::iterator P;
		P = m_ModelList.begin();
		while( P != m_ModelList.end() )
		{
			if( (*P)->GetUID() == modelID )
			{
				m_ModelList.erase( P );
				return true;
			}
		}

		return false;
	}

	void CTemplate::DeleteAllModels()
	{
		vector<CModel*>::iterator P;
		P = m_ModelList.begin();

		while( P != m_ModelList.end() )
		{
			P = m_ModelList.erase( P );
		}
	}

	// Returns a pointer to a model.
	CModel* CTemplate::GetModelByUID(TUInt32 modelID)
	{
		vector<CModel*>::iterator P;
		P = m_ModelList.begin();

		while( P != m_ModelList.end() )
		{
			if( (*P)->GetUID() == modelID )
				return (*P);
		}

		return 0;
	}

	// Returns a pointer to a model at the specified position in the model list.
	CModel* CTemplate::GetModelByLocation(TUInt32 modelNumber)
	{
		if( modelNumber < m_ModelList.size() )
			return m_ModelList[modelNumber];
		
		return NULL;
	}

	// Returns the number of models currently associated with this template.
	TUInt32 CTemplate::ModelCount()
	{
		return m_ModelList.size();
	}

}// namespace DX
