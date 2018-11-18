#pragma once
#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2DynArray.h"
#include "p2PQueue.h"
#include "p2Point.h"
#include "j1Module.h"
#define COST_MAP 100
struct NodeList;
struct Node
{
	Node();
	Node(int g, int h, iPoint position, Node*parent);

	int g;
	int h;
	iPoint position;
	Node* parent;
	int DataTile();
	void FillNeigborhs(NodeList &list);
	void CalculateF(const iPoint &destination);
};
struct NodeList
{
	p2List<Node> node_list;
	p2List_item<Node>* GetLowerNode()const;
	p2List_item<Node>* Find(const iPoint & index)const;
};
class j1Astar
{
public:
	j1Astar();
	~j1Astar();
	void ResetPath();
	void Path(int x, int y);

	void PropagateAstar(iPoint destination);
	p2DynArray<iPoint> *GenerateAstar(iPoint origin, iPoint destination);
	int VisitedPos(iPoint curr);
	int MovementCost(int x, int y) const;
private:
	p2PQueue<iPoint>	frontier;
	p2List<iPoint>		visited;
	p2List<iPoint>		breadcrumbs;
	uint				cost_so_far[COST_MAP][COST_MAP];
	uint				h_distance[COST_MAP][COST_MAP];
	p2DynArray<iPoint>	path;
};