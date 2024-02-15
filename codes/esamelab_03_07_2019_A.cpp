#include <iostream>
#include <cstdlib>
#include <typeinfo>
#define DIM 50

using namespace std;

class A
{
private:
    int *arr;
    short len;

public:
    A(short m, int a, int b) : len(m)
    {
        arr = new int[m];
        for (int i = 0; i < m; i++)
        {
            arr[i] = rand() % (b - a + 1) + a;
        }
    }

    virtual double func(short i) = 0;

    short getLen()
    {
        return len;
    }

    virtual ostream & print(ostream & os){
        os<<"arr=[";
        for (int i=0; i<len; i++)
            os<<get(i)<<" ";

        os<<"], ";
        return os;
    }

    int & operator [](short i){
        return arr[i];
    }

protected:
    double get(short i)
    {
        return arr[i % len];
    }
};

ostream & operator <<(ostream & os, A & a){
    return a.print(os);
}



class B : public A
{
private:
    double p;

public:
    B(short m, int y, int z, double x) : A(m, y, z){
        p=x;
    };

    double func(short i)
    {
        int min = get(0);
        int max = min;
        for (int i = 1; i < getLen(); i++)
        {
            if (get(i) < min)
                min = get(i);
            if (get(i) > max)
                max = get(i);
        }

        return min + max + p;
    }

        ostream & print(ostream & os){
            A::print(os);
            os<<"p="<<p<<", "<<"func(3)="<<func(3)<<endl;
            return os;
        }
};



class C : public A
{
private:
    char t;

public:
    C(short n, char c, int a, int b) : A(n, a, b){
        t=c;
      }

    double func(short i)
    {
        int sum = 0;
        double media = 0;
        for (int i = 0; i < getLen(); i++)
            sum += get(i);

        media = sum / (getLen() * 1.0);
        return media;
    }

    string g(char c, short k)
    {
        string temp = "";
        for (int i = 0; i < k; i++)
            temp += t + c;

        return temp;
    }

    ostream & print(ostream & os){
        A::print(os);
        os<<"t="<< t <<", "<<"func(3)="<<func(3)<<endl;
        return os;
    }
};

int main()
{
    srand(111222333);
    A * vett[DIM];

    for (int i = 0; i < DIM; i++) {
        short n = 1 + rand() % 10;
        if (rand() % 2 == 0)
            vett[i] = new B(n, rand() % 5 + 1, rand() % 11 + 10, (double)rand() / (RAND_MAX));
        else
            vett[i] = new C(n, (char)(rand() % ('z' - 'a' + 1) + 'a'), rand() % 5 + 1, rand() % 11 + 10);
    }

    //*****Punto 1
    for(int i=0; i<DIM; i++){
       cout<<i<<")"<<typeid(*vett[i]).name()<<", ";
       cout<<*vett[i]<<endl;
    }

    //*****Punto 2
    int sum=0;
    double media=0;
    for (int i=0; i<DIM; i++){
        sum += (*vett[i]).func(3);
    }
    media = sum/(DIM*1.0);
    cout<<endl<<"Media="<<media<<endl;

    short count=0;
    for (int i=0; i<DIM && count<3; i++){
        string temp="";
        if (typeid(*vett[i]) == typeid(C)){
            temp=(static_cast<C*>(vett[i]))->g('h',2);
            count++;
            cout<<"stringa "<<count<<"= "<<temp<<endl;
        }
    }

    //*****Punto 3
    cout<<endl<<"*vett[3]= "<<*vett[3]<<endl;
    cout<<"(*vett[3])[2]="<<(*vett[3])[2]<<endl;
    (*vett[3])[2]= 99;
    cout<<"(*vett[3])[2]="<<(*vett[3])[2]<<endl;
    

    
}