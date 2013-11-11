#ifndef _HTN__HTNDEFINES_H_
#define _HTN__HTNDEFINES_H_

#include <string>
#include <vector>
using std::string;
using std::vector;

#include "HTNUtility.h"

namespace HTN {

	

	// Say whether a given task is primitive or non-primitive.
	enum ETaskType
	{
		kPrimitive,
		kNonPrimitive,

		kNumTaskTypes//	Leave at end.
	};

	// The meaning of the operators. Each one maps to an SAction function pointer.
	enum EAction
	{

		BEFORE = 0,// <-
		AFTER,// ->
		DURING,// --

		ASSIGN,// =

		LESS,// <
		GREATER,// >
		EQUAL,// ==
		GTOREQ,// >=
		LTOREQ,// <=

		DIV,// /
		MUL,// *
		ADD,// +
		SUB,// -
		POW,// ^
		SQRT,// ¬

		CALL,// extern()

		kNumActions//	leave at end.

	};

	// This is for the primitive functions.
	// **Messy code. Find better way to implement this.**
	struct SAction
	{
		union
		{
			// Comparison
			typedef bool (*ipF)(int, int);
			typedef bool (*lpF)(long, long);
			typedef bool (*fpF)(float, float);
			typedef bool (*cpF)(char, char);
			
			// Basic Arithmatic
			typedef int (*iF)(int, int);
			typedef long (*lF)(long, long);
			typedef float (*fF)(float, float);

			// Sqrt
			typedef float (*iSqrtFunc)(int);
			typedef float (*lSqrtFunc)(long);
			typedef float (*fSqrtFunc)(float);
			
			// Pow
			typedef float (*iPowFunc)(int, int);
			typedef float (*lPowFunc)(long, long);
			// can use fF function pointer for floatPowFunc.
		};
	};// SAction


	// Used to quickly build a lookup table for the creation of constraints.
	struct SOperator
	{
		string Op;
		EAction eAction;
		SAction sAction;
	};

	// A constraint within a task.
	struct SConstraint
	{
		
		string Desc;
		SAction Op;// The meaning of the constraint operator.

	};// SSubtask

	// A variable within a task.
	struct SVar
	{
		string VarName;

		union
		{
			int iVal;
			char cVal;
			float fVal;
			char* sMethod;

			// uncommon data types.
			long lVal;
			double dVal;
			short shVal;
			void* pVal;// other data type (e.g. class/struct/pointer/etc)
		};

	};// SVar

	// A single task (Primitive or non-primitive) within the network.
	struct STask
	{

		~STask()
		{
			vector<SVar*>::iterator varP;
			varP = m_Input.begin();
			while(varP != m_Input.end())
			{
				delete (*varP);
				varP = m_Input.erase( varP );
			}

			varP = m_Variables.begin();
			while(varP != m_Variables.end())
			{
				delete (*varP);
				varP = m_Variables.erase( varP );
			}

			vector<SConstraint*>::iterator conP;
			conP = m_Constraints.begin();
			while(conP != m_Constraints.end())
			{
				delete (*conP);
				conP = m_Constraints.erase( conP );
			}
		}

		ETaskType TaskType;// Set whether primitive or non-primitive type.

		string TaskName;// The main name of the task.
		
		string TaskDesc;// the task's method name.

		vector<int> m_Methods;// All of the subtasks in this task, if any. Number stored is the position in the array of the task.

		vector<SConstraint*> m_Constraints;// All of the constraints in this task, if any.
		vector<SVar*> m_Variables;// All of the variables in this task, if any. **Consider merging with m_Input**

		vector<SVar*> m_Input;// The parameters for this task. **Consider merging with m_Variables**

	};// STask

}// namespace HTN

#endif// _HTN__HTNDEFINES_H_
