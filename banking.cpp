#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>

using namespace std;

#define MINIMUM_BALANCE 500

class InsufficientBalance{};

class Account
{
private:

 long accNo;
 string fName;
 string lName;
 float balance;
 static long nxtAccountNo;
 
public:

 Account(){}
 Account(string fname,string lname,float balance);
 long getAccNo(){return accNo;}
 string getfName(){return fName;}
 string getlName(){return lName;}
 float getBalance(){return balance;}

 void Deposit(float amount);
 void Withdraw(float amount);
 static void setLastaccNo(long accNo);
 static long getLastaccNo();
 friend ofstream & operator<<(ofstream &ofs,Account &acc);
 friend ifstream & operator>>(ifstream &ifs,Account &acc);
 friend ostream & operator<<(ostream &os,Account &acc);
};

long Account::nxtAccountNo=0;

class Bank
{
private:

 map<long,Account> accounts;
public:

 Bank();
 Account OpenAccount(string fname,string lname,float balance);
 Account BalanceEnquiry(long accNo);
 Account Deposit(long accNo,float amount);
 Account Withdraw(long accNo,float amount);
 void CloseAccount(long accNo);
 void ShowAllAccounts();
 ~Bank();
};

int main()
{
 Bank b;
 Account acc;

 int choice;
 string fname,lname;
 long accNo;
 float balance;
 float amount;
 cout<<"~~~Banking System~~~"<<endl;
 
 do
 {
 cout<<"\n\nAvailable Operation ";
 cout<<"\n\t1 Open Account";
 cout<<"\n\t2 Balance Enquiry";
 cout<<"\n\t3 Deposit Amount";
 cout<<"\n\t4 Withdraw Amount";
 cout<<"\n\t5 Close Account";
 cout<<"\n\t6 Display all saved Accounts";
 cout<<"\n\t7 Quit";
 cout<<"\nEnter your Operation: ";
 
 cin>>choice;
 
 switch(choice)
 {
 case 1:
 cout<<"Enter First Name: ";
cin>>fname;
cout<<"Enter Last Name: ";
cin>>lname;
cout<<"Enter initial Balance: ";
cin>>balance;
 acc=b.OpenAccount(fname,lname,balance);
 cout<<endl<<"Account is Created"<<endl;
 cout<<acc;
break;
 case 2:
 cout<<"Enter Account Number:";
cin>>accNo;
 acc=b.BalanceEnquiry(accNo);
 cout<<endl<<"Your Account Details"<<endl;
 cout<<acc;
break;
 case 3:
 cout<<"Enter Account Number:";
cin>>accNo;
cout<<"Enter Balance:";
cin>>amount;
 acc=b.Deposit(accNo, amount);
 cout<<endl<<"Amount is Deposited"<<endl;
 cout<<acc;
break;
 case 4:
 cout<<"Enter Account Number:";
cin>>accNo;
cout<<"Enter Balance:";
cin>>amount;
 acc=b.Withdraw(accNo, amount);
 cout<<endl<<"Amount Withdrawn"<<endl;
 cout<<acc;
break;
 case 5:
 cout<<"Enter Account Number:";
cin>>accNo;
 b.CloseAccount(accNo);
 cout<<endl<<"Account is Closed"<<endl;
 cout<<acc;
 case 6:
 b.ShowAllAccounts();
 break;
 case 7: break;
 default:
 cout<<"\nEnter corret choice";
exit(0);

 }
 }while(choice!=7);

 return 0;
}
Account::Account(string fname,string lname,float balance)
{
 nxtAccountNo++;
 accNo=nxtAccountNo;
 fName=fname;
 lName=lname;
 this->balance=balance;
}
void Account::Deposit(float amount)
{
 balance+=amount;
}
void Account::Withdraw(float amount)
{
 if(balance-amount<MINIMUM_BALANCE)
 throw InsufficientBalance();
 balance-=amount;
}
void Account::setLastaccNo(long accNo)
{
 nxtAccountNo=accNo;
}
long Account::getLastaccNo()
{
 return nxtAccountNo;
}
ofstream & operator<<(ofstream &ofs,Account &acc)
{
 ofs<<acc.accNo<<endl;
 ofs<<acc.fName<<endl;
 ofs<<acc.lName<<endl;
 ofs<<acc.balance<<endl;
 return ofs;
}
ifstream & operator>>(ifstream &ifs,Account &acc)
{
 ifs>>acc.accNo;
 ifs>>acc.fName;
 ifs>>acc.lName;
 ifs>>acc.balance;
 return ifs;

}
ostream & operator<<(ostream &os,Account &acc)
{
 os<<"First Name:"<<acc.getfName()<<endl;
 os<<"Last Name:"<<acc.getlName()<<endl;
 os<<"Account Number:"<<acc.getAccNo()<<endl;
 os<<"Balance:"<<acc.getBalance()<<endl;
 return os;
}
Bank::Bank()
{

 Account account;
 ifstream infile;
 infile.open("Bank.data");
 if(!infile)
 {
 //cout<<"Error in Opening! File Not Found!!"<<endl;
 return;
 }
 while(!infile.eof())
 {
 infile>>account;
 accounts.insert(pair<long,Account>(account.getAccNo(),account));
 }
 Account::setLastaccNo(account.getAccNo());

 infile.close();

}
Account Bank::OpenAccount(string fname,string lname,float balance)
{
 ofstream outfile;
 Account account(fname,lname,balance);
 accounts.insert(pair<long,Account>(account.getAccNo(),account));

 outfile.open("Bank.data", ios::trunc);

 map<long,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 outfile<<itr->second;
 }
 outfile.close();
 return account;
}
Account Bank::BalanceEnquiry(long accNo)
{
 map<long,Account>::iterator itr=accounts.find(accNo);
 return itr->second;
}
Account Bank::Deposit(long accNo,float amount)
{
 map<long,Account>::iterator itr=accounts.find(accNo);
 itr->second.Deposit(amount);
 return itr->second;
}
Account Bank::Withdraw(long accNo,float amount)
{
 map<long,Account>::iterator itr=accounts.find(accNo);
 itr->second.Withdraw(amount);
 return itr->second;
}
void Bank::CloseAccount(long accNo)
{
 map<long,Account>::iterator itr=accounts.find(accNo);
 cout<<"Account Deleted"<<itr->second;
 accounts.erase(accNo);
}
void Bank::ShowAllAccounts()
{
 map<long,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
 }
}
Bank::~Bank()
{
 ofstream outfile;
 outfile.open("Bank.data", ios::trunc);

 map<long,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 outfile<<itr->second;
 }
 outfile.close();
}
