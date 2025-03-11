#include<bits/stdc++.h>
using namespace std;
#define int long long
class Comp{ //Functor to compare less than greater than in mergesort
public:
    bool operator() (int a, int b, char s){ //char s is param to check lt gt
        if(s == 'L'){
            return a <= b;
        }else{
            return a >= b;
        }
    }
};
class Board{
public:
    int merge(vector<int>&arr, int l, int m, int r, char s){ //merge impl, returns int, therefore only 1 mergesort fn needed for both inv and sorting by asc
        int n1 = m - l + 1;
        int n2 = r - m;
        int inv = 0;
        vector<int> L(n1), R(n2);
        for(int i = 0; i < n1; i++){
            L[i] = arr[l + i];
        }
        for(int i = 0; i < n2; i++){
            R[i] = arr[m + 1 + i];
        }
        int i = 0, j = 0;
        int k = l;
        while(i < n1 && j < n2){
            Comp comp;
            if(comp(L[i], R[j], s)){
                arr[k] = L[i];
                i++;
            }else{
                arr[k] = R[j];
                inv += n1 - i;
                j++;
            }
            k++;
        }
        while(i < n1){
            arr[k] = L[i];
            i++;
            k++;
        }
        while(j < n2){
            arr[k] = R[j];
            j++;
            k++;
        }
        return inv;
    }
    int mergeSort(vector<int>&arr, int l, int r, char s){ //recursive call on mergesort
        int inv = 0;
        if(l < r){
            int m = (r + l)/2;
            inv += mergeSort(arr, l, m, s);
            inv += mergeSort(arr, m + 1, r, s);
            inv += merge(arr, l, m, r, s);
        }
        return inv;
    }
    void sortBoard(char s){ //sortboard row-wise, with param lt/gt
        for(int i = 0; i < board.size(); i++){
            mergeSort(board[i], 0, board[i].size() - 1, s);
        }
    }
    int inversions(){
        return mergeSort(flat, 0, flat.size() - 1, 'L'); //param lt
    }
    void display(){ //display board
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[i].size(); j++){
                cout<<board[i][j]<<' ';
            }
            cout<<endl;
        }
    }
    void dflat(){ //display flattened board (tc checks)
        for(int i = 0; i < flat.size(); i++){
            cout<<flat[i]<<' ';
        }
        cout<<endl;
    }
    void setboard(vector<vector<int>>&arr){ //sets board to input
        board = arr;
    }
    void setflat(){ //sets flat to current board (board changes after every sort)
        flat.clear();
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[i].size(); j++){
                flat.push_back(board[i][j]);
            }
        }
    }
private:
    vector<vector<int>>board;
    vector<int>flat;
};
class Point { //point class, with x, y and index to break ties
public:
    int x, y, index;
    Point(int x = 0, int y = 0) : x(x), y(y), index(index) {}
};
bool Xc(Point &a, Point &b) {//x-wise sorting
    return a.x < b.x;
}
bool Yc(Point &a, Point &b) {//y-wise sorting
    return a.y < b.y;
}
int dist(Point &a, Point &b) {//distance fn for 2 points
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
pair<Point, Point> TB(pair<Point, Point>&a, pair<Point, Point>&b){//TieBreak fn
    if(a.first.index > a.second.index){
        swap(a.first, a.second);
    }
    if(b.first.index > b.second.index){
        swap(b.first, b.second);
    }
    if(a.first.x < b.first.x){
        return a;
    }else if(b.first.x < a.first.x){
        return b;
    }
    if(a.first.y < b.first.y){
        return a;
    }else if(b.first.y < a.first.y){
        return b;
    }
    if(a.second.x < b.second.x){
        return a;
    }else if(b.second.x < a.second.x){
        return b;
    }
    if(a.second.y < b.second.y){
        return a;
    }else if(b.second.y < a.second.y){
        return b;
    }
    if(a.first.index < b.first.index){
        return a;
    }else{
        return b;
    }
}
pair<Point, Point> CL(vector<Point>&Pts, int l, int r){//closest pt function
    pair<Point, Point>res;
    pair<Point, Point>res1;
    if(r - l <= 3){//Bruteforce
        int mini = 1e18;//long long datatype as distances can be big
        for(int i = l; i <= r; i++){
            for(int j = i + 1; j <= r; j++){
                int d = dist(Pts[i], Pts[j]);
                if(d < mini){
                    mini = d;
                    res.first = Pts[i];
                    res.second = Pts[j];
                }else if(d == mini){
                    res1.first = Pts[i];
                    res1.second = Pts[j];
                    res = TB(res, res1);
                }
            }
        }
        return TB(res, res);
    }
    int m = (r + l)/2;
    pair<Point, Point>rh = CL(Pts, m + 1, r); //right half
    pair<Point, Point>lh = CL(Pts, l, m); //left half
    int dl = dist(lh.first, lh.second);
    int dr = dist(rh.first, rh.second);
    int mini = min(dl, dr);
    if(mini == dl){
        res = lh;
    }else{
        res = rh;
    }
    if(mini == dr){
        res = TB(res, rh);
    }
    int del = floor(sqrt(mini)) + 1; //getting the delta distance line
    vector<Point>delta; //vector of points within delta line
    for(int i = l; i <= r; i++){
        if((Pts[i].x >= Pts[m].x - del) && (Pts[i].x <= Pts[m].x + del)){ //Checking if within delta line
            delta.push_back(Pts[i]);
        }
    }
    sort(delta.begin(), delta.end(), Yc); //sorting delta accd Y
    int ds = delta.size();
    for(int i = 0; i < ds; i++){ //Checking for min distance within delta line
        for(int j = i + 1; j < min(i + 16, ds); j++){
            int dis = dist(delta[i], delta[j]);
            if(dis < mini){
                mini = dis;
                res.first = delta[i];
                res.second = delta[j];
            }else if(mini == dis){
                res1.first = delta[i];
                res1.second = delta[j];
                res = TB(res, res1);
            }
        }
    }
    return TB(res, res);
}
int32_t main(){//main fn with various string checks for each type of impl
    string a;
    Board chess;
    while(cin>>a){
        if(a == "CREATE_2D"){
            int n;
            cin>>n;
            vector<vector<int>>arr(n, vector<int>(n));
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    cin>>arr[i][j];
                }
            }
            chess.setboard(arr);
            chess.setflat();
        }else if(a == "SORT_2D"){
            string b;
            cin>>b;
            char s;
            if(b == "ascending"){
                s = 'L';
            }else{
                s = 'R';
            }
            chess.sortBoard(s);
        }else if(a == "INVERSION_2D"){
            chess.setflat(); //setting board to current every time before inv checks
            cout << chess.inversions() << endl;
        }else if(a == "DISPLAY_2D"){
            chess.display();
        }else if(a == "CLOSEST_2D"){
            int n;
            cin>>n;
            vector<Point>pts(n);
            for(int i = 0; i < n; i++){
                cin>>pts[i].x>>pts[i].y;
                pts[i].index = i;
            }
            sort(pts.begin(), pts.end(), Xc);//passing X sorted vector
            pair<Point, Point>res = CL(pts, 0, pts.size()-1);
            cout << res.first.x << ' ' << res.first.y << ' ' << res.second.x << ' ' << res.second.y <<endl;
        }else if(a == "END"){
            break;
        }
    }
}
