#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;
//global variable declaration
int k=7,r=0,flag=0;
COORD coord = {0, 0};
 
void gotoxy(int x, int y)
{
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{int mm,dd,yy;};
 
ofstream fout;
ifstream fin;
 
class item
{
int itemno;
char name[25];
date d;
public:
void add()
{
cout<<"nntItem No: ";
cin>>itemno;
cout<<"nntName of the item: ";
cin>>name;
//gets(name);
cout<<"nntManufacturing Date(dd-mm-yy): ";
cin>>d.mm>>d.dd>>d.yy;
}
void show()
{
cout<<"ntItem No: ";
cout<<itemno;
cout<<"nntName of the item: ";
cout<<name;
cout<<"nntDate : ";
cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
}
void report()
{
gotoxy(3,k);
cout<<itemno;
gotoxy(13,k);
puts(name);
}
int retno()
{
    return(itemno);
 
}
 
};
 
class amount: public item
{
float price,qty,tax,gross,dis,netamt;
public:
void add();
void show();
void report();
void calculate();
void pay();
float retnetamt()
{
    return(netamt);
}
}amt;
 
void amount::add()
{
item::add();
cout<<"nntPrice: ";
cin>>price;
cout<<"nntQuantity: ";
cin>>qty;
cout<<"nntTax percent: ";
cin>>tax;
cout<<"nntDiscount percent: ";
cin>>dis;
calculate();
fout.write((char *)&amt,sizeof(amt));
fout.close();
}
void amount::calculate()
{gross=price+(price*(tax/100));
netamt=qty*(gross-(gross*(dis/100)));
}
void amount::show()
{fin.open("itemstore.dat",ios::binary);
fin.read((char*)&amt,sizeof(amt));
item::show();
cout<<"nntNet amount: ";
cout<<netamt;
fin.close();
}
 
void amount::report()
{item::report();
gotoxy(23,k);
cout<<price;
gotoxy(33,k);
cout<<qty;
gotoxy(44,k);
cout<<tax;
gotoxy(52,k);
cout<<dis;
gotoxy(64,k);
cout<<netamt;
k=k+1;
if(k==50)
{gotoxy(25,50);
cout<<"PRESS ANY KEY TO CONTINUE...";
getch();
k=7;
system("cls");
gotoxy(30,3);
cout<<" ITEM DETAILS ";
gotoxy(3,5);
cout<<"NUMBER";
gotoxy(13,5);
cout<<"NAME";
gotoxy(23,5);
cout<<"PRICE";
gotoxy(33,5);
cout<<"QUANTITY";
gotoxy(44,5);
cout<<"TAX";
gotoxy(52,5);
cout<<"DEDUCTION";
gotoxy(64,5);
cout<<"NET AMOUNT";
}
}
 
void amount::pay()
{show();
cout<<"nnntt*********************************************";
cout<<"ntt                 DETAILS                  ";
cout<<"ntt*********************************************";
cout<<"nnttPRICE                     :"<<price;
cout<<"nnttQUANTITY                  :"<<qty;
cout<<"nttTAX PERCENTAGE              :"<<tax;
cout<<"nttDISCOUNT PERCENTAGE         :"<<dis;
cout<<"nnnttNET AMOUNT              :Rs."<<netamt;
cout<<"ntt*********************************************";
}
 
int main()
{
cout.setf(ios::fixed);
cout.setf(ios::showpoint);
cout<<setprecision(2);
fstream tmp("temp.dat",ios::binary|ios::out);
menu:
system("cls");
gotoxy(25,2);
cout<<"Super Market Billing ";
gotoxy(25,3);
cout<<"===========================nn";
cout<<"ntt1.Bill Reportnn";
cout<<"tt2.Add/Remove/Edit Itemnn";
cout<<"tt3.Show Item Detailsnn";
cout<<"tt4.Exitnn";
cout<<"ttPlease Enter Required Option: ";
int ch,ff;
float gtotal;
cin>>ch;
switch(ch)
{case 1:ss:
system("cls");
gotoxy(25,2);
cout<<"Bill Details";
gotoxy(25,3);
cout<<"================nn";
cout<<"ntt1.All Itemsnn";
cout<<"tt2.Back to Main menunn";
cout<<"ttPlease Enter Required Option: ";
int cho;
cin>>cho;
if(cho==1)
{system("cls");
gotoxy(30,3);
cout<<" BILL DETAILS ";
gotoxy(3,5);
cout<<"ITEM NO";
gotoxy(13,5);
cout<<"NAME";
gotoxy(23,5);
cout<<"PRICE";
gotoxy(33,5);
cout<<"QUANTITY";
gotoxy(44,5);
cout<<"TAX %";
gotoxy(52,5);
cout<<"DISCOUNT %";
gotoxy(64,5);
cout<<"NET AMOUNT";
fin.open("itemstore.dat",ios::binary);
if(!fin)
{cout<<"nnFile Not Found...";
goto menu;}
fin.seekg(0);
gtotal=0;
while(!fin.eof())
{fin.read((char*)&amt,sizeof(amt));
if(!fin.eof())
{amt.report();
gtotal+=amt.retnetamt();
ff=0;}
if(ff!=0) gtotal=0;
}gotoxy(17,k);
cout<<"nnntttGrand Total="<<gtotal;
getch();
fin.close();
}
if(cho==2)
{goto menu;}
goto ss;
case 2:
db:
system("cls");
gotoxy(25,2);
cout<<"Bill Editor";
gotoxy(25,3);
cout<<"=================nn";
cout<<"ntt1.Add Item Detailsnn";
cout<<"tt2.Edit Item Detailsnn";
cout<<"tt3.Delete Item Detailsnn";
cout<<"tt4.Back to Main Menu ";
int apc;
cin>>apc;
switch(apc)
{
case 1:fout.open("itemstore.dat",ios::binary|ios::app);
amt.add();
cout<<"nttItem Added Successfully!";
getch();
goto db;
 
case 2:
int ino;
flag=0;
cout<<"nntEnter Item Number to be Edited :";
cin>>ino;
fin.open("itemstore.dat",ios::binary);
fout.open("itemstore.dat",ios::binary|ios::app);
if(!fin)
{cout<<"nnFile Not Found...";
goto menu;
}
fin.seekg(0);
r=0;
while(!fin.eof())
{fin.read((char*)&amt,sizeof(amt));
if(!fin.eof())
{int x=amt.item::retno();
if(x==ino)
{flag=1;
fout.seekp(r*sizeof(amt));
system("cls");
cout<<"nttCurrent Details aren";
amt.show();
cout<<"nnttEnter New Detailsn";
amt.add();
cout<<"nttItem Details editted";
}
}r++;
}
if(flag==0)
{cout<<"nttItem No does not exist...Please Retry!";
getch();
goto db;
}
fin.close();
getch();
goto db;
 
case 3:flag=0;
cout<<"nntEnter Item Number to be deleted :";
cin>>ino;
fin.open("itemstore.dat",ios::binary);
if(!fin)
{cout<<"nnFile Not Found...";
goto menu;
}
//fstream tmp("temp.dat",ios::binary|ios::out);
fin.seekg(0);
while(fin.read((char*)&amt, sizeof(amt)))
{int x=amt.item::retno();
if(x!=ino)
tmp.write((char*)&amt,sizeof(amt));
else
{flag=1;}
}
fin.close();
tmp.close();
fout.open("itemstore.dat",ios::trunc|ios::binary);
fout.seekp(0);
tmp.open("temp.dat",ios::binary|ios::in);
if(!tmp)
{cout<<"Error in File";
goto db;
}
while(tmp.read((char*)&amt,sizeof(amt)))
fout.write((char*)&amt,sizeof(amt));
tmp.close();
fout.close();
if(flag==1)
cout<<"nttItem Succesfully Deleted";
else if (flag==0)
cout<<"nttItem does not Exist! Please Retry";
getch();
goto db;
case 4:
goto menu;
default: cout<<"nnttWrong Choice!!! Retry";
getch();
goto db;
}
case 3:system("cls");
flag=0;
int ino;
cout<<"nnttEnter Item Number :";
cin>>ino;
fin.open("itemstore.dat",ios::binary);
if(!fin)
{cout<<"nnFile Not Found...nProgram Terminated!";
goto menu;
}
fin.seekg(0);
while(fin.read((char*)&amt,sizeof(amt)))
{int x=amt.item::retno();
if(x==ino)
{amt.pay();
flag=1;
break;
}
}
if(flag==0)
cout<<"nttItem does not exist....Please Retry!";
getch();
fin.close();
goto menu;
case 4:system("cls");
gotoxy(20,20);
cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
char yn;
cin>>yn;
if((yn=='Y')||(yn=='y'))
{gotoxy(12,20);
system("cls");
cout<<"************************** THANKS **************************************";
getch();
exit(0);
}
else if((yn=='N')||(yn=='n'))
goto menu;
else{goto menu;}
default:cout<<"nnttWrong Choice....Please Retry!";
getch();
goto menu;
}
return 0;
}
 
