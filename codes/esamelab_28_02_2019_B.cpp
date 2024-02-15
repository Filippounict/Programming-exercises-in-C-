#include<iostream>
#include<cstdlib>
#include<typeinfo>
#include<cmath>
#define DIM 50

using namespace std;

class A{

    private:
        char *ptr;
        short len;


    public:
        A(short m, char c) : len(m) {
            ptr = new char[m];
            for (int i=0; i<m; i++){
                ptr[i] =(char) (rand()%(c - 'a' +1)+'a');
            }
        }

        virtual string elab (short a, char c) = 0;

        short getLen(){
            return len;
        }

        virtual ostream &print(ostream & os){
            os<<"ptr=[";
            for(int i=0; i<len; i++)
                os<<ptr[i]<<" ";
            os<<"], ";
            return os;
        }

        char &operator[](short i){
            return ptr[i];
        }

    
    protected:
        char get(short i){
            return ptr[i];
        }

};

ostream &operator<<(ostream &os, A&a){
    return a.print(os);
}





class B : public A{

    private: 
        double x;

    
    public:
        B(short m, double y, char c) : A(m,c) {
            x=y;
        }

        double foo(short s){
            return sin(x+s)/(log(x+s)*1.0);
        }

        string elab(short a, char c){
            string temp="";
            for (int i=0; i<getLen(); i++){
                if((get(i) - c) <= a)
                    temp += get(i);
            }
            return temp;
        }

        ostream &print(ostream &os){
            A::print(os);
            os<<"x="<<x<<", elab(5,'z')="<<elab(5,'z');
            return os;
        }
};



template<typename T>
class C : public A {

    private:
        T y;

    
    public:
        C(short n, double k, char c) : A(n,c) {
            if(typeid(T) == typeid(short))
                y = (100*k)+0.5;
            else 
                y = k;
        }

        string elab(short a, char c){
            string temp = "";
            if(getLen() >= a){
                for (int i=0; i<a; i++){
                    temp += c;
                }
            }
            else{
                for(int i=0; i<getLen(); i++){
                    temp += get(i);
                }
            }
          return temp;
        }

        double g(short w){
            return sin(w+y);
        }

        ostream &print(ostream &os){
            A::print(os);
            os<<"y="<<y<<", elab(5,'z')="<<elab(5,'z');
            return os;
        }

};





int main(){
    srand(111222333);

    A *vett[DIM];

    for (int i = 0; i < DIM; i++) {
        short n = 1 + rand() % 10;
        switch (rand() % 3) {
             case 0:
                vett[i] = new B(n, (double)rand() / RAND_MAX, rand() % ('z' - 'a' + 1) + 'a');
                 break;
             case 1:
                vett[i] = new C<double>(n, (double)rand() / RAND_MAX, rand() % ('z' - 'a' + 1) + 'a');
                 break;
             case 2:
                vett[i] = new C<short>(n, (double)rand() / RAND_MAX, rand() % ('z' - 'a' + 1) + 'a');
        }
    }

    //Punto 1
    cout<<endl<<"Punto 1:"<<endl;
    for (int i=0; i<DIM; i++){
        cout<<i<<")"<<typeid(*vett[i]).name()<<" ";
        cout<<*vett[i]<<endl;
        //cout<<", elab(5,'z')="<<vett[i]->elab(5,'z')<<endl;
    }

    //Punto 2
    cout<<endl<<"Punto 2:"<<endl;
    double sum = 0;
    int count = 0;
    double sum2=0;
    int count2=0;
    for (int i=0; i<DIM; i++){
        if(typeid(*vett[i]) == typeid(B)){
            sum += (static_cast<B*>(vett[i]))->foo(5);
            count++;
        }   
    
        if(typeid(*vett[i]) == typeid(C<short>)){
            sum2 += (static_cast<C<short>*>(vett[i]))->g(5);
            count2++;
        }
    }

    cout<<"Avg(foo(5)) = "<<sum/(count*1.0)<<", ";
    cout<<"Avg(g(5)) = "<<sum2/(count2*1.0)<<endl;


    //Punto 3
    cout<<endl<<"Punto 3:"<<endl;
    cout<<"*vett[0]: "<<typeid(*vett[0]).name()<<" "<<*vett[0]<<endl;
    cout<<"(*vett[0])[0]='*'"<<endl;
    (*vett[0])[0]='*';
    cout<<"*vett[0]: "<<typeid(*vett[0]).name()<<" "<<*vett[0]<<endl;











}