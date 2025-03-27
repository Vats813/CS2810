#include <bits/stdc++.h>
using namespace std;
class comp { //Complex Class
public:
    long long r, im;
    comp(long long re = 0, long long i = 0){
        r = re;
        im = i;
    }
    comp operator+(comp &a){ 
        return comp(r + a.r, im + a.im); 
    }
    comp operator-(comp &a){ 
        return comp(r - a.r, im - a.im); 
    }
    comp operator*(comp &a){
        return comp(r * a.r - im * a.im, r * a.im + im * a.r);
    }
    comp operator/(long long d){ 
        return comp(r / d, im / d); 
    }
 };
template<typename T>
class Poly{
public:
    Poly(vector<T>in){//Multiplying 2 polys
        for(long long i=0;i<in.size();i++){
            coeffs.push_back(in[i]);
        }
    }
    vector<T>coeffs;
    vector<T> Karat(vector<T>& a, vector<T>& b) { //Karatsuba Impl.
        if (a.empty() || b.empty()){
            return {};
        }
        if (a.size() == 1 && b.size() == 1){
            return {a[0] * b[0]};
        }
        long long n = max(a.size(), b.size());
        n = (n + 1) / 2 * 2; 
        
        vector<T> a1(a.begin(), a.begin() + min((long long)a.size(), n / 2));
        vector<T> a2(a.begin() + min((long long)a.size(), n / 2), a.end());
        vector<T> b1(b.begin(), b.begin() + min((long long)b.size(), n / 2));
        vector<T> b2(b.begin() + min((long long)b.size(), n / 2), b.end());
        
        vector<T> p1 = Karat(a1, b1); //rec call 1
        vector<T> p2 = Karat(a2, b2); //rec call 2
        
        vector<T> as = a1;
        vector<T> bs = b1;
        for (long long i = 0; i < a2.size(); i++){
            if(as.size() == i){
                break;
            }
            as[i] = as[i] + a2[i];
        }
        for (long long i = 0; i < b2.size(); i++){
            if(bs.size() == i){
                break;
            }
            bs[i] = bs[i] + b2[i];
        }
        
        vector<T> p3 = Karat(as, bs); //rec call 3
        for (long long i = 0; i < p1.size(); i++){
            if(p3.size() == i){
                break;
            }
            p3[i] = p3[i] - p1[i];
        }
        for (long long i = 0; i < p2.size(); i++){
            if(p3.size() == i){
                break;
            }
            p3[i] = p3[i] - p2[i];
        }
        vector<T> res(2 * n);
        for(int i=0;i<res.size();i++){
            T var = T(); 
            res[i] = var;
        }
        for (long long i = 0; i < p1.size(); i++){
            if(i == 2*n){
                break;
            }
            res[i] = res[i] + p1[i];
        }
        for (long long i = 0; i < p3.size(); i++){
            if(i + n/2 == 2*n){
                break;
            }
            res[i + n / 2] = res[i + n / 2] + p3[i];
        }
        for (long long i = 0; i < p2.size(); i++){
            if(i + n == 2*n){
                break;
            }
            res[i + n] = res[i + n] + p2[i];
        }
        return res;
    }
    vector<T> operator * (Poly b){ //Overloading * operator for polynomial objects
        return Karat(coeffs, b.coeffs);
    }
};
template<typename T>
class Polyeval{
public:
    Polyeval(vector<T>in){//Evaluating poly at x
        for(long long i=0;i<in.size();i++){
            coeffs.push_back(in[i]);
        }
    }
    T evalp(long long x){//Horner's method for integer and float
        T ans;
        ans = coeffs[coeffs.size()-1];
        for(long long i=coeffs.size()-2;i>=0;i--){
            ans *= x;
            ans += coeffs[i];
        }
        return ans;
    }
    T evalsp(long long x){//Brute force for string
        T ans = "";
        long long times = floor(pow(x, coeffs.size()-1));
        for(long long i=coeffs.size()-1;i>=0;i--){
            for(long long j=0;j<times;j++){
                ans += coeffs[i];
            }
            times /= x;
        }
        return ans;
    }
    vector<T>coeffs;
};
template<typename T>
class Polydiff{
public:
    Polydiff(vector<T>in){//Differentiating a poly
        for(long long i=0;i<in.size();i++){
            coeffs.push_back(in[i]);
        }
    }
    vector<T>coeffs;
    void diff(){
        for(long long i=0;i<coeffs.size();i++){
            coeffs[i] *= i;
        }
        coeffs.erase(coeffs.begin());
    }
};
int main() { //Main fn.
    long long q;
    cin>>q;
    while(q--){
        long long op;
        cin>>op;
        string a;
        cin>>a;
        if(op == 1){
            if(a == "integer"){
                int d1;
                cin>>d1;
                vector<long long>deg1(d1);
                for(int i=0;i<d1;i++){
                    cin>>deg1[i];
                }
                Poly<long long>p(deg1);
                int d2;
                cin>>d2;
                vector<long long>deg2(d2);
                for(int i=0;i<d2;i++){
                    cin>>deg2[i];
                }
                Poly<long long>b(deg2);
                vector<long long>res = p * b;
                for(int i=0;i<d1 + d2 - 1;i++){
                    cout<<res[i]<<' ';
                }
            }else if(a == "float"){
                int d1;
                cin>>d1;
                vector<long double>deg1(d1);
                for(int i=0;i<d1;i++){
                    cin>>deg1[i];
                }
                Poly<long double>p(deg1);
                int d2;
                cin>>d2;
                vector<long double>deg2(d2);
                for(int i=0;i<d2;i++){
                    cin>>deg2[i];
                }
                Poly<long double>b(deg2);
                vector<long double>res = p * b;
                for(int i=0;i<d1 + d2 - 1;i++){
                    cout<<fixed;
                    cout<<setprecision(6);
                    cout<<res[i]<<' ';
                }
            }else{
                int d1;
                cin>>d1;
                vector<comp>deg1(d1);
                for(int i=0;i<d1;i++){
                    cin>>deg1[i].r>>deg1[i].im;
                }
                Poly<comp>p(deg1);
                int d2;
                cin>>d2;
                vector<comp>deg2(d2);
                for(int i=0;i<d2;i++){
                    cin>>deg2[i].r>>deg2[i].im;
                }
                Poly<comp>b(deg2);
                vector<comp>res = p * b;
                for(int i=0;i<d1 + d2 - 1;i++){
                    cout<<res[i].r<<' '<<res[i].im<<' ';
                }
            }
            cout<<endl;
        }else if(op == 2){
            int d;
            cin>>d;
            if(a == "integer"){
                vector<long long>deg(d);
                for(int i=0;i<d;i++){
                    cin>>deg[i];
                }
                Polyeval<long long>P(deg);
                int x;
                cin>>x;
                cout<<P.evalp(x)<<endl;
            }else if(a == "float"){
                vector<long double>deg(d);
                for(int i=0;i<d;i++){
                    cin>>deg[i];
                }
                Polyeval<long double>P(deg);
                int x;
                cin>>x;
                cout<<fixed;
                cout<<setprecision(6);
                cout<<P.evalp(x)<<endl;
            }else{
                vector<string>deg(d);
                for(int i=0;i<d;i++){
                    cin>>deg[i];
                }
                Polyeval<string>P(deg);
                int x;
                cin>>x;
                cout<<P.evalsp(x)<<endl;
            }
        }else{
            int d;
            cin>>d;
            if(a == "integer"){
                vector<long long>deg(d);
                for(int i=0;i<d;i++){
                    cin>>deg[i];
                }
                Polydiff<long long>P(deg);
                P.diff();
                if(P.coeffs.size()==0){
                    cout<<0;
                }
                for(int i=0;i<P.coeffs.size();i++){
                    cout<<P.coeffs[i]<<' ';
                }
                cout<<endl;
            }else{
                vector<long double>deg(d);
                for(int i=0;i<d;i++){
                    cin>>deg[i];
                }
                Polydiff<long double>P(deg);
                P.diff();
                if(P.coeffs.size()==0){
                    cout<<fixed;
                    cout<<setprecision(6);
                    cout<<0;
                }
                for(int i=0;i<P.coeffs.size();i++){
                    cout<<fixed;
                    cout<<setprecision(6);
                    cout<<P.coeffs[i]<<' ';
                }
                cout<<endl;
            }
        }
    }
}
