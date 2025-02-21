#include<bits/stdc++.h>
using namespace std;
class Graph{
public:
    Graph(int nv1, int ne1){
        nv = nv1;
        ne = ne1;
        for(int i=0;i<nv1;i++){
            vertices.insert(i);
        }
    }
    bool isReachable(int u, int v){   
        queue<int> queue;
        queue.push(u);
        bool visited[nv] = {0};
        set<int> reachableNodes;
        while(!queue.empty()){
            int u = queue.front();
            visited[u] = true;
            queue.pop();
            reachableNodes.insert(u);
            for (auto & x: edges[u]){
                if (!visited[x]){
                    visited[x] = true;
                    queue.push(x);
                }
            }
        }
        if(reachableNodes.find(v)!=reachableNodes.end()){
            cout<<"Yes"<<endl;
            return true;
        }else{
            cout<<"No"<<endl;
            return false;
        }
    }
    void add_edge(int u, int v){
        edges[u].insert(v);
        edges[v].insert(u);
    }
    void remove_edge(int u, int v){
        if(edges[u].find(v)!=edges[u].end()){
            edges[u].erase(v);
            edges[v].erase(u);
        }
    }
    bool isEdge(int u, int v){
        if(edges[u].find(v)!=edges[u].end()){
            return true;
        }else{
            return false;
        }
    }
    void operator !(){
        map<int, set<int>>nmap;
        for(int i=0;i<nv;i++){
            for(int j=0;j<nv;j++){
                if(i==j){
                    continue;
                }
                if(edges[i].find(j)==edges[i].end()){
                    nmap[i].insert(j);
                }
            }
        }
        edges = nmap;
    }
    void operator +(Graph &G2){
        for(auto &x: G2.vertices){
            vertices.insert(x);
        }
        for(auto &x: G2.vertices){
            for(auto &y: G2.edges[x]){
                add_edge(x, y);
            }
        }
        nv = max(nv, G2.nv);
    }
    void operator -(Graph &G2){
        map<int, set<int>>nmap;
        for(auto &x: G2.vertices){
            vertices.insert(x);
        }
        for(auto &x: vertices){
            for(auto &y: edges[x]){
                if(isEdge(x, y) && G2.isEdge(x, y)){
                    nmap[x].insert(y);
                }
            }
        }
        edges = nmap;
        nv = max(nv, G2.nv);
    }
    int getn(){
        return nv;
    }
private:
    set<int>vertices;
    map<int, set<int>>edges;
    int nv;
    int ne;
friend ostream& operator << (ostream& stream, Graph &G);
friend istream& operator >> (istream& stream, Graph &G);
};
ostream& operator << (ostream& stream, Graph &G) {
    for(int i=0;i<G.nv;i++){
        stream<<"Vertex "<<i<<": ";
        for(auto &x : G.edges[i]){
            stream<<x<<' ';
        }
        stream<<endl;
    }
    return stream;
}
istream& operator >> (istream& stream, Graph &G){
    for(int i=0;i<G.ne;i++){
        int a, b;
        stream>>a>>b;
        G.add_edge(a, b);
    }
    return stream;
}
int main(){
    string a;
    cin>>a;
    int x, y;
    cin>>x>>y;
    Graph graph(x, y);
    cin>>graph;
    while(true){
        cin>>a;
        if(a == "union"){
            string b;
            cin>>b;
            cin>>x>>y;
            Graph g2(x, y);
            cin>>g2;
            graph + g2;
        }else if(a=="intersection"){
            string b;
            cin>>b;
            cin>>x>>y;
            Graph g2(x, y);
            cin>>g2;
            graph - g2;
        }else if(a=="complement"){
            !graph;
        }else if(a=="printGraph"){
            cout<<graph;
        }else if(a=="isReachable"){
            cin>>x>>y;
            graph.isReachable(x, y);
        }else if(a=="add_edge"){
            cin>>x>>y;
            graph.add_edge(x, y);
        }else if(a=="remove_edge"){
            cin>>x>>y;
            graph.remove_edge(x, y);
        }else if(a=="end"){
            break;
        }
    }
}