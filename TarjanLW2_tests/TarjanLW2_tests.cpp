#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../TarjanLW2/Tarjan.h"
#include <iostream>
#include <vector>

SCENARIO("Graph Inversion Tests")
{
	GIVEN("A bidirectional graph")
	{
		Graph graph = {
			{ 0, 1, 0, 0 },
			{ 1, 0, 1, 0 },
			{ 0, 1, 0, 1 },
			{ 0, 0, 1, 0 }
		};

		WHEN("Inverting the graph")
		{
			Graph inverted = InvertGraph(graph);

			THEN("The inverted graph should be the same as the original graph")
			{
				REQUIRE(inverted == graph);
			}
		}
	}

	GIVEN("A unidirectional graph")
	{
		Graph graph = {
			{ 0, 1, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 },
			{ 1, 0, 1, 0 }
		};

		WHEN("Inverting the graph")
		{
			Graph inverted = InvertGraph(graph);

			THEN("The inverted graph should have reversed edges")
			{
				Graph expected = {
					{ 0, 0, 0, 1 },
					{ 1, 0, 0, 0 },
					{ 0, 1, 0, 1 },
					{ 0, 0, 1, 0 }
				};

				REQUIRE(inverted == expected);
			}
		}
	}
}


TEST_CASE("DepthSearch function test ")
{
	SECTION("Compare exit paths from vertices during dfs for common graph")
	{
		Graph invertedGraph1 = {
			{ 0, 1, 0 },
			{ 1, 0, 1 },
			{ 0, 1, 0 }
		};

		Ids nodeIds1(3, -1);
		Low lowLink1(3, -1);
		OnStack isOnStack1(3, 0);
		SCC stronglyConnectedComponents1(3, -1);
		int currentId1 = 0;
		int componentCount1 = 0;
		int vertex1 = 0;

		DepthSearch(invertedGraph1, nodeIds1, lowLink1, isOnStack1, stronglyConnectedComponents1, currentId1, componentCount1, vertex1);

		REQUIRE(nodeIds1 == std::vector<int>{ 0, 1, 2 });

		std::vector<int> expectedExitOrder1 = { 0, 1, 2 };
		std::vector<int> actualExitOrder1;

		for (int i = 0; i < nodeIds1.size(); ++i)
		{
			actualExitOrder1.push_back(nodeIds1[i]);
		}

		REQUIRE(expectedExitOrder1 == actualExitOrder1);
	}

	SECTION("Compare exit paths from vertices during dfs for in an oriented graph  ")
	{
		Graph invertedGraph2 = {
			{ 0, 1, 0, 0, 1 },
			{ 1, 0, 1, 0, 0 },
			{ 0, 1, 0, 1, 0 },
			{ 0, 0, 1, 0, 1 },
			{ 1, 0, 0, 1, 0 }
		};

		Ids nodeIds2(5, -1);
		Low lowLink2(5, -1);
		OnStack isOnStack2(5, 0);
		SCC stronglyConnectedComponents2(5, -1);
		int currentId2 = 0;
		int componentCount2 = 0;
		int vertex2 = 0;

		DepthSearch(invertedGraph2, nodeIds2, lowLink2, isOnStack2, stronglyConnectedComponents2, currentId2, componentCount2, vertex2);

		REQUIRE(nodeIds2 == std::vector<int>{ 0, 1, 2, 3, 4 });

		std::vector<int> expectedExitOrder2 = { 0, 1, 2, 3, 4 };
		std::vector<int> actualExitOrder2;

		for (int i = 0; i < nodeIds2.size(); ++i)
		{
			actualExitOrder2.push_back(nodeIds2[i]);
		}

		REQUIRE(expectedExitOrder2 == actualExitOrder2);
	}
}


TEST_CASE("Tarjan's SCC Test - Combined Scenario")
{
	SECTION("Graph 0")
	{
		Graph graph = {
			{ 0, 1, 0, 0 },
			{ 1, 0, 1, 0 },
			{ 0, 1, 0, 1 },
			{ 0, 0, 1, 0 }
		};

		std::stringstream buffer;
		std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

		TarjanStronglyConnectedComponents(graph);

		std::string output0 = buffer.str();
		std::string expectedOutput0 = "Component 0: 0 1 2 3 \n";

		REQUIRE(output0 == expectedOutput0);

		std::cout.rdbuf(old);
	}

	SECTION("Graph 1")
	{
		Graph adjacencyMatrix = {
			{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0, 0, 0, 1, 1, 1 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }
		};

		std::stringstream buffer;
		std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

		TarjanStronglyConnectedComponents(adjacencyMatrix);

		std::string output1 = buffer.str();
		std::string expectedOutput1 = "Component 0: 0 5 \nComponent 1: 1 \nComponent 2: 2 \nComponent 3: 6 \nComponent 4: 3 4 \nComponent 5: 7 \nComponent 6: 8 9 \n";

		REQUIRE(output1 == expectedOutput1);

		std::cout.rdbuf(old);
	}

	SECTION("Empty Graph")
	{
		Graph emptyGraph = {};

		std::stringstream buffer;
		std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

		TarjanStronglyConnectedComponents(emptyGraph);

		std::string output2 = buffer.str();
		std::string expectedOutput2 = "";

		REQUIRE(output2 == expectedOutput2);

		std::cout.rdbuf(old); 
	}
}
