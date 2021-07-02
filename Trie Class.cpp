#include<bits/stdc++.h>
using namespace std;
struct TrieNode
{
    unordered_map<int , TrieNode*> um;
    bool isend;
    TrieNode()
    {
        isend=false;
    }
};
    class Trie
    {

        TrieNode *roote;
    public:
        int size{0};

        Trie()
        {
            roote=new TrieNode();
        }

        void Insert(string );
        bool Search(string );
        TrieNode* DeleteU(string&s,int i,TrieNode*root);
        void Delete(string );
        int Size()
        {
            return this->size;
        }
    };
    void Trie::Insert(string s)
    {
        TrieNode *root=roote;
        for(int i{0};i<s.size();i++)
            {
                if(root->um.find(s.at(i))!=root->um.end())
                {
                    root=  root->um[s.at(i)];
                }
                else
                {
                    TrieNode *temp= new TrieNode();
                    root->um[s.at(i)]=temp;
                    root=temp;
                }
            }
            root->isend=true;
            size++;
    }
    bool Trie:: Search( string target)
    {
        TrieNode *root=roote;
        for(int i=0;i<target.size();i++)
        {
            if(root->um.find(target.at(i))!=root->um.end())
            {
                root= root->um[target.at(i)];
            }
            else
            {
                return false;
            }
        }

        return root->isend;
    }
    void Trie::Delete(string s)
    {
        TrieNode *root=roote;
        roote=DeleteU(s,0,root);
        size--;
    }
    TrieNode* Trie:: DeleteU( string &s,int i, TrieNode* root)
        {
            if(root==nullptr) return root;
            if(i==s.size())
            {
                root->isend=false;
                if(root->um.empty())
                {
                    if(root!=roote) {delete root; root=nullptr;}
                }
                return root;
            }

            root->um[s.at(i)]=DeleteU(s,i+1,root);
            if(root->um.empty())
                {
                    if(root!=roote) {delete root; root=nullptr;}
                }
                return root;
        }
    int main()
    {
        cout<<"Trie Class Implementation\n";
        Trie T;
        T.Insert("geek");
        T.Insert("geeks");
        if(T.Search("geek")) cout<<"present"<<endl;
        cout<<T.Size()<<endl;
        T.Delete("geek");
         if(!T.Search("geek")) cout<<" Not present"<<endl;
        cout<<T.Size()<<endl;
    }
