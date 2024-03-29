#include "Tarjan.h"

using namespace std;
//SCC - strongly connected component

void PrintGraph(const Graph& graph)
{
	for (const auto& row : graph)
	{
		for (int val : row)
		{
			cout << val << " ";
		}
		cout << endl;
	}
}

Graph InvertGraph(const Graph& graph)
{
	int numVertices = graph.size();
	Graph invertedGraph(numVertices, vector<int>(numVertices, 0));

	for (int i = 0; i < numVertices; ++i)
	{
		for (int j = 0; j < numVertices; ++j)
		{
			invertedGraph[i][j] = graph[j][i]; 
		}
	}
	return invertedGraph;
}

void DepthSearch(const Graph& invertedGraph, Ids& nodeIds, Low& lowLink, OnStack& isOnStack, SCC& stronglyConnectedComponents, int& currentId, int& componentCount, int vertex)
{
	nodeIds[vertex] = lowLink[vertex] = currentId++;
	isOnStack[vertex] = 1;

	for (int neighbor = 0; neighbor < invertedGraph.size(); ++neighbor)
	{
		if (invertedGraph[vertex][neighbor] == 1)
		{
			if (nodeIds[neighbor] == -1)
			{
				DepthSearch(invertedGraph, nodeIds, lowLink, isOnStack, stronglyConnectedComponents, currentId, componentCount, neighbor);
				lowLink[vertex] = min(lowLink[vertex], lowLink[neighbor]);
			}
			else if (isOnStack[neighbor])
			{
				lowLink[vertex] = min(lowLink[vertex], nodeIds[neighbor]);
			}
		}
	}

	if (nodeIds[vertex] == lowLink[vertex])
	{
		for (int neighbor = 0; neighbor < invertedGraph.size(); ++neighbor)
		{
			if (stronglyConnectedComponents[neighbor] == -1 && nodeIds[neighbor] >= nodeIds[vertex])
			{
				stronglyConnectedComponents[neighbor] = componentCount;
			}
		}
		componentCount++;
	}

	isOnStack[vertex] = 0;
}

void TarjanStronglyConnectedComponents(const Graph& graph)
{
	int numVertices = graph.size();
	Graph invertedGraph = InvertGraph(graph);

	Ids nodeIds(numVertices, -1);
	Low lowLink(numVertices, -1);
	OnStack isOnStack(numVertices, 0);
	SCC stronglyConnectedComponents(numVertices, -1);
	int currentId = 0;
	int componentCount = 0;

	for (int vertex = 0; vertex < numVertices; ++vertex)
	{
		if (nodeIds[vertex] == -1)
		{
			DepthSearch(invertedGraph, nodeIds, lowLink, isOnStack, stronglyConnectedComponents, currentId, componentCount, vertex);
		}
	}

	Graph components(componentCount);
	for (int i = 0; i < numVertices; ++i)
	{
		components[stronglyConnectedComponents[i]].push_back(i);
	}

	for (int i = 0; i < componentCount; ++i)
	{
		cout << "Component " << i << ": ";
		for (int j = 0; j < components[i].size(); ++j)
		{
			cout << components[i][j] << " ";
		}
		cout << endl;
	}
}