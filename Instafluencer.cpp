#include<bits/stdc++.h>
using namespace std;
#define int long long
class GraphAlgorithm{ //Parent class with constructor, has hypescore and adjacency list and size.
public:
    GraphAlgorithm(int n, vector<int>hy, vector<pair<int, int>>al){
        for(int i=0;i<n;i++){
            hs[i+1] = hy[i];
        }
        for(int i=0;i<al.size();i++){
            int u = al[i].first;
            int v = al[i].second;
            adj[u].push_back(v);
        }
        size = n;
    }
    virtual void query(){ //virtual function

    }
    map<int, int>hs;
    map<int, vector<int>>adj;
    int size;
};
class isCycle:public GraphAlgorithm{ //Cycle checker
public:
    isCycle(int n, vector<int>hy, vector<pair<int, int>>al) : GraphAlgorithm(n, hy, al){

    }
    void query(){
        int v = size;
        vector<int> Din(v+1, 0); //BFS with in-degree method to find cycle
        queue<int>q;
        int vis = 0;
        for(int i=1;i<=v;i++){
            for(auto v : adj[i]){
                Din[v]++;
            }
        }
        for(int i=1;i<=v;i++){
            if(Din[i]==0){
                q.push(i);
            }
        }
        while(!q.empty()){
            int u = q.front();
            q.pop();
            vis++;
            for(auto v : adj[u]){
                Din[v]--;
                if(Din[v]==0){
                    q.push(v);
                }
            }
        }
        if(v != vis){
            isCyclic = true; //If number of nodes visited is not equal to size of graph, then there is a cycle.
        }
    }
    bool isCyclic = false;
};
class indepComponent:public GraphAlgorithm{ //To print out number of SCCs and the one with max size.
public:
    map<int, vector<int>>tadj;
    vector<int>order;
    int SCC = 0;
    vector<int>SCCsize;
    int SCCmax;
    indepComponent(int n, vector<int>hy, vector<pair<int, int>>al) : GraphAlgorithm(n, hy, al){
        for(int i=1;i<=size;i++){
            for(auto u : adj[i]){
                tadj[u].push_back(i); //Transposed adjaceny list
            }
        }
    }
    void DFS(int ve, vector<bool>&vis){ //DFS fn
        if(vis[ve]){
            return;
        }
        vis[ve] = true;
        for(auto u : adj[ve]){
            if(!vis[u]){
                DFS(u, vis);
            }
        }
        order.push_back(ve);
    }
    void cnt(int ve, vector<bool>&vis, int& co){ //Count checking DFS on transpose
        if(vis[ve]){
            return;
        }
        co++;
        vis[ve]=true;
        for(auto u : tadj[ve]){
            cnt(u, vis, co);
        }
    }
    void query(){
        int v = size;
        vector<bool>vis(v+1, false);
        for(int i=1;i<=v;i++){
            if(!vis[i]){
                DFS(i, vis);
            }
        }
        vector<bool>nvis(v+1, false);
        for(int i=order.size()-1;i>=0;i--){ //Reverse order method on Transposed graph.
            if(!nvis[order[i]]){
                int a = 0;
                cnt(order[i], nvis, a);
                SCCsize.push_back(a);
                SCC++;
            }
        }
        SCCmax = *max_element(SCCsize.begin(), SCCsize.end());
    }
};
class validOrder:public GraphAlgorithm{
public:
    vector<int>forder;
    validOrder(int n, vector<int>hy, vector<pair<int, int>>al) : GraphAlgorithm(n, hy, al){

    }
    void query(){
        int v = size;
        vector<int>Din(v+1, 0); //in-degree method as lexicographic toposort
        for(int i=1;i<=v;i++){
            for(auto u : adj[i]){
                Din[u]++;
            }
        }
        priority_queue<int, vector<int>, greater<int>>pq; //priority queue to ensure lexicographical ordering
        for(int i=1;i<=v;i++){
            if(Din[i]==0){
                pq.push(i);
            }
        }
        int cnt = 0;
        while(!pq.empty()){
            int u = pq.top();
            pq.pop();
            forder.push_back(u);
            for(auto w : adj[u]){
                if(--Din[w] == 0){
                    pq.push(w);
                }
            }
            cnt++;
        }
    }
};
class maxHype:public GraphAlgorithm{
public:
    maxHype(int n, vector<int>hy, vector<pair<int, int>>al) : GraphAlgorithm(n, hy, al){
        for(int i=0;i<=n;i++){
            roots.push_back(0);
        }
        for(int i=1;i<=n;i++){
            for(auto u : adj[i]){
                tadj[u].push_back(i);
            }
        }
    }
    map<int, vector<int>>tadj;
    map<int, vector<int>>adjcond;
    set<int>cond;
    map<int, int>weights;
    vector<int>roots;
    vector<int>order;
    vector<vector<int>>comps;
    int maxw = INT_MIN;
    void DFS(int ve, vector<bool>&vis){
        if(vis[ve]){
            return;
        }
        vis[ve] = true;
        for(auto u : adj[ve]){
            if(!vis[u]){
                DFS(u, vis);
            }
        }
        order.push_back(ve);
    }
    void spDFS(int ve, vector<bool>&vis, vector<int>&op){ //DFS for transpose graph, with parameter to maintain components
        if(vis[ve]){
            return;
        }
        vis[ve] = true;
        for(auto u : tadj[ve]){
            if(!vis[u]){
                spDFS(u, vis, op);
            }
        }
        op.push_back(ve);
    }
    void topo(int ve, vector<bool>&vis, stack<int>&stk){ //toposort (non lexicographic)
        if(vis[ve]){
            return;
        }
        vis[ve]=true;
        for(auto u : adjcond[ve]){
            if(!vis[u]){
                topo(u, vis, stk);
            }
        }
        stk.push(ve);
    }
    void query(){
        int v = size;
        vector<bool>vis(v+1, false);
        for(int i=1;i<=v;i++){
            if(!vis[i]){
                DFS(i, vis);
            }
        }
        vector<bool>nvis(v+1, false);
        for(int i=order.size()-1;i>=0;i--){
            if(!nvis[order[i]]){
                vector<int>comp;
                spDFS(order[i], nvis, comp); //condensing graph
                comps.push_back(comp);
                int root = *min_element(comp.begin(), comp.end());
                for(auto u : comp){
                    roots[u] = root;
                    weights[root] += hs[u]; //finding weight of each node in condensed graph.
                }
            }
        }
        for(int i=1;i<=size;i++){   
            cond.insert(roots[i]);
            for(auto u : adj[i]){
                if(roots[i] != roots[u]){
                    adjcond[roots[i]].push_back(roots[u]); //adding edges between SCCs to condensed graph
                }
            }
        }
        stack<int>stk;
        vector<bool>nnvis(v+1, false);
        for(auto i : cond){
            if(!nnvis[i]){
                topo(i, nnvis, stk);
            }
        }
        map<int, int>dp = weights;
        vector<bool>nnnvis(v+1, false);
        while(!stk.empty()){ //method to find longest path in condensed graph.
            int u = stk.top();
            stk.pop();
            if(adjcond[u].size() == 0){
                maxw = max(maxw, dp[u]);
            }
            for(auto v : adjcond[u]){
                dp[v] = max(dp[v], dp[u] + weights[v]);
                maxw = max(maxw, dp[v]);
            }
        }
    }
};
int32_t main(){
    int n, m;
    cin>>n>>m;
    vector<int>hy(n);
    vector<pair<int,int>>al(m);
    for(int i=0;i<n;i++){
        cin>>hy[i];
    }
    for(int i=0;i<m;i++){
        cin>>al[i].first>>al[i].second;
    }
    //precomputing all queries, to ensure each query type only runs once, and just has to output the stored answer on repeated calls.
    string cyc;
    int SCC, SCCmax;
    vector<int>forder;
    int flag = 0;
    int maxw;
    isCycle cy(n, hy, al);
    cy.query();
    if(cy.isCyclic){
        cyc = "YES";
    }else{
        cyc = "NO";
    }
    indepComponent ind(n, hy, al);
    ind.query();
    SCC = ind.SCC;
    SCCmax = ind.SCCmax;
    validOrder val(n, hy, al);
    if(cyc == "NO"){
        val.query();
        forder = val.forder;
    }
    maxHype hmax(n, hy, al);
    hmax.query();
    maxw = hmax.maxw;
    int q;
    cin>>q;
    for(int i=0;i<q;i++){ 
        int a;
        cin>>a;
        if(a==1){
            cout<<cyc<<endl;
        }else if(a==2){
            cout<<SCC<<' '<<SCCmax<<endl;
        }else if(a==3){
            if(cyc == "YES"){
                cout<<"NO"<<endl;
                continue;
            }
            for(int i=0;i<forder.size();i++){
                cout<<forder[i]<<' ';
            }
            cout<<endl;
        }else if(a==4){
            cout<<maxw<<endl;
        }
    }
}
