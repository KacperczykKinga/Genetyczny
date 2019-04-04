#include "pch.h"
#include "CKnapsackProblem.h"
//#include "CGeneticAlgorithm.h"
#include "CIndividual.h"
#include "Consts.h"
#include <iostream>
#include <string>

using namespace std;

template <class T> CKnapsackProblem<T>::CKnapsackProblem(int iAmountOfThings, double* pdTabOfValues, double* pdTabOfSize, double dMaxWeight, string& sError)
{
	sError = NO_ERROR;
	if (iAmountOfThings > 0)
	{
		//cout << "buja";
		if (dMaxWeight > 0)
		{
			if (pdTabOfValues == nullptr || pdTabOfSize == nullptr) sError = EMPTY_TABLES;
			else
			{
				i_amount_of_things = iAmountOfThings;
				pd_tab_of_things = new double*[2];
				pd_tab_of_things[0] = pdTabOfValues;
				pd_tab_of_things[1] = pdTabOfSize;
				d_max_weight = dMaxWeight;
			}
		}
		else sError = NEGATIVE_WEIGHT;
	}
	else
	{
		sError = NEGATIVE_AMOUNT_OF_THHINGS;
	}
}


template <class T> CKnapsackProblem<T>::~CKnapsackProblem()
{
	//delete[] pd_tab_of_things[0];
	//delete[] pd_tab_of_things[1];
	delete[] pd_tab_of_things;
}


template <class T> double CKnapsackProblem<T>::dGetFitness(double* pdTabOfGens, int iNumberOfGens)
{
	double d_fitness = 0;
	if (pd_tab_of_things == nullptr) string sError = NO_DATA;
	else if (d_max_weight < 0) string sError = NEGATIVE_WEIGHT;
	else
	{
		double d_weight = 0;
		for (int j = 0;j < iNumberOfGens;j++)
		{
			//if (piTabOfGens[j] >= 1)
			//{
			d_fitness += pd_tab_of_things[0][j] * pdTabOfGens[j];
			d_weight += pd_tab_of_things[1][j] * pdTabOfGens[j];
			//}
		}
		//cout << d_fitness << " " << d_weight << endl;
		if (d_weight > d_max_weight)
		{
			d_fitness = 0;
		}
	}
	return d_fitness;
}


template class CKnapsackProblem<bool>;
template class CKnapsackProblem<int>;
template class CKnapsackProblem<double>;
