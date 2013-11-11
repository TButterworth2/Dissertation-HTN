
#include "CLightManager.h"

namespace DX {

	CLightManager::CLightManager()
	{
		m_IsEnumerating = false;
	}
	CLightManager::~CLightManager()
	{
		vector<ILight*>::iterator P;
		P = m_LightList.begin();

		while( P != m_LightList.end() )
		{
			delete (*P);
			P++;
		}
	}


	ILight* CLightManager::CreateLight(CVector3 position, CVector3 colour, float intensity)
	{
		ILight* light = new CLight( position );
		light->SetColour( colour.x, colour.y, colour.z );
		light->SetIntensity( intensity );

		m_LightList.push_back( light );

		return light;
	}

	void CLightManager::DeleteLight(ILight* light)
	{
		vector<ILight*>::iterator P;
		P = m_LightList.begin();

		while( P != m_LightList.end() )
		{
			if( (*P) == light )
			{
				delete (*P);
				m_LightList.erase( P );
				return;
			}

			P++;
		}
	}

	gen::TUInt32 CLightManager::GetNumLights()
	{
		return m_LightList.size();
	}

	void CLightManager::StartLightEnum()
	{
		m_CurrentLight = 0;
		m_IsEnumerating = true;
	}
	void CLightManager::EndLightEnum()
	{
		m_IsEnumerating = false;
	}
	bool CLightManager::IsEnumerating()
	{
		return m_IsEnumerating;
	}

	ILight* CLightManager::EnumLights()
	{
		if( m_IsEnumerating )
		{
			return m_LightList[m_CurrentLight++];
		}

		return 0;
	}

}// namespace DX
