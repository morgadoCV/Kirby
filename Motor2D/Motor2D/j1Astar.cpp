#include "j1Astar.h"
#include "j1Map.h"
#include "p2Point.h"
#include "j1App.h"
j1Astar::j1Astar()
{
}
j1Astar::~j1Astar()
{
}
void j1Astar::ResetPath()
{
	frontier.Clear();
	visited.clear();
	breadcrumbs.clear();
	frontier.Push(iPoint(19, 4), 0);
	visited.add(iPoint(19, 4));
	breadcrumbs.add(iPoint(19, 4));
	memset(cost_so_far, 0, sizeof(uint) * COST_MAP * COST_MAP);
}
void j1Astar::Path(int x, int y)
{
	path.Clear();
	iPoint goal = App->map->WorldToMap(x, y);
	iPoint curr = goal;
	int pos = 0;
	while (curr != visited.start->data)
	{
		path.PushBack(curr);
		pos = visited.find(curr);
		curr = breadcrumbs.At(pos)->data;
		if (curr == visited.start->data)
			path.PushBack(curr);
	}
}
void j1Astar::PropagateAstar(iPoint destination)
{
	// TODO 3: Taking BFS as a reference, implement the Dijkstra algorithm
	// use the 2 dimensional array "cost_so_far" to track the accumulated costs
	// on each cell (is already reset to 0 automatically)
	iPoint curr;
	int distance = 0;
	int priority = 0;
	if (frontier.Pop(curr))
	{
		iPoint neighbors[4];
		neighbors[0].create(curr.x + 1, curr.y + 0);
		neighbors[1].create(curr.x + 0, curr.y + 1);
		neighbors[2].create(curr.x - 1, curr.y + 0);
		neighbors[3].create(curr.x + 0, curr.y - 1);
		for (uint i = 0; i < 4; ++i)
		{
			if (MovementCost(neighbors[i].x, neighbors[i].y) >= 0)
			{
				if (visited.find(neighbors[i]) == -1)
				{
					priority = cost_so_far[neighbors[i].x][neighbors[i].y] = cost_so_far[curr.x][curr.y] + MovementCost(curr.x, curr.y);
					distance = h_distance[neighbors[i].x][neighbors[i].y] = abs(neighbors[i].x - destination.x) + abs(neighbors[i].y - destination.y);
					frontier.Push(neighbors[i], distance + priority);
					visited.add(neighbors[i]);
					breadcrumbs.add(curr);
				}
			}
		}
	}
}
p2DynArray<iPoint> * j1Astar::GenerateAstar(iPoint origin, iPoint destination)
{
	iPoint map_origin = App->map->WorldToMap(origin.x, origin.y);
	iPoint map_destination = App->map->WorldToMap(destination.x, destination.y);
	if (!App->map->IsWalkable(map_origin) && !App->map->IsWalkable(map_destination))
	{
		return nullptr;
	}
	NodeList close;
	NodeList open;
	open.node_list.add(Node(0, map_origin.DistanceManhattan(map_destination), map_origin, nullptr));

	while (open.node_list.count != 0)
	{
		close.node_list.add(open.GetLowerNode()->data);
		open.node_list.del(open.GetLowerNode());
		if (close.node_list.end->data.position == map_destination)
		{
			p2DynArray<iPoint>* positions;

			for (p2List_item<Node>* iterator = close.node_list.end; iterator->data.parent != nullptr; iterator = close.Find(iterator->data.parent->position))
			{
				positions->PushBack(iterator->data.position);
			}
			positions->PushBack(close.node_list.start->data.position);
			positions->Flip();
			return positions;
		}
		else
		{
			NodeList neigborhs;
			close.node_list.end->data.FillNeigborhs(neigborhs);

			for (p2List_item<Node>* iterator = neigborhs.node_list.start; iterator != NULL; iterator = iterator->next)
			{
				if (close.Find(iterator->data.position))
				{
					continue;
				}
				else if (open.Find(iterator->data.position))
				{
					Node tmp = open.Find(iterator->data.position)->data;
					iterator->data.CalculateF(map_destination);
					if (tmp.g > iterator->data.g)
					{
						tmp.parent = iterator->data.parent;
					}
				}
				else
				{
					iterator->data.CalculateF(map_destination);
					open.node_list.add(iterator->data);
				}
			}
			neigborhs.node_list.clear();
		}
	}
	return nullptr;
}
int j1Astar::VisitedPos(iPoint curr)
{
	int visit;
	visit = visited.find(curr);
	return visit;
}
int j1Astar::MovementCost(int x, int y) const
{
	int ret = -1;
	if (x >= 0 && x < App->map->mapdata.width && y >= 0 && y < App->map->mapdata.height)
	{
		int id = App->map->mapdata.layers.start->next->data->Get(x, y);
		if (id == 0)
			ret = 3;
		else
			ret = 1;
	}
	return ret;
}
p2List_item<Node>* NodeList::GetLowerNode() const
{
	p2List_item<Node>* iterator = node_list.start;
	p2List_item<Node>* tmp = nullptr;
	int min_value = 9999;
	while (iterator)
	{
		if (iterator->data.DataTile() < min_value)
		{
			min_value = iterator->data.DataTile();
			tmp = iterator;
		}
		iterator = iterator->next;
	}
	return tmp;
}
p2List_item<Node>* NodeList::Find(const iPoint & index) const
{
	p2List_item<Node>* iterator = node_list.start;

	while (iterator)
	{
		if (iterator->data.position == index)
		{
			return iterator;
		}
		iterator = iterator->next;
	}
	return nullptr;
}
void Node::FillNeigborhs(NodeList & list)
{
	iPoint neighbors[4];
	neighbors[0].create(position.x + 1, position.y + 0);
	neighbors[1].create(position.x + 0, position.y + 1);
	neighbors[2].create(position.x - 1, position.y + 0);
	neighbors[3].create(position.x + 0, position.y - 1);

	for (int i = 0; i < 4; i++)
	{
		if (App->map->IsWalkable(neighbors[i]))
		{
			list.node_list.add(Node(0, 0, neighbors[i], this));
		}
	}
}
void Node::CalculateF(const iPoint & destination)
{
	g = parent->g + 1;
	h = position.DistanceManhattan(destination);
}
int Node::DataTile()
{
	return g + h;
}
