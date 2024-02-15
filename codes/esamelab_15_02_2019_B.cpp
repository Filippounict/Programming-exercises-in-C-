#include<iostream>
#include<cstdlib>
#include<typeinfo>
#include<cmath>
#define DIM 50

using namespace std;

class A{

    private:
        int x;

    
    public:
        A(int m){
            x=m;
        }

        virtual double v(int a) const = 0;

        virtual ostream & print(ostream & os){
            os<<"x="<<x<<" ";
            return os;
        }

};

ostream &operator <<(ostream &os, A& a){
    return a.print(os);
}


class B : public A {
    
    private:
        int *ptr;
        int l;

    
    public:
        B(int z, int y) : A((short)(z)), l(y) {
            ptr= new int[y];
            for (int i=0; i<y; i++)
                ptr[i]=rand()%(100)+1;
        }

        double v(int a)const{
            return l*1000/(sum(a)+1);
        }
    
        ostream & print(ostream & os){
            A::print(os);
            os<<"ptr=[ ";
            for (int i=0; i<l; i++)
                os<<ptr[i]<<" ";

            os<<"], ";
            os<<"v(50)="<<v(50);
            return os;
        }

        int & operator [](int i){
            return ptr[i];
        }
    

    protected:
        int sum(int t)const{
            int sum=0;
            for (int i=0; i<l; i++){
                if (ptr[i]<=t)
                    sum += ptr[i];
            }
            return sum;
        }
};


template<typename T>
class C : public A {

    private:
        T k;

    public:
        C(int n) : A((short)(n)){
            if(typeid(T) == typeid(int))
                k=2*n;
            else    
                k= log(1+(sin(n)*sin(n)));
        }

        double v(int r) const{
            return g(r);
        }

        T g(T w)const{
            return k*(w+1);
        }

        ostream & print(ostream & os){
            A::print(os);
            os<<"k="<<k;
            os<<", v(50)="<<v(50);
            return os;
        }

};





int main(){

    srand(111222333);

    A *vett[DIM];

    for (int i = 0; i < DIM; i++){
        int n = 1 + rand() % 10;
        switch (rand() % 3){
            case 0:
                vett[i] = new B(n, rand() % 10 + 1);
                break;
            case 1:
                vett[i] = new C<int>(n);
                break;
            case 2:
                vett[i] = new C<double>(n);
        }
    }

    //Punto 1
    for (int i=0; i<DIM; i++){
        cout<<i<<")"<<typeid(*vett[i]).name()<<", ";
        cout<<*vett[i]<<endl;
    }

    //Punto 2
    double max = vett[0]->v(50);
    double min = max;
    double sum = 0;

    for (int i=0; i<DIM; i++){
        if((vett[i]->v(50)) > max)
            max = vett[i]->v(50);
        if (min < vett[i]->v(50))
            min = vett[i]->v(50);
        if (typeid(*vett[i]) == typeid(C<double>))
            sum += (static_cast<C<double>*> (vett[i])->g(5));
            

    }

    cout<<endl<<"Max= "<<max<<" , Media= "<<sum/(DIM*1.0)<<endl<<endl;

    //Punto 3
    B b(3,5);
    cout<<"Vett[3]="<<b<<endl;
    (b)[2]= 9;
    cout<<"Vett[3]="<<b<<endl;

}