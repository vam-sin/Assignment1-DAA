#include<bits/stdc++.h>
using namespace std;

/*
Time Complexity: O(VlogE)
n = |V|
m = |E|
(i, j) belongs to E if edge from i to j.
Desc(G, v), is the subset of vertices in G that are reachable from v.
Pred(G, v), is the subset of vertices from which v is reachable.
The set of vertices that is neither reachable from v nor reach v is
called the remainder, denoted by Rem(G, v) = V \ (Desc(G, v) ∪ P red(G, v)).
*/

void addEdge(vector<int> adj[], int u, int v)
{
	// u -> v
	adj[u].push_back(v);
}

void DFS(vector<int> adj[], bool visited[], int source, int start, vector<int> Desc[])
{
	visited[source] = true;
	for(int j = 0; j < adj[source].size(); j++)
	{
		if(visited[adj[source][j]] == false)
		{
			Desc[start].push_back(adj[source][j]);
			DFS(adj, visited, adj[source][j], start, Desc);
		}
	}
}

void desc(vector<int> adj[], int v, int V, vector<int> Desc[])
{
	// v is pivot, V is the number of vertices
	Desc[v].push_back(v);
	bool visited[V] = {false};
	DFS(adj, visited, v, v, Desc);
}

vector<int> intersection(vector<int> A, vector<int> B, int V)
{
	vector<int> inter;
	for(int i=0;i<V;i++)
	{
		if((find(A.begin(), A.end(), i) != A.end()) && (find(B.begin(), B.end(), i) != B.end()))
			inter.push_back(i);
	}

	return inter;
}

vector<int> slash(vector<int> A, vector<int> B)
{
	// A\B
	for(int i=0;i<A.size();i++)
	{
		if(find(B.begin(), B.end(), A[i]) != B.end())
			remove(A.begin(), A.end(), i); 
	}

	return A;
}

int main()
{
	int V, E;
	vector<int> Desc[V], Pred[V], Rem[V];
	cin >> V >> E;
	// Adjacency list for G
	vector<int> adj[V];
	for(int i = 0; i < E; i++)
	{
		int m, n;
		cin >> m >> n;
		addEdge(adj, m, n);
	}

	// Make Desc
	for(int i = 0; i < V; i++)
	{
		desc(adj, i, V, Desc);
	}

	// Make Pred
	for(int i = 0; i < V; i++)
	{
		for(auto t=Desc[i].begin(); t!=Desc[i].end(); ++t)
		{
			Pred[*t].push_back(i);
		}
	}

	// Make Rem
	for(int j=0;j<V;j++)
	{
		for(int i=0;i<V;i++)
		{
			if(!(find(Desc[i].begin(), Desc[i].end(), i) != Desc[i].end()) && !(find(Pred[i].begin(), Pred[i].end(), i) != Pred[i].end()))
				Rem[j].push_back(i);
		}
	}

	// // // Printing Outputs
	// // Pred
	// for(int i = 0; i < V; i++)
	// {
	// 	for(auto t=Pred[i].begin(); t!=Pred[i].end(); ++t)
	// 	{
	// 		cout << *t;
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;

	// // Desc
	// for(int i = 0; i < V; i++)
	// {
	// 	for(auto t=Desc[i].begin(); t!=Desc[i].end(); ++t)
	// 	{
	// 		cout << *t;
	// 	}
	// 	cout << endl;
	// }

	// cout << endl;
	// // Rem
	// for(int i = 0; i < V; i++)
	// {
	// 	for(auto t=Rem[i].begin(); t!=Rem[i].end(); ++t)
	// 	{
	// 		cout << *t;
	// 	}
	// 	cout << endl;
	// }
}