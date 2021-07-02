#include <bits/stdc++.h>
//using namespace std;
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
#define IOS ios_base::sync_with_stdio(false),cin.tie(NULL)
#define READ freopen("input.txt", "r", stdin); 
#define ERROR freopen("error.txt", "w", stderr); 
#define OUTPUT freopen("output.txt", "w", stdout); 


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
int main() 
{ 
	IOS;
#ifndef ONLINE_JUDGE 
  	READ;
  	ERROR;
  	OUTPUT; 
#endif 	
  
	int t;
	cin>>t;  
	while(t--) 
	{ 
		cout<<"For int: \n";
		disjoint_set<int> ds_int(4); //for int
		ds_int.Union(0,1);
		ds_int.Union(2,3);
		cout<<ds_int.Find(1)<<endl;
		cout<<ds_int.Find(3)<<endl;
		ds_int.Union(2,3);
		cout<<ds_int.Find(0)<<" "<<ds_int.Find(1)<<" "<<ds_int.Find(2)<<" "<<ds_int.Find(3)<<endl;
		
		cout<<"FOR char : \n";
		disjoint_set<char> ds_char({'a','b','c','d'}); //for char
		ds_char.Union('a','b');
		ds_char.Union('c','d');
		cout<<ds_char.Find('b')<<endl;
		cout<<ds_char.Find('d')<<endl;
		ds_char.Union('b','d');
		cout<<ds_char.Find('a')<<" "<<ds_char.Find('b')<<" "<<ds_char.Find('c')<<" "<<ds_char.Find('d')<<endl;

		cout<<"FOR string : \n";
		disjoint_set<string> ds_string({"A","B","C","D"}); // for string 
		ds_string.Union("A","B");
		ds_string.Union("C","D");   
		cout<<ds_string.Find("B")<<endl;
		cout<<ds_string.Find("D")<<endl;
		ds_string.Union("B","D");
		cout<<ds_string.Find("A")<<" "<<ds_string.Find("B")<<" "<<ds_string.Find("C")<<" "<<ds_string.Find("D")<<endl;

	
	} 
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<"\n"; 
return 0; 
} 






