#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

const int SIZE = 6;

inline double prob() { return (rand() % 100) / 100.0; }

class Graph
{
public:
	Graph(double n, int range);
	vector<vector<int>> getMatrix(){ return matrix; }
	int V() { return SIZE * SIZE; };
	int E() { return (SIZE * (SIZE - 1)) / 2; }
	bool adjacent(int x, int y);
	void neighbors(int x);
	void add(int x, int y);
	void del(int x, int y) { matrix[x][y] = matrix[y][x] = 0; }
	int get_edge_value(int x, int y) { return matrix[x][y]; }
	void set_edge_value(int x, int y, int v) { matrix[x][y] = matrix[y][x] = v; }
	void print();
	bool is_connected();

private:
	vector<vector<int>> matrix;
};

class queue_element{
public:
	queue_element(int n = 0, int u = 0) :node(n), cost(u) {}
	int node;
	int cost;
};

class PriorityQueue
{
public:
	void print();
	void chgPriority(int node);
	queue_element minPriority();
	bool contains(int q);
	void insert(int q, int c) { x.insert(x.begin(), queue_element(q, c)); };
	queue_element top() { return x[0]; };
	int size() { return x.size(); };

private:
	vector<queue_element> x;
};

class ShortestPath
{
public:
	ShortestPath(Graph g) :graph(g) {}
	void vertices();
	void path(int u, int w);
	int path_size(int u, int w);
private:
	Graph graph;
	vector<vector<int>> matrix = graph.getMatrix();
};

void ShortestPath::path(int u, int w){
	int old_size = 0, c_size = 0, total_cost = 0;
	vector<bool> close(SIZE, false);
	PriorityQueue q;
	q.insert(u, total_cost);
	while (q.size() != 0){
		queue_element temp = q.minPriority();
		for (int i = 0; i < SIZE; ++i){
			if (matrix[temp.node][i]){
				q.insert(i, total_cost + temp.cost);
			}
		}
	}
}

void ShortestPath::vertices(){
	for (int i = 0; i < SIZE; ++i){
		graph.neighbors(i);
		cout << endl;
	}
	cout << endl;
}

void PriorityQueue::chgPriority(int n) {
	vector<queue_element> temp = x;
	for (int i = 1; i < x.size(); ++i) {
		x[i] = temp.at(i - 1);
	}
	x[0].node = n;
}

void PriorityQueue::print() {
	for (int i = 0; i < x.size(); ++i) {
		cout << x[i].node << ", ";
	}
	cout << endl;
}

queue_element PriorityQueue::minPriority() {
	queue_element temp = x.front();
	x.front() = move(x.back());
	x.pop_back();
	return temp;
}

bool PriorityQueue::contains(int n) {
	for (int i = 0; i < x.size(); ++i) {
		if (x[i].node == n) {
			return true;
		}
	}
	return false;
}

Graph::Graph(double n, int range)
{

	for (int i = 0; i < SIZE; ++i)
	{
		vector<int> y;
		for (int j = 0; j < SIZE; ++j)
		{
			y.push_back(0);
		}
		matrix.push_back(y);
	}

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = i; j < SIZE; ++j)
		{
			if (i == j)
				matrix[i][j] = 0;
			else
			{
				if (prob() < n)
					matrix[i][j] = matrix[j][i] = (rand() % range) + 1;
				else
					matrix[i][j] = matrix[i][j] = 0;
			}
		}
	}
}

bool Graph::adjacent(int x, int y)
{
	int old_size = 0, c_size = 0;
	vector<bool> close(SIZE);
	vector<bool> open(SIZE);
	if (matrix[x][y])
	{
		return true;
	}
	for (int i = 0; i < SIZE; ++i)
	{
		open[i] = close[i] = false;
	}
	open[x] = true;
	while (c_size < SIZE) {
		for (int i = 0; i < SIZE; ++i)
		{
			old_size = c_size;
			if (open[i] && (close[i] == false))
			{
				close[i] = true;
				c_size++;
			}
			for (int j = 0; j < SIZE; ++j) {
				if (open[i]) {
					open[j] = open[j] || matrix[i][j];
				}
			}
		}
		if (open[y] == true)
			return true;
		if (old_size == c_size)
			return false;
	}
}

void Graph::neighbors(int x) {
	int old_size = 0, c_size = 0;
	vector<bool> close(SIZE);
	vector<bool> open(SIZE);
	for (int i = 0; i < SIZE; ++i)
	{
		open[i] = close[i] = false;
	}
	open[x] = true;
	while (c_size < SIZE) {
		for (int i = 0; i < SIZE; ++i)
		{
			old_size = c_size;
			if (open[i] && (close[i] == false))
			{
				close[i] = true;
				c_size++;
			}
			for (int j = 0; j < SIZE; ++j) {
				if (open[i]) {
					open[j] = open[j] || matrix[i][j];
				}
			}
		}
		if (c_size == SIZE || old_size == c_size) {
			for (int i = 0; i < SIZE; ++i) {
				if (open[i])
					cout << i << ", ";
			}
			return;
		}
	}
	cout << endl;
}

void Graph::add(int x, int y) {
	if (!matrix[x][y])
		matrix[x][y] = matrix[y][x] = 1;
}



void Graph::print()
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			cout << matrix[i][j] << ", ";
		}
		cout << endl;
	}
}

bool Graph::is_connected()
{
	int old_size = 0, c_size = 0;
	vector<bool> close(SIZE);
	vector<bool> open(SIZE);
	for (int i = 0; i < SIZE; ++i)
	{
		open[i] = close[i] = false;
	}
	open[0] = true;
	while (c_size < SIZE) {
		for (int i = 0; i < SIZE; ++i)
		{
			old_size = c_size;
			if (open[i] && (close[i] == false))
			{
				close[i] = true;
				c_size++;
			}
			for (int j = 0; j < SIZE; ++j)
			{
				open[j] = open[j] || matrix[i][j];
			}
		}
		if (SIZE == c_size)
			return true;
		if (c_size == old_size)
			return false;
	}
}

int main()
{
	srand(time(0));
	Graph a(0.1, 5);
	a.print();

	// if (a.adjacent(0, 3))
		// cout << "yes" << endl;
	// else
		// cout << "no" << endl;

	// a.neighbors(1);
	// cout << endl;

	// PriorityQueue q;
	// q.print();
	// for (int i = 0; i < SIZE; ++i) {
		// q.chgPriority(i);
	// }
	// q.print();
	// q.minPrioirty();
	// q.print();
	
	cout << endl;
	ShortestPath d(a);
	d.vertices();
	d.path(0, 1);
}