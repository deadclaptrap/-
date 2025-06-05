#include <iostream>
#include <map>

using namespace std;

template <typename key, typename weight, typename value>
class Node{
    value val;
    map<key,weight> edges;
public:
    Node() : val(),edges(){}
    Node(Node const & nn ) : edges(nn.edges), val(nn.val){};
    Node(Node && t) noexcept {
        edges= move(t.vertecie);
        val = t.val;
        t.vertecies.clear();
        t.value = 0;
    }
    Node& operator= (const Node & t){
        edges=t.edges;
        val=t.val;
        return *this;
    };
    Node& operator=(Node && t) noexcept {
        edges= move(t.vertecie);
        val = t.val;
        t.vertecies.clear();
        t.value = 0;
        return *this;
    }
    value& v(){
        return val;
    }
    const value& v() const{
        return val;
    }
    size_t size(){
        return edges.size();
    }
    bool empty(){
        return edges.empty();
    }
    void clear(){
        edges.clear();
    }
    typename map<key, weight>::iterator beginn(){
        auto it = edges.begin();
        return it;
    }
    typename map<key, weight>::iterator endd(){
        auto it = edges.end();
        return it;
    }
    const typename map<key, weight>::iterator cendd(){
        auto it = edges.cend();
        return it;
    }
    const typename map<key, weight>::iterator cbeginn(){
        auto it = edges.cbegin();
        return it;
    }
};


template <typename key_type, typename weight_type,typename value_type>
class Graph{
    map<key_type,Node<key_type,weight_type,value_type>> point ;
    template <typename key_type1, typename weight_type1,typename value_type1>
    friend class Node;
public:
    Graph(): point (){}
    Graph(const Graph& t): point (t.point ){}
    Graph(Graph && t)  {
        point  = move(t.point );
        t.point .clear();
    }

    Graph& operator= (Graph const & t){
        point  = t.point ;
        return *this;
    }
    Graph& operator= (Graph && t)  {
        point  = move(t.vertexes);
        t.vertexes.clear();
        return *this;
    }
    size_t size(){
        return point .size();
    }
    bool empty(){
        return point.empty();
    }
    void clear(){
        point.clear();
    };
    void swap(Graph& t){
        std::swap(this->point,t.point);
    }
    friend void swap(Graph& Graph1,Graph& Graph2){
        std::swap(Graph1.point,Graph2.point);
    }
    typename map<key_type,Node<key_type,weight_type,value_type>>::iterator beging(){
        auto it = point.begin();
        return it;
    }
    typename map<key_type,Node<key_type,weight_type,value_type>>::iterator endg(){
        auto it = point.end();
        return it;
    }
    const typename map<key_type,Node<key_type,weight_type,value_type>>::iterator cendg(){
        auto it = point.cend();
        return it;
    }
    const typename map<key_type,Node<key_type,weight_type,value_type>>::iterator cbeging(){
        auto it = point.cbegin();
        return it;
    }
    size_t degree_out(key_type key){
        return point[key].size();
    }
    size_t degree_in(key_type key){
        if(point.find(key)==point.end())
        {
            throw "not found";
        }
        int number = 0;
        for(auto& item : point)
        {

                for(auto it = item.second.beginn();it!= item.second.endd(); it++)
                {
                    if(it->first == key&& item.first!= key)
                        number++;
                }
        }
        return number;
    }

    bool loop(key_type key){
        if(point.find(key)==point.end())
        {
            throw "not found";
        }
        int number = 0;
        for(auto& item : point)
        {

            for(auto it = item.second.beginn();it!= item.second.endd(); it++)
            {
                if(it->first == key && item.first== key)
                    return true;
            }
        }
    return false;
    }
};



int main(){
    Node <int, int, int> n;
    n.v()= 2 ;
    cout << n.v() << " ";
    Graph<int,int,int> g1;
    Graph<int,int,int> g2(g1);
    cout << g1.size() << " ";
    swap(g1,g2);
    g1.swap(g2);
    cout << g1.size();
    g1 = g2;
    return 0;
}
