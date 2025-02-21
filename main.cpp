#include<bits/stdc++.h>
using namespace std;
#include "Faculty.h"
bool sortcg(BTech B1, BTech B2){
    return B1.getCG() > B2.getCG();
}
bool sorthost(DualDegree D1, DualDegree D2){
    return D1.getHostel() > D2.getHostel();
}
class IITM{
    vector<BTech>BTs;
    vector<DualDegree>DDs;
    vector<Faculty *>Profs;
    vector<string>Hostels = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
public:
    string getR(){
        string a = "";
        string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        for(int i=0;i<10;i++){
            a += b[rand() % b.size()];
        }
        return a;
    }
    string getProf(){
        return Profs[rand()%100]->getName();
    }
    void setProfs(){
        for(int i=0;i<100;i++){
            string name = getR();
            Faculty* f = new Faculty;
            f->setP(name, rand() % 2);
            Profs.push_back(f);
        }
    }
    void setBts(){
        for(int i=0;i<50000;i++){
            string rno = getR();
            string name = getR();
            string hostel = Hostels[rand()%10];
            int n = rand() % 100;
            float cgpa = (rand() % 1000)/100;
            BTech B(rno, name, hostel, Profs[n], cgpa);
            BTs.push_back(B);
        }
    }
    void setDDs(){
        for(int i=0;i<50000;i++){
            string rno = getR();
            string name = getR();
            string hostel = Hostels[rand()%10];
            int n = rand() % 100;
            DualDegree DD(rno, name, hostel, Profs[n]);
            DDs.push_back(DD);
        }
    }
    void setGuides(){
        int bid = 0;
        sort(BTs.begin(), BTs.end(), sortcg);
        for(int i=0;i<100;i++){
            Profs[i]->addBTP(BTs[bid]);
            Profs[i]->addBTP(BTs[bid+1]);
            BTs[bid].setBTPGuide(Profs[i]);
            BTs[bid+1].setBTPGuide(Profs[i]);
            bid+=2;
        }
        int dta = 0;
        for(int i=0;i<100;i++){
            Profs[i]->addTA(DDs[dta]);
            Profs[i]->addTA(DDs[dta + 1]);
            Profs[i]->addTA(DDs[dta + 2]);
            Profs[i]->addTA(DDs[dta + 3]);
            Profs[i]->addTA(DDs[dta + 4]);
            DDs[dta].setTASupervisor(Profs[i]);
            DDs[dta+1].setTASupervisor(Profs[i]);
            DDs[dta+2].setTASupervisor(Profs[i]);
            DDs[dta+3].setTASupervisor(Profs[i]);
            DDs[dta+4].setTASupervisor(Profs[i]);
        }
        sort(DDs.begin(), DDs.end(), sorthost);
        int did=0;
        for(int i=0;i<100;i++){
            Profs[i]->addDDP(DDs[did]);
            Profs[i]->addDDP(DDs[did+1]);
            DDs[did].setDDPGuide(Profs[i]);
            DDs[did+1].setDDPGuide(Profs[i]);
            did+=2;
        }
    }
    void printP(){
        for(int i=0;i<100;i++){
            cout<<Profs[i]->getName()<<endl;
            cout<<BTs[i].getName()<<endl;
            cout<<DDs[i].getName()<<endl;
        }
    }
    void DDPTA(){
        float tot = 0;
        for(int i=0;i<DDs.size();i++){
            if(DDs[i].getFacad()!=nullptr && DDs[i].getTASupervisor()!=nullptr){
                if(DDs[i].getFacad()->getName() == DDs[i].getTASupervisor()->getName()){
                    tot++;
                }
            }
        }
        cout<<tot/(BTs.size() + DDs.size()) * 100<<endl;
    }
    void printSrno(){
        vector<pair<string, string>>Srno;
        for(int i=0;i<BTs.size();i++){
            pair<string, string>p;
            p.first = BTs[i].getRno();
            p.second = BTs[i].getName();
            Srno.push_back(p);
        }
        for(int i=0;i<DDs.size();i++){
            pair<string, string>p;
            p.first = DDs[i].getRno();
            p.second = DDs[i].getName();
            Srno.push_back(p);
        }
        sort(Srno.begin(), Srno.end());
        for(int i=0;i<Srno.size();i++){
            cout<<Srno[i].second<<endl;
        }
    }
    void printSH(){
        vector<pair<string, string>>SH;
        for(int i=0;i<BTs.size();i++){
            pair<string, string>p;
            p.first = BTs[i].getHostel();
            p.second = BTs[i].getName();
            SH.push_back(p);
        }
        for(int i=0;i<DDs.size();i++){
            pair<string, string>p;
            p.first = DDs[i].getHostel();
            p.second = DDs[i].getName();
            SH.push_back(p);
        }
        sort(SH.begin(), SH.end());
        for(int i=0;i<SH.size();i++){
            cout<<SH[i].second<<endl;
        }
    }
    void printSGuide(){
        vector<pair<string, string>>SGuide;
        for(int i=0;i<BTs.size();i++){
            pair<string, string>p;
            if(BTs[i].getBTPGuide() == nullptr){
                continue;
            }
            p.first = BTs[i].getBTPGuide()->getName();
            if(p.first == ""){
                continue;
            }
            p.second = BTs[i].getName();
            SGuide.push_back(p);
        }
        for(int i=0;i<DDs.size();i++){
            pair<string, string>p;
            if(DDs[i].getDDPGuide() == nullptr){
                continue;
            }
            p.first = DDs[i].getDDPGuide()->getName();
            if(p.first == ""){
                continue;
            }
            p.second = DDs[i].getName();
            SGuide.push_back(p);
        }
        sort(SGuide.begin(), SGuide.end());
        for(int i=0;i<SGuide.size();i++){
            cout<<SGuide[i].second<<endl;
        }
    }
    void printDDs(string &hostel, string& f){
        for(int i=0;i<DDs.size();i++){
            if(DDs[i].getHostel() == hostel && (DDs[i].getDDPGuide()->getName() == f || DDs[i].getFacad()->getName() == f)){
                cout<<DDs[i].getName()<<endl;
            }
        }
    }
    void findFac(){
        Faculty* a;
        int nmax = -1;
        for(int i=0;i<Profs.size();i++){
            if(Profs[i]->checkHostels() > nmax){
                a = Profs[i];
            }
            nmax = max(Profs[i]->checkHostels(), nmax);
        }
        cout<<a->getName()<<endl;
    }
    void pguideless(){
        for(int i=0;i<BTs.size();i++){
            if(BTs[i].getBTPGuide()->getName() == ""){
                cout<<BTs[i].getRno()<<endl;
            }
        }
        for(int i=0;i<DDs.size();i++){
            if(DDs[i].getDDPGuide()->getName() == ""){
                cout<<DDs[i].getRno()<<endl;
            }
        }
    }
};
int main(){
    IITM Insti;
    Insti.setProfs();
    Insti.setBts();
    Insti.setDDs();
    Insti.setGuides();
    Insti.DDPTA();
    Insti.printSrno();
    Insti.printSGuide();
    Insti.printSH();
    string f1 = Insti.getProf();
    string f2 = "5";
    Insti.printDDs(f1, f2);
    Insti.findFac();
}