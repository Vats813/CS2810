#include<bits/stdc++.h>
using namespace std;
class QNS{
public:
    QNS(int pl = 1000, int d = 500, int es = 300, int hl = 0){ //Default constructor for suit.
        powerLevel = pl;
        durability = d;
        energyStorage = es;
        heatLevel = hl;
        state = 1;
        if(durability <= 0){
            state = 0;
        }else if(heatLevel > 500){
            state = 2;
        }
        if(powerLevel > 5000){
            powerLevel = 5000;
        }
        if(heatLevel < 0){
            heatLevel = 0;
        }
    }
    QNS(const QNS& a){ //Copy constructor for suit
        powerLevel = a.powerLevel;
        durability = a.durability;
        energyStorage = a.energyStorage;
        heatLevel = a.heatLevel;
        state = 1;
        if(durability <= 0){
            state = 0;
        }else if(heatLevel > 500){
            state = 2;
        }else if(heatLevel <= 500){
            state = 1;
        }
        if(powerLevel > 5000){
            powerLevel = 5000;
        }
        if(heatLevel < 0){
            heatLevel = 0;
        }
    }
    void operator +(QNS a){ //Suit adder
        powerLevel += a.energyStorage;
        durability += a.durability;
        energyStorage += a.powerLevel;
        if(durability <= 0){
            state = 0;
        }else if(heatLevel > 500){
            state = 2;
        }else if(heatLevel <= 500){
            state = 1;
        }
        if(powerLevel > 5000){
            powerLevel = 5000;
        }
        if(heatLevel < 0){
            heatLevel = 0;
        }
    }
    void operator -(int x){ //Attack subtractor
        durability -= x;
        energyStorage += x;
        heatLevel += x;
        if(durability <= 0){
            state = 0;
        }else if(heatLevel > 500){
            state = 2;
        }else if(heatLevel <= 500){
            state = 1;
        }
        if(powerLevel > 5000){
            powerLevel = 5000;
        }
        if(heatLevel < 0){
            heatLevel = 0;
        }
    }
    void operator *(int x){ //Boostpower multiplier
        powerLevel += (powerLevel * x)/100;
        energyStorage += 5*x;
        heatLevel += x;
        if(durability <= 0){
            state = 0;
        }else if(heatLevel > 500){
            state = 2;
        }else if(heatLevel <= 500){
            state = 1;
        }
        if(powerLevel > 5000){
            powerLevel = 5000;
        }
        if(heatLevel < 0){
            heatLevel = 0;
        }
    }
    void operator /(int x){ //Repair Divider
        durability += x;
        heatLevel -= x;
        if(durability <= 0){
            state = 0;
        }else if(heatLevel > 500){
            state = 2;
        }else if(heatLevel <= 500){
            state = 1;
        }
        if(powerLevel > 5000){
            powerLevel = 5000;
        }
        if(heatLevel < 0){
            heatLevel = 0;
        }
    }
    bool operator == (QNS a){ //checks two suits eq
        if(powerLevel == a.powerLevel && durability == a.durability){
            return true;
        }else{
            return false;
        }
    }
    bool operator <(QNS a){ //checks two suits lt
        if(powerLevel + durability < a.powerLevel + a.durability){
            return true;
        }else{
            return false;
        }
    }
    void print(){ //printout1
        cout << powerLevel << ' '<< durability << ' ' << energyStorage << ' ' << heatLevel << endl;
    }
    //4 getters
    int getP(){
        return powerLevel;
    }
    int getD(){
        return durability;
    }
    int getE(){
        return energyStorage;
    }
    int getH(){
        return heatLevel;
    }
    int getState(){
        return state;
    }
private: //private attributes
    int powerLevel;
    int durability;
    int energyStorage;
    int heatLevel;
    int state;
};
class Avenger{
public: 
    Avenger(string avName, QNS avSuit, int strength){ //Param constructor
        name = avName;
        suit = avSuit;
        attackStrength = strength;
    }
    void attack(Avenger& enemy){ //attack function
        if(suit.getState() == 1 && enemy.suit.getState()!=0){
            enemy.suit - attackStrength;
        }
    }
    void upgradeSuit(QNS a){ //Suit add function
        if(suit.getState()!=0){
            suit + a;
        } 
    }
    void repair(int x){ //Suit repair function
        if(suit.getState()!=0){
            suit / x;
        } 
    }
    void printStatus(){ //print status of avenger
        cout << name << ' ';
        suit.print();
    }
    void boostPower(int factor){
        suit * factor;
    }
    void boostPower(QNS a){
        suit + a;
    }
    QNS getSuit(){ //getter for suit
        return suit;
    }
    string getName(){
        return name;
    }
//private attributes
private:
    string name;
    QNS suit;
    int attackStrength;
};
class Battle{
public:
    Battle(int k, int n, int m){ //constructor, takes in input by itself
        for(int i=0;i<k;i++){
            int a, b, c, d;
            cin>>a>>b>>c>>d;
            QNS S(a, b, c, d);
            suits.push_back(S);
        }
        int it = 0;
        while(it < n && it < k){ //Taking in heroes
            string a;
            int b;
            cin>>a>>b;
            Avenger A(a, suits[it], b);
            heroes.push_back(A);
            it++;
        }
        if(it == k){
            while(it < n + m){ //If no suits
                string a;
                int b;
                cin>>a>>b;
                Outof.push_back(a);
                it++;
            }
        }else{
            while(it < n + m && it < k){ //Taking in villains
                string a;
                int b;
                cin>>a>>b;
                Avenger A(a, suits[it], b);
                enemies.push_back(A);
                it++;
            }
            if(it == k){
                while(it < n + m){ //If no suits
                    string a;
                    int b;
                    cin>>a>>b;
                    Outof.push_back(a);
                    it++;
                }
            }
        }
        suitit = it;
    }
    void startBattle(){ //starts the battle
        for(int i=0;i<Outof.size();i++){
            cout<<Outof[i]<<" is out of fight"<<endl;
        }
        string b;
        while(cin>>b){ //To be completed
            if(b == "Attack"){
                string c, d;
                cin>>c>>d;
                pair<int,int>aid={-1, 0};
                pair<int,int>did={-1, 0};
                for(int i=0;i<heroes.size();i++){
                    if(heroes[i].getName()==c){
                        aid.first = i;
                        aid.second = 1;
                    }else if(heroes[i].getName()==d){
                        did.first = i;
                        did.second = 1;
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(enemies[i].getName()==c){
                        aid.first = i;
                        aid.second = -1;
                    }else if(enemies[i].getName()==d){
                        did.first = i;
                        did.second = -1;
                    }
                }
                if(aid.first == -1 || did.first == -1){
                    continue;
                }else{
                    if(aid.second == 1 && did.second == 1){
                        heroes[aid.first].attack(heroes[did.first]);
                        if(heroes[aid.first].getSuit().getState()==1){
                            vector<string>push={c, "attacks", d};
                            battlelog.push_back(push);
                        }
                        if(heroes[did.first].getSuit().getState() == 0){
                            vector<string>push={d, "suit destroyed"};
                            battlelog.push_back(push);
                        }else if(heroes[did.first].getSuit().getState() == 2){
                            vector<string>push={d, "suit overheated"};
                            battlelog.push_back(push);
                        }
                    }else if(aid.second == -1 && did.second == -1){
                        enemies[aid.first].attack(enemies[did.first]);
                        if(enemies[aid.first].getSuit().getState()==1){
                            vector<string>push={c, "attacks", d};
                            battlelog.push_back(push);
                        }
                        if(enemies[did.first].getSuit().getState() == 0){
                            vector<string>push={d, "suit destroyed"};
                            battlelog.push_back(push);
                        }else if(enemies[did.first].getSuit().getState() == 2){
                            vector<string>push={d, "suit overheated"};
                            battlelog.push_back(push);
                        }
                    }else if(aid.second == 1 && did.second == -1){
                        heroes[aid.first].attack(enemies[did.first]);
                        if(heroes[aid.first].getSuit().getState()==1){
                            vector<string>push={c, "attacks", d};
                            battlelog.push_back(push);
                        }
                        if(enemies[did.first].getSuit().getState() == 0){
                            vector<string>push={d, "suit destroyed"};
                            battlelog.push_back(push);
                        }else if(enemies[did.first].getSuit().getState() == 2){
                            vector<string>push={d, "suit overheated"};
                            battlelog.push_back(push);
                        }
                    }else if(aid.second == -1 && did.second == 1){
                        enemies[aid.first].attack(heroes[did.first]);
                        if(enemies[aid.first].getSuit().getState()==1){
                            vector<string>push={c, "attacks", d};
                            battlelog.push_back(push);
                        }
                        if(heroes[did.first].getSuit().getState() == 0){
                            vector<string>push={d, "suit destroyed"};
                            battlelog.push_back(push);
                        }else if(heroes[did.first].getSuit().getState() == 2){
                            vector<string>push={d, "suit overheated"};
                            battlelog.push_back(push);
                        }
                    }
                }
                
            }else if(b == "Repair"){
                string c;
                int d;
                cin>>c>>d;
                for(int i=0;i<heroes.size();i++){
                    if(heroes[i].getName()==c && heroes[i].getSuit().getState()!=0){
                        heroes[i].repair(d);
                        vector<string>push={c, "repaired"};
                        battlelog.push_back(push);
                        break;
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(enemies[i].getName()==c && heroes[i].getSuit().getState()!=0){
                        enemies[i].repair(d);
                        vector<string>push={c, "repaired"};
                        battlelog.push_back(push);
                        break;
                    }
                }
            }else if(b == "Upgrade"){
                string c;
                cin>>c;
                for(int i=0;i<heroes.size();i++){
                    if(heroes[i].getName()==c && heroes[i].getSuit().getState()!=0){
                        if(suitit >= suits.size()){
                            vector<string>push={c, "upgrade Fail"}; 
                            battlelog.push_back(push);
                            break;
                        }else{
                            heroes[i].upgradeSuit(suits[suitit]);
                            suitit++;
                            vector<string>push={c, "upgraded"};
                            battlelog.push_back(push);
                            break;
                        }
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(enemies[i].getName()==c && enemies[i].getSuit().getState()!=0){
                        if(suitit >= suits.size()){
                            vector<string>push={c, "upgrade Fail"}; 
                            battlelog.push_back(push);
                            break;
                        }else{
                            enemies[i].upgradeSuit(suits[suitit]);
                            suitit++;
                            vector<string>push={c, "upgraded"};
                            battlelog.push_back(push);
                            break;
                        }
                    }
                }
            }else if(b == "BoostPowerByFactor"){
                string c;
                int d;
                cin>>c>>d;
                for(int i=0;i<heroes.size();i++){
                    if(heroes[i].getName()==c && heroes[i].getSuit().getState()!=0){
                        heroes[i].boostPower(d);
                        vector<string>push={c, "boosted"};
                        battlelog.push_back(push);
                        if(heroes[i].getSuit().getState()==2){
                            vector<string>p1={c, "suit overheated"};
                            battlelog.push_back(p1);
                        }
                        break;
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(enemies[i].getName()==c && enemies[i].getSuit().getState()!=0){
                        enemies[i].boostPower(d);
                        vector<string>push={c, "boosted"};
                        battlelog.push_back(push);
                        if(enemies[i].getSuit().getState()==2){
                            vector<string>p1={c, "suit overheated"};
                            battlelog.push_back(p1);
                        }
                        break;
                    }
                }
            }else if(b == "BoostPower"){
                string c;
                int a, b, d, e;
                cin>>c>>a>>b>>d>>e;
                QNS S(a, b, d, e);
                for(int i=0;i<heroes.size();i++){
                    if(heroes[i].getName()==c && heroes[i].getSuit().getState()!=0){
                        heroes[i].boostPower(S);
                        vector<string>push={c, "boosted"};
                        battlelog.push_back(push);
                        if(heroes[i].getSuit().getState()==2){
                            vector<string>p1={c, "suit overheated"};
                            battlelog.push_back(p1);
                        }
                        break;
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(enemies[i].getName()==c && enemies[i].getSuit().getState()!=0){
                        enemies[i].boostPower(S);
                        vector<string>push={c, "boosted"};
                        battlelog.push_back(push);
                        if(enemies[i].getSuit().getState()==2){
                            vector<string>p1={c, "suit overheated"};
                            battlelog.push_back(p1);
                        }
                        break;
                    }
                }
            }else if(b == "AvengerStatus"){ 
                string c;
                cin>>c;
                for(int i=0;i<heroes.size();i++){
                    if(heroes[i].getName()==c){
                        heroes[i].printStatus();
                        break;
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(enemies[i].getName()==c){
                        enemies[i].printStatus();
                        break;
                    }
                }
            }else if(b == "PrintBattleLog"){
                printBattleLog();
            }else if(b == "BattleStatus"){
                int stat = result();
                if(stat == 1){
                    cout<<"heroes are winning"<<endl;
                }else if(stat == -1){
                    cout<<"enemies are winning"<<endl;
                }else{
                    cout<<"tie"<<endl;
                }
            }else if(b == "End"){
                break;
            }
        }
    }
    void printBattleLog(){ //print log function
        for(int i=0;i<battlelog.size();i++){
            for(int j=0;j<battlelog[i].size();j++){
                cout<<battlelog[i][j]<<' ';
            }
            cout<<endl;
        }
    }
    int result(){ //result check function
        int htot = 0;
        int etot = 0;
        for(auto &&x : heroes){
            if(x.getSuit().getD() > 0){
                htot += x.getSuit().getD() + x.getSuit().getP();
            }
        }
        for(auto &&x : enemies){
            if(x.getSuit().getD() > 0){
                etot += x.getSuit().getD() + x.getSuit().getP();
            }
        }
        int flag;
        if(etot < htot){
            flag = 1;
        }else if(etot > htot){
            flag = -1;
        }else{
            flag = 0;
        }
        return flag;
    }
//private attributes
private:
    int suitit;
    vector<QNS>suits;
    vector<Avenger>heroes;
    vector<Avenger>enemies;
    vector<string>Outof;
    vector<vector<string>>battlelog;
};
int main(){
    int k, n, m;
    cin>>k>>n>>m;
    Battle B(k, n, m);
    string s;
    cin>>s;
    if(s=="BattleBegin"){
        B.startBattle();
    }
}
