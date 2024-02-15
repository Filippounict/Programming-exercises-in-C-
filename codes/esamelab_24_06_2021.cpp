#include<iostream>
#include<cstdlib>
#include<typeinfo>
#include<cmath>
#define DIM 50

using namespace std;

class A{

    private:
        double* vec;
        short len;


    public:
        A(short w, double a, double b) : len(w) {
            vec = new double[w];
            for (int i=0; i<len; i++)
                vec[i] = a+(double)(rand())/((double)(RAND_MAX)/((b-a)*1.0));
        }
        
        virtual double foo(short a) = 0;

        short getLen(){
            return len;
        }

        virtual ostream & print(ostream &os){
            os<<"vec=[";
            for (int i=0; i<len; i++)
                os<<vec[i]<<" ";
            os<<"],";
            return os;
        }

        double & operator [](short i){
            return vec[i];
        }


    

    protected:
        double get(short i){
            return vec[i%len];
        }

};

ostream &operator <<(ostream &os,A &a){
    return a.print(os);
}





class B : public A{

    private:
        int p;


    public:
        B(short m, short x, short y) : A(m, x, y) {
            if((100*y) > (10*x))
                p = rand()%((100*y) - (10*x)+1) + (10*x);
            else    
                p = rand()%((10*x) - (100*y)+1) + (100*y);
        }

        double foo(short a){
            return log(prod(a, a/2));
        }

        ostream &print(ostream &os){
            A:: print(os);
            os<<"p="<<p;
            return os;
        }




    
    protected:
        double prod(short s, double v){
            double sum=0;
            for (int i=s%getLen(); i<getLen(); i++){
                sum += get(i);
            }
            return v*sum;
        }
        
};



template <typename T>
class C : public A{

    private:
        T y;


    public:
        C(short n, double x, double y) : A(n,x,y)  {
            if (typeid(T) == typeid(short))
                y = n;
            else    
                y = 1+ cos(n)*cos(n);
        }

        double foo(short r){
            return g(r);
        }

        double g(double k){
            return (double)(2*y*(k+1));

        }

         ostream &print(ostream &os){
            A:: print(os);
            os<<"y="<<y;
            return os;
        }

        

};






int main(){

    A* vett[DIM];
    srand(111222333);

      for(int i=0; i<DIM; i++) {
	    short n=5+rand()%5;
	     switch(rand()%3) {
	        case 0: 
	          vett[i]= new B(n, rand()%5 + 1, rand()%10 + 5);
	          break;
	        case 1:
	          vett[i]= new C<double>(n, rand()%5 + 1, rand()%10 + 5);
	          break;
	        case 2: 
	          vett[i]= new C<short>(n, rand()%5 + 1, rand()%10 + 5);
	     }
      }


      //Punto 1
      cout<<endl<<"Punto 1:"<<endl;
      for (int i=0; i<DIM; i++){
        cout<<i<<")"<<typeid(*vett[i]).name()<<",";
        cout<<*vett[i]<<", foo(3)="<<vett[i]->foo(3)<<endl;
      }


      //Punto 2
      cout<<endl<<"Punto 2:"<<endl;
      double max = vett[0]->foo(3);
      double sum = 0;
      int conta = 0;
      for (int i=0; i<DIM; i++){
        if(vett[i]->foo(3) > max)
            max= vett[i]->foo(3);   
        if(typeid(*vett[i]) == typeid(C<double>)){
            sum += (static_cast<C<double>*>(vett[i])->g(0.5));
            conta++;
        }
      }

      cout<<endl<<"Max="<<max<<", avg="<<sum/(conta*1.0)<<endl;

     
      //Punto 3
      cout<<endl<<"Punto 3:"<<endl;
      cout<<"vett[10]="<<typeid(*vett[10]).name()<<", "<<*vett[10]<<endl;
      cout<<"(*vett[10])[0]"<<(*vett[10])[0]<<endl;
      (*vett[10])[0] = 23.33;
      cout<<"(*vett[10])[0]"<<(*vett[10])[0]<<endl;
      cout<<"vett[10]="<<typeid(*vett[10]).name()<<", "<<*vett[10]<<endl;



}