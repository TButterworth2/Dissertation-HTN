
#include "CTemplateManager.h"

namespace DX {

	CTemplateManager::CTemplateManager()
	{
		m_IsEnumerating = false;
	}
	CTemplateManager::~CTemplateManager()
	{
		vector<ITemplate*>::iterator P;
		P = m_TemplateList.begin();

		while( P != m_TemplateList.end() )
		{
			delete (*P);

			P++;
		}
	}

	ITemplate* CTemplateManager::CreateTemplate(const char* fileName)
	{
		ITemplate* temp = new CTemplate( m_TemplateList.size() );
		m_TemplateList.push_back( temp );
		return temp;
	}
	
	void CTemplateManager::DeleteTemplate(ITemplate* temp)
	{
		vector<ITemplate*>::iterator P;
		P = m_TemplateList.begin();

		while( P != m_TemplateList.end() )
		{
			if( (*P) == temp )
			{
				delete (*P);
				m_TemplateList.erase( P );
				return;
			}

			P++;
		}
	}

	unsigned int CTemplateManager::GetNumTemplates()
	{
		return m_TemplateList.size();
	}


	bool CTemplateManager::IsEnumerating()
	{
		m_CurrentTemplate = 0;
		return m_IsEnumerating;
	}
	void CTemplateManager::BeginTemplateEnum()
	{
		m_IsEnumerating = true;
	}
	void CTemplateManager::EndTemplateEnum()
	{
		m_IsEnumerating = false;
	}
	ITemplate* CTemplateManager::EnumTemplates()
	{
		if( m_IsEnumerating )
		{
			return m_TemplateList[m_CurrentTemplate++];
		}

		return 0;
	}

}// namespace DX
