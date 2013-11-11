#ifndef _DEMO__DX_CCAMERA_H_
#define _DEMO__DX_CCAMERA_H_

#include "CModel.h"

#include "CMatrix4x4.h"
#include "CVector3.h"
using gen::CMatrix4x4;
using gen::CVector3;
using gen::TUInt32;

namespace Scene {
	class IRTSCamera : public DX::CModel
	{

	public:

		// Basic Constructor
		IRTSCamera(CVector3 worldY, TUInt32 modelID, TUInt32 templateID)
			: CModel( modelID, templateID )
		{}

		// Basic Constructor. Set the start position of the model in ( fX, fY, fZ ).
		explicit IRTSCamera(CVector3 worldY, TUInt32 modelID, TUInt32 templateID, float fX, float fY, float fZ)
			: CModel( modelID, templateID, fX, fY, fZ )
		{}

		// Basic Constructor. Set the start position of the model.
		explicit IRTSCamera(CVector3 worldY, TUInt32 modelID, TUInt32 templateID, const CVector3& position)
			: CModel( modelID, templateID, position )
		{}

		// Need to implement a local version since the camera will be angled down.
		virtual void MoveLocalZ(float distance) = 0;

		virtual void SetFOV(float fovY, float aspect) = 0;

		virtual void SetClipPlanes(float clipX, float clipY) = 0;

		virtual CMatrix4x4 GetViewProjMatrix() = 0;
	};
}

namespace DX {

	class CRTSCamera : public Scene::IRTSCamera
	{

	public:

		// Basic Constructor
		CRTSCamera(CVector3 worldY, TUInt32 modelID, TUInt32 templateID);

		// Basic Constructor. Set the start position of the model in ( fX, fY, fZ ).
		explicit CRTSCamera(CVector3 worldY, TUInt32 modelID, TUInt32 templateID, float fX, float fY, float fZ);

		// Basic Constructor. Set the start position of the model.
		explicit CRTSCamera(CVector3 worldY, TUInt32 modelID, TUInt32 templateID, const CVector3& position);

		// Need to implement a local version since the camera will be angled down.
		virtual void MoveLocalZ(float distance);

		void SetFOV(float fovY, float aspect)
		{
			m_FovY = fovY;
			m_FovX = 2 * gen::ATan( gen::Tan( m_FovY / 2 ) * aspect );
		}

		void SetClipPlanes(float clipX, float clipY)
		{
			m_ClipX = clipX;
			m_ClipY = clipY;
		}

		CMatrix4x4 GetViewProjMatrix();

	private:

		CMatrix4x4& BuildViewMatrix();
		CMatrix4x4& BuildProjMatrix();

		CMatrix4x4 m_ViewMatrix;
		CMatrix4x4 m_ProjMatrix;
		CVector3 m_WorldY;

		float m_FovY, m_FovX;

		float m_ClipX, m_ClipY;

	};

}// namespace DX

#endif// _DEMO__DX_CCAMERA_H_
