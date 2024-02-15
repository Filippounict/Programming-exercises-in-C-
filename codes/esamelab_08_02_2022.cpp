#include<iostream>
#include<cstdlib>
#include<typeinfo>
#define DIM 50

using namespace std;

class A{

    private:
        double *vec;
        short len;

    
    public:
        A(short w, double a, double b) : len(w) {
            vec = new double[w];
            for (int i=0; i<w; i++){
                vec[i] = (double)(-a+rand())/(double)((RAND_MAX)/(b-a*1.0));
            }
        }

        virtual bool test(short a) = 0;

        virtual ostream &print (ostream &os){
            os<<"vec=[";
            for (int i=0; i<len; i++)
                os<<vec[i]<<" ";
            os<<"] ";
            return os;
        }

        double &operator [](short i){
            return vec[i];
        }


    
    protected:
        double select(double x){
            double sum = 0;
            int conta = 0;
            for(int i=0; i<len; i++){
                if (vec[i] >= x){
                    sum += vec[i];
                    conta++;
                }
            }
            return sum/(conta*1.0);
        }

};

ostream &operator<<(ostream &os, A&a){
    return a.print(os);
}



class B : public A{

    private:
        short p;

    
    public:
        B(short m, short a, short b) : A(m,(double)(a),(double)(b)){
            p = - rand()%(-b-(-a)+1)+a;
        }

        bool test(short a){
            if (p >= a)
                return true;
            else 
                return false;
        }

        ostream &print (ostream &os){
            A::print(os);
            os<<"p="<<p;
            return os;
        }

};



template <typename T>
class C : public A {

    private:
        T alpha;


    public:
        C(short n, double x, double y) : A(n,x,y) {
            if (typeid(T) == typeid(short))
                alpha = n;
            else    
                alpha = (double)(-x+rand())/(double)((RAND_MAX)/(-y+x+1));
        }

        bool test(short r){
            if ((g(r)/alpha)>=1)
                return true;
            else 
                return false;
        }

        double g(double k){
            return select(k)*2;
        }

        ostream &print (ostream &os){
            A::print(os);
            os<<"alpha="<<alpha;
            return os;
        }
};






int main(){

    A* vec[DIM];
    srand(11223367);

    for (unsigned short i = 0; i < DIM; i++){
        short r = rand() % 3;
        if (r == 0) 
            vec[i] = new C<double>(rand() % 5 + 5,
                                   rand() % 5 + 5 + rand() / (RAND_MAX * 1.0),
                                   rand() % 10 + 10 + rand() / (RAND_MAX * 1.0));
        else if (r == 1)
            vec[i] = new C<short>(rand() % 5 + 5,
                                  rand() % 5 + 5 + rand() / (RAND_MAX * 1.0),
                                  rand() % 10 + 10 + rand() / (RAND_MAX * 1.0));
        else // B
            vec[i] = new B(rand() % 5 + 5, rand() % 5 + 5, rand() % 15 + 10);
    }


    //Punto 1
    cout<<endl<<"Punto 1:"<<endl;
    for (int i=0; i<DIM; i++){
        cout<<i<<")"<<typeid(*vec[i]).name()<<" ";
        cout<<*vec[i]<<endl;

    }


    //Punto 2
    double max=-1000;
    int conta = 0;
    cout<<endl<<"Punto 2:"<<endl;
    for (int i=0; i<DIM; i++){
        if(typeid(*vec[i]) == typeid(C<double>)){
            if(((static_cast<C<double>*>(vec[i]))->g(12)) > (max))
                max = (static_cast<C<double>*>(vec[i]))->g(12);
        }

        if(vec[i]->test(12))
            conta++;

    }

    cout<<"Max= "<<max<<", conta="<<conta<<endl;

    //Punto 3
    cout<<endl<<"Punto 3:"<<endl;
    cout<<"(*vec[2])[2]="<<(*vec[2])<<endl;
    (*vec[2])[2]=56.9;
    cout<<"(*vec[2])[2]="<<(*vec[2])<<endl;
    

}