#include<bits/stdc++.h>
using namespace std;
#define MAX 1000

/*
Decomposing a directed graph into its strongly connected components by running two 
depth first searches.
Strongly connected component of a directed graph G = (V, E) is a maximal set of vertices
C < V such that for every pair of vertices u and v in C, we have both u -> v and v -> u; 
that is, vertices u and v are reachable from each other.
G and G.T(Transpose, has edges reversed) have the same connected components. 
(u and v are reachable in G only if they are reachable in G.T)
Finishing Time: The finishing time f[v] is the number of nodes discovered or finished before finishing
the expansion of v.
*/
/* Kosaraju's Linear Time Algorithm
O(V + E)
One dfs on G and another on G.T
*/

stack<int> stck;
int component[MAX];
vector<int> components[MAX];
int num_comp;

void DFS1(vector<int> adj[], bool visited[], int source)
{
	visited[source] = true;
	for(int j = 0; j < adj[source].size(); j++)
	{
		if(visited[adj[source][j]] == false)
			DFS1(adj, visited, adj[source][j]);
	}
	stck.push(source);
}

void DFS2(vector<int> adjT[], bool visited[], int source)
{
	cout << source << " ";
	component[source] = num_comp;
	components[num_comp].push_back(source);
	visited[source] = true;
	for(int j = 0; j < adjT[source].size(); j++)
	{
		if(visited[adjT[source][j]] == false)
			DFS2(adjT, visited, adjT[source][j]);
	}
}

void addEdge(vector<int> adj[], int u, int v)
{
	// u -> v
	adj[u].push_back(v);
}

int main()
{
	int V, E;
	cin >> V >> E;
	// Adjacency list for G and G.T
	vector<int> adj[V], adjT[V];
	for(int i = 0; i < E; i++)
	{
		int m, n;
		cin >> m >> n;
		// To get Transpose, do addEdje(adj, n, m);
		addEdge(adj, m, n);
		addEdge(adjT, n, m);
	}
	bool visited[V] = {false};

	// DFS on G
	DFS1(adj, visited, 0);

	for(int i=0;i<V;i++)
		visited[i] = false;

	// DFS on G.T
	while(!stck.empty())
	{
		int source = stck.top();
		stck.pop();
		if(visited[source] == false)
		{
			cout << "Component " << num_comp << ": ";
			DFS2(adjT, visited, source);
			num_comp++;
			cout << endl;
		}
	}
}