#include <bits/stdc++.h>
using namespace std;
#define ll long long int

vector<set<ll>> final_ans;
map<ll,bool> visited;
set<ll> all_nodes;

void print_graph(map<ll,set<ll>> &adj){
	for (auto i = adj.begin(); i != adj.end(); i++){
		cout<<i->first<<"->";
		for(auto j = i->second.begin(); j != i->second.end(); j++){
			cout<<(*j)<<" ";
		}
		cout<<endl;
	}
}

void print_set(set<ll> &a){
	for(auto i = a.begin(); i != a.end(); i++){
		cout<<(*i)<<" ";
	}
	cout<<endl;
}

void DFS(ll v,map<ll, set<ll>> &adj,set<ll> &ans){
	cout<<"In DFS | Node: "<<v<<endl;
	visited[v] = true;
	ans.insert(v);
	auto itr = adj.find(v);
	if(itr != adj.end()){
		set<ll> aux = itr->second;
		for(auto i=aux.begin();i != aux.end();i++){
			if(visited[(*i)] != true && (*i) != v){
				ans.insert((*i));
				DFS((*i),adj,ans);
			}
		}
	}
	else{
		cout<<"Returning from DFS"<<endl;
		visited.clear();
		return;
	}
}

set<ll> desc(map<ll, set<ll>> &adj,ll v){
	set<ll> ans;
	cout<<"In desc for node : "<<v<<endl;
	DFS(v,adj,ans);
	cout<<"Graph gotten: "<<endl;
	print_graph(adj);
	cout<<"Desc for "<<v<<" : ";
	print_set(ans);
	cout<<"Size of ans. Im in desc : "<<ans.size()<<endl;
	return ans;
}

set<ll> pred(map<ll, set<ll>> &adj, set<ll> &nodes, ll v){
	set<ll> ans;
	cout<<"In pred for node "<<v<<endl;
	for(auto i=nodes.begin();i != nodes.end();i++){
		set<ll> aux = desc(adj,*i);
		auto itr = aux.find(v);
		if(itr != aux.end()){
			ans.insert((*i));
		}
	}
	cout<<"Graph gotten: "<<endl;
	print_graph(adj);
	cout<<"Pred for "<<v<<" : ";
	print_set(ans);
	return ans;
}

set<ll> intersection(set<ll> &a, set<ll> &b){
	set<ll> ans;
	for(auto i = a.begin(); i != a.end(); i++){
		if(b.find(*i) != b.end()++){
			ans.insert(*i);
		}
	}
	return ans;
}

set<ll> slash(set<ll> &a,set<ll> &b){
	set<ll> ret;
	for (auto i = a.begin(); i != a.end(); i++){
		if(b.find(*i) == b.end()++){
			ret.insert(*i);
		}
	}
	return ret;
}

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

void DCSC(ll E, map<ll,set<ll>> &adj, char *filename){

	cout<<"Number of edges in current itr: "<<adj.size()<<endl;
	cout<<"These:"<<endl;
	print_graph(adj);
	
	if(adj.size() == 0){
		cout<<"Bro E = 0"<<endl;
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
 		set<ll> pred_slash_SCC = slash(pre,SCC);
 		set<ll> des_slash_SCC = slash(des,SCC);
 		set<ll> bla = union_(des,pre);
 		set<ll> rem = slash(aux_nodes,bla);
 		map<ll,set<ll>> new_adj = adj;
 		for (auto i = SCC.begin(); i != SCC.end(); ++i){
 			new_adj.erase(*i);
 			for(auto itr = adj.begin(); itr != adj.end();itr++){
 				auto j = find(itr->second.begin(), itr->second.end(), *i);
 				if(j != itr->second.end()){
 					itr->second.erase(j);
 				}
 			}
 		}
 		// cout<<"New graph done"<<endl;

 		map<ll,set<ll>> m1,m2,m3;


 		for (auto i = pred_slash_SCC.begin(); i != pred_slash_SCC.end(); i++){
 			m1[*i] = new_adj[*i];
 		}
 		// cout<<"Size of m1: "<<m1.size()<<endl;
 		for (auto i = des_slash_SCC.begin(); i != des_slash_SCC.end(); i++){
 			m2[*i] = new_adj[*i];
 		}
 		// cout<<"Size of m2: "<<m2.size()<<endl;
 		for (auto i = rem.begin(); i != rem.end(); i++){
 			m3[*i] = new_adj[*i];
 		}
 		// cout<<"Size of m3: "<<m3.size()<<endl;

 		DCSC(new_adj.size(), m1, filename);
 		DCSC(new_adj.size(), m2, filename);
 		DCSC(new_adj.size(), m3, filename);
 	}
}

int main(int argc, char** argv){
	char *filename = argv[1];
	map<ll,set<ll>> adj;
	
	ll V,E;
	cin >> V >> E;
	ll a,b;
	cout<<"Input started..."<<endl;

	for (ll i = 0; i < E; ++i){
		cin>>a>>b;
		adj[a].insert(b);
		all_nodes.insert(a);
		all_nodes.insert(b);
	}

	cout<<"Init graph gotten:"<<endl;
	print_graph(adj);
	
	// cout<<"All nodes:";
	// print_set(all_nodes);
	// DCSC(E,adj,filename);

	// // cout<<"I returned wtf"<<endl;
	// for (ll i = 0; i < final_ans.size(); ++i){
	// 	cout<<i<<" | ";
	// 	for(auto j = final_ans[i].begin(); j != final_ans[i].end(); j++){
	// 		cout<<(*j)<<" ";
	// 	}
	// 	cout<<"\nSize of this SCC: "<<final_ans[i].size()<<endl;
	// }

	// cout<<"Number of nodes in graph: "<<adj.size()<<endl;
	// cout<<"Number of SCCs: "<<final_ans.size()<<endl;
	return 0;
}