#include<bits/stdc++.h>
using namespace std;
class Book{
    string isbn;
    int copiesAvailable;
    int totalCopies;
public:
    string title;
    string author;
    Book(string title1 = "UnknownTitle", string author1 = "UnknownAuthor", string isbn1 = "ISBN", int CA = 0, int TC = 5){
        title = title1;
        author = author1;
        isbn = isbn1;
        copiesAvailable = CA;
        totalCopies = TC;
    }
    Book(Book& a, string isbn1){
        title = a.title;
        author = a.author;
        isbn = isbn1;
        copiesAvailable = a.getTC();
        totalCopies = a.getTC();
    }
    string getisbn(){
        return isbn;
    }
    int getCA(){
        return copiesAvailable;
    }
    int getTC(){
        return totalCopies;
    }
    void updateCopies(int count){
        if(copiesAvailable + count < 0 || totalCopies + count < 0){
            cout<<"Invalid request! Count becomes negative"<<endl;
        }else{
            copiesAvailable += count;
            totalCopies += count;
        }
    }
    bool borrowBook(){
        if(copiesAvailable > 0){
            copiesAvailable--;
            return true;
        }else{
            cout<<"Invalid request! Copy of book not available"<<endl;
            return false;
        }
    }
    bool returnBook(){
        if(copiesAvailable == totalCopies){
            cout<<"Invalid request! Copy of book exceeds total copies"<<endl;
            return false;
        }else{
            copiesAvailable++;
            return true;
        }
    }
    void printDetails(){
        cout<<title<<' '<<author<<endl;
    }
};
class Member{
    string memberID;
    map<string, int>borrowedBooks;
    int borrowLimit;
public:
    string name;
    Member(string memID, string name1, int BL = 3){
        memberID = memID;
        name = name1;
        borrowLimit = BL;
    }
    Member(){
    }
    string getID(){
        return memberID;
    }
    bool borrowBook(string isbn1){
        int count = 0;
        for(auto it = borrowedBooks.begin();it!=borrowedBooks.end();it++){
            count += it->second;
        }
        if(count < borrowLimit){
            borrowedBooks[isbn1]++;
            return true;
        }else{
            cout<<"Invalid request! Borrow limit exceeded"<<endl;
            return false;
        }
    }
    bool returnBook(string isbn1){
        if(borrowedBooks.find(isbn1)!=borrowedBooks.end() && borrowedBooks[isbn1] > 0){
            borrowedBooks[isbn1]--;
            return true;
        }else{
            cout<<"Invalid request! Book not borrowed"<<endl;
            return false;
        }
    }
    void printDetails(){
        for(auto it = borrowedBooks.begin();it!=borrowedBooks.end();it++){
            if(it->second != 0){
                cout<<memberID<<' '<<name<<' '<<it->first<<' '<<it->second<<endl;
            }
        }
    }
};
class Library{
    vector<Book>books;
    vector<Member>members;
    set<string>isbns;
    set<string>IDs;
public:
    bool addBook(Book &a){
        if(books.size()==50){
            return false;
        }
        if(isbns.find(a.getisbn()) != isbns.end()){
            cout<<"Invalid request! Book with same isbn already exists"<<endl;
            return false;
        }else{
            books.push_back(a);
            isbns.insert(a.getisbn());
            return true;
        }
    }
    void copyBook(string isbn1, string isbn2){
        if(isbns.find(isbn1)!=isbns.end()){
            int idx=0;
            for(int i=0;i<books.size();i++){
                if(books[i].getisbn()==isbn1){
                    idx = i;
                    break;
                }
            }
            Book a(books[idx],  isbn2);
            books.push_back(a);
            isbns.insert(isbn2);
        }
    }
    void updateCopies(string isbn1, int nC){
        if(isbns.find(isbn1) != isbns.end()){
            int idx=0;
            for(int i=0;i<books.size();i++){
                if(books[i].getisbn()==isbn1){
                    idx = i;
                    break;
                }
            }
            books[idx].updateCopies(nC);
        }
    }
    bool registerMember(Member& a){
        if(members.size()==150){
            return false;
        }
        if(IDs.find(a.getID()) != IDs.end()){
            cout<<"Invalid request! Member with same id already exists"<<endl;
            return false;
        }else{
            members.push_back(a);
            IDs.insert(a.getID());
            return true;
        }
    }
    bool borrowBook(string ID, string isbn1){
        if(isbns.find(isbn1) != isbns.end()){
            int idx=0;
            for(int i=0;i<books.size();i++){
                if(books[i].getisbn()==isbn1){
                    idx = i;
                    break;
                }
            }
            if(books[idx].getCA() > 0){
                if(IDs.find(ID)!=IDs.end()){
                    int idx1=0;
                    for(int i=0;i<members.size();i++){
                        if(members[i].getID()==ID){
                            idx1 = i;
                            break;
                        }
                    }
                    if(members[idx1].borrowBook(isbn1)){
                        books[idx].borrowBook();
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    cout<<"Invalid request! Book not borrowed"<<endl;
                    return false;
                }
            }else{
                cout<<"Invalid request! Copy of book not available"<<endl;
                return false;
            }
        }else{
            cout<<"Invalid request! Copy of book not available"<<endl;
            return false;
        }
    }
    bool returnBook(string ID, string isbn1){
        if(isbns.find(isbn1) != isbns.end()){
            int idx=0;
            for(int i=0;i<books.size();i++){
                if(books[i].getisbn()==isbn1){
                    idx = i;
                    break;
                }
            }
            if(books[idx].getCA() < books[idx].getTC()){
                if(IDs.find(ID)!=IDs.end()){
                    int idx1=0;
                    for(int i=0;i<members.size();i++){
                        if(members[i].getID()==ID){
                            idx1 = i;
                            break;
                        }
                    }
                    if(members[idx1].returnBook(isbn1)){
                        books[idx].returnBook();
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    cout<<"Invalid request! Book not borrowed"<<endl;
                    return false;
                }
            }else{
                cout<<"Invalid request! Copy of book exceeds total copies"<<endl;
                return false;
            }
        }else{
            cout<<"Invalid request! Copy of book not available"<<endl;
            return false;
        }
    }
    void printLibraryDetails(){
        for(int i=0;i<books.size();i++){
            cout<<books[i].title<<' '<<books[i].author<<' '<<books[i].getCA()<<endl;
        }
        for(int i=0;i<members.size();i++){
            cout<<members[i].getID()<<' '<<members[i].name<<endl;
        }
    }
    void printBook(string isbn1){
        int idx=0;
        for(int i=0;i<books.size();i++){
            if(books[i].getisbn()==isbn1){
                idx = i;
                break;
            }
        }
        books[idx].printDetails();
    }
    void printMember(string ID){
        int idx1=0;
        for(int i=0;i<members.size();i++){
            if(members[i].getID()==ID){
                idx1 = i;
                break;
            }
        }
        members[idx1].printDetails();
    }
};
int main(){
    Library Lib;
    string op;
    while(true){
        cin>>op;
        if(op == "Done"){
            break;
        }else if(op == "Book"){
            string s1, s2, s3;
            int CA, TC;
            cin>>s1;
            if(s1 == "ExistingBook"){
                cin>>s2>>s3;
                Lib.copyBook(s2, s3);
            }else if(s1 == "None"){
                Book a;
                Lib.addBook(a);
            }else{
                cin>>s2>>s3>>CA>>TC;
                Book a(s1, s2, s3, CA, TC);
                Lib.addBook(a);
            }
        }else if(op == "UpdateCopiesCount"){
            string isbn1;
            int nC;
            cin>>isbn1>>nC;
            Lib.updateCopies(isbn1, nC);
        }else if(op == "Member"){
            string s1, s2, s3;
            int BL;
            cin>>s1;
            if(s1 == "NoBorrowLimit"){
                cin>>s2>>s3;
                Member m(s2, s3);
                Lib.registerMember(m);
            }else{
                cin>>s2>>BL;
                Member m(s1, s2, BL);
                Lib.registerMember(m);
            }
        }else if(op == "Borrow"){
            string ID, isbn1;
            cin>>ID>>isbn1;
            Lib.borrowBook(ID, isbn1);
        }else if(op == "Return"){
            string ID, isbn1;
            cin>>ID>>isbn1;
            Lib.returnBook(ID, isbn1);
        }else if(op == "PrintBook"){
            string a;
            cin>>a;
            Lib.printBook(a);
        }else if(op == "PrintMember"){
            string a;
            cin>>a;
            Lib.printMember(a);
        }else if(op == "PrintLibrary"){
            Lib.printLibraryDetails();
        }
    }
}
