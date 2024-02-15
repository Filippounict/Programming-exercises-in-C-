#include<iostream>
#include<cstdlib>
#include<typeinfo>
#include<cmath>
#define DIM 50

using namespace std;

class A{

    private:
        double *w;
        short len;


    public:
        A(short m) : len(m) {
            w = new double [m];
            for (int i=0; i<len; i++)
                w[i]=rand()/(RAND_MAX*1.0);
        }

        virtual double foo(short a) const = 0;

        short getLen()const{
            return len;
        }

        virtual ostream &print(ostream &os){
            os<<"w=[";
            for (int i=0; i<len; i++)
                os<<get(i)<<" ";

            os<<"], ";
            return os;
        }

        double & operator[](short i) {
            return w[i];
        }

    
    protected:
        double get(short i)const{
            return w[i%len];
        }
        

};

ostream & operator <<(ostream &os, A & a){
    return a.print(os);
}




class B : public A {

    private:
        int p;


    public:
        B(short m, int x) : A(m) {
            p=x;
        }

    double foo(short a)const{
        return sum(a)/(p*1.0);
    }

    ostream &print(ostream & os){
        A::print(os);
        os<<"p="<<p<<", foo(3)="<<foo(3)<<endl;
        return os;
    }

    


    protected:
        double sum(short s) const{
            double sum=0;
            for (int i=s%getLen(); i<getLen(); i++)
                sum += get(i);

            return sum;
        }
};


template <typename T>
class C : public A{
    
    private:
        T x;

    
    public:
        C(short n) : A(n) {
            if (typeid(T) == typeid(short))
                x = n;
            else    
                x = log(1+sin(n)*sin(n));
        }

        double foo(short r)const{
            return g(r);
        }

        T g(T k)const{
            return 2*x*(k+1);
        }

        ostream &print(ostream & os){
        A::print(os);
        os<<"x="<<x<<", foo(3)="<<foo(3)<<endl;
        return os;
    }

};



int main(){

    srand(111222333);
    A *vett[DIM];
    for (int i = 0; i < DIM; i++){
        short n = 1 + rand() % 10;
        switch (rand() % 3){
            case 0:
                 vett[i] = new B(n, rand() % 10 + 1);
                 break;
            case 1:
                 vett[i] = new C<double>(n);
                 break;
            case 2:
                 vett[i] = new C<short>(n);
        }
    }

    //Punto 1
    for (int i=0; i<DIM; i++)
        cout<<i<<")"<<typeid(*vett[i]).name()<<", "<<*vett[i]<<endl;

    //Punto 2
    double max=vett[0]->foo(3);
    double sum=0;
    for (int i=0; i<DIM; i++){
        if ((vett[i]->foo(3)) > max)
            max = vett[i]->foo(3);
        if (typeid(*vett[i]) == typeid(C<double>))
            sum += (static_cast <C<double>*> (vett[i])->g(5));

    }

    cout<<"Max= "<<max<<" , Media= "<<sum/(DIM*1.0)<<endl;
    cout<<endl;

    //Punto 3
    cout<<"*Vett[3]="<<*vett[3]<<endl;
    (*vett[3])[2]=0.22;
    cout<<"*Vett[3]="<<*vett[3]<<endl;

}