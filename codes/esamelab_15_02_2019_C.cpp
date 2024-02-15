#include<iostream>
#include<cstdlib>
#include<typeinfo>
#include<string>
#define DIM 50

using namespace std;

class A{

    private:
        char * str;
        short len;

    
    public:
        A(short m) : len(m){
            str = new char[m];
            for (int i=0; i<m; i++)
                str[i] =(char) (rand()%(122-97+1)+97);
        }

        virtual double elab(short a)const = 0;

        short getLen() const{
            return len;
        }

        virtual ostream &print(ostream &os){
            os<<"w= ";
            for (int i=0; i<len; i++)
                os<<str[i];
            os<<", ";
            return os;
        }


    protected:
        char get (short i)const{
            return str[i%len];
        }


};

ostream &operator <<(ostream &os, A &a){
    return a.print(os);
}



class B : public A{
    
    private:
        int p;


    public:
        B(short m, int x) : A(m){
            p=x;
        }

        double elab(short a)const {
            short sum=0;
            short *temp=map();
            for (int i=0; i<getLen(); i++){
                sum += temp[i];
            }
            return sum/(p*1.0);
        }

        ostream &print(ostream &os){
            A:: print(os);
            os<<"p="<<p<<", elab(3)="<<elab(3);
            return os;
        }

        B operator ++(int){
            p++;
            return *this;
        }



    protected:
        short *map()const{
            short *a=new short[getLen()];
            for(int i=0; i<getLen(); i++){
                switch(get(i)){
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                        a[i]=false;
                        break;
                    default:
                        a[i]=true;
                }
            }
            return a;
        }
};



class C : public A{

    private:
        char x;


    public:
        C(short n, char c) : A(n){
            x=c;
        }

        double elab(short r)const{
            int count=0;
            for (int i=0; i<getLen(); i++){
                if (get(i) >= x)
                    count++;
            }
            return count/(getLen()*1.0);
        }

        string g(char c)const{
            string temp = "";
            return temp+x+c;
        }

        ostream &print(ostream &os){
            A:: print(os);
            os<<"x="<<x <<", elab(3)="<<elab(3);
            return os;
        }
};




int main(){
    srand(111222333);

    A *vett[DIM];

    for (int i = 0; i < DIM; i++){
        short n = 1 + rand() % 10;
        if (rand() % 2 == 0)
            vett[i] = new B(n, rand() % 10 + 1);
        else
            vett[i] = new C(n, (char)(rand() % ('z' - 'a' + 1) + 'a'));
    }

    //Punto 1
    for(int i=0; i<DIM; i++){
        cout<<i<<")"<<typeid(*vett[i]).name()<<" ";
        cout<<*vett[i]<<endl;
        }

    //Punto 2
    double sum=0;
    string concat="";
    for (int i=0; i<DIM; i++){
        sum += vett[i]->elab(3);
        if (typeid(*vett[i]) == typeid(C)){
           concat += (static_cast<C *>(vett[i]))->g('h');
        }
    }

    cout<<endl<<"Media= "<<sum/(DIM*1.0)<<", Concat= "<<concat<<endl;

    //Punto 3
    B b(3,5);
    cout<<b<<endl;
    b++;
    cout<<b<<endl;
    

}