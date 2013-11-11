#ifndef _PARSER__HTN_HTNUTILITY_H_
#define _PARSER__HTN_HTNUTILITY_H_

#include "BaseMath.h"

namespace HTN {

	// Check if Val1 is less than val2
	bool IsLessThan(int val1, int val2) { return val1 < val2; }
	bool IsLessThan(float val1, float val2) { return val1 < val2; }
	bool IsLessThan(long val1, long val2) { return val1 < val2; }
	bool IsLessThan(char val1, char val2) { return val1 < val2; }

	bool IsGreaterThan(int val1, int val2) { return val1 > val2; }
	bool IsGreaterThan(long val1, long val2) { return val1 > val2; }
	bool IsGreaterThan(float val1, float val2) { return val1 > val2; }
	bool IsGreaterThan(char val1, char val2) { return val1 > val2; }

	bool IsEqual(int val1, int val2) { return val1 == val2; }
	bool IsEqual(long val1, long val2) { return val1 == val2; }
	bool IsEqual(float val1, float val2) { return gen::AreEqual( val1, val2 ); }
	bool IsEqual(char val1, char val2) { return val1 == val2; }

	bool IsGreaterOrEqual(int val1, int val2) { return val1 >= val2; }
	bool IsGreaterOrEqual(long val1, long val2) { return val1 >= val2; }
	bool IsGreaterOrEqual(float val1, float val2) { return gen::AreEqual( val1, val2 ) || val1 > val2; }
	bool IsGreaterOrEqual(char val1, char val2) { return val1 >= val2; }

	bool IsLessOrEqual(int val1, int val2) { return val1 <= val2; }
	bool IsLessOrEqual(long val1, long val2) { return val1 <= val2; }
	bool IsLessOrEqual(float val1, float val2) { return gen::AreEqual( val1, val2 ) || val1 < val2; }
	bool IsLessOrEqual(char val1, char val2) { return val1 <= val2; }

	int Add(int n1, int n2) { return n1+n2; }
	long Add(long n1, long n2) { return n1+n2; }
	float Add(float n1, float n2) { return n1+n2; }

	int Sub(int n1, int n2) { return n1-n2; }
	long Sub(long n1, long n2) { return n1-n2; }
	float Sub(float n1, float n2) { return n1-n2; }

	int Mul(int n1, int n2) { return n1*n2; }
	long Mul(long n1, long n2) { return n1*n2; }
	float Mul(float n1, float n2) { return n1*n2; }

	int Div(int n1, int n2) { return n1/n2; }
	long Div(long n1, long n2) { return n1/n2; }
	float Div(float n1, float n2) { return n1/n2; }

	float Pow(int n1, int n2) { return gen::Pow(n1, n2); }
	float Pow(long n1, long n2) { return gen::Pow(n1, n2); }
	float Pow(float n1, float n2) { return gen::Pow(n1, n2); }

	float Sqrt(int n) { return gen::Sqrt(n); }
	float Sqrt(long n) { return gen::Sqrt(n); }
	float Sqrt(float n) { return gen::Sqrt(n); }

}// namespace HTN

#endif// _PARSER__HTN_HTNUTILITY_H_
