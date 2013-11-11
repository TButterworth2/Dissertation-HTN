#ifndef _DEMO__DX_CLIGHTMANAGER_H_
#define _DEMO__DX_CLIGHTMANAGER_H_

#include "CLight.h"
using Scene::ILight;

#include <vector>
using std::vector;

#include "CMatrix4x4.h"
#include "CVector3.h"
using gen::CMatrix4x4;
using gen::CVector3;

namespace DX {

	class CLightManager
	{

	public:

		CLightManager();
		~CLightManager();


		ILight* CreateLight(CVector3 position, CVector3 colour, float intensity);

		void DeleteLight(ILight* light);

		gen::TUInt32 GetNumLights();

		void StartLightEnum();
		void EndLightEnum();
		bool IsEnumerating();

		ILight* EnumLights();

	private:

		vector<ILight*>	m_LightList;

		bool			m_IsEnumerating;
		gen::TUInt32	m_CurrentLight;

	};

}// namespace DX

#endif// _DEMO__DX_CLIGHTMANAGER_H_
