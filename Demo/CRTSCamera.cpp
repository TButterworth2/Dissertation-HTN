
#include "CRTSCamera.h"

#include "CVector4.h"
using gen::CVector4;

#include <Windows.h>

#include "BaseMath.h"

namespace DX {

	// Basic Constructor
	CRTSCamera::CRTSCamera(CVector3 worldY, TUInt32 modelID, TUInt32 templateID)
		: IRTSCamera( worldY, modelID, templateID )
	{
		m_WorldY = worldY;
	}

	// Basic Constructor. Set the start position of the model in ( fX, fY, fZ ).
	CRTSCamera::CRTSCamera(CVector3 worldY, TUInt32 modelID, TUInt32 templateID, float fX, float fY, float fZ)
		: IRTSCamera( worldY, modelID, templateID, fX, fY, fZ )
	{
		m_WorldY = worldY;
	}

	// Basic Constructor. Set the start position of the model.
	CRTSCamera::CRTSCamera(CVector3 worldY, TUInt32 modelID, TUInt32 templateID, const CVector3& position)
		: IRTSCamera( worldY, modelID, templateID, position )
	{
		m_WorldY = worldY;
	}

	// Need to implement a local version since the camera will be angled down.
	void CRTSCamera::MoveLocalZ(float distance)
	{
		CMatrix4x4* worldMatrix = GetWorldMatrix();

		// Cross world Y with local X to give the new Z axis
		CVector3 newZ = worldMatrix->GetRow( 0 ).Vector3().Cross( m_WorldY );

		// Set the new position using standard local movement formula, but substituting local Z with new Z.
		float newDist = distance * gen::InvSqrt( newZ.x*newZ.x + newZ.y*newZ.y + newZ.z*newZ.z );
		worldMatrix->SetPosition( CVector3( newDist*newZ.x, newDist*newZ.y, newDist*newZ.z ) );
	}

	CMatrix4x4 CRTSCamera::GetViewProjMatrix()
	{
		return m_ViewMatrix * m_ProjMatrix;
	}

	CMatrix4x4& CRTSCamera::BuildViewMatrix()
	{
		m_ViewMatrix = (*m_pWorldMatrix);
		m_ViewMatrix.Invert();

		return m_ViewMatrix;
	}

	CMatrix4x4& CRTSCamera::BuildProjMatrix()
	{
		float w, h, Q;
		w	= (float)1/tan(m_FovX/2);
		h	= (float)1/tan(m_FovY/2);
		Q	= m_ClipY / (m_ClipY - m_ClipY);

		ZeroMemory( &m_ProjMatrix, sizeof(m_ProjMatrix) );

		m_ProjMatrix.e00 = w;m_ProjMatrix.e01 = 0;m_ProjMatrix.e02 = 0;m_ProjMatrix.e03 = 0;
		m_ProjMatrix.e10 = 0;m_ProjMatrix.e11 = h;m_ProjMatrix.e12 = 0;m_ProjMatrix.e13 = 0;
		m_ProjMatrix.e20 = 0;m_ProjMatrix.e21 = 0;m_ProjMatrix.e22 = Q;m_ProjMatrix.e23 = 1;
		m_ProjMatrix.e30 = 0;m_ProjMatrix.e31 = 0;m_ProjMatrix.e32 = -m_ClipX*Q;m_ProjMatrix.e33 = 0;

		return m_ProjMatrix;
	}

}// namespace DX
