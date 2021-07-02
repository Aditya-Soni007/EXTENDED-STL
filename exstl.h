#ifndef _EXSTL_H_  //include guards 
#define _EXSTL_H_


#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<utility>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<algorithm>
#include<functional>
#include<numeric>
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
using std::map;
using std::queue;
using std::stack;
using std::priority_queue;

namespace exstd{

				//*****GRAPH STARTED*****//

		//undirected graph template class start

template<typename T> class undirected_graph
	{
		template<typename U> friend ostream& operator<<(ostream &,const undirected_graph<U> &);
	protected:
		vector< vector<int> > G;
		vector<T> mapping_table;
		map<T,int> reverse_mapping_table;
	private:
		void bfs_utility(int,vector<bool> &);
		void bfs_utility(int,vector<bool>&,vector<T> &); //bfs utility function
		void dfs_utility(int,vector<bool> &,vector<T> &); //dfs utility function
		bool is_cycle_utility(int,vector<bool> &,int parent=-1);

	public:
		//ctor and dtor
		undirected_graph(const vector<T>&);
		~undirected_graph(){};
		
		//input functions
		void cin_graph(int );   // to input a graph from istream
		void cin_graph(const vector< pair<T,T > >&); // overloaded cin which excepts array of edges
		void add_vertex(const T); //utility function to add a vertex
		void add_edge(const T,const T);  // to add a edge in the graph

		//output functions
		void cout_graph();  //function to output graph

		//traversal techniques
		vector<T> bfs(const T&);  //bfs driver function
		vector<T> bfs();  //overloaded bfs function
		vector<T> dfs();  //overloaded dfs function
		vector<T> dfs(const T&); //dfs driver function

		//misc functions
		bool is_cycle(); //REPLACE IT WITH DISJOINT SET METHOD LATER
		vector<int> shortest_path(const T&); //shortest path by BFS 
		int connected_compoenents(); // return compoenents in a graph by bfs
	};
				//undirected graph template class end

				//undirected graph template specialized int class start
	template<>
	class undirected_graph<int>
	{
		friend ostream& operator<<(ostream &,const undirected_graph<int>&);
	protected:
		vector< vector<int> > G;
	private:
		void bfs_utility(int,vector<bool>&);//overloaded bfs utility
		void bfs_utility(int,vector<bool>&,vector<int> &); //bfs utility function
		void dfs_utility(int,vector<bool> &,vector<int> &); //dfs utility function
		bool is_cycle_utility(int,vector<bool> &,int parent=-1);

	public:
		//ctor and dtor
		undirected_graph(int s=0); // one arg ctor
		~undirected_graph(){};  //destructor

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
		bool is_cycle(); //REPLACE IT WITH DISJOINT SET METHOD LATER
		vector<int> shortest_path(int s=0); //by BFS
		int connected_compoenents(); // return compoenents in a graph by bfs

	};
				//undirected graph specialized template class end

				//undirected weighted graph template class started 

	template<typename T> class undirected_w_graph
	{
		template<typename U>friend ostream& operator<<(ostream &, undirected_w_graph<U> &);

	protected:
		vector< vector< pair<int,int> > > G;
		vector<T> mapping_table;
		map<T,int> reverse_mapping_table;
	private:
		void bfs_utility(int,vector<bool> &, vector<T> &);
		void dfs_utility(int,vector<bool> &, vector<T> &);
		bool is_cycle_utility(int,vector<bool> &,int parent=-1);
		void bfs_utility(int,vector<bool> &);
	public:

		// ctors and dtors 
		undirected_w_graph(const vector<T> &init);
		~undirected_w_graph(){}

		//input/output
		void cin_graph(int);// to input graph via istream
		void cin_graph(const vector<pair< pair<T,T> ,int> > &);//input graph via vector
		void add_edge(const T &,const T &, const int &); //to add an edge 
		void add_vertex(const T&); //to add an vertex
		void cout_graph();

		//traversal functions
		vector<T> bfs(const T &s);
		vector<T> bfs();
		vector<T> dfs(const T &s);
		vector<T> dfs();

		//misc functions
		bool is_cycle();
		int connected_compoenents();

		//shortest distance functions
		vector<int> shortest_distance(const T &);
		vector<int> shortest_distance_bf(const T &);

		//minimum spanning tree functions 
		int mst_prims(const T &);
		int mst_kruskals(const T &);

   };
   			//undirected weighted graph template class ends

   			//undirected weighted graph template specialized int class start
   template<> class undirected_w_graph<int>
	{
		friend ostream& operator<<(ostream &, undirected_w_graph<int> &);
	protected:
		vector< vector< pair<int,int> > > G;

	private:
		void bfs_utility(int,vector<bool> &,vector<int> &); //bfs utility function
		void dfs_utility(int,vector<bool> &, vector<int> &); //dfs utility function
		bool is_cycle_utility(int,vector<bool> &,int parent=-1);
		void bfs_utility(int,vector<bool> &);
	public:
		//ctors and dtors
		undirected_w_graph(int s=0);// ctor 
		~undirected_w_graph(){}; //dtor

		//input/output functions 
		void cin_graph(int);  // to input graph from istream
		void cin_graph(const vector< pair<pair<int,int>,int> >&); // to take input from vector
		void add_edge(const int &,const int &,const int &); //add and edge 
		void add_vertex(); //add a vertex
		void cout_graph(); //to print the graph via ostream 

		//traversal functions 
		vector<int> bfs(int s=0);  //bfs driver function
		vector<int> dfs(int s=0);  //dfs driver function

		//misc functions
		bool is_cycle();
		int connected_compoenents();

		//shortest distance 
		vector<int> shortest_distance(int s=0);
		vector<int> shortest_distance_bf(int s=0);

		//Minimum spanning tree functions 
		int mst_prims(int s=0);
		int mst_kruskals();//pending implementation
	};
   			//undirected weighted graph template specialized int class end

			//directed graph template class started 

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
				//directed graph template class ends

				//directed graph template specialized int class start
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
				//directed graph template specialized class end

				//directed weighted graph template class started 
	template<typename T> class directed_w_graph
	{
		template<typename U>friend ostream& operator<<(ostream &, directed_w_graph<U> &);

	protected:
		vector< vector< pair<int,int> > > G;
		vector<T> mapping_table;
		map<T,int> reverse_mapping_table;
	private:
		void bfs_utility(int,vector<bool> &, vector<T> &);
		void dfs_utility(int,vector<bool> &, vector<T> &);
		void kosarajus_algorithm(int,vector<bool> &,vector<int> &);
		void kosarajus_utility(int,vector<bool> &);
	public:

		// ctors and dtors 
		directed_w_graph(const vector<T> &init);
		~directed_w_graph(){}

		//input/output
		void cin_graph(int);// to input graph via istream
		void cin_graph(const vector<pair< pair<T,T> ,int> > &);//input graph via vector
		void add_edge(const T &,const T &, const int &); //to add an edge 
		void add_vertex(const T&); //to add an vertex
		void cout_graph();

		//traversal functions
		vector<T> bfs(const T &s);
		vector<T> bfs();
		vector<T> dfs(const T &s);
		vector<T> dfs();

		//misc functions
		bool is_cycle();
		int connected_compoenents();

		//shortest distance functions
		vector<int> shortest_distance(const T &);
		vector<int> shortest_distance_bf(const T &);

	
   };
   			//directed weighted graph template class end

   			//directed weighted graph template specialized int class start
   template<> class directed_w_graph<int>
	{
		friend ostream& operator<<(ostream &, directed_w_graph<int> &);
	protected:
		vector< vector< pair<int,int> > > G;

	private:
		void bfs_utility(int,vector<bool> &,vector<int> &); //bfs utility function
		void dfs_utility(int,vector<bool> &, vector<int> &); //dfs utility function
		void kosarajus_algorithm(int,vector<bool> &,vector<int> &);
		void kosarajus_utility(int, vector<bool> &);
	public:
		//ctors and dtors
		directed_w_graph(int s=0);// ctor 
		~directed_w_graph(){}; //dtor

		//input/output functions 
		void cin_graph(int);  // to input graph from istream
		void cin_graph(const vector< pair<pair<int,int>,int> >&); // to take input from vector
		void add_edge(const int &,const int &,const int &); //add and edge 
		void add_vertex(); //add a vertex
		void cout_graph(); //to print the graph via ostream 

		//traversal functions 
		vector<int> bfs(int s=0);  //bfs driver function
		vector<int> dfs(int s=0);  //dfs driver function

		//misc functions
		bool is_cycle();
		int connected_compoenents();

		//shortest distance 
		vector<int> shortest_distance(int s=0);
		vector<int> shortest_distance_bf(int s=0);

	};
					//directed weighted graph template specialized int class end 

					//DAG template class started 
	template<typename T> class dag
	{
		template<typename U> friend ostream& operator<<(ostream &,const dag<U> &); 
	protected:
		vector< vector<int> > G;
		vector<T> mapping_table;
		map<T,int> reverse_mapping_table;
	private:
		void bfs_utility(int,vector<bool>&,vector<T> &); //bfs utility function
		void dfs_utility(int,vector<bool> &,vector<T> &); //dfs utility function
		void kosarajus_algorithm(int,vector<bool> &,vector<int> &);
		void kosarajus_utility(int,vector<bool> &);
		bool is_cycle(); 

	public:
		//ctor and dtor
		dag(const vector<T>&);
		~dag(){};
		
		//input functions
		void cin_graph(int );   // to input a graph from istream
		void cin_graph(const vector< pair<T,T > >&); // overloaded cin which excepts array of edges
		void add_vertex(const T); //utility function to add a vertex
		void add_edge(const T,const T);  // to add a edge in the graph

		//output functions
		void cout_graph();  //function to output graph

		//traversal techniques
		vector<T> bfs(const T&);  //bfs driver function
		vector<T> bfs();  //overloaded bfs function
		vector<T> dfs();  //overloaded dfs function
		vector<T> dfs(const T&); //dfs driver function

		//misc functions
		vector<int> shortest_path(const T&); //shortest path by BFS
		int connected_compoenents();

		//dag function
		vector<T> topological_sort();
	};
						//DAG template class ends

						//DAG template specialized int class started 
	template<>
	class dag<int>
	{
		friend ostream& operator<<(ostream &,const dag<int>&);
	protected:
		vector< vector<int> > G;
	private:
		void bfs_utility(int,vector<bool>&,vector<int> &); //bfs utility function
		void dfs_utility(int,vector<bool> &,vector<int> &); //dfs utility function
		void kosarajus_algorithm(int,vector<bool> &,vector<int> &);
		void kosarajus_utility(int,vector<bool> &);
		bool is_cycle();

	public:
		//ctor and dtor
		dag(int s=0); // one arg ctor
		~dag(){};  //destructor

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
		int connected_compoenents();

		//dag functions 
		vector<int> topological_sort();

	};
				//DAG template specialized int class end
	template<typename T> class dag_w
	{
		template<typename U>friend ostream& operator<<(ostream &, dag_w<U> &);

	protected:
		vector< vector< pair<int,int> > > G;
		vector<T> mapping_table;
		map<T,int> reverse_mapping_table;
	private:
		void bfs_utility(int,vector<bool> &, vector<T> &);
		void dfs_utility(int,vector<bool> &, vector<T> &);
		void kosarajus_algorithm(int,vector<bool> &,vector<int> &);
		void kosarajus_utility(int,vector<bool> &);
		bool is_cycle();
		vector<int> shortest_distance_utility();
	public:

		// ctors and dtors 
		dag_w(const vector<T> &init);
		~dag_w(){}

		//input/output
		void cin_graph(int);// to input graph via istream
		void cin_graph(const vector<pair< pair<T,T> ,int> > &);//input graph via vector
		void add_edge(const T &,const T &, const int &); //to add an edge 
		void add_vertex(const T&); //to add an vertex
		void cout_graph();

		//traversal functions
		vector<T> bfs(const T &s);
		vector<T> bfs();
		vector<T> dfs(const T &s);
		vector<T> dfs();

		//misc functions
		int connected_compoenents();

		//dag functions 
		vector<T> topological_sort();
		vector<int> shortest_distance(const T & );

	
   };
   template<> class dag_w<int>
	{
		friend ostream& operator<<(ostream &, dag_w<int> &);
	protected:
		vector< vector< pair<int,int> > > G;

	private:
		void bfs_utility(int,vector<bool> &,vector<int> &); //bfs utility function
		void dfs_utility(int,vector<bool> &, vector<int> &); //dfs utility function
		void kosarajus_algorithm(int,vector<bool> &,vector<int> &);
		void kosarajus_utility(int, vector<bool> &);
		bool is_cycle();

	public:
		//ctors and dtors
		dag_w(int s=0);// ctor 
		~dag_w(){}; //dtor

		//input/output functions 
		void cin_graph(int);  // to input graph from istream
		void cin_graph(const vector< pair<pair<int,int>,int> >&); // to take input from vector
		void add_edge(const int &,const int &,const int &); //add and edge 
		void add_vertex(); //add a vertex
		void cout_graph(); //to print the graph via ostream 

		//traversal functions 
		vector<int> bfs(int s=0);  //bfs driver function
		vector<int> dfs(int s=0);  //dfs driver function

		//misc functions
		int connected_compoenents();


		//dag functions 
		vector<int> topological_sort();
		vector<int> shortest_distance(int s=0);

	};


	//DISJOINT SET CLASS

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
	#include "exstl.inl"
} // namespace exstd closed
#endif //include guards closed
