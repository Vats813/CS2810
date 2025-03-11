#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MOD 1000000007
class CurrencySorter{
public:
    int partition(vector<int>&arr, int l, int r){
        int piv = arr[r];
        int i = l - 1;
        for(int j=l;j<r;j++){
            if(arr[j]<piv){
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i+1], arr[r]);
        return i+1;
    }
    void quickSort(vector<int>&arr, int l, int r){
        if(l < r){
            int piv = partition(arr, l, r);
            quickSort(arr, l, piv - 1);
            quickSort(arr, piv + 1, r);
        }
    }
    void operator()(vector<int>&arr){
        quickSort(arr, 0, arr.size()-1);
        for(int i=0;i<arr.size();i++){
            cout<<arr[i]<<' ';
        }
        cout<<endl;
    }
};
class FibonacciGenerator{
public:
    pair<int,int>fibonacci(int x){
        pair<int,int>p;
        if(x==0){
            p.first = 0;
            p.second = 1;
            return p;
        }
        pair<int,int>res = fibonacci(x/2);
        int x0 = res.first;
        int x1 = res.second;
        int x2 = (x0 * ((2 * x1 % MOD - x0 + MOD) % MOD)) % MOD;
        int x3 = ((x0 % MOD) * (x0 % MOD) + (x1 % MOD) * (x1 % MOD)) % MOD;
        if(x%2==1){
            p.first = x3;
            p.second = (x2 + x3) % MOD;
        }else{
            p.first = x2;
            p.second = x3;
        }
        return p;
    }
    int operator()(int x){
        return fibonacci(x).first;
    }
};
class PrimeCalculator{
public:
    void sp(int bound, vector<int>& primes){
        vector<bool>isPrime(bound + 1, true);
        isPrime[0] = isPrime[1] = false;
        for(int i=2;i*i<=bound;i++){
            if(isPrime[i]){
                for(int j=i*i;j<=bound;j+=i){
                    isPrime[j] = false;
                }
            }
        }
        for(int i=2;i<=bound;i++){
            if(isPrime[i]){
                primes.push_back(i);
            }
        }
    }
    vector<int>lP(int l, int r){
        int bound = sqrt(r)+ 1;
        vector<int>sP;
        sp(bound, sP);
        vector<bool>isPrime(r - l + 1, true);
        for(int prime : sP){
            int start = max(prime * prime, ((l + prime - 1)/ prime)* prime);
            for(int j=start;j<= r;j+=prime){
                isPrime[j - l] = false;
            }
        }
        vector<int>range;
        for(int i=0;i<=r - l;i++){
            if(isPrime[i] && (l + i)>1){
                range.push_back(l + i);
            }
        }
        return range;
    }
    void printPrimes(int l, int r){
        vector<int>arr = lP(l, r);
        for(int i=0;i<arr.size();i++){
            cout<<arr[i]<<' ';
        }
        cout<<endl;
    }
    void printPrimeSum(int l, int r){
        vector<int>arr = lP(l, r);
        int tot = 0;
        for(int i=0;i<arr.size();i++){
            tot += arr[i];
        }
        cout<<tot<<endl;
    }
};
class NumberAnalyzer{
public:
    bool isSquareFree(int x){
        if(x%2==0){
           x=x/2;
        }
        if(x%2==0){
            return false;
        }
        for(int i=3;i<=sqrt(x);i+=2){
            if(x%i==0){
               x=x/i;
                if(x%i==0){
                    return false;
                }
            }
        }
        return true;    
    }
    int countDivisors(int x){
        int cnt = 0; 
        for(int i=1;i<=sqrt(x);i++){ 
            if(x%i==0){ 
                if(x/i==i){
                    cnt++; 
                }else{ 
                    cnt = cnt + 2; 
                }
            } 
        } 
        return cnt; 
    }
    int sumOfDivisors(int x){
        int tot = 0; 
        for(int i=1;i<=sqrt(x);i++){ 
            if(x%i==0){ 
                if(x/i==i){
                    tot += i; 
                }else{ 
                    tot += i + x/i; 
                }
            } 
        } 
        return tot; 
    }  
};
int32_t main(){
    int t;
    cin>>t;
    int no;
    cin>>no;
    while(no--){
        if(t==1){
            int n;
            cin>>n;
            vector<int>arr(n);
            for(int i=0;i<n;i++){
                cin>>arr[i];
            }
            CurrencySorter CS;
            CS(arr);
        }else if(t==2){
            int n;
            cin>>n;
            FibonacciGenerator fib;
            cout<<fib(n)<<endl;
            continue;
        }else if(t==3){
            string a;
            cin>>a;
            int l, r;
            cin>>l>>r;
            PrimeCalculator pr;
            if(a=="printPrimes"){
                pr.printPrimes(l, r);
            }else{
                pr.printPrimeSum(l, r);
            }
        }else{
            string a;
            cin>>a;
            int n;
            cin>>n;
            NumberAnalyzer na;
            if(a=="isSquareFree"){
                if(na.isSquareFree(n)){
                    cout<<"yes"<<endl;
                }else{
                    cout<<"no"<<endl;
                }
            }else if(a=="countDivisors"){
                cout<<na.countDivisors(n)<<endl;
            }else{
                cout<<na.sumOfDivisors(n)<<endl;
            }
        }
    }
}