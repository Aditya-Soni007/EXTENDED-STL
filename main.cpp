#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define PI 3.1415926535897932384626433832795

#define IOS ios_base::sync_with_stdio(false),cin.tie(NULL)
#define READ freopen("input.txt", "r", stdin); 
#define ERROR freopen("error.txt", "w", stderr); 
#define OUTPUT freopen("output.txt", "w", stdout); 
#define debug(x) cout <<'>'<<#x<<':'<< x<<"\n";
#define debug2(x, y) cout<<'>'<<#x<<':'<<x<<","<<#y<<':'<<y<<"\n"

#define endl '\n'
#define MP make_pair
#define F first
#define S second
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(),(x).end()
#define FOR(i,from,to) for(int i = from ; i<to ; i++)
#define RFOR(i,from,to) for(int i=from ; i>=to ; i--)

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef pair<int,PII> PPII;
typedef pair<LL,LL> PLL;
typedef pair<LL,PLL> PPLL;
typedef pair<string,int> PSI;
typedef pair<int,string> PIS;
typedef vector<PLL> VPLL;
typedef vector<VLL> GRAPH;
typedef vector<VPLL> WGRAPH;
typedef set<LL> SLL;
typedef unordered_set<LL> USLL;
typedef map<LL,LL> MLL;
typedef unordered_map<LL,LL> UMLL;
	class Cycle: public std::exception
	{
	public:
		virtual ~Cycle(){}
		virtual const char* what() const noexcept override
		{
			return "M_internal_Cycle Check->true::DAGs can't have a CYCLE\n"; 
		}

	};
	ostream& operator<<(ostream &os,const GRAPH &G)
	{
		for(int i=0;i<G.size();i++)
		{
			os<<i<<"|->";
			for(int j=0 ; j<G.at(i).size() ; j++)
			{
				os<<G[i][j];
				if(j!=G.at(i).size()-1) os<<"->";
			}
			cout<<endl;
		}
		return os;
	}
	void cin_graph(GRAPH &G,LL V,LL E)
	{
		while(E--)
		{
			LL to,from;
			cin>>to>>from;
			G[to].push_back(from);
			G[from].push_back(to);
		}
	}
	auto bfs01(WGRAPH &G,int s=0)
	{
		VB visited(G.size(),false);
		VLL dist(G.size(),LLONG_MAX);
		dist.at(s)=0;
		deque<LL> dq;
		dq.push_back(s);
		visited.at(s)=true;
		while(!dq.empty())
		{
			int f=dq.front();
			dq.pop_front();
			for(auto &child : G[f])
			{
				dist[child.first]=min(dist[child.first],dist[f]+child.second);
				if(!visited.at(child.first))
				{
					if(!child.second) dq.push_front(child.first);
					else dq.push_back(child.first);
					visited.at(child.first)=true;
				}
			}
		}
		return dist;
	}
	
	bool is_bipartite(GRAPH &G,int s=0)
	{
		VI color(G.size(),0);
		queue<int> q;
		q.push(s);
		color.at(s)=1;
		while(!q.empty())
		{
			for(auto &child: G[q.front()])
			{
				if(color.at(q.front())==color.at(child)) 
				{
					return false;
				}
				if(!color.at(child))
				{
					q.push(child);
					color.at(child)=(color.at(q.front())==1)?(2):(1);

				}
			}
			color.at(q.front())=3;
			q.pop();
		}
		return true;
	}
	auto topological_sort(WGRAPH &G,LL s=0)
	{
		int c{0};
		VLL res;
		VI color(G.size(),0),indegree(G.size(),0);
		for(auto &i: G) for(auto &j: i) indegree.at(j.first)++;
		queue<LL> q;
		for(int i=s;i<indegree.size();i++)
		{
			if(indegree.at(i)==0)
			{
				q.push(i);
				color.at(i)=1;
			}
		}
		while(!q.empty())
		{
			for(auto &child: G[q.front()])
			{
				indegree.at(child.F)--;
				if(indegree.at(child.F)==0)
				{
					q.push(child.F);
					color.at(child.F)=1;
				}
			}
			color.at(q.front())=2;
			res.emplace_back(q.front());
			q.pop();
			c++;
		}
		if(c<G.size()) throw Cycle();
		return res;
	}
	auto shortest_distance_dag(WGRAPH &G,int s=0)
	{
		VLL tps;
		try{
			 tps= topological_sort(G);
		}
		catch(Cycle &E)
		{
			cerr<<E.what()<<endl;
			exit(0);
		}
		VLL dist(G.size(),INT_MAX);
		dist[s]=0;
		for(auto &i: tps)
		{
			for(auto &child: G[i]) dist[child.F]= min(dist[child.F],dist[i]+child.S);
		}
		return dist;
	}




	bool is_cycle_utility(const WGRAPH &G,VI &color,LL s,LL parent=-1)
	{
		color.at(s)=1;
		for(auto &child : G[s])
		{
			if(child.F==parent) continue;
			else if(color.at(child.F)!=0 or is_cycle_utility(G,color,child.F,s)) return true;
		}
		return false;
	}
	auto is_cycle(const WGRAPH &G)
	{
		VI color(G.size(),0);
		for(int i=0;i<G.size();i++)
		{
			if(!color.at(i) and is_cycle_utility(G,color,i)) return true; 
		}
		return false;
	}

namespace dsu{
		vector<LL> parent;  //path compression
		vector<LL> rank;	//rank selection

		auto Find(LL x)
		{
			if(parent[x]==x) return x;
			auto pc=Find(parent[x]);
			return pc;
		}
		auto Union(LL x,LL y);
		auto Union(LL x, LL y)
		{
			auto _x=Find(x);
			auto _y=Find(y);
			if(_x==_y) return false;
			if(rank.at(_x)>rank.at(_y)) parent.at(_y)=_x;
			else if(rank.at(_x)<rank.at(_y)) parent.at(_x)=_y;
			else
			{
				parent.at(_y)=_x;
				rank.at(_x)++;
			}
			return true;
		}
}


	auto kruskals_mst(WGRAPH &WG)
	{
		LL res{0},c{0};
		dsu::parent=vector<LL>(WG.size());
		std::iota(all(dsu::parent),0);
		dsu::rank=vector<LL>(WG.size(),0);
		vector< tuple<LL,LL,LL> > edge_list;
		for(int i=0;i<WG.size();i++)
		{
			for(auto &j: WG[i])
			{
				if(i<j.F) edge_list.emplace_back(make_tuple(i,j.F,j.S));
			}
		}
		sort(all(edge_list),[](const auto &l,const auto &r){return get<2>(l)<get<2>(r);});
		for(auto &i: edge_list)
		{
			auto x= dsu::Find(get<0>(i));
			auto y= dsu::Find(get<1>(i));
			if(x!=y)
			{
				res+=get<2>(i);
				dsu::Union(get<0>(i),get<1>(i));
				c++;
			}
			if(c==WG.size()-1) return res;
		}
		return res;

	}
	auto prims_mst(WGRAPH &WG)
	{
		LL res{0},sz{0};
		VLL color(WG.size(),0);
		priority_queue<PLL,vector<PLL>,greater<> > pq;
		pq.push({0,0});
		while(sz<WG.size() and !pq.empty())
		{	while(!pq.empty() and color.at(pq.top().F)!=0) pq.pop();
			if(pq.empty()) return res;
			auto top=pq.top();
			res+=top.S;
			color.at(top.F)=true;
			pq.pop();
			sz++;
			for(auto &child: WG[top.F])
			{
				if(color.at(child.F)==0) pq.push({child.F,child.S});
			}
		}
		return res;
	}
	auto dijkstras(const WGRAPH &WG,LL s=0)
	{
		LL sz{0}; //to keep the count of the vertices which are already been processed
		VI color(WG.size(),0); //to keep the track about the status of a vertex
		VLL dist(WG.size(),INT_MAX); //array to maintain the shortest distance from give source
		dist.at(s)=0;
		priority_queue<PLL,vector<PLL>,std::greater<> > pq; //min-heap
		pq.push({0,s}); //pushing the source vertex with distnace 0
		while(!pq.empty() and sz<WG.size()) //repeat until pq is not empty or all the vertices are not processed
		{
			//remove all the already processed vertices in the min-heap
			while(!pq.empty() and color.at(pq.top().S)!=0) pq.pop();
			if(pq.empty()) return dist; //if there is no vertex to process just return the dist vector
			auto top = pq.top();  //take the greedy choice and mark it as visited
			color.at(pq.top().S)=1; //marked visited
			pq.pop(); //remove it from the min-heap
			sz++;//increment the sz variable when a vertex is processed
			if(dist.at(top.S)==INT_MAX) continue; //if the distnace of the currently proessed vertex is infinite from the source there is no pint of relxing its adjacents so continue

			for(auto &i: WG[top.S])  //hover over the adjacency list of the processed vertex
			{
				//ONLY DO THIS FOR THE UNPROCESSED VERTICES
				if(!color.at(i.F) and dist[i.F]>dist[top.S]+i.S) //check if relaxation is possibe
				{ 
					dist[i.F]=dist[top.S]+i.S; //relax the vertex
					pq.push({dist[i.F],i.F}); //perform the decrease key operation
				}
			}
		}
		return dist;
	}
	auto bellman_ford(WGRAPH &WG,LL s=0)
	{
		VLL dist(WG.size(),INT_MAX);
		dist[s]=0;
		for(int c=0;c<(WG.size()-1);c++)
		{
			bool flag{false};
			for(int i=0;i<WG.size();i++)
			{
				if(dist[i]==INT_MAX) continue;
				for(auto &j: WG[i]) 
				{
					if(dist[j.F]>dist[i]+j.S) 
					{
						dist[j.F]=dist[i]+j.S;
						flag=true;
					}
				}
				
			}
			if(flag==false) return dist;
		}
		for(int i=0;i<WG.size();i++)
		{
			if(dist[i]==INT_MAX) continue;
			for(auto &j: WG[i]) 
			{
				if(dist[j.F]>dist[i]+j.S) 
				{
					throw Cycle();
				}
			}
		}
		return dist;
	}
	// void kosarajus_utility(GRAPH &G,VI &color,LL s)
	// {
	// 	color.at(s)=1;
	// 	for(auto &child : G[s])
	// 	{
	// 		if(color.at(child)!=0) continue; //only visit the unvisited vertices
	// 		kosarajus_utility(G,color,child); 
	// 	}
	// 	color.at(s)=2;
	// }
	// void kosarajus_algorithm(GRAPH &G,VI &color,VLL &order,LL s)
	// {
	// 	color.at(s)=1; //in process
	// 	for(auto &child :  G[s])
	// 	{
	// 		if(color.at(child)!=0) continue; //only visit unvisited vertices
	// 		kosarajus_algorithm(G,color,order,child);
	// 	}
	// 	color.at(s)=2;
	// 	order.emplace_back(s);
	// }
	void _dfs(const GRAPH &G,VI &color,VLL &disc_time,VLL &lowest_disc,LL timer,LL s,VLL &res,LL parent)
	{
		++timer;
		color.at(s)=1;
		disc_time.at(s)=timer;
		LL val1{disc_time[s]},val2{INT_MAX};
		for(auto &child : G[s])
		{
			if(child==parent) continue;
			if(color.at(child)!=0)
			{
				val1=min(val1,lowest_disc[child]);
			}
			else
			{
				_dfs(G,color,disc_time,lowest_disc,timer,child,res,s);
				val2=min(val2,lowest_disc[child]);
				if(lowest_disc[child]>disc_time[s]) cout<<s<<" -> "<<child<<endl;
				if(val2>=disc_time[s] and color.at(s)!=-1)
				{
					// cout<<s<<" "<<val2<<" "<<disc_time[s]<<endl;
					res.emplace_back(s);
					color.at(s)=-1;
				}
			}
		}
	
		lowest_disc[s]=min(val1,val2);
	}
	auto articulation_points(const GRAPH &G)
	{
		LL timer{1},count{0};
		VI color(G.size(),0);
		VLL disc_time(G.size(),0),lowest_disc(G.size()),res;
		std::iota(all(lowest_disc),1);
		color.at(0)=1;
		disc_time.at(0)=timer;
		for(auto &child: G[0])
		{
			if(color.at(child)!=0) continue;
			_dfs(G,color,disc_time,lowest_disc,timer,child,res,0);
			if(lowest_disc[child]>disc_time[0]) cout<<0<<" -> "<<child<<endl;
			count++;
		}
		// cout<<lowest_disc[1]<<" "<<disc_time[0]<<endl;
		if(count>1) res.emplace_back(0);
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

	int t;
	// cin>>t;  
	t=1;
	while(t--) 
	{ 

		LL V,E;
		cin>>V>>E;
		GRAPH G(V);	
		cin_graph(G,V,E);
		cout<<G<<endl;
		auto res=articulation_points(G);
		for(auto &i: res) cout<<i<<" ";
	} 
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<"\n"; 
return 0; 
} 









