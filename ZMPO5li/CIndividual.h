#pragma once
#include <string>
#include "CKnapsackProblem.h"
#include <iostream>
using namespace std;

template <class T> class CIndividual
{
private:
	double* pd_my_genotype;
	int i_number_of_gens;
	CKnapsackProblem<T>* pc_own_problem;
	double d_fitness;
	void vSetParameters(CKnapsackProblem<T>& pcOwnProblem, CIndividual<T>& cFirstParent, CIndividual<T>& cSecondParent, int iWhenCut, string& sError);
public:
	CIndividual();
	CIndividual(CKnapsackProblem<T>& pcOwnProblem, int iNumberOfGens, string& sError);
	CIndividual(CKnapsackProblem<T>& pcOwnProblem, CIndividual<T>& cMyParent, string& sError);
	CIndividual(CKnapsackProblem<T>& pcOwnProblem, CIndividual<T>& cFirstParent, CIndividual<T>& cSecondParent, int iWhenCut, string& sError);
	~CIndividual();
	void operator++(int);
	CIndividual<T> operator+(CIndividual cSecondParent);
	void vDoFitness(string& sError);
	void vDoMutate(double dWhenMutate, string& sError);
	CIndividual<T>& cGetCHildren(CIndividual<T>& cSecondParent, double dWhenChild, int iAmount, string& sError);
	void vWriteGenotype(string& sError);
	double* pdGetGenotype();
	int iGetNumberOfGens();
	double dGetFitness();
	void vWriteBug(string sError);
};


