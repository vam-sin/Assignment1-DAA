/**
 * \mainpage
 * The strongly connected component of a directed graph G = (V, E) is defined
 * as a maximal set of vertices C (subset of V) such that for every pair of 
 * vertices u and v in C, we have both u -> v and v -> u; that is, any pair of
 * vertices u and v are reachable from each other. This repo implements two
 * different algorithms to find the strongly connected components of graphs, 
 * runs it on various datasets taken from the SNAP Large Network Datasets and
 * compares the runtimes of both algorithms. 
 */

/**
 * \file traditional_scc.cpp
 * This program works by decomposing a directed graph intp its strongly connected
 * components by running two depth first searches.  G contains the graph and G.T is
 * the transpose of G - a graph with same nodes as G, but with directions reversed.
 * This algorithm works on the principle that both the graph and its transpose
 * have the same connected components (that is, u and v are reachable in G only if 
 * they are reachable in G.T). This is an implementation of the traditional
 * Kosaraju's Linear Time Algorithm that runs in O(V + E) in a graph with V nodes and
 * E edges. 
 */

#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define ll long long int

stack<ll> stck;
vector<vector<ll>> components;
ll num_comp = 0;


/**
 * @brief the first graph traversal (on the original graph)
 * @param adj the adjacency list of the graph
 * @param visited stores the list of nodes already visited/reached
 * @param source start location of the traversal
 */
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

/**
 * @brief the second graph traversal (on the transposed graph)
 * @param adjT the adjacency list of the transposed graph
 * @param visited stores the list of nodes already visited/reached
 * @param source start location of the traversal
 */
void DFS2(map<ll, vector<ll>> adjT, unordered_map<ll, bool>& visited, ll source)
{
	components[num_comp].push_back(source);
	visited[source] = true;
	for(ll j = 0; j < adjT[source].size(); j++)
	{
		if(!visited[adjT[source][j]])
			DFS2(adjT, visited, adjT[source][j]);
	}
}


/**
 * @brief driver code for input, output and running the algorithm. Expects command
 *		  line arguments. 
 * @param argc number of command line arguments
 * @param argv command line arguments list (first argument should be output file name)
 */
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
			components.push_back(tmp);
			DFS2(adjT, visited2, source);
			num_comp++;
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