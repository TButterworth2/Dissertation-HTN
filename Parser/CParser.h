#ifndef _PARSER__CPARSER_H_
#define _PARSER__CPARSER_H_

#include "HTNDefines.h"
using namespace HTN;

#include <vector>
using std::vector;

#include "CTaskBuffer.h"

class CParser
{

public:

	CParser();
	~CParser();

	void ParseHTN(const char* htnFile);

private:

	// Get an action associated with an action type.
	SAction GetAction(EAction action);

	// Load the next task from the buffer.
	STask* LoadTask();


	EAction m_OperatorLookup[kNumActions];// A lookup table for the various actions and their meaning. Will be hard coded in constructor.

	vector<STask*> TaskNetwork;

	CTaskBuffer* m_pTaskBuffer;

};

#endif// _PARSER__CPARSER_H_
