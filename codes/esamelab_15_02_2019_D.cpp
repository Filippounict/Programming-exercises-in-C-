#include<iostream>
#include<cstdlib>
#include<typeinfo>

#define DIM 50

using namespace std;

class A{

    private:
        int *ptr;
        short len;

    
    public:
        A(short m, short k) : len(m){
            ptr = new int[m];
            for (int i=0; i<m; i++){
                ptr[i] = rand()%(k-1+1)+1;
            }
        }

        virtual double f()const = 0;

        int get(short i)const{
            return ptr[i%len];
        }

        short getLen()const{
            return len;
        }

        virtual ostream &print(ostream &os){
            os<<", ptr=[ ";
            for (int i=0; i<len; i++)
                os<<ptr[i]<<" ";
            os<<"] , ";
            return os;
        }

        int &operator[](short i){
            return ptr[i];
        }


};

ostream &operator <<(ostream &os, A &a){
    return a.print(os);
}


class B : public A {

    private:
        double p;


    public:
        B(short m, short k, double y) : A(m,k) {
             p=y;
        }

        double f()const{
            int sum=0;
            for (int i=0; i<getLen(); i+=2){
                sum += get(i);
            }
            return sum/p;
        }

        ostream &print(ostream &os){
            A::print(os);
            os<<"p="<<p<<", f()="<<f();
            return os;
        }

};



class C : public A {

    private:
        char x;

    
    public:
        C(short n, short k, char c) : A(n,k){
            x=c;
        }

        double f()const{
            int count=0;
            int sum=0;
            for (int i=0; i<getLen(); i++){
                if (get(i)%2){
                    sum+=get(i);
                    count++;
                }
            }
            if (count)
                return sum/(count*1.0);
            else 
                return count;
        }

        string g(char c)const{
            string temp="";
            return temp+x+c;
        }

        ostream &print(ostream &os){
            A::print(os);
            os<<"x="<<x<<", f()="<<f();
            return os;
        }

};



int main(){
    srand(111222333);
    A *vett[DIM];

    for (int i = 0; i < DIM; i++){
        short n = 1 + rand() % 10;
        short m = 1 + rand() % 8;
        if (rand() % 2 == 0)
            vett[i] = new B(n, m, rand() / (double)RAND_MAX + 0.05);
        else
            vett[i] = new C(n, m, (char)(rand() % ('z' - 'a' + 1) + 'a'));
    }

    //Punto 1
    for (int i=0; i<DIM; i++){
        cout<<typeid(*vett[i]).name();
        cout<<*vett[i]<<endl;
    }

    //Punto 2
    double sum=0;
    string concat="";
    for(int i=0; i<DIM; i++){
        sum += vett[i]->f();
        if (typeid(*vett[i]) == typeid(C))
            concat += (static_cast<C*> (vett[i])->g('h'));
    }
    cout<<endl<<"Media="<<sum/(DIM*1.0)<<" , ";
    cout<<"Concat= "<<concat<<endl;


    //Punto 3
    cout<<endl<<"vett[3]="<<*vett[3]<<endl;
    (*vett[3])[2]= 15;
    cout<<"vett[3]="<<*vett[3]<<endl;


}