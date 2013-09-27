
#include "CModel.h"

namespace DX {

	// Basic Constructor
	CModel::CModel(unsigned int ID)
	{
		m_ModelID = ID;

		m_TextureID = 0;

		m_pWorldMatrix = new CMatrix4x4();
	}

	// Basic Constructor. Set the start position of the model in ( fX, fY, fZ ).
	CModel::CModel(unsigned int ID, float fX, float fY, float fZ)
	{
		m_ModelID = ID;

		m_TextureID = 0;

		m_pWorldMatrix = new CMatrix4x4( CVector3( fX, fY, fZ ) );
	}

	// Basic Constructor. Set the start position of the model.
	CModel::CModel(unsigned int ID, const CVector3& position)
	{
		m_ModelID = ID;

		m_TextureID = 0;

		m_pWorldMatrix = new CMatrix4x4( position );
	}

	// Basic Destructor.
	// This will delete the WorldMatrix
	CModel::~CModel()
	{
		delete m_pWorldMatrix;
	}

	// Returns a pointer to the WorldMatrix.
	// This will be used for the rendering.
	CMatrix4x4* CModel::GetWorldMatrix()
	{
		return m_pWorldMatrix;
	}


	//============================================================
	// Misc
	//============================================================

	// Sets the UID of the texture to be used for rendering.
	void CModel::SetTextureID(unsigned int texID)
	{
		m_TextureID = texID;
	}

	// Gets the UID of the texture to be used for rendering.
	unsigned int CModel::GetTextureID()
	{
		return m_TextureID;
	}

	// Gets the UID of the current model.
	unsigned int CModel::GetUID()
	{
		return m_ModelID;
	}

	//============================================================
	// Translation
	//============================================================

	// Move the model in the world X direction.
	void CModel::MoveX(float distance)
	{
	}

	// Move the model in the world Y direction.
	void CModel::MoveY(float distance)
	{
	}

	// Move the model in the world Z direction.
	void CModel::MoveZ(float distance)
	{
	}


	// Move the model in the local X direction.
	void CModel::MoveLocalX(float distance)
	{
	}

	// Move the model in the local Y direction.
	void CModel::MoveLocalY(float distance)
	{
	}

	// Move the model in the local Z direction.
	void CModel::MoveLocalZ(float distance)
	{
	}



	
	// Set the X position of the model.
	void CModel::SetX(float position)
	{
	}

	// Set the Y position of the model.
	void SetY(float position)
	{
	}

	// Set the Z position of the model.
	void CModel::SetZ(float position)
	{
	}




	// Rotate the model around the local X axis.
	void CModel::RotateX(float angle)
	{
	}

	// Rotate the model around the local Y axis.
	void CModel::RotateY(float angle)
	{
	}

	// Rotate the model around the local Z axis.
	void CModel::RotateZ(float angle)
	{
	}




	// Get the current X position of the model in world space.
	float CModel::GetX()
	{
		return 0.0f;
	}

	// Get the current Y position of the model in world space.
	float CModel::GetY()
	{
		return 0.0f;
	}

	// Get the current Z position of the model in world space.
	float CModel::GetZ()
	{
		return 0.0f;
	}


	// Get the current position of the model in world space.
	CVector3 CModel::GetPosition()
	{
		return CVector3();
	}

}// namespace DX
