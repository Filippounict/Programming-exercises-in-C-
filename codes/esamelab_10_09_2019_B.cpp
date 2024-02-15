#include<iostream>
#include<cstdlib>
#include<typeinfo>
#include<cmath>
#define DIM 50

using namespace std;

class A{
S
    private:
        double *arr;
        short len;

    
    public: 
        A(short m) : len(m){
            arr = new double[m];
            for (int i=0; i<m; i++) 
                arr[i] = rand()/(RAND_MAX*1.0);
        }

        virtual double f(short a) = 0;

        short getLen(){
            return len;
        }

        virtual ostream &print(ostream &os){
            os<<"arr=[";
            for (int i=0; i<len; i++)
                os<<get(i)<<" ";
            os<<"], ";
            return os;
        }

        double operator ()(int i1, int i2){
            double sum=0;
            for (int i=i1; i<i2 && i<getLen(); i++)
                sum+= arr[i];

            return sum;
        }

    protected:
        double get(short i){
            return arr[i%len];
        }
};

ostream & operator <<(ostream &os, A &a){
    return a.print(os);
}


class B : public A {

    private:
        double p;


    public:
        B(short m) : A(m) {
            double sum=0;
            for (int i=0; i<getLen(); i++){
                sum+=get(i);
            }
            p = sum/(getLen()*1.0);
        }

        double f(short a){
            return log(foo(a, 2*a))/(p*1.0);
        }

        ostream &print(ostream &os){
            A::print(os);
            os<<"p="<<p<<", f(3)= "<<f(3)<<endl;
            return os;
        }

    protected:
        double foo(short s, int k){
            double sum=0;
            for (int i=s%getLen(); i<getLen(); i++){
                sum += get(i);
            }
            return sum*k*1.0;
        }

};


template<typename T>
class C : public A {

    private:
        T x;


    public:
        C(short n) : A(n) {
            if(typeid(T) == typeid(short))
                x = n;
            else    
                x= log(1+(sin(n))*(sin(n)));
        }

        double f(short r){
            return g(r);
        }

        T g(T k){
            return 2*x*(k+1);
        }

        ostream &print(ostream &os){
            A::print(os);
            os<<"x="<<x<<", f(3)= "<<f(3)<<endl;
            return os;
        }

};



int main(){
    A* vett[DIM];
    srand(111222333);

    for (int i = 0; i < DIM; i++){
        short n = 1 + rand() % 10;
        switch (rand() % 3){
            case 0:
                 vett[i] = new B(n);
                 break;
            case 1:
                 vett[i] = new C<double>(n);
                 break;
            case 2:
                 vett[i] = new C<short>(n);
         }
    }

    //Punto 1
    for (int i=0; i<DIM; i++){
        cout<<i<<")"<<typeid(*vett[i]).name()<<", ";
        cout<<*vett[i]<<endl;
    }

    //Punto 2
    double max=vett[0]->f(3);
    double sum=0;
    for (int i=0; i<DIM; i++){
        if (vett[i]->f(3) > max)
            max = vett[i]->f(3);
        if (typeid(*vett[i]) == typeid(C<double>))
            sum +=static_cast<C<double>*>(vett[i])->g(5);

    }
    cout<<endl<<"Max="<<max<<endl;
    cout<<"Media= "<<sum/(DIM*1.0)<<endl;
    cout<<endl;

    //Punto 3
    cout<<"*vett[3]= "<<*vett[3]<<endl;
    cout<<"(*vett[3])(2,5)= "<<(*vett[3])(2,5)<<endl;

}
