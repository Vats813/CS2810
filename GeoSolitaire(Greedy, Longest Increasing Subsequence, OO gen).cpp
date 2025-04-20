#include<bits/stdc++.h>
using namespace std;
class Card{
public:
    Card(){
        prev = nullptr;
    }
    void setArea(int a){
        area = a;
    }
    int getArea(){
        return area;
    }
    void setType(string a){
        Type = a;
    }
    string getType(){
        return Type;
    }
    bool operator < (Card a){
        int ar = a.getArea();
        if(area < ar){
            return true;
        }else{
            return false;
        }
    }
    void setPrev(Card * a){
        prev = a;
    }
    Card * getPrev(){
        return prev;
    }
    virtual int getLength(){
        return 0;
    }
    virtual int getBase(){
        return 0;
    }
    virtual int getHeight(){
        return 0;
    }
    virtual int getBreadth(){
        return 0;
    }
private:
    int area;
    string Type;
    Card * prev;
friend ostream& operator << (ostream& stream, Card *C);
friend istream& operator >> (istream& stream, Card *&C);
friend class CardOrganizer;
};
class Triangle:public Card{
public:
    Triangle(int b, int h){
        this->setType("TRIANGLE");
        this->setArea((b * h)/2);
        base = b;
        height = h;
    }
    int getBase() override{
        return base;
    }
    int getHeight() override{
        return height;
    }
private:
    int base, height;
};
class Square:public Card{
public:
    Square(int l){
        this->setType("SQUARE");
        this->setArea(l * l);
        length = l;
    }
    int getLength(){
        return length;
    }
private:
    int length;
};
class Rectangle:public Card{
public:
    Rectangle(int l, int b){
        this->setType("RECTANGLE");
        this->setArea(l * b);
        length = l;
        breadth = b;
    }
    int getLength(){
        return length;
    }
    int getBreadth(){
        return breadth;
    }
private:
    int length, breadth;
};
istream& operator >> (istream& stream, Card *&C){
    string a;
    stream>>a;
    if(a == "TRIANGLE"){
        int b, h;
        stream>>b>>h;
        C = new Triangle(b, h);
    }else if(a == "RECTANGLE"){
        int l, b;
        stream>>l>>b;
        C = new Rectangle(l, b);
    }else{
        int l;
        stream>>l;
        C = new Square(l);
    }
    return stream;
}
ostream& operator << (ostream& stream, Card *C) {
    string a = C->getType();
    stream << a << ' ';
    if(a == "TRIANGLE"){
        int b = C->getBase();
        int h = C->getHeight();
        stream<<b<<' '<<h<<'\n';  
    }else if(a == "SQUARE"){
        int l = C->getLength();
        stream<<l<<'\n'; 
    }else{
        int b = C->getBreadth();
        int l = C->getLength();
        stream<<l<<' '<<b<<'\n'; 
    }
    return stream;
}
class CardOrganizer{
public:
    CardOrganizer(){

    }
    int bins(Card * a){
        int low = 0;
        int high = piles.size();
        while(low < high){
            int mid = (low + high)/2;
            if(*(piles[mid][piles[mid].size()-1]) < *(a)){
                low = mid + 1;
            }else{
                high = mid;
            }
        }
        return low;
    }
    int binsLIS(Card * a){
        int low = 0;
        int high = LIS.size();
        while(low < high){
            int mid = (low + high)/2;
            if(*(LIS[mid]) < *(a)){
                low = mid + 1;
            }else{
                high = mid;
            }
        }
        return low;
    }
    void addCard(Card * a){
        Cards.push_back(a);
        if(piles.size()==0){
            vector<Card *>vec;
            vec.push_back(a);
            piles.push_back(vec);
        }else if(*(piles[piles.size()-1][piles[piles.size()-1].size() - 1]) < *(a)){
            vector<Card *>vec;
            vec.push_back(a);
            piles.push_back(vec);
        }else{
            int ins = bins(a);
            piles[ins].push_back(a);
        }
        if(LIS.size()==0){
            LIS.push_back(a);
        }else if((*(LIS[LIS.size() - 1]) < *(a)) || (LIS[LIS.size() - 1]->getArea() == a->getArea())){
            a->setPrev(LIS[LIS.size()-1]);
            LIS.push_back(a);
        }else{
            int ins = binsLIS(a);
            if(ins > 0){
                a->setPrev(LIS[ins-1]);
            }
            LIS[ins] = a;
        }
    }
    size_t getPileCount() const{
        return piles.size();
    }
    vector<Card *> getLIS() const{
        vector<Card *>vec;
        Card * a = LIS[LIS.size() - 1];
        vec.push_back(a);
        while(a->getPrev() != nullptr){
            a = a->getPrev();
            vec.push_back(a);
        }
        return vec;
    }
    void printLIS(){
        vector<Card *>L = this->getLIS();
        cout<<L.size()<<'\n';
        for(int i=L.size()-1;i>=0;i--){
            cout<<L[i];
        }
    }
private:
    vector<vector<Card *>>piles;
    vector<Card *>Cards;
    vector<Card *>LIS;
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin>>q;
    CardOrganizer CO;
    while(q--){
        int t;
        cin>>t;
        if(t == 1){
            Card * A;
            cin>>A;
            CO.addCard(A);
        }else if(t == 2){
            cout<<CO.getPileCount()<<'\n';
        }else{
            CO.printLIS();
        }
    }
}
