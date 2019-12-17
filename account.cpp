#include <iostream>
using namespace std;
class Account{
    int yuan;
    int jiaofen;
public:
    Account(int yuan, int jiaofen):yuan(yuan),jiaofen(jiaofen){};
    Account operator+(Account& a){
        Account account(yuan+a.yuan , jiaofen+a.jiaofen);
        return account;
    }
    Account& operator++(){
        jiaofen++;
        return *this;
    }
    Account operator++(int){
        Account account(yuan , jiaofen);
        account.jiaofen++;
        return account;
    }
};

