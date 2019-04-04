#pragma once
#include <string>


using namespace std;

template <class T> class CKnapsackProblem
{
private:
	int i_amount_of_things;
	double** pd_tab_of_things;
	double d_max_weight;
public:
	CKnapsackProblem(int iAmountOfThings, double* pdTabOfValues, double* pdTabOfSize, double dMaxWeight, string& s_error);
	~CKnapsackProblem();
	double dGetFitness(double* pdTabOfGens, int iNumberOfGens);
};

