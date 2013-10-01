
#include "CModel.h"

namespace DX {

	// Basic Constructor
	CModel::CModel(TUInt32 modelID, TUInt32 templateID)
	{
		m_ModelID = modelID;

		m_TemplateID = templateID;

		m_pWorldMatrix = new CMatrix4x4();
	}

	// Basic Constructor. Set the start position of the model in ( fX, fY, fZ ).
	CModel::CModel(TUInt32 modelID, TUInt32 templateID, float fX, float fY, float fZ)
	{
		m_ModelID = modelID;

		m_TemplateID = templateID;

		m_pWorldMatrix = new CMatrix4x4( CVector3( fX, fY, fZ ) );
	}

	// Basic Constructor. Set the start position of the model.
	CModel::CModel(TUInt32 modelID, TUInt32 templateID, const CVector3& position)
	{
		m_ModelID = modelID;

		m_TemplateID = templateID;

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

	// Gets the UID of the current model.
	TUInt32 CModel::GetUID()
	{
		return m_ModelID;
	}

	TUInt32 CModel::GetTemplateID()
	{
		return m_TemplateID;
	}

	//============================================================
	// Translation
	//============================================================

	// Move the model in the world X direction.
	void CModel::MoveX(float distance)
	{
		m_pWorldMatrix->MoveX( distance );
	}

	// Move the model in the world Y direction.
	void CModel::MoveY(float distance)
	{
		m_pWorldMatrix->MoveY( distance );
	}

	// Move the model in the world Z direction.
	void CModel::MoveZ(float distance)
	{
		m_pWorldMatrix->MoveZ( distance );
	}


	// Move the model in the local X direction.
	void CModel::MoveLocalX(float distance)
	{
		m_pWorldMatrix->MoveLocalX( distance );
	}

	// Move the model in the local Y direction.
	void CModel::MoveLocalY(float distance)
	{
		m_pWorldMatrix->MoveLocalY( distance );
	}

	// Move the model in the local Z direction.
	void CModel::MoveLocalZ(float distance)
	{
		m_pWorldMatrix->MoveLocalZ( distance );
	}



	
	// Set the X position of the model.
	void CModel::SetX(float position)
	{
		m_pWorldMatrix->SetX( position );
	}

	// Set the Y position of the model.
	void CModel::SetY(float position)
	{
		m_pWorldMatrix->SetY( position );
	}

	// Set the Z position of the model.
	void CModel::SetZ(float position)
	{
		m_pWorldMatrix->SetZ( position );
	}




	// Rotate the model around the local X axis.
	void CModel::RotateX(float angle)
	{
		m_pWorldMatrix->RotateLocalX( angle );
	}

	// Rotate the model around the local Y axis.
	void CModel::RotateY(float angle)
	{
		m_pWorldMatrix->RotateLocalY( angle );
	}

	// Rotate the model around the local Z axis.
	void CModel::RotateZ(float angle)
	{
		m_pWorldMatrix->RotateLocalZ( angle );
	}




	// Get the current X position of the model in world space.
	float CModel::GetX()
	{
		return m_pWorldMatrix->GetX();
	}

	// Get the current Y position of the model in world space.
	float CModel::GetY()
	{
		return m_pWorldMatrix->GetY();
	}

	// Get the current Z position of the model in world space.
	float CModel::GetZ()
	{
		return m_pWorldMatrix->GetZ();
	}


	// Get the current position of the model in world space.
	CVector3 CModel::GetPosition()
	{
		return m_pWorldMatrix->GetPosition();
	}

}// namespace DX
