#include <cmath>
#include <iostream>
#include <vector>
#include "KirchhoffMatrix.h"

using namespace std;

int main()
{
	int n = 4;

	vector<vector<double>> adjacency = {
		{ 0, 1, 0, 0},
		{ 1, 0, 1, 1},
		{ 0, 1, 0, 1},
		{ 0, 1, 1, 0}
	};


	KirchhoffMatrix kirchhoff(adjacency, n);
	double numSpanningTrees = kirchhoff.CountSpanningTrees();

	cout << "Number of trees: " << numSpanningTrees;
	return 0;
}

