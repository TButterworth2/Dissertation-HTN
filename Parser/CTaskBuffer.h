#ifndef _PARSER__HTN_CTASKBUFFER_H_
#define _PARSER__HTN_CTASKBUFFER_H_

#include <list>
#include <string>
using std::list;
using std::string;

namespace HTN {

	class CTaskBuffer
	{

	public:

		CTaskBuffer() {}
		~CTaskBuffer()
		{
			list<string*>::iterator P = m_Tasks.begin();
			while(P != m_Tasks.end())
			{
				delete (*P);
				P++;
			}
		}

		// Add a task to the back of the queue.
		void AddToQueue(string* taskName) { m_Tasks.push_back( taskName ); }

		// Returns the next task in the queue.
		string GetNext() { return *m_Tasks.front(); }

		// Removes a task from the queue.
		void RemoveTask(string* taskName)
		{
			m_Tasks.remove(taskName);
		}

		// Return the number of tasks currently in the queue.
		unsigned int NumTasks() { return m_Tasks.size(); }

	private:

		// Set as a FIFO list for the buffer. When a new task is queued
		// to be loaded it will be added to back of this list.
		list<string*> m_Tasks;

	};

}// namespace HTN

#endif// _PARSER__HTN_CTASKBUFFER_H_
