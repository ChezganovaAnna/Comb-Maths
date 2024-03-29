#pragma once
#include <iostream>
#include <vector>

using arrayOfInt = std::vector<int>;
using Ids = arrayOfInt; //хранит идентификаторы вершин
using Low = arrayOfInt; //хранит информацию о самом низком идентификаторе вершины, к которому можно добраться из данной вершины в рамках текущего обхода.
using OnStack = arrayOfInt; //нужен для отслеживания вершины на стеке в процессе обхода графа
using SCC = arrayOfInt; //хранит идентификаторы вершин компонент сильной связности 
using Graph = std::vector<arrayOfInt>;

void TarjanStronglyConnectedComponents(const Graph& graph);
Graph InvertGraph(const Graph& graph);

void DepthSearch(const Graph& invertedGraph, Ids& nodeIds, Low& lowLink, OnStack& isOnStack, SCC& stronglyConnectedComponents, int& currentId, int& componentCount, int vertex);
//void FindStronglyConnectedComponents(const Graph& invertedGraph, Ids& nodeIds, Low& lowLink, OnStack& isOnStack, SCC& stronglyConnectedComponents);
void PrintGraph(const Graph& graph);