/*

class of exstd::directed_graph for extended STL 
Developed by : Squad Inc.
by :	Aditya Soni
on 10th April 2021
*/
/*
Completed work-:
	1.Handling Conatiners
	2.Handle I/O
	3.BFS
	4.DFS
	5.is cycle()
	6.shortest path by BFS
	7.Connected compoenents
	8.Operator Overloading
Pending work - :
	1.Change the cycle detection method to work with disjoint set method 
	2. Make a class for Exception handling by overriding the what() method of std::exception
	3.Write test file for the detail() method of the class .
Extra Features added:
	1.Container is made protected so accessing it via inheritence is possible
	2.Various overloaded methods to make classe powerful than before
	3. Especially for cin_graph() methos many ways availible this increasing the flexibility
	4. Damn User Friendly
*/

#include <bits/stdc++.h>
using std::istream;
using std::ostream;
using std::vector;
using std::unordered_map;
using std::cout;
using std::cin;
using std::endl;
using std::ios_base;
using std::string;
using std::cerr;
using std::pair;
using std::unordered_map;
using std::map;
using std::queue;
using std::stack;
using std::priority_queue;
#define IOS ios_base::sync_with_stdio(false),cin.tie(NULL)
#define READ freopen("input.txt", "r", stdin); 
#define ERROR freopen("error.txt", "w", stderr); 
#define OUTPUT freopen("output.txt", "w", stdout); 
#define endl '\n'



	template<typename T> class directed_graph
	{
		template<typename U> friend ostream& operator<<(ostream &,const directed_graph<U> &); 
	protected:
		vector< vector<int> > G;
		vector<T> mapping_table;
		map<T,int> reverse_mapping_table;
	private:
		void bfs_utility(int,vector<bool>&,vector<T> &); //bfs utility function
		void dfs_utility(int,vector<bool> &,vector<T> &); //dfs utility function
		void kosarajus_algorithm(int,vector<bool> &,vector<int> &);
		void kosarajus_utility(int,vector<bool> &);
	public:
		//ctor and dtor
		directed_graph(const vector<T>&);
		~directed_graph(){};
		
		//input functions
		void cin_graph(int );   // to input a graph from istream
		void cin_graph(const vector< pair<T,T > >&); // overloaded cin which excepts array of edges
		void add_vertex(const T); //utility function to add a vertex
		void add_edge(const T &,const T &);  // to add a edge in the graph

		//output functions
		void cout_graph();  //function to output graph

		//traversal techniques
		vector<T> bfs(const T&);  //bfs driver function
		vector<T> bfs();  //overloaded bfs function
		vector<T> dfs();  //overloaded dfs function
		vector<T> dfs(const T&); //dfs driver function

		//misc functions
		vector<int> shortest_path(const T&); //shortest path by BFS
		bool is_cycle(); 
		int connected_compoenents();
	};
template<typename T>void directed_graph<T>::kosarajus_utility(int s,vector<bool> &visited)
	{
		visited.at(s)=true;
		for(auto &i: G[s])
		{
			if(visited.at(i)==false) kosarajus_utility(i,visited);
		}
	}
template<typename T> void directed_graph<T>::kosarajus_algorithm(int s,vector<bool> &visited,vector<int> &sequence)
	{
		visited.at(s)=true;
		for(auto &i: G[s])
		{
			if(visited.at(i)==false) kosarajus_algorithm(i,visited,sequence);
		}
		sequence.emplace_back(s);
	}
template<typename T>int directed_graph<T>::connected_compoenents()
	{
		int c{0};
		vector<bool> visited(G.size(),false);
		vector<int> sequence;
		for(int i=0;i<G.size();i++) //first dfs call
		{
			if(!visited.at(i)) kosarajus_algorithm(i,visited,sequence);
		}		
		fill(visited.begin(),visited.end(),false);
		for(int i=sequence.size()-1 ; i>=0 ; i--)
		{
			if(!visited.at(sequence[i]))
			{
				kosarajus_utility(sequence[i],visited);
				c++;
			}
		}
		return c;
	}

template<typename T> bool directed_graph<T>::is_cycle()
	{
		int c{0};
		vector<int> indegree(G.size(),0);
		for(auto &i : G)
		{
			for(auto &j: i)
			{
				indegree[j]++;
			}
		}
		queue<int> q;
		for(int i=0;i<indegree.size();i++)
		{
			if(indegree[i]==0) q.push(i);
		}
		while(!q.empty())
		{
			for(auto &i:G[q.front()])
			{
				indegree[i]--;
				if(indegree[i]==0) q.push(i);
			}
			q.pop();
			c++;
		}
		return !(c==G.size());
	}
	template<typename T> vector<int> directed_graph<T>::shortest_path(const T &s)
	{
		int _s;
		auto it=reverse_mapping_table.find(s);
		if(it==reverse_mapping_table.end())
		{
			throw "Error 404!\n";
		}
		_s=it->second;
		vector<int> dist(G.size(),INT_MAX);
		vector<bool> visited(G.size(),false);
		dist[_s]=0;
		int d{0};
		queue<int> q;
		q.push(_s);
		visited.at(_s)=true;
		while(!q.empty())
		{
			int sz=q.size();
			for(int k=0;k<sz;k++)
			{
				for(auto &i: G.at(q.front()))
				{
					if(visited.at(i)==false)
					{
						q.push(i);
						visited.at(i)=true;
					}
				}
				dist.at(q.front())=d;
				q.pop();
			}
			
			d++;
		}
		return dist;

	}
	
	template<typename T>void directed_graph<T>::dfs_utility(int s,vector<bool> &visited,vector<T> &res)
	{
		visited.at(s)=true;
		res.emplace_back(mapping_table[s]);
		for(auto &i: G.at(s))
		{
			if(visited.at(i)==false)
			{
				dfs_utility(i,visited,res);
			}
		}
	}
	template<typename T> vector<T> directed_graph<T>::dfs(const T &s)
	{
		int _s;
		auto it= reverse_mapping_table.find(s);
		if(it==reverse_mapping_table.end())  //RAISE AN EXCEPTION 
		{
			throw -1;
		}
		_s=it->second;
		vector<T> res;
		vector<bool> visited(G.size(),false);
		for(int i=_s;i<G.size();i++)
		{
			if(visited.at(i)==false)
			{
				dfs_utility(i,visited,res);
			}
		}
		return res;
	}
	template<typename T> vector<T> directed_graph<T>::dfs()
	{
		vector<T> res;
		if(reverse_mapping_table.empty()) return res;
		vector<bool> visited(G.size(),false);
		for(int i=0;i<G.size();i++)
		{
			if(visited.at(i)==false) dfs_utility(i,visited,res);
		}
		return res;
	}
	template<typename T>void directed_graph<T>:: bfs_utility(int s,vector<bool> &visited,vector<T> &res)
	{
		queue<int> q;
			q.push(s);
			visited[s]=true;
			while(!q.empty())
			{
				for(auto &i: G.at(q.front()))
				{
					if(visited.at(i)==false)
					{
						q.push(i);
						visited.at(i)=true;
					}
				}
				res.emplace_back(mapping_table[q.front()]);
				q.pop();
			}
	}
	template<typename T> vector<T> directed_graph<T>::bfs(const T &s)
	{
		int _s;
		auto it=reverse_mapping_table.find(s);
		if(it==reverse_mapping_table.end()) //RAISE AN EXCEPTION HERE
		{
			throw -1;
		}
		_s=it->second;
		vector<T> res;
		vector<bool> visited(G.size(),false);
		for(int i=_s;i<G.size();i++)
		{
			if(!visited.at(i)) bfs_utility(i,visited,res);
		}
		return res;
	}
	template<typename T> vector<T> directed_graph<T>::bfs()
	{
		vector<T> res;
		if(reverse_mapping_table.empty())
		{
			return res;
		}
		vector<bool> visited(G.size(),false);
		for(int i=0;i<G.size();i++)
		{
			if(!visited.at(i)) bfs_utility(i,visited,res);
		}
		return res;
	}
	template<typename T> void directed_graph<T>::cout_graph()
	{
		for(int i=0;i<G.size();i++)
		{
			cout<<mapping_table[i]<<"|->";
			for(int j=0;j<G.at(i).size();j++)
			{
				cout<<mapping_table[G.at(i).at(j)];
				if(j!=G.at(i).size()-1) cout<<"->";
			}
			cout<<"\n";
		}
	}
	template<typename T> directed_graph<T>::directed_graph(const vector<T> &init)
	{
		//RAISE AN EXCEPTION HERE IF INIT.SIZE()!=S
		for(int i=0;i<init.size();i++)
		{
			mapping_table.emplace_back(init[i]);
			reverse_mapping_table[init[i]]=i;
		}
		G.resize(init.size());
	}
	template<typename T> void directed_graph<T>:: add_vertex(const T temp)
	{
		mapping_table.emplace_back(temp);
		reverse_mapping_table[temp]=mapping_table.size()-1;
		G.resize(G.size()+1);
	}
	template<typename T> void  directed_graph<T>::add_edge(const T &from ,const T &to)
	{
			int _from,_to;
			auto it=reverse_mapping_table.find(from);
			if(it==reverse_mapping_table.end())  //RAISE AN EXCEPTION HERE
			{
				throw -1;
			}
			_from=it->second;
		    it=reverse_mapping_table.find(to);
		    if(it==reverse_mapping_table.end()) //RAISE AN EXCEPTION HERE
		    {
		    	throw -1;
		    }
		    _to=it->second;
		    G[_from].emplace_back(_to);
	}
	template<typename T> void directed_graph<T>::cin_graph(int E)
	{
		while(E--)
		{
			T from,to;
			cin>>from>>to;
			add_edge(from,to);
		}
	}
	template<typename T> void directed_graph<T>::cin_graph(const vector< pair<T,T> >&temp)
	{
		for(auto &i: temp)
		{
			add_edge(i.first,i.second);
		}
	}

//___________________________________________________________________________________



	template<>
	class directed_graph<int>
	{
		friend ostream& operator<<(ostream &,const directed_graph<int>&);
	protected:
		vector< vector<int> > G;
	private:
		void bfs_utility(int,vector<bool>&,vector<int> &); //bfs utility function
		void dfs_utility(int,vector<bool> &,vector<int> &); //dfs utility function
		void kosarajus_algorithm(int,vector<bool> &,vector<int> &);
		void kosarajus_utility(int,vector<bool> &);
	public:
		//ctor and dtor
		directed_graph(int s=0); // one arg ctor
		~directed_graph(){};  //destructor

		//input functions
		void cin_graph(int );   // to input a graph from istream
		void cin_graph(const vector< pair< int,int > >&); // overloaded cin which excepts array of edges
		void add_vertex(); //utility function to add a vertex
		void add_edge(int,int);  // to add a edge in the graph
		
		//output functions
		void cout_graph();  //function to output graph

		//traversal techniques
		vector<int> bfs(int s=0);  //bfs driver function
		vector<int> dfs(int s=0); //dfs driver function

		//misc functions 
		vector<int> shortest_path(int s=0); //by BFS
		bool is_cycle();
		int connected_compoenents();

	};
	void directed_graph<int>::kosarajus_utility(int s,vector<bool> &visited)
	{
		visited.at(s)=true;
		for(auto &i: G[s])
		{
			if(visited.at(i)==false) kosarajus_utility(i,visited);
		}
	}
	void directed_graph<int>::kosarajus_algorithm(int s,vector<bool> &visited,vector<int> &sequence)
	{
		visited.at(s)=true;
		for(auto &i: G[s])
		{
			if(visited.at(i)==false) kosarajus_algorithm(i,visited,sequence);
		}
		sequence.emplace_back(s);
	}
	int directed_graph<int>::connected_compoenents()
	{
		int c{0};
		vector<bool> visited(G.size(),false);
		vector<int> sequence;
		for(int i=0;i<G.size();i++) //first dfs call
		{
			if(!visited.at(i)) kosarajus_algorithm(i,visited,sequence);
		}		
		std::fill(visited.begin(),visited.end(),false);
		for(int i=sequence.size()-1 ; i>=0 ; i--)
		{
			if(!visited.at(sequence[i]))
			{
				kosarajus_utility(sequence[i],visited);
				c++;
			}
		}
		return c;
	}
	bool directed_graph<int>::is_cycle()
	{
		int c{0};
		vector<int> indegree(G.size(),0);
		for(auto &i : G)
		{
			for(auto &j: i)
			{
				indegree[j]++;
			}
		}
		queue<int> q;
		for(int i=0;i<indegree.size();i++)
		{
			if(indegree[i]==0) q.push(i);
		}
		while(!q.empty())
		{
			for(auto &i:G[q.front()])
			{
				indegree[i]--;
				if(indegree[i]==0) q.push(i);
			}
			q.pop();
			c++;
		}
		return !(c==G.size());
	}
	vector<int> directed_graph<int>::shortest_path(int s)
	{ 
		//RAISE AN EXCEPTION IF THE SOURCE VERTEX IS INVALID
	// finding shortest path in directed unweighted graph by BFS
		vector<int> dist(G.size(),INT_MAX);
		vector<bool> visited(G.size(),false);
		dist[s]=0;
		int d{0};
		queue<int> q;
		q.push(s);
		visited.at(s)=true;
		while(!q.empty())
		{
			int sz=q.size();
			for(int k=0;k<sz;k++)
			{
				for(auto &i: G.at(q.front()))
				{
					if(visited.at(i)==false)
					{
						q.push(i);
						visited.at(i)=true;
					}
				}
				dist.at(q.front())=d;
				q.pop();
			}
			
			d++;
		}
		return dist;
	}
	void directed_graph<int>::dfs_utility(int s,vector<bool> &visited,vector<int> &res)
	{
		visited.at(s)=true;
		res.emplace_back(s);
		for(auto &i: G.at(s))
		{
			if(visited.at(i)==false)
			{
				dfs_utility(i,visited,res);
			}
		}
	}
	vector<int> directed_graph<int>:: dfs(int s)
	{
		//RAISE AN EXCEPTION WHEN SOURCE IS INVALID
		vector<bool> visited(G.size(),false);
		vector<int> res;
		for(int i=0;i<G.size();i++)
		{
			if(visited.at(i)==false)
			{
				dfs_utility(i,visited,res);
			}
		}
		return res;
	}
	void directed_graph<int>:: bfs_utility(int s,vector<bool> &visited,vector<int> &res)
	{
		queue<int> q;
			q.push(s);
			visited[s]=true;
			while(!q.empty())
			{
				for(auto &i: G.at(q.front()))
				{
					if(visited.at(i)==false)
					{
						q.push(i);
						visited.at(i)=true;
					}
				}
				res.emplace_back(q.front());
				q.pop();
			}
	}
	vector<int> directed_graph<int>::bfs(int s)
	{	//RAISE AN EXEPTION IF THE GIVEN SOURCE IS INVALID
		vector<int> res;

		vector<bool> visited(G.size(),false);
		for(int i=s;i<G.size();i++)
		{
			if(visited.at(i)==false)
			{
				bfs_utility(i,visited,res);
			}
		}
		return res;
	}
	directed_graph<int>::directed_graph(int s)
	{
		G.resize(s); // initializing the number of vertices in the graph
	}
	void directed_graph<int>::cout_graph()
	{
		for(int i=0;i<G.size();i++)
		{
			cout<<i<<"|->";
			for(int j=0;j<G.at(i).size();j++)
			{
				cout<<G.at(i).at(j);
				if(j!=G.at(i).size()-1) cout<<"->";
			}
			cout<<"\n";
		}
	}
	void directed_graph<int>:: add_vertex()
	{
		G.resize(G.size()+1);
	}
	void directed_graph<int>::add_edge(int from,int to)//utility function //to add edge
	{
		//RAISE AN EXCEPTION HERE IF TO OT FROM DOENT EXIST INT THE GRAPH
		G[from].emplace_back(to);  // adding an edge in the adjacency list
	}
	void directed_graph<int> ::cin_graph(const vector< pair<int,int> > &temp)
	{
		for(auto &i: temp)
		{
			add_edge(i.first,i.second);
		}
	}
	void directed_graph<int> ::cin_graph(int E)
	{
			while(E--)  // looping no. of edges time
			{
				int from,to;  
				cin>>from>>to;  //inputing the edge
				add_edge(from,to); //calling the directed_graph<int>::add_edge(int ,int)
			}
	}
template<typename T> ostream& operator<<(ostream &os,const directed_graph<T> &obj)
	{
		for(int i=0;i<obj.G.size();i++)
		{
			os<<obj.mapping_table[i]<<"|->";
			for(int j=0;j<obj.G.at(i).size();j++)
			{
				os<<obj.mapping_table[obj.G.at(i).at(j)];
				if(j!=obj.G.at(i).size()-1) os<<"->";
			}
			os<<"\n";
		}
		return os;
	}
	ostream& operator<<(ostream &os,const directed_graph<int> &obj)
	{
		for(int i=0;i<obj.G.size();i++)
		{
			os<<i<<"|->";
			for(int j=0;j<obj.G.at(i).size();j++)
			{
				os<<obj.G.at(i).at(j);
				if(j!=obj.G.at(i).size()-1) os<<"->";
			}
			os<<"\n";
		}
		return os;
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
		directed_graph<int> G(4);
		G.cin_graph(5);
		cout<<G;
		cout<<G.connected_compoenents()<<endl;
	} 
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<"\n"; 
return 0; 
} 






