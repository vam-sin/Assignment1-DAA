/**
 * \file dcsc.cpp
 * This program is an implementation of the 2003 rsearch paper, A divide-and-conquer 
 * algorithm for identifying strongly connected components. This program works by finding 
 * one strongly connected component, removing that from the graph and then recursively
 * dividing and concurring the graph into smaller and smaller parts. The key selling point
 * of this algorithm is the fact that it can be easily parallelized.
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long int

vector<set<ll>> final_ans;
set<ll> all_nodes;

/**
 * @brief print the graph as an adjacency list. Used primarily for debugging
 * @param adj the adjacency list of the graph
 */
void print_graph(map<ll,set<ll>> &adj){
	for (auto i = adj.begin(); i != adj.end(); i++){
		cout<<i->first<<"->";
		for(auto j = i->second.begin(); j != i->second.end(); j++){
			cout<<(*j)<<" ";
		}
		cout<<endl;
	}
}

/**
 * @brief print all the elements in a given set
 * @param a a set
 */
void print_set(set<ll> &a){
	for(auto i = a.begin(); i != a.end(); i++){
		cout<<(*i)<<" ";
	}
	cout<<endl;
}

/**
 * @brief depth first search on the given graph
 * @param v source/start point
 * @param adj adjacency list of graph
 * @param visited nodes already visited
 */
void DFS(ll v,map<ll, set<ll>> &adj,set<ll> &ans, map<ll, bool> &visited){
	visited[v] = true;
	ans.insert(v);
	auto itr = adj.find(v);
	if(itr != adj.end()){
		set<ll> aux = itr->second;
		for(auto i=aux.begin();i != aux.end();i++){
			if(visited[(*i)] != true && (*i) != v){
				ans.insert((*i));
				DFS((*i),adj,ans, visited);
			}
		}
	}
	else{
		return;
	}
}

/**
 * @brief calculates the descendants of a node, the subset of vertices in G reachable from that point
 * @param adj the adjacency list of the graph
 * @param v the node
 * @return descendents of the node
 */
set<ll> desc(map<ll, set<ll>> &adj,ll v){
	set<ll> ans;
	map<ll, bool> visited;
	DFS(v,adj,ans, visited);
	return ans;
}


/**
 * @brief calculates the predecessors of a node 'v', the subset of vertices from which v is reachable
 * @param adj the adjacency list of the graph
 * @param nodes a set containing all the nodes in the graph
 * @param v the node
 * @return set of predecessors
 */
set<ll> pred(map<ll, set<ll>> &adj, set<ll> &nodes, ll v){
	set<ll> ans;
	for(auto i=nodes.begin();i != nodes.end();i++){
		set<ll> aux = desc(adj,*i);
		auto itr = aux.find(v);
		if(itr != aux.end()){
			ans.insert((*i));
		}
	}
	return ans;
}

/**
 * @brief calculates the intersection of two sets
 * @param a the first set
 * @param b the second set
 * @return the intersection of the sets, another set
 */
set<ll> intersection(set<ll> &a, set<ll> &b){
	set<ll> ans;
	for(auto i = a.begin(); i != a.end(); i++){
		if(b.find(*i) != b.end()++){
			ans.insert(*i);
		}
	}
	return ans;
}

/**
 * @brief calculates the complement of two sets
 * @param a the first set 
 * @param b the second set
 * @return set of elements in a - b
 */
set<ll> slash(set<ll> &a,set<ll> &b){
	set<ll> ret;
	for (auto i = a.begin(); i != a.end(); i++){
		if(b.find(*i) == b.end()++){
			ret.insert(*i);
		}
	}
	return ret;
}

/**
 * @brief calculates the union of two sets
 * @param a the first set 
 * @param b the second set
 * @return set of elements in a + b
 */
set<ll> union_(set<ll> &a,set<ll> &b){
	set<ll> s;
	for (auto i = a.begin(); i != a.end(); ++i){
		s.insert(*i);
	}
	for (auto i = b.begin(); i != b.end(); ++i){
		s.insert(*i);
	}
	return s;
}

/**
 * @brief computes one strongly connected component of the graph
 * @param adj adjacency list of the graph 
 */
void DCSC(map<ll,set<ll>> &adj){	
	if(adj.size() == 0){
		return;
	}	
	else{
		set<ll> aux_nodes;
		for(auto i = adj.begin(); i != adj.end(); i++){
			aux_nodes.insert(i->first);
			for(auto j = i->second.begin(); j != i->second.end(); j++){
				aux_nodes.insert(*j);
			}
		}
		ll random_v = (*aux_nodes.begin());
		set<ll> pre = pred(adj,aux_nodes,random_v);
		set<ll> des = desc(adj,random_v);
 		set<ll> SCC = intersection(pre,des);
 		final_ans.push_back(SCC);
 		set<ll> pred_slash_SCC = slash(pre, SCC);
 		set<ll> des_slash_SCC = slash(des, SCC);
 		set<ll> bla = union_(des, pre);
 		set<ll> rem = slash(aux_nodes, bla);
 		
 		map<ll,set<ll>> new_adj = adj;
 		
 		for (auto i = SCC.begin(); i != SCC.end(); ++i){
 			new_adj.erase(*i);
 			for(auto itr = adj.begin(); itr != adj.end();itr++){
 				auto j = itr->second.find(*i);
 				if(j != itr->second.end()){
 					itr->second.erase(j);
 				}
 			}
 		}

 		map<ll,set<ll>> m1,m2,m3;


 		for (auto i = pred_slash_SCC.begin(); i != pred_slash_SCC.end(); i++){
 			m1[*i] = new_adj[*i];
 		}
 		for(auto i = m1.begin();i!=m1.end();i++){
 			for(auto j = i->second.begin();j!=i->second.end();j++){
 				if(pred_slash_SCC.find(*j) == pred_slash_SCC.end()){
 					m1[i->first].erase(j);
 				}
 			}
 		}
 		for (auto i = des_slash_SCC.begin(); i != des_slash_SCC.end(); i++){
 			m2[*i] = new_adj[*i];
 		}
 		for(auto i = m2.begin();i!=m2.end();i++){
 			for(auto j = i->second.begin();j!=i->second.end();j++){
 				if(des_slash_SCC.find(*j) == des_slash_SCC.end()){
 					m2[i->first].erase(j);
 				}
 			}
 		}
 		for (auto i = rem.begin(); i != rem.end(); i++){
 			m3[*i] = new_adj[*i];
 		}
 		for(auto i = m3.begin();i!=m3.end();i++){
 			for(auto j = i->second.begin();j!=i->second.end();j++){
 				if(rem.find(*j) == rem.end()){
 					m3[i->first].erase(j);
 				}
 			}
 		}
 		DCSC(m1);
 		DCSC(m2);
 		DCSC(m3);
 	}
}

int main(int argc, char** argv){
	auto start = chrono::steady_clock::now();
	map<ll,set<ll>> adj;	
	ll V,E;
	cin >> V >> E;
	ll a,b;

	for (ll i = 0; i < E; ++i){
		cin>>a>>b;
		adj[a].insert(b);
		all_nodes.insert(a);
		all_nodes.insert(b);
	}

	cout<<"[UPDATE] Input complete."<<endl;
	DCSC(adj);
	cout<<"[UPDATE] DCSC complete."<<endl;
	auto end = chrono::steady_clock::now();
	auto calculation_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	cout << "[RESULT] Time taken: " << 1.00 * calculation_time/1000 << endl;
	cout << "[RESULT] Number of SCCs: "<< final_ans.size()<<endl;
	ll max_scc = final_ans[0].size();
	for(ll i = 0; i < final_ans.size();i++){
		if(final_ans[i].size() > max_scc) max_scc = final_ans[i].size();
	}
	cout << "[RESULT] Largest SCC size: " << max_scc << "("<< 1.0 * max_scc/V << ")"<<endl;
	ofstream outfile;
	outfile.open(argv[1], ios::out);
	for(ll i=0;i<final_ans.size();i++){
		for(auto it = final_ans[i].begin(); it!=final_ans[i].end(); it++){
			outfile << *it << " ";	
		}
		outfile << endl;
	}
	return 0;
}