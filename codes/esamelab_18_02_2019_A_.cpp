#include<iostream>
#include<cstdlib>
#include<typeinfo>
#include<cmath>
#define DIM 50

using namespace std;

class A{

    private:
        short *arr;
        short len;

    
    public:
        A(short m) : len(m) {
            arr = new short[m];
            for (int i=0; i<m; i++){
                arr[i] = rand()%(10)+1;
            }
        }

        virtual double f(short a) = 0;

        short getLen(){
            return len;
        }

        virtual ostream & print(ostream &os){
            os<<"arr=[";
            for (int i=0; i<len; i++)
                os<<arr[i]<<" ";
            os<<"], ";
            return os;
        }



    protected:
        short get(short i){
            return arr[i%len];
        }

};

ostream &operator <<(ostream &os, A&a){
    return a.print(os);
}




template<typename T>
class B : public A{

    private:
        T x;

    
    public:
        B(short m, char c) : A(m) {
            string temp="";
            for (int i=0; i<m; i++){
                temp += c;
            }
            
            if(typeid(T) == typeid(char))
                x = c;
            else
               x = temp;
            }

        double foo(short s){
            return log(s) + sin(f(s));
        }

        double f(short a){
            double sum=0;
            int count=0;
            for (int i=a%getLen(); i<getLen(); i++){
                sum += get(i);
                count++;
            }
            return sum/(count *1.0);
        }

        ostream &print(ostream&os){
            A:: print(os);
            os<<"x="<<x<<", f(3)="<<f(3);
            return os;
        }

};



class C : public A{

    private:
        int y;
    

    public:
        C(short n, int k) : A(n){
            y=k;
        }

        double f(short a){
            short r;
            r=get(rand()%getLen());
            return (a+y)/(r*1.0);
        }

        short g(short w){
            return sin(w+y);
        }

        ostream &print(ostream&os){
            A:: print(os);
            os<<"y="<<y<<", f(3)="<<f(3);
            return os;
        }

};


int main(){

srand(111222333);

      A *vett[DIM];

      for(int i=0; i<DIM; i++) {
	short n=1+rand()%10;
	switch(rand()%3) {
	  case 0: 
	    vett[i]= new C(n, rand()%10 + 1);
	    break;
	  case 1:
	    vett[i]= new B<string>(n, rand()%('z' - 'a' + 1) + 'a');
	    break;
	  case 2: 
	    vett[i]= new B<char>(n, rand()%('z' - 'a' + 1) + 'a');
	}
    }

    //Punto 1
    cout<<"Punto 1:"<<endl;
    for (int i=0; i<DIM; i++){
        cout<<i<<")"<<typeid(*vett[i]).name()<<" ";
        cout<<*vett[i]<<endl;
    }

    //Punto 2
    cout<<"Punto 2:"<<endl;
}