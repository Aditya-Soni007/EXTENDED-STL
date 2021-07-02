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
#define endl '\n'

template<typename T> class segment_tree
{
protected:
	vector<T> tree; 
	int starting_index;
	int ending_index;
	const std::function<T(const T &,const T &)> *combine;
	T base_case;
private:
	T query_utility(int qs,int qe,int low,int high,int index=0);
	T update_utility(int target,int value,int low,int high,int index=0);

public:
	//ctors and dtors 
	segment_tree(const vector<T> &,const T & ,const std::function<T(const T &,const T &)>&);
	segment_tree(const typename vector<T>::iterator &,const typename vector<T>::iterator &,const T &,const std::function<T(const T&,const T&)> &);
	~segment_tree(){}

	//build tree
	T build_tree(const vector<T> &,int ,int,int index=0);
	T build_tree(const typename vector<T>::iterator &,const typename vector<T>::iterator &,int ,int ,int index=0);

	//query function 
	T query(int,int);

	//update function
	void update(int,int);

	//return the root of the tree
	auto root();

};
template<typename T>auto segment_tree<T>::root()
{

	return tree.cbegin();
}
template<typename T> T segment_tree<T>::update_utility(int target,int value,int low,int high,int index)
{
	if(low>target or high<target) return tree[index];
	else if(target==low and target==high) 
	{
		tree[index]=value;
		return tree[index];
	}
	int mid=low+((high-low)/2);
return tree[index]=(*combine)(update_utility(target,value,low,mid,2*index+1),update_utility(target,value,mid+1,high,2*index+2));
}
template<typename T> void segment_tree<T>::update(int target,int value)
{
	if(target<starting_index or target>ending_index)
	{
		cerr<<"Exception 404!";
		exit(1);
	}
	update_utility(target,value,starting_index,ending_index);
}
template<typename T> T segment_tree<T>::query_utility(int qs,int qe,int low,int high,int index)
{
	if(low>qe or high<qs)
	{
		return base_case;
	}
	else if(qs<=low and qe>=high)
	{
		return tree[index];
	}
	int mid= low+((high-low)/2);
return (*combine)(query_utility(qs,qe,low,mid,2*index+1),query_utility(qs,qe,mid+1,high,2*index+2));
}
template<typename T> T segment_tree<T>::query(int low,int high)
{
	if(low<starting_index or high>ending_index)  //RAISE AN EXCEPTION HERE
	{
		cerr<<"Exception 404!\n";
		exit(0);
	}
	return query_utility(low,high,starting_index,ending_index);
}
	template<typename T> segment_tree<T>::segment_tree(const vector<T> &v,const T &bc,const std::function<T(const T&,const T&)> &func)
	{		
			T init;
			base_case=bc;
			tree.resize(4*v.size(),init);
			this->starting_index=0;
			this->ending_index=v.size()-1;
			combine=&func;
			build_tree(v,starting_index,ending_index);
			// for(auto &i: tree) cout<<i<<" ";
			// 	cout<<endl;
	}
template<typename T> segment_tree<T>::segment_tree(const typename vector<T>::iterator &low,const typename vector<T>::iterator &high,const T &bc,const std::function<T(const T &,const T&)> &func )
{
	T init;
	base_case=bc;
	int vec_size= high-low;
	tree.resize(4*vec_size,init);
	this->starting_index=0;
	this->ending_index=vec_size-1;
	combine=&func;
	build_tree(low,high,starting_index,ending_index);
	// for(auto &i: tree) cout<<i<<" ";
	// 			cout<<endl;
}
template<typename T> T segment_tree<T>::build_tree(const vector<T> &v,int low,int high,int index)
{
		if(low==high)
		{
			tree[index]=*(v.begin()+low);
			return tree[index];
		}
		int mid=low+((high-low)/2);
		return tree[index]=(*combine)(build_tree(v,low,mid,2*index+1),build_tree(v,mid+1,high,2*index+2));
}
template<typename T> T segment_tree<T>::build_tree(const typename vector<T>::iterator &sta,const typename vector<T>::iterator &en,int low,int high,int index)
{
	if(low==high)
	{
		tree[index]=*(sta+low);
		return tree[index];
	}
	int mid=low+((high-low)/2);
return tree[index]=(*combine)(build_tree(sta,en,low,mid,2*index+1),build_tree(sta,en,mid+1,high,2*index+2));	
}





int combine(const int &a,const int &b){return a+b;}

int main()
{
	IOS;
	#ifndef ONLINE_JUDGE
		READ;
		ERROR;
		OUTPUT;
	#endif
		int testcases;
		// cin>>testcases;
		testcases=1;
		while(testcases--)
		{
			segment_tree<int> seg{{10,20,30,40},0,combine};
			const auto it=seg.root();
			cout<<*it<<endl;
			
		}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<"\n"; 
	return 0;
}