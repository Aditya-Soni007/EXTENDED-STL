#include<bits/stdc++.h>
using namespace std;
class error_404: public exception
{
protected:
	string msg;
public:
	error_404(const char * c,int ver,int ul): msg{c}
	{
		msg+=":: _M_range_check:_n(which is "+to_string(ver)+")"+"doesn't exist in this->size(which is "+to_string(ul)+")\n";
	}
	virtual ~error_404() noexcept=default;
	virtual const char* what() const noexcept override
	{
		return msg.c_str();
	}

};
class cycle_in_DAG : public exception
{
protected:
    string msg;
public:
    cycle_in_DAG(const char *c):msg{c}
    {
        msg+="::_M_cycle_check->true:_cycle_not_allowed in ";
        msg+=c;
    }
    virtual ~cycle_in_DAG() noexcept =default;
    const char* what() const noexcept override
    {
        return msg.c_str();
    }
};
int main()
{
//    throw error_404("exstd::undirected_w_graph",3,3);
    throw cycle_in_DAG("exstd::dag");

}
