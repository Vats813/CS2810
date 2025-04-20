#include<bits/stdc++.h>
using namespace std;
class Sentinel{
public:
    Sentinel(){

    }
    void setID(int ID){
        id = ID;
    }
    void setName(string N){
        name = N;
    }
    void setRank(string R){
        rank = R;
    }
    virtual void setNHR(int n){

    }
    string getRank(){
        return rank;
    }
    int getID(){
        return id;
    }
    virtual int countHigherRanked(){
        return 0;
    }
private:
    int id;
    string name;
    string rank;
friend class CMP;
};
class CMP{
public:
    bool operator()(Sentinel * A, Sentinel * B){
        if(A->rank == "SENAPATI" && B->rank == "SENAPATI"){
            return A->id < B->id;
        }else if(A->rank == "SENAPATI"){
            return true;
        }else if(B->rank == "SENAPATI"){
            return false;
        }else if(A->rank == "DANDANAYAKA" && B->rank == "DANDANAYAKA"){
            return A->id < B->id;
        }else if(A->rank == "DANDANAYAKA"){
            return true;
        }else if(B->rank == "DANDANAYAKA"){
            return false;
        }else if(A->rank == "CHATURANGINI" && B->rank == "CHATURANGINI"){
            return A->id < B->id;
        }
        return false;
    }
};
class Senapati:public Sentinel{
public:
    Senapati(int ID, string N, string R){
        this->setID(ID);
        this->setName(N);
        this->setRank(R);
    }
    int countHigherRanked(){
        return 0;
    }
};
class Dandanayaka:public Sentinel{
public:
    Dandanayaka(int ID, string N, string R){
        this->setID(ID);
        this->setName(N);
        this->setRank(R);
    }
    void setNHR(int n){
        nhr = n;
    }
    int countHigherRanked(){
        return nhr;
    }
private:
    int nhr;
};
class Chaturangini:public Sentinel{
public:
    Chaturangini(int ID, string N, string R){
        this->setID(ID);
        this->setName(N);
        this->setRank(R);
    }
    void setNHR(int n){
        nhr = n;
    }
    int countHigherRanked(){
        return nhr;
    }
private:
    int nhr;
};
template<typename T>
class Kingdom{
public:
    Kingdom(int n){
        num = n;
        nsena = 0;
        ndanda = 0;
    }
    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void setNmap(){
        for(int i=0;i<num;i++){
            Sentinel * A;
            string name;
            string rank;
            cin>>name>>rank;
            if(rank == "SENAPATI"){
                A = new Senapati(i, name, rank);
                Nmap.push_back(A);
                nsena++;
            }else if(rank == "DANDANAYAKA"){
                A = new Dandanayaka(i, name, rank);
                Nmap.push_back(A);
                ndanda++;
            }else{
                A = new Chaturangini(i, name, rank);
                Nmap.push_back(A);
            }
        }
    }
    void setNHRS(){
        for(int i=0;i<num;i++){
            if(Nmap[i]->getRank()=="DANDANAYAKA"){
                Nmap[i]->setNHR(nsena);
            }else if(Nmap[i]->getRank()=="CHATURANGINI"){
                Nmap[i]->setNHR(nsena + ndanda);
            }
        }
    }
    void dfs(int u, vector<vector<int>>&dp, vector<int>&vis){
        vis[u] = 1;
        dp[u][0] = 0;
        dp[u][1] = 1;
        for(auto x : adj[u]){
            if(vis[x] == 0){
                dfs(x, dp, vis);
                dp[u][0] += dp[x][1];
                dp[u][1] += min(dp[x][0], dp[x][1]);
            }
        }
    }
    int calcmincover(vector<vector<int>>&dp, vector<int>&vis){
        dfs(0, dp, vis);
        return min(dp[0][0], dp[0][1]);
    }
    vector<T *>sortNmap(){
        vector<T *>ret = Nmap;
        sort(ret.begin(), ret.end(), CMP());
        return ret;
    }
    int getNHRid(int b){
        return Nmap[b]->countHigherRanked();
    }
private:
    int num;
    int nsena;
    int ndanda;
    map<int, vector<int>>adj;
    vector<T *>Nmap;
};
int main(){
    int n;
    cin>>n;
    Kingdom<Sentinel>K(n);
    for(int i=0;i<n-1;i++){
        int u, v;
        cin>>u>>v;
        K.addEdge(u, v);
    }
    K.setNmap();
    K.setNHRS();
    vector<Sentinel *>vec = K.sortNmap();
    int q;
    cin>>q;
    vector<vector<int>>dp(n, vector<int>(2));
    vector<int>vis(n, 0);
    int mincov = K.calcmincover(dp, vis);
    while(q--){
        int a;
        cin>>a;
        if(a==1){
            cout<<mincov<<'\n';
        }else if(a==2){
            for(int i=0;i<n;i++){
                cout<<vec[i]->getID()<<' ';
            }
            cout<<'\n';
        }else{
            int b;
            cin>>b;
            cout<<K.getNHRid(b)<<'\n';
        }
    }
}
