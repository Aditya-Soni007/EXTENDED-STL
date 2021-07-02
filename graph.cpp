#include <bits/stdc++.h>
using namespace std;
/*
				QUICK TUTORIAL TO SOME USEFUL BUT LESS USED STL THINGS
				-------------------------------------------------
	std::tuple<int,float,string> tup;
	tup=make_tuple(1,1.0,"a");
	cout<<get<0>(tup)...and so on;
___________________________________________________________________________
	
	partial_sum(first, last, b, myfun);
	first, last : first and last element of range 
              	  whose elements are to be added
	b : index of array where  corresponding partial 
    	sum will be stored;
	myfun : a user defined function for performing 
        	any specific task

____________________________________________________________________________
	accumulate(first,last,starting_sum,my_func);

	(i) It returns an integer value which is the sum of the range provided
		from starting sum
___________________________________________________________________________

	iota(first,last, initial_value);
	 used to initialize a container with contigous values
__________________________________________________________________________

	lower_bound(first,last,val); : acts as proper ceil
	upper_bound(first,last,val); :acts as extended ceil
__________________________________________________________________________

*/
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795

#define IOS ios_base::sync_with_stdio(false),cin.tie(NULL)
#define READ freopen("input.txt", "r", stdin)
#define ERROR freopen("error.txt", "w", stderr) 
#define OUTPUT freopen("output.txt", "w", stdout) 
#define debug(x) cout <<'>'<<#x<<':'<< x<<"\n";
#define debug2(x, y) cout<<'>'<<#x<<':'<<x<<","<<#y<<':'<<y<<"\n"

#define endl '\n'
#define MP make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(),(x).end()
#define FOR(i,from,to) for(int i = from ; i<to ; i++)
#define RFOR(i,from,to) for(int i=from ; i>=to ; i--)

typedef long long ll;
typedef vector<int> VI;
typedef vector<ll> VLL;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef pair<string,int> PSI;
typedef pair<int,string> PIS;
typedef vector< vector<int> > graph;
typedef vector< vector<PII> > Wgraph;
	void oGraph(graph &G)
	{	cout<<"----------------------------------------\n";
		int itr{0};
		for(auto &i: G)
		{
			cout<<itr<<"|->";
			for(auto &j: i)
			{
				cout<<j<<"->";
			}
			cout<<"#"<<endl;
			itr++;
		}
		cout<<"----------------------------------------\n";

	}
	void iDirectedGraph(int V,int E,graph &G)
	{
		auto add_edge=[&G](auto &from,auto &to){
				G.at(from).emplace_back(to);
		};
		while(E--)
		{
			int from,to;
			cin>>from>>to;
			add_edge(from,to);
		}
	}
	void iUndirectedGraph(int V,int E,graph &G)
	{
		auto add_edge=[&G](auto &from,auto &to){
				G.at(from).emplace_back(to);
				G.at(to).emplace_back(from);

		};
		while(E--)
		{
			int from,to;
			cin>>from>>to;
			add_edge(from,to);
		}
	}
	void oWgraph(Wgraph &G)
	{	cout<<"----------------------------------------\n";

		int itr{0};
		for(auto &i: G)
		{
			cout<<itr<<"|-> ";
			for(auto &j: i)
			{
				cout<<j.first<<"("<<j.second<<")"<<"-> ";
			}
			cout<<"#"<<endl;
			itr++;
		}
		cout<<"----------------------------------------\n";

	}
	void iDirectedWGraph(int V,int E,Wgraph &G)
	{
		auto add_edge=[&G](auto &from,auto &to,auto &weight){
				G.at(from).push_back({to,weight});

		};
		while(E--)
		{
			int from,to,weight;
			cin>>from>>to>>weight;
			add_edge(from,to,weight);
		}
	}
	void iUndirectedWGraph(int V,int E,Wgraph &G)
	{
		auto add_edge=[&G](auto &from,auto &to,auto &weight){
				G.at(from).push_back({to,weight});
				G.at(to).push_back({from,weight});

		};
		while(E--)
		{
			int from,to,weight;
			cin>>from>>to>>weight;
			add_edge(from,to,weight);
		}
	}
	auto BFS_utility(graph &G,vector<bool> &visited,int s,vector<int> &res)
	{	
		queue<int> q;
		q.push(s);
		visited[s]=true;
		while(!q.empty())
		{
			int sz= q.size();
				res.emplace_back(q.front());
				for(auto &j: G[q.front()])
				{
					if(visited[j]==false)
					{
						q.push(j);
						visited[j]=true;
					}
				}
				q.pop();
		}
		return res;

	}
	auto BFS(graph &G)
	{	int c{0};
		vector<int> res;
		vector<bool> visited(G.size(),false);
		for(int i=0;i<G.size();i++)
		{
			if(visited[i]==false)
			{
				BFS_utility(G,visited,i,res);
				c++;
			}
		}
		cout<<"No of island in graph are : "<<c<<endl;
		return res;
	}
	void dfs_utility(graph &G , int s, vector<bool> &visited , vector<int> &res)
	{
		res.emplace_back(s);
		visited.at(s)=true;
		for(auto &i: G[s])
		{
			if(visited.at(i)==false)
			{
				dfs_utility(G,i,visited,res);
			}
		}
	}
	auto DFS(graph &G)
	{
		vector<int> res;
		vector<bool> visited(G.size(),false);
		for(int i=0;i<G.size();i++)
		{
			if(visited.at(i)==false)
			{
				dfs_utility(G,i,visited,res);
			}
		}
		return res;
	}
	bool cycle_detection_UG_utility(graph &G,int s,vector<bool> &visited,int parent=-1)
	{
		visited.at(s)= true;

		for(auto &i: G.at(s))
		{
			if(visited.at(i)==false)
			{
				if(cycle_detection_UG_utility(G,i,visited,s)) return true;
			}
			else if(i!=parent)
			{
				return true;
			}
		}

		return false;
	}
	bool cycle_detection_UG(graph &G)
	{
		vector<bool> visited(G.size(),false);
		for(int i=0;i<G.size();i++)
		{
			if(visited.at(i)==false and cycle_detection_UG_utility(G,i,visited))
			{
				return true;
			}
		}
		return false;
	}
	auto cycle_detection_DG(graph &G)
	{
		std::vector<int> indegree(G.size(),0);
		for(auto &i: G)
		{
			for(auto &j: i)
				indegree.at(j)++;
		}
		queue<int> q;
		for(int i=0;i<indegree.size();i++)
		{
			if(indegree.at(i)==0) q.push(i);
		}
		int c{0};
		while(!q.empty())
		{
			for(auto &i: G.at(q.front()))
			{
				indegree.at(i)--;
				if(indegree.at(i)==0)
				{
					//cout<<i<<" pushed in queue\n";
					 q.push(i);
				}
			}
			q.pop();
			c++;
		}
		return (c!=G.size());
	}
	void tps_dfs(graph &G,int s,vector<bool> &visited,stack<int> &st)
	{
		visited.at(s)=true;
			for(auto &i: G.at(s))
			{
				if(visited.at(i)==false)
				{
					tps_dfs(G,i,visited,st);
				}
			}
			st.push(s);
	}
	auto topological_sort(graph &G)
	{
		vector<int> res;
		vector<bool> visited(G.size(),false);
		stack<int> st;
		for(int i=0;i<G.size();i++)
		{
			if(visited.at(i)==false)
				tps_dfs(G,i,visited,st);
		}
		while(!st.empty())
		{
			res.emplace_back(st.top());
			st.pop();
		}
		return res;
	}
	auto Wtoplogical_sort(Wgraph &WG)
	{
		vector<int> res;
		vector<int> indegree(WG.size(),0);
		for(auto &i: WG)
		{
			for(auto &j: i)
			{
				indegree.at(j.first)++;
			}
		}
		queue<int> q;
		for(int i=0;i<indegree.size();i++)
		{
			if(indegree.at(i)==0) q.push(i);

		}
		while(!q.empty())
		{
			res.emplace_back(q.front());
			for(auto &i: WG.at(q.front()))
			{
				indegree.at(i.first)--;
				if(indegree.at(i.first)==0) q.push(i.first);
			}
			q.pop();
		}
		return res;
	}
	auto shortest_path_in_DAG(Wgraph &WG,int s)
	{
		vector<int> dist(WG.size(),INT_MAX);
		dist[s]=0;
		auto tps= Wtoplogical_sort(WG);
		for(auto &i: tps)
		{
			for(auto &j: WG.at(i))
			{
				if(dist.at(i)==INT_MAX) continue; // to avoid integer overflow
				dist.at(j.first)=min(dist.at(j.first),dist.at(i)+j.second);
			}
	
		}
		return dist;
	}
	auto dijksrtas_algorithm(Wgraph &WG , int s)
	{
		int sz{0};
		vector<bool> visited(WG.size(),false);
		vector<int> distance(WG.size(),INT_MAX);
		distance.at(s)=0;
		priority_queue<PII,vector<PII>,greater<> > pq;
		for(int i=0;i<distance.size();i++)
		{
			pq.push({distance.at(i),i});
		}
		while(sz!=WG.size())
		{
			if(visited.at(pq.top().second)==false)
			{	visited.at(pq.top().second)=true;
				sz++;
				pair<int,int> p= pq.top();
				pq.pop();
				distance[p.second]=p.first;
				if(distance[p.second]!=INT_MAX)
				{
					for(auto &i: WG.at(p.second))
					{
						if(visited.at(i.first)==false and (distance[i.first]>distance[p.second]+i.second))
						{
							distance[i.first]=distance[p.second]+i.second;
							pq.push({distance[i.first],i.first});
						}
					}
				}
			}
			else pq.pop();
		}
		return distance;
	}
	vector<int> bellman_ford(Wgraph WG,int s)
	{
		vector<int> distance(WG.size(),INT_MAX);
		distance[s]=0;
		for(int i=0;i<(WG.size()-1);i++)
		{
			for(int j=0;j<WG.size();j++)
			{
				for(auto &k : WG.at(j))
				{
					if(distance[j]!=INT_MAX and (distance[k.first]> distance[j]+k.second))
					{
						distance[k.first]= distance[j]+k.second;
					}
				}
			}
		}

		for(int j=0;j<WG.size();j++)
			{
				for(auto &k : WG.at(j))
				{
					if(distance[j]!=INT_MAX and (distance[k.first]> distance[j]+k.second))
					{
						cout<<"YOU ARE FUCKED!! THIS GRAPH HAS NEGATIVE CYCLE LMAO\n";
						distance.clear();
						return distance;
					}
				}
			}
			return distance;
	}
	namespace exstd
	{
		template<typename T> class disjoint_set
	{
	private:
		vector<int>Parent;
		vector<int> Rank;
		vector<T> mapping_table;
		unordered_map<T,int> reverse_mapping_table; 
	public:
		disjoint_set(){} // no args constructor
		disjoint_set(vector<T>); // constructor for initialization
		void Insert(T);   // used for arbitrary insertion in the object
		auto Find(T);      // standard find function for disjoint set 
		auto Find_utility(int);  //helping function for find
		void Union(T,T);  // standard union function for mreverse mapping
		void Union_utility(int,int); // helper union function which perform actual union

	};
	// too much overhead but cant really do anything 
	template<typename T> disjoint_set<T>::disjoint_set(vector<T> initializer)
	{
		for(int i=0;i<initializer.size();i++)
		{
			mapping_table.emplace_back(initializer.at(i));
			reverse_mapping_table[initializer.at(i)]=i;
			Parent.emplace_back(i);
			Rank.push_back(0);
		}
	}
	template<typename T> void disjoint_set<T>::Insert(T x)
	{
		mapping_table.emplace_back(x);
		reverse_mapping_table[x]=mapping_table.size()-1;
		Parent.emplace_back(mapping_table.size()-1);
		Rank.push_back(0);
	}
	template<typename T> auto disjoint_set<T>::Find_utility(int x)
	{
		if(Parent.at(x)==x)
		{
			return x;
		}
		Parent.at(x)=Find_utility(Parent.at(x));
		return Parent.at(x);
	}
	template<typename T> auto disjoint_set<T>::Find(T ele)
	{
			auto it= reverse_mapping_table.find(ele);
			int x;
			if(it==reverse_mapping_table.end())
			{	
				cout<<"Error 404: The give element is not present in the container\n ";
				T ret;
				return ret;
			}
			x=it->second;
			return mapping_table.at(Find_utility(x));
	}
	template<typename T> void disjoint_set<T>::Union_utility(int x,int y)
	{  
		int x_rep= Find_utility(x);
		int y_rep=Find_utility(y);
		if(x_rep==y_rep) return ;
		if(Rank.at(x_rep)>Rank.at(y_rep))
		{
			Parent.at(y_rep)=x_rep;
			return;
		}
		else if(Rank.at(x_rep)<Rank.at(y_rep))
		{
			Parent.at(x_rep)=y_rep;
			return ;
		}
		else
		{
			Parent.at(y_rep)=x_rep;
			Rank.at(x_rep)++;
			return ;
		}
		cout<<"Error 69 : something is wrong (Logic Failed )\n";
	}
	template<typename T> void disjoint_set<T>::Union(T x,T y)
	{
		int x_new,y_new;
		auto it= reverse_mapping_table.find(x);
		if(it==reverse_mapping_table.end()) return;
		x_new=it->second;
		it=reverse_mapping_table.find(y);
		if(it==reverse_mapping_table.end()) return ;
		y_new=it->second;
		Union_utility(x_new,y_new);
	}
	template<> class disjoint_set<int>
	{
	private:
		vector<int> Parent;
		vector<int> Rank;
	public:
		disjoint_set(){ } //no args constructor
		disjoint_set(int); // constructor with size
		void Insert();   //use to insert a another element in the disjint set
		auto Find(int); // standard find function for the disjoint set container
		void Union(int,int); //standard union function
	};
	 disjoint_set<int>::disjoint_set(int sz)
	{
		for(int i=0;i<sz;i++)
		{
			Parent.emplace_back(i);
			Rank.push_back(0);
		}
	}
	void disjoint_set<int>::Insert()
	{
		Parent.push_back(Parent.size());
		Rank.push_back(0);
	}
	 auto disjoint_set<int>::Find(int x)
	{
		if(Parent.at(x)==x) return x;
		Parent.at(x)=Find(Parent.at(x));
		return Parent.at(x);
	}
	void disjoint_set<int>::Union(int x,int y)
	{
		int x_rep=Find(x);
		int y_rep=Find(y);
		if(x_rep==y_rep) return ;
		if(Rank.at(x_rep)>Rank.at(y_rep))
		{
			Parent.at(y_rep)=x_rep;
		}
		else if(Rank.at(x_rep)<Rank.at(y_rep))
		{
			Parent.at(x_rep)= y_rep;
		}
		else
		{
			Parent.at(y_rep)=x_rep;
			Rank.at(x_rep)++;
		}
	}
	
	}
	void kruskals_utility(Wgraph &WG, vector< pair< pair<int,int>,int> > &edges_arr)
	{
		for(int i=0;i<WG.size();i++)
		{
			for(auto &j: WG.at(i))
			{
				edges_arr.push_back({{i,j.first},j.second});
			}
		}
		auto mycmp=[](auto &l,auto &r){

			return l.second<r.second;
		};
		sort(edges_arr.begin(),edges_arr.end(),mycmp);
	}
	auto kruskals(Wgraph &WG)
	{
		vector< pair< pair<int,int>,int > > edges_arr;
		kruskals_utility(WG,edges_arr);

		//exstd is here bayybyyy

		exstd::disjoint_set<int> ds(WG.size());


		int i{0},res{0},c{0};
		while(c<WG.size() and i<edges_arr.size())
		{
			if(ds.Find(edges_arr.at(i).first.first)!=ds.Find(edges_arr.at(i).first.second))
			{
				c++;
				res+=edges_arr.at(i).second;
				ds.Union(edges_arr.at(i).first.first,edges_arr.at(i).first.second);
			}
			i++;
		}
		return res;
	}
	int prims(Wgraph &WG,int s=0)
	{
		int sz{0};
		vector<int> visited(WG.size(),false);
		vector<int> key_val(WG.size(),INT_MAX);
		key_val.at(s)=0;
		priority_queue<PII,vector<PII>,greater<> > pq;
		pq.push({0,0});
		for(int i=1;i<WG.size();i++) pq.push({INT_MAX,i});
		while(sz<WG.size() and !pq.empty())
		{
			if(visited.at(pq.top().second)==false)
			{	sz++;
				visited.at(pq.top().second)=true;
				pair<int,int> p= pq.top();
				pq.pop();
				for(auto &i: WG.at(p.second))
				{
					if(visited.at(i.first)==false and key_val.at(i.first)>i.second)
					{
						key_val.at(i.first)=i.second;
						pq.push({key_val.at(i.first),i.first});
					}
				}
			}
			else pq.pop();
		}
		return accumulate(key_val.begin(),key_val.end(),0);

	}
	void fill_sequence(graph &G,vector<bool> &visited,vector<int> &sequence,int s)
	{ 
		visited.at(s)=true;
			for(auto &i: G.at(s))
			{
				if(visited.at(i)==false)
				{
					fill_sequence(G,visited,sequence,i);
				}
			}
			sequence.emplace_back(s);
	}
	int kosarajus_algorithm(graph &G)
	{
		vector<int> sequence;
		vector<bool> visited(G.size(),false);
		vector<int> for_dfs;
		for(int i=0;i<G.size();i++)
		{
			if(visited.at(i)==false) fill_sequence(G,visited,sequence,i);
		}
		int res{0};
		std::fill(visited.begin(),visited.end(),false);
		cout<<"hello \n";
		for(int i=sequence.size()-1 ; i>=0 ; i--)
		{
			if(visited.at(sequence[i])==false)
			{
				res++;
				dfs_utility(G,i,visited,for_dfs);
			}
		}
		return res;
	}

int main()
{ 
	IOS;
#ifndef ONLINE_JUDGE 
  	READ;
  	ERROR;
  	OUTPUT;
#endif 
  	cout<<"sudb";
	int t;	
	cin>>t;       
	// t=1;
	while(t--)  
	{
		int V,E;
		cin>>V>>E;
		graph G(V);
		iDirectedGraph(V,E,G);
		cout<<kosarajus_algorithm(G)<<endl;
	
	}
	cerr<<"yahan aayega \n";
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<"\n"; 
return 0; 
} 