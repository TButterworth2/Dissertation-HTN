
#include "CEntity.h"

namespace DX {

	// Move the model in the world X direction.
	void CEntity::MoveX(float distance)
	{
		m_pWorldMatrix->MoveX( distance );
	}

	// Move the model in the world Y direction.
	void CEntity::MoveY(float distance)
	{
		m_pWorldMatrix->MoveY( distance );
	}

	// Move the model in the world Z direction.
	void CEntity::MoveZ(float distance)
	{
		m_pWorldMatrix->MoveZ( distance );
	}


	// Move the model in the local X direction.
	void CEntity::MoveLocalX(float distance)
	{
		m_pWorldMatrix->MoveLocalX( distance );
	}

	// Move the model in the local Y direction.
	void CEntity::MoveLocalY(float distance)
	{
		m_pWorldMatrix->MoveLocalY( distance );
	}

	// Move the model in the local Z direction.
	void CEntity::MoveLocalZ(float distance)
	{
		m_pWorldMatrix->MoveLocalZ( distance );
	}



	
	// Set the X position of the model.
	void CEntity::SetX(float position)
	{
		m_pWorldMatrix->SetX( position );
	}

	// Set the Y position of the model.
	void CEntity::SetY(float position)
	{
		m_pWorldMatrix->SetY( position );
	}

	// Set the Z position of the model.
	void CEntity::SetZ(float position)
	{
		m_pWorldMatrix->SetZ( position );
	}




	// Rotate the model around the local X axis.
	void CEntity::RotateX(float angle)
	{
		m_pWorldMatrix->RotateX( angle );
	}

	// Rotate the model around the local Y axis.
	void CEntity::RotateY(float angle)
	{
		m_pWorldMatrix->RotateY( angle );
	}

	// Rotate the model around the local Z axis.
	void CEntity::RotateZ(float angle)
	{
		m_pWorldMatrix->RotateZ( angle );
	}




	// Get the current X position of the model in world space.
	float CEntity::GetX()
	{
		return m_pWorldMatrix->GetX();
	}

	// Get the current Y position of the model in world space.
	float CEntity::GetY()
	{
		return m_pWorldMatrix->GetY();
	}

	// Get the current Z position of the model in world space.
	float CEntity::GetZ()
	{
		return m_pWorldMatrix->GetZ();
	}


	// Get the current position of the model in world space.
	CVector3& CEntity::GetPosition()
	{
		return m_pWorldMatrix->Position();
	}

}// namespace DX
