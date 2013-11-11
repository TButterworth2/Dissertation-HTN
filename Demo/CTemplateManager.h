#ifndef _DEMO__DX_CTEMPLATEMANAGER_H_
#define _DEMO__DX_CTEMPLATEMANAGER_H_

#include "CTemplate.h"
using Scene::ITemplate;

#include <vector>
using std::vector;

namespace DX {

	class CTemplateManager
	{

	public:

		CTemplateManager();
		~CTemplateManager();

		ITemplate* CreateTemplate(const char* fileName);
		
		void DeleteTemplate(ITemplate* temp);

		unsigned int GetNumTemplates();


		bool IsEnumerating();
		void BeginTemplateEnum();
		void EndTemplateEnum();
		ITemplate* EnumTemplates();

	private:

		vector<ITemplate*>	m_TemplateList;

		bool	m_IsEnumerating;
		unsigned int m_CurrentTemplate;

	};

}// namespace DX

#endif// _DEMO__DX_CTEMPLATEMANAGER_H_
