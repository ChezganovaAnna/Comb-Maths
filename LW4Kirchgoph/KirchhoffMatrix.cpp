#include "KirchhoffMatrix.h"
#include <iomanip>
#include <iostream>

using namespace std;


void KirchhoffMatrix::ConvertToKirchhoffMatrix(std::vector<std::vector<double>>& adjacency)
{
	matrix = std::vector<std::vector<double>>(size, std::vector<double>(size, 0));
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (adjacency[i][j] != 0)
			{
				matrix[i][j] = -1;
				matrix[j][i] = -1;
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		int degree = 0;
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] != 0)
			{
				degree++;
			}
		}
		matrix[i][i] = degree;
	}
}


double KirchhoffMatrix::DeterminantByGauss() 
{
	double det = 1;
	//берем алгебраическое дополнение А11
	double a11 = DeterminantByGaussForAlgebraicComplement(0, 0);
	det = a11; // вот так пока

	return det;
}

double KirchhoffMatrix::DeterminantByGaussForAlgebraicComplement(int row, int col) 
{
	vector<vector<double>> submatrix(size - 1, vector<double>(size - 1, 0));
	int ti = 0;
	for (int i = 0; i < size; ++i)
	{
		if (i == row)
			continue;
		int tj = 0;
		for (int j = 0; j < size; ++j)
		{
			if (j == col)
				continue;
			submatrix[ti][tj++] = matrix[i][j];
		}
		++ti;
	}

	double det = DeterminantByGauss(submatrix, size - 1);
	double algebraic_complement = pow(-1, row + col) * det;

	return algebraic_complement;
}

double KirchhoffMatrix::DeterminantByGauss(vector<vector<double>>& submatrix, int n)
{
	double det = 1;

	for (int i = 0; i < n; ++i)
	{
		bool flag = false;
		if (submatrix[i][i] == 0)
		{
			flag = true;
			for (int j = i; j < n; ++j)
			{
				//с чем сравнить - сравнить с эпсилон
				if (submatrix[j][i] != 0)
				{
					det *= -1;
					for (int k = 0; k < n; ++k)
					{
						double temp = submatrix[i][k];
						submatrix[i][k] = submatrix[j][k];
						submatrix[j][k] = temp;
						flag = false;
					}
				}
			}
		}
		//return 0
		//флаги плохо
		if (flag)
		{
			det = 0;
			break;
		}
		else
		{
			for (int j = i + 1; j < n; ++j)
			{
				double store = submatrix[j][i];
				for (int k = i; k < n; ++k)
				{
					submatrix[j][k] -= (submatrix[i][k] * store) / submatrix[i][i];
				}
			}
			det *= submatrix[i][i];
		}
	}
	return det;
}


double KirchhoffMatrix::CountSpanningTrees()
{
	double det = DeterminantByGauss();
	return static_cast<int>(floor(abs(det)));
}
