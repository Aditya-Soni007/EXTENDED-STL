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
#include<time.h>
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
#define IOS ios_base::sync_with_stdio(false),cin.tie(NULL)
#define READ freopen("input.txt", "r", stdin); 
#define ERROR freopen("error.txt", "w", stderr); 
#define OUTPUT freopen("output.txt", "w", stdout); 

	struct TrieNode
	{
		unordered_map<char,TrieNode*> um;
		bool isEnd{false};
		size_t augmented_sz{0};
	};
template<typename T=string>class trie
{
	template<typename U> friend ostream& operator<<(ostream &,const trie<U> &);
protected:
	TrieNode *root;

private:
	bool insert_utility(TrieNode *,const T &,int i);
	pair<TrieNode*,bool> delete_utility(TrieNode *,const T &,int );
	int count_utility(TrieNode *,const T &,int i);
	void prefix_search_utility(TrieNode *,string s,vector<T> &)const;
	void clear_utility(TrieNode *);
public:
	//ctors and destructors
	trie(); //constructor
	trie(const typename vector<T>::iterator &,const typename vector<T>::iterator &);  //iterator ctor
	trie(const vector<T> &); //container ctor
	~trie(){}  //dtor

	//inserton functions 
	bool insert(const T &,int i=0);

	//search functions
	bool find(const T &) const;

	//deletion function
	bool erase(const T &,int i=0);

	//size function
	size_t size() const;

	//count words with given prefix
	int count(const T &,int i=0);

	//OVERLOADED COUNT FUNCTION TO GET ALL PREFIXES
	vector<T> prefix_search(const T &,int i=0) const;

	//get trie in lexigraphical order
	vector<T> lexiographical_prefix_search(const T &,int i=0) const;

	//is empty function
	bool empty()const;

	//clear function 
	void clear();

};
	template<typename T> void trie<T>::clear_utility(TrieNode *temp)
	{
		for(auto &i: temp->um)
		{
			clear_utility(i.second);

		}
		temp->augmented_sz=temp->isEnd=0;
		delete temp;
		temp=nullptr;
	}
	template<typename T> void trie<T>::clear()
	{

		TrieNode *temp{root};
		for(auto &i: temp->um)
		{
			clear_utility(i.second);
		}
		temp->um.clear();
		temp->augmented_sz=0;
	}
	template<typename T> bool trie<T>::empty() const
	{
			return (root->augmented_sz==0);
	}
	//PREFIX SEARCH FUNCTION
	template<typename T> vector<T> trie<T>::lexiographical_prefix_search(const T &s,int i)const
	{
		vector<T> res;
		TrieNode *temp{root};
		for(auto &i:s)
		{
			if(temp->um.find(i)==temp->um.end()) return res;
			temp=temp->um[i];
		}

		prefix_search_utility(temp,s,res);
		sort(res.begin(),res.end());
		return res;
	}
	template<typename T> void trie<T>::prefix_search_utility(TrieNode *temp,string s,vector<T> &res) const
	{
		if(temp->isEnd)
		{
			res.emplace_back(s);
		}
		if(temp->um.empty()) return;

		for(auto &i: temp->um)
		{
			prefix_search_utility(i.second,s+i.first,res);
		}
	}
	template<typename T> vector<T> trie<T>::prefix_search(const T &s,int i) const
	{
		vector<T> res;
		TrieNode *temp{root};
		for(auto &i:s)
		{
			if(temp->um.find(i)==temp->um.end()) return res;
			temp=temp->um[i];
		}

		prefix_search_utility(temp,s,res);

		return res;
	}


	//COUNT PREFIX FUNCTIONS
	template<typename T> int trie<T>::count_utility(TrieNode *temp,const T &s,int i)
	{
		if(i==s.size())
		{
			return temp->isEnd+temp->augmented_sz;
		}
		if(temp->um.find(s[i])==temp->um.end()) return 0;
		return count_utility(temp->um[s[i]],s,i+1);
	}
	template<typename T> int trie<T>::count(const T &s,int i)
	{
		TrieNode *temp{root};
		return count_utility(temp,s,i);
	}

	//DELETE FUNCTIONS
	template<typename T> pair<TrieNode*,bool> trie<T>::delete_utility(TrieNode *temp,const T &s,int i)
	{
		if(i==s.size())
		{
			if(!temp->isEnd) return {temp,false};
			if(temp->um.empty())
			{
				delete temp;
				temp=nullptr;
				return {nullptr,true};
			}
			temp->isEnd=false;
			return {temp,true};

		}
		if(temp->um.find(s[i])==temp->um.end())
		{
			return {temp,false};
		}
		pair<TrieNode*,bool> p= delete_utility(temp->um[s[i]],s,i+1);
		if(p.first==nullptr) temp->um.erase(s[i]);
		if(p.second) temp->augmented_sz--;
		if(temp->um.empty() and temp->isEnd==false)
		{
			delete temp;
			temp=nullptr;
			return {nullptr,true};
		}
		return {temp,p.second};

		
	}
	template<typename T> bool trie<T>::erase(const T &s,int i)
	{
			TrieNode *temp{root};
			pair<TrieNode*,bool> p= delete_utility(temp,s,i);
			return p.second;
	}

	//SIZE FUNCTION
	template<typename T>size_t trie<T>::size() const
	{
		return root->augmented_sz;
	}

	//SEARCH FUNCTION
	template<typename T>bool trie<T>::find(const T &s) const
	{
		const TrieNode *temp{root};

		for(auto &i: s)
		{
		 	if(temp->um.find(i)==temp->um.end())
		 	{
		 		return false;
		 	}
		 	temp=temp->um.at(i);
		}
		 	return temp->isEnd;

	}

	//CONSTRUCTORS
	template<typename T>trie<T>::trie()
	 {
	 	root=new TrieNode();
	 }
	template<typename T>trie<T>::trie(const typename vector<T>::iterator &b,const typename vector<T>::iterator &e)
	 {
	 	root=new TrieNode();
	 	for(auto itr=b ; itr!=e ; itr++) insert(*itr);
	 }
	template<typename T>trie<T>::trie(const vector<T> &v)
	 {
	 	root=new TrieNode();
	 	for(auto &i : v) insert(i);
	 }

	//INSERT FUNCTIONS 
	template<typename T>bool trie<T>::insert_utility(TrieNode *temp,const T &s,int i)
	 {
	 		if(i==s.size())
	 		{
	 			if(temp->isEnd)
	 			{
	 				return false;
	 			}
	 			return temp->isEnd=true;
	 		}

	 		if(temp->um.find(s[i])==temp->um.end())
	 		{
	 			temp->um[s[i]]=new TrieNode();
	 		}
	 		if(insert_utility(temp->um[s[i]],s,i+1))
	 		{
	 			temp->augmented_sz++;
	 			if(s[i]=='k') cout<<temp->augmented_sz<<endl;
	 			return true;
	 		}
	 		return false;

	 }
	template<typename T>bool trie<T>::insert(const T &s,int i)
	 {
	 	TrieNode *temp{root};
	 	return insert_utility(temp,s,i);
	 }
	 template<typename T> ostream& operator<<(ostream &os,const trie<T> &obj) 
	 {
	 	auto res=obj.prefix_search("");
	 	for(auto &i: res) cout<<i<<" ";
	 		cout<<"\n";
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

	int testcases;
	// cin>>t;  
	testcases=1;
	while(testcases--)  
	{
		trie t;
		t.insert("geek");
		t.insert("geeks");
		cerr<<t.erase("geeks");
		cerrd<<t.find("geek")<<endl;

	} 
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<"\n"; 
return 0; 
} 