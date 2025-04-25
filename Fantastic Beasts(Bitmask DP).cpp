#include<bits/stdc++.h>
using namespace std;
float dist(float x1, float y1, float x2, float y2){
    return sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
class Island{
public:
    Island(){

    }
    void setID(string& id){
        ID = id;
    }
    void setType(string typ){
        type = typ;
    }
    string getID(){
        return ID;
    }
    string getType(){
        return type;
    }
    void setCentre(float a, float b){
        centre.first = a;
        centre.second = b;
    }
    void setRadius(float r){
        radius = r;
    }
    float getRadius(){
        return radius;
    }
    pair<float, float>getCentre(){
        return centre;
    }
    bool valid(Island * A){
        if(dist(A->centre.first, A->centre.second, centre.first, centre.second) <= (radius + A->radius)){
            return true;
        }
        return false;
    }
private:
    string ID;
    string type;
    pair<float, float>centre;
    float radius;
friend ostream& operator << (ostream& stream, Island *&C);
friend istream& operator >> (istream& stream, Island *&C);
};
class Rectangle:public Island{
public:
    Rectangle(string& id, float a1, float b1, float a2, float b2, float a3, float b3, float a4, float b4){
        this->setID(id);
        this->setType("RECTANGLE");
        this->setCentre((a1 + a2 + a3 + a4)/4, (b1 + b2 + b3 + b4)/4);
        this->setRadius(dist((a1 + a2 + a3 + a4)/4, (b1 + b2 + b3 + b4)/4, a1, b1));
    }
};
class Triangle:public Island{
public:
    Triangle(string& id, float a1, float b1, float a2, float b2, float a3, float b3){
        this->setID(id);
        this->setType("TRIANGLE");
        this->setCentre((a1 + a2 + a3)/3, (b1 + b2 + b3)/3);
        float md = max(dist((a1 + a2 + a3)/3, (b1 + b2 + b3)/3, a1, b1), dist((a1 + a2 + a3)/3, (b1 + b2 + b3)/3, a2, b2));
        md = max(md, dist((a1 + a2 + a3)/3, (b1 + b2 + b3)/3, a3, b3));
        this->setRadius(md);
    }
};
class Circle:public Island{
public:
    Circle(string& id, float a1, float b1, float ra){
        this->setID(id);
        this->setType("CIRCLE");
        this->setCentre(a1, b1);
        this->setRadius(ra);
    }
};
istream& operator >> (istream& stream, Island *&C){
    string a;
    stream>>a;
    string b;
    stream>>b;
    if(a == "TRIANGLE"){
        float a1, b1, a2, b2, a3, b3;
        stream>>a1>>b1>>a2>>b2>>a3>>b3;
        C = new Triangle(b, a1, b1, a2, b2, a3, b3);
    }else if(a == "RECTANGLE"){
        float a1, b1, a2, b2, a3, b3, a4, b4;
        stream>>a1>>b1>>a2>>b2>>a3>>b3>>a4>>b4;
        C = new Rectangle(b, a1, b1, a2, b2, a3, b3, a4, b4);
    }else{
        float a1, b1, r;
        stream>>a1>>b1>>r;
        C = new Circle(b, a1, b1, r);
    }
    return stream;
}
ostream& operator << (ostream& stream, Island *&C){
    stream << C->getID();
    return stream;
}
vector<int> Hamiltonian_path(vector<vector<int>>&adj, int N, vector<vector<int>>&parent){
    int dp[N][(1 << N)];
    memset(dp, 0, sizeof dp);

    for(int i = 0; i < N; i++){
        dp[i][(1 << i)] = true;
    }

    for(int i = 0; i < (1 << N); i++){
        for(int j = 0; j < N; j++){
            if(i & (1 << j)){
                for(int k = 0; k < N; k++){
                    if(i & (1 << k) && adj[k][j] && j != k && dp[k][i ^ (1 << j)]){
                        parent[j][i] = k;
                        dp[j][i] = true;
                        break;
                    }
                }
            }
        }
    }
    vector<int> res;
    int max_len = 0;
    int end_node = -1;
    int final_mask = 0;

    for (int mask = 0; mask < (1 << N); mask++) {
        for (int j = 0; j < N; j++) {
            if (dp[j][mask]) {
                int path_len = __builtin_popcount(mask);
                if (path_len > max_len) {
                    max_len = path_len;
                    end_node = j;
                    final_mask = mask;
                }
            }
        }
    }
    res.push_back(max_len);
    res.push_back(end_node);
    res.push_back(final_mask);
    return res;
}
int main(){
    int n;
    cin>>n;
    map<int, Island *>isl;
    vector<vector<int>>adj(n, vector<int>(n, 0));
    for(int i=0;i<n;i++){
        Island * A = new Island;
        cin>>A;
        isl[i] = A;
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(isl[i]->valid(isl[j])){
                adj[i][j] = 1;
                adj[j][i] = 1;
            }
        }
    }
    vector<vector<int>>parent(n, vector<int>(1 << n));
    vector<int>res = Hamiltonian_path(adj, n, parent);
    int path_len = res[0];
    int node = res[1];
    int mask = res[2];
    vector<int> path;
    while (path_len--) {
        path.push_back(node);
        int prev = parent[node][mask];
        mask ^= (1 << node);
        node = prev;
    }
    reverse(path.begin(), path.end());
    if(res[0] != n){
        cout<<"NO"<<'\n';
        cout<<res[0]<<'\n';
    }else{
        cout<<"YES"<<'\n';
    }
    for(int i=0;i<path.size();i++){
        cout<<isl[path[i]]<<' ';
    }
    cout<<endl;
}
