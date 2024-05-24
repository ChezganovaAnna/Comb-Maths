#pragma once
#include <vector>

using namespace std;

class KirchhoffMatrix
{
private:
	 vector< vector<double>> matrix;
	int size;

	void ConvertToKirchhoffMatrix( vector< vector<double>>& adjacency);
	double DeterminantByGauss();
	double DeterminantByGauss(vector<vector<double>>& submatrix, int n);
	double DeterminantByGaussForAlgebraicComplement(int row, int col);

public:
	KirchhoffMatrix( vector< vector<double>>& adjacency, int n)
	{
		size = n;
		ConvertToKirchhoffMatrix(adjacency);
	}

	double CountSpanningTrees();
	vector< vector<double>> getMatrix() const { return matrix; };
	int getSize() const { return size; };
	double getDeterminantByGauss()  { return DeterminantByGauss(); };
	double getDeterminantByGaussForAlgebraicComplement(int row, int col)  { 
		return DeterminantByGaussForAlgebraicComplement(row, col); 
	};
};
