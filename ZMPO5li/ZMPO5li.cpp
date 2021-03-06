// ZMPO5li.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "CIndividual.h"
//#include "CGeneticAlgorithm.h"
#include <string>
#include <ctime>
#include <cstdlib>
#include "CKnapsackProblem.h"
#include "Consts.h"

int main()
{
	srand(time(NULL));
	string s_err = NO_ERROR;
  //  std::cout << "Hello World!\n"; 
	double* tab1 = new double[4];
	tab1[0] = 5;
	tab1[1] = 1;
	tab1[2] = 4;
	tab1[3] = 3;
	double* tab2 = new double[4];
	tab2[0] = 4;
	tab2[1] = 1;
	tab2[2] = 3;
	tab2[3] = 2;
	//CKnapsackProblem <bool> * c_new_knapsack = new CKnapsackProblem < bool > (4, tab1, tab2, 5, s_err);
	CKnapsackProblem <int> c_new_knapsack2(4, tab1, tab2, 5, s_err);
	CIndividual<int>* n = new CIndividual<int>(c_new_knapsack2, 4, s_err);
	CIndividual<int>* n2 = new CIndividual<int>(c_new_knapsack2, 4, s_err);
	for (int i = 0;i < 200000000;i++)
	{
		CIndividual<int>* n3 =& n->cGetCHildren(*n2, 0.6, 2, s_err);
		delete n3;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
