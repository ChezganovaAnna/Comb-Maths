#define CATCH_CONFIG_MAIN
#include "../LW4Kirchgoph/KirchhoffMatrix.h"
#include "../catch.hpp"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

//полный граф должен вернуть для 5 5 в кубе
//гграф из двух компонент = там ответ 0
//дерево простое
//одна изолированная вершина
//как на лекции пример


SCENARIO("DeterminantByGauss returns correct determinant for a 3x3 matrix")
{
	GIVEN("A 3x3 adjacency matrix")
	{
		vector<vector<double>> adjacency = { 
			{ 0, 1, 0 }, 
			{ 1, 0, 1 }, 
			{ 0, 1, 0 } 
		};
		KirchhoffMatrix km(adjacency, 3);

		WHEN("Determinant is calculated")
		{
			double determinant = km.CountSpanningTrees();

			THEN("Determinant should be 0 for a singular matrix")
			{
				REQUIRE(determinant == 1.0);
			}
		}
	}
}

SCENARIO("DeterminantByGaussForAlgebraicComplement returns correct determinant for a 2x2 submatrix")
{
	GIVEN("A 2x2 submatrix")
	{
		vector<vector<double>> submatrix = { 
			{ 0, 1 }, 
			{ 1, 0 } 
		};
		KirchhoffMatrix km(submatrix, 2);

		WHEN("Determinant is calculated")
		{
			double determinant = km.CountSpanningTrees();

			THEN("Algebraic complement should be -2 for a 2x2 matrix")
			{
				REQUIRE(determinant == 1);
			}
		}
	}
}


SCENARIO("Testing matrix deeper - using getters")
{
	GIVEN("A 3x3 adjacency matrix")
	{
		vector<vector<double>> adjacency = {
			{ 0, 1, 0 },
			{ 1, 0, 1 },
			{ 0, 1, 0 }
		};

		KirchhoffMatrix km(adjacency, 3);

		WHEN("Determinant is retrieved using getDeterminantByGauss")
		{
			double determinant = km.getDeterminantByGauss();

			THEN("Determinant should be calculated correctly")
			{
				REQUIRE(determinant == 1);
			}
		}

		WHEN("Algebraic complement is retrieved using getDeterminantByGaussForAlgebraicComplement")
		{
			double algebraicComplement = km.getDeterminantByGaussForAlgebraicComplement(0, 0);

			THEN("Algebraic complement should be calculated correctly")
			{
				REQUIRE(algebraicComplement == 1);
			}
		}
	}
}
