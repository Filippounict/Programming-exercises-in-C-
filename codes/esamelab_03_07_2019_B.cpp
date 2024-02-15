#include<iostream>
#include<cstdlib>
#include<typeinfo>
#include<string>
#define DIM 50

using namespace std;

class A{
    private:
        char *s;
        short len;


    public:
        A(short m) : len(m) {
            s=new char[m];
            for (int i=0; i<m; i++)
                s[i]=(char)(rand()%(122-97+1)+97);
        }

        short getLen(){
            return len;
        }

        virtual double elab(short a) = 0;

        virtual ostream & print(ostream &os){
            os<<"s= ";
            for (int i=0; i<len; i++)
                os<<*s;

            os<<", ";
            return os;
        }
    
    protected:
        char get(short i){
            return s[i%len];
        }

};

ostream & operator <<(ostream & os, A & a){
    return a.print(os);
}


class B : public A{

    private:
        int p;

    public:
        B (short m, int x) : A(m){
            p=x;
        }

        double elab(short a){
            int voc=0;
            int cons=0;
            for (int i=0; i<getLen(); i++){
                switch(get(i)){
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                        voc++;
                        break;
                    default:
                        cons++;
                }
             }

            return voc/(cons+1);
            }

        ostream & print (ostream & os){
            A:: print(os);
            os<< "p="<<p<<", elab(3)="<< elab(3)<<endl;
            return os;
        }

        B operator ++(int){
            B aux = *this;
            p++;
            return aux;
        }



    protected:
        bool test(){
            for (int i=0; i<4 && i<getLen(); i++){
               switch(get(i)){
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                        return true;
                 }
                return false;
             }
        }

};



class C : public A{
    private:
        char x;

    public:
        C(short n, char c) : A(n) {
            x=c;
        }

        double elab(short r){
            int count=0;
            for (int i=r%getLen(); i<getLen(); i++){
                if (get(i)>= x)
                    count++;
            }
            return count/(getLen()*1.0);
        }

    string g(char c){
        string temp="";
        temp += x+c;
        return temp;
    }

    ostream & print (ostream & os){
            A:: print(os);
            os<< "x="<<x<<", elab(3)="<< elab(3)<<endl;
            return os;
        }
};



int main(){

    A* vett[DIM];
    srand(111222333);

    for (int i = 0; i < DIM; i++){
        short n = 1 + rand() % 10;
        if (rand() % 2 == 0)
            vett[i] = new B(n, rand() % 10 + 1);
        else
            vett[i] = new C(n, (char)(rand() % ((int)'z' - (int)'a' + 1) + (int)'a'));
    }

    //Punto 1
    for (int i=0; i<DIM; i++){
        cout<<i<<")"<<typeid(*vett[i]).name()<<" " <<*vett[i]<<endl;
    }

    //Punto 2
    double sum=0;
    for (int i=0; i<DIM; i++)
        sum += vett[i]->elab(3);

    cout<<"Media= "<< sum/(DIM*1.0)<<"  Concatenata= ";

    string temp = "";
    for (int i=0; i<DIM; i++){
        if (typeid(*vett[i]) == typeid(C))
            temp += (static_cast<C*>(vett[i]))->g('h');
    }
    cout<<temp<<endl;

    //Punto 3
    B b(2,6);
    cout<<b<<endl;
    b++;
    cout<<b;
}