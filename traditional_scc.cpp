#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define ll long long int

/*
Decomposing a directed graph llo its strongly connected components by running two 
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

stack<ll> stck;
vector<vector<ll>> components;
ll num_comp = 0;

void DFS1(map<ll, vector<ll>> adj, unordered_map<ll, bool>& visited, ll source)
{
	visited[source] = true;
	if(!adj[source].empty()){
		for(ll j = 0; j < adj[source].size(); j++){
		if(visited[adj[source][j]] == false)
			DFS1(adj, visited, adj[source][j]);
		}
	}
	stck.push(source);
}

void DFS2(map<ll, vector<ll>> adjT, unordered_map<ll, bool>& visited, ll source)
{
	// cout << source << " ";
	components[num_comp].push_back(source);
	visited[source] = true;
	for(ll j = 0; j < adjT[source].size(); j++)
	{
		if(!visited[adjT[source][j]])
			DFS2(adjT, visited, adjT[source][j]);
	}
}

int main(int argc, char** argv)
{
	auto start = chrono::steady_clock::now();
	ll V, E;
	cin >> V >> E;
	cout << "Nodes: " << V << ". Edges: "<< E <<endl;
	
	// Adjacency list for G and G.T
	map<ll, vector<ll>> adj, adjT;
	map<ll, bool> nodes;
	for(ll i = 0; i < E; i++)
	{
		ll m, n;
		cin >> m >> n;
		adj[m].push_back(n);
		adjT[n].push_back(m);
		nodes[m] = true;
		nodes[n] = true;
	}
	cout<<"[UPDATE] Input complete. " << endl;
	unordered_map<ll, bool> visited;

	// DFS on G
	for(auto it = nodes.begin(); it != nodes.end();++it){
		if(!visited[it->first]){
			DFS1(adj, visited, it->first);
		}
	}
	unordered_map<ll, bool> visited2;
	cout<<"[UPDATE] DFS 1 complete. " << endl;

	// DFS on G.T
	while(!stck.empty())
	{
		ll source = stck.top();
		stck.pop();
		vector<ll> tmp;
		if(!visited2[source])
		{
			// cout << "Component " << num_comp << ": ";
			components.push_back(tmp);
			DFS2(adjT, visited2, source);
			num_comp++;
			// cout << endl;
		}
	}
	cout<<"[UPDATE] DFS 2 complete." << endl;
	auto end = chrono::steady_clock::now();
	auto calculation_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	cout << "[RESULT] Time taken: " << 1.00 * calculation_time/1000 << endl;
	cout << "[RESULT] Number of SCCs: " << components.size() << endl;
	ll max_scc = components[0].size();
	for(ll i = 0; i < components.size();i++){
		if(components[i].size() > max_scc) max_scc = components[i].size();
	}
	cout << "[RESULT] Largest SCC size: " << max_scc << "("<< 1.0 * max_scc/V << ")"<<endl;
	ofstream outfile;
	outfile.open(argv[1], ios::out);
	for(ll i=0;i<components.size();i++){
		for(ll j = 0;j<components[i].size();j++){
			outfile << components[i][j] << " ";
		}
		outfile << endl;
	}
	return 0;
}