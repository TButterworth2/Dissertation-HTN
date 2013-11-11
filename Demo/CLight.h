#ifndef _DEMO__DX_CLIGHT_H_
#define _DEMO__DX_CLIGHT_H_

#include "CMatrix4x4.h"
#include "CVector3.h"
using gen::CMatrix4x4;
using gen::CVector3;

namespace Scene
{
	class ILight
	{

	public:

		ILight(CVector3 position) {}

		virtual ~ILight() {}

		virtual void SetPosition(float fX, float fY, float fZ) = 0;

		virtual CVector3 GetPosition() = 0;

		virtual void SetColour(float fR, float fG, float fB) = 0;

		virtual CVector3 GetColour() = 0;

		virtual void SetIntensity(float intensity) = 0;

		virtual float GetIntensity() = 0;
	};
}

namespace DX {

	class CLight : public Scene::ILight
	{

	public:

		CLight(CVector3 position=CVector3(0.0f, 0.0f, 0.0f))
			: ILight( position )
		{
			m_WorldMatrix = CMatrix4x4::kIdentity;
			m_WorldMatrix.SetPosition( position );

			m_Colour = CVector3(0.0f, 0.0f, 0.0f);
			m_Intensity = 1.0f;
		}

		~CLight() {}

		void SetPosition(float fX, float fY, float fZ)
		{
			m_WorldMatrix.SetPosition( CVector3(fX, fY, fZ) );
		}

		CVector3 GetPosition()
		{
			return m_WorldMatrix.Position();
		}

		void SetColour(float fR, float fG, float fB)
		{
			m_Colour.Set( fR, fG, fB );
		}

		CVector3 GetColour()
		{
			return m_Colour;
		}

		void SetIntensity(float intensity)
		{
			m_Intensity = intensity;
		}

		float GetIntensity()
		{
			return m_Intensity;
		}

	private:

		CMatrix4x4	m_WorldMatrix;
		CVector3	m_Colour;

		float		m_Intensity;

	};

}// namespace DX

#endif// _DEMO__DX_CLIGHT_H_
