#include "pch.h"
#include "CIndividual.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Consts.h"

using namespace std;

template <class T> CIndividual<T>::CIndividual()
{
	pd_my_genotype = new double[0];
}

template <> CIndividual<bool>::CIndividual(CKnapsackProblem<bool>& pcOwnProblem, int iNumberOfGens, string& sError)
{
	if (iNumberOfGens > 0)
	{
		//cout << "tworze";
		d_fitness = 0;
		i_number_of_gens = iNumberOfGens;
		pd_my_genotype = new double[iNumberOfGens];
		pc_own_problem = &pcOwnProblem;
		for (int i = 0;i < iNumberOfGens;i++)
		{
			pd_my_genotype[i] = rand() % 2;
		}
	}
	else
	{
		sError = NEGATIVE_GENOTYPE;
	}
}

template <> CIndividual<double>::CIndividual(CKnapsackProblem<double>& pcOwnProblem, int iNumberOfGens, string& sError)
{
	if (iNumberOfGens > 0)
	{
		//cout << "tworze";
		d_fitness = 0;
		i_number_of_gens = iNumberOfGens;
		pd_my_genotype = new double[iNumberOfGens];
		pc_own_problem = &pcOwnProblem;
		for (int i = 0;i < iNumberOfGens;i++)
		{
			pd_my_genotype[i] = MAX_INITIAL_AMOUNT * ((double)(rand() % TO_DO_PERCENTAGE) / TO_DO_PERCENTAGE);
		}
	}
	else
	{
		sError = NEGATIVE_GENOTYPE;
	}
}

template <> CIndividual<int>::CIndividual(CKnapsackProblem<int>& pcOwnProblem, int iNumberOfGens, string& sError)
{
	if (iNumberOfGens > 0)
	{
		//cout << "tworze";
		d_fitness = 0;
		i_number_of_gens = iNumberOfGens;
		pd_my_genotype = new double[iNumberOfGens];
		pc_own_problem = &pcOwnProblem;
		for (int i = 0;i < iNumberOfGens;i++)
		{
			pd_my_genotype[i] = rand() % MAX_INITIAL_AMOUNT;
		}
	}
	else
	{
		sError = NEGATIVE_GENOTYPE;
	}
}

template <class T> CIndividual<T>::CIndividual(CKnapsackProblem<T>& pcOwnProblem, CIndividual& cMyParent, string& sError)
{
	vSetParameters(pcOwnProblem, cMyParent, cMyParent, 0, sError);
}


template <class T> CIndividual<T>::CIndividual(CKnapsackProblem<T>& pcOwnProblem, CIndividual& cFirstParent, CIndividual& cSecondParent, int iWhenCut, string& sError)
{
	vSetParameters(pcOwnProblem, cFirstParent, cSecondParent, iWhenCut, sError);
}

template <class T> void CIndividual<T>::vSetParameters(CKnapsackProblem<T>& pcOwnProblem, CIndividual& cFirstParent, CIndividual& cSecondParent, int iWhenCut, string& sError)
{
	pc_own_problem = &pcOwnProblem;
	d_fitness = 0;
	i_number_of_gens = cFirstParent.iGetNumberOfGens();
	if (iWhenCut<0 || iWhenCut>i_number_of_gens)
	{
		sError = BAD_PLACE_TO_CUT;
	}
	else
	{
		//cout << "tworze";
		double* pd_first_help = cFirstParent.pdGetGenotype();
		double* pd_second_help = cSecondParent.pdGetGenotype();
		pd_my_genotype = new double[i_number_of_gens];
		for (int i = 0;i < iWhenCut;i++)
		{
			pd_my_genotype[i] = pd_first_help[i];
		}
		for (int j = iWhenCut;j < i_number_of_gens;j++)
		{
			pd_my_genotype[j] = pd_second_help[j];
		}
		//delete[] pd_first_help;
	}
}



template <class T> CIndividual<T>::~CIndividual()
{
	//cout << "usuwam";
	if (pd_my_genotype != nullptr)
		delete[] pd_my_genotype;
}

template <class T> int CIndividual<T>::iGetNumberOfGens()
{
	return i_number_of_gens;
}

template <class T> double* CIndividual<T>::pdGetGenotype()
{
	return pd_my_genotype;
}

template <class T> double CIndividual<T>::dGetFitness()
{
	return d_fitness;
}

template <class T>  void CIndividual<T>::vWriteGenotype(string& sError)
{
	if (pd_my_genotype == nullptr) sError = NO_GENOTYPE;
	else
	{
		for (int i = 0;i < i_number_of_gens;i++) cout << pd_my_genotype[i];
		cout << endl;
	}
}

template <class T> void CIndividual<T>::operator++(int)
{
	string s_error = NO_ERROR;
	this->vDoMutate(1, s_error);
	if (s_error != NO_ERROR) vWriteBug(s_error);
}

template <class T> void CIndividual<T>::vWriteBug(string sError)
{
	cout << sError << endl;
}

template <class  T> CIndividual<T> CIndividual<T>::operator+(CIndividual cSecondParent)
{
	string s_error = NO_ERROR;
	int i_when_cut = (rand() % (i_number_of_gens - 1)) + 1;
	//cout << "yyyyy";
	CIndividual c_new_kid(*pc_own_problem, *this, cSecondParent, i_when_cut, s_error);
	//cout << "ppppppppppppppp";
	string bu = "pp";
	//c_new_kid.vWriteGenotype(bu);
	if (s_error != NO_ERROR) { vWriteBug(s_error); return CIndividual<T>(); }
	else return CIndividual(*pc_own_problem, c_new_kid, bu);
}
template <class T> void CIndividual<T>::vDoFitness(string& sError)
{
	d_fitness = pc_own_problem->dGetFitness(this->pd_my_genotype, this->i_number_of_gens);
}

template <> void CIndividual<double>::vDoMutate(double dWhenMutate, string& sError)
{
	if (dWhenMutate < 0 || dWhenMutate>1) sError = BAD_PROBABILITY;
	else
	{
		for (int i = 0;i < i_number_of_gens;i++)
		{
			double d_if_mutate = (double)(rand() % TO_DO_PERCENTAGE) / TO_DO_PERCENTAGE;
			if (d_if_mutate < dWhenMutate)
			{
				double d_value_to_mutation = (double)(rand() % TO_DO_PERCENTAGE) / TO_DO_PERCENTAGE;
				int i_plus_or_minus = rand() % 2;
				if (i_plus_or_minus == 1) pd_my_genotype[i] += d_value_to_mutation;
				else
				{
					pd_my_genotype[i] -= d_value_to_mutation;
					if (pd_my_genotype[i] < 0) pd_my_genotype[i] = 0;
				}
				//if (pd_my_genotype[i] == 0) pd_my_genotype[i] = 1;
				//else pd_my_genotype[i] = 0;
			}
		}
	}
}

template <> void CIndividual<int>::vDoMutate(double dWhenMutate, string& sError)
{
	if (dWhenMutate < 0 || dWhenMutate>1) sError = BAD_PROBABILITY;
	else
	{
		for (int i = 0;i < i_number_of_gens;i++)
		{
			double d_if_mutate = (double)(rand() % TO_DO_PERCENTAGE) / TO_DO_PERCENTAGE;
			if (d_if_mutate < dWhenMutate)
			{
				int i_plus_or_minus = rand() % 2;
				if (i_plus_or_minus == 1) pd_my_genotype[i] += 1;
				else
				{
					pd_my_genotype[i] -= 1;
					if (pd_my_genotype[i] < 0) pd_my_genotype[i] = 0;
				}
			}
		}
	}
}

template <> void CIndividual<bool>::vDoMutate(double dWhenMutate, string& sError)
{
	if (dWhenMutate < 0 || dWhenMutate>1) sError = BAD_PROBABILITY;
	else
	{
		for (int i = 0;i < i_number_of_gens;i++)
		{
			double d_if_mutate = (double)(rand() % TO_DO_PERCENTAGE) / TO_DO_PERCENTAGE;
			if (d_if_mutate < dWhenMutate)
			{
				if (pd_my_genotype[i] == 0) pd_my_genotype[i] = 1;
				else pd_my_genotype[i] = 0;
			}
		}
	}
}

template <class T>  CIndividual<T>& CIndividual<T>::cGetCHildren(CIndividual<T>& cSecondParent, double dWhenChild, int iAmount, string &sError)
{
	if (dWhenChild < 0 || dWhenChild>1) sError = BAD_PROBABILITY;
	else
	{
		if (iAmount == 2)
		{
			CIndividual<T>* e = new CIndividual<T>(*pc_own_problem, 4, sError);
			//CIndividual<T>* e2 = new CIndividual<T>(*pc_own_problem, 4, sError);
			//delete e;
			//delete e2;
			//delete[] c_new_individuals;
			/*CIndividual<T> *c_new_individuals = new CIndividual<T>[2];
			double d_if_child = (double)(rand() % TO_DO_PERCENTAGE) / TO_DO_PERCENTAGE;
			if (d_if_child > dWhenChild)
			{
				//delete[] c_new_individuals;
				c_new_individuals[0] = *(new CIndividual<T>(*pc_own_problem, 4, sError));// *(new CIndividual<T>(*pc_own_problem, cSecondParent, sError));
				c_new_individuals[1] = *(new CIndividual<T>(*pc_own_problem, 4, sError));// *(new CIndividual<T>(*pc_own_problem, *this, sError));
			}
			else
			{
				do
				{
							//delete[] c_new_individuals;
					int i_when_cut = (rand() % (i_number_of_gens - 1)) + 1;
					sError = NO_ERROR;
					c_new_individuals[0] = *(new CIndividual<T>(*pc_own_problem, 4, sError));//*(new CIndividual<T>(*pc_own_problem, cSecondParent, *this, i_when_cut, sError));
					c_new_individuals[1] = *(new CIndividual<T>(*pc_own_problem, 4, sError));//*(new CIndividual<T>(*pc_own_problem, *this, cSecondParent, i_when_cut, sError));
				} while (sError != NO_ERROR);
			}
			delete c_new_individuals[0];
			delete[] c_new_individuals;*/
			return *e; //*c_new_individuals;
		}
		else if (iAmount == 1)
		{
			//cout << "wybieram";
			//delete[] c_new_individuals;
			CIndividual<T> *c_new_individuals = new CIndividual<T>[1];
			double d_if_child = (double)(rand() % TO_DO_PERCENTAGE) / TO_DO_PERCENTAGE;
			if (d_if_child > dWhenChild)
			{
				//delete[] c_new_individuals;
				c_new_individuals[0] = *(new CIndividual<T>(*pc_own_problem, 4, sError));// *(new CIndividual<T>(*pc_own_problem, cSecondParent, sError));
			}
			else
			{
				do
				{
					//delete[] c_new_individuals;
					int i_when_cut = (rand() % (i_number_of_gens - 1)) + 1;
					sError = NO_ERROR;
					c_new_individuals[0] = *(new CIndividual<T>(*pc_own_problem, 4, sError));//*(new CIndividual<T>(*pc_own_problem, cSecondParent, *this, i_when_cut, sError));
				} while (sError != NO_ERROR);
			}
			return *c_new_individuals;
		}

	}
}
template class CIndividual<bool>;
template class CIndividual<int>;
template class CIndividual<double>;
