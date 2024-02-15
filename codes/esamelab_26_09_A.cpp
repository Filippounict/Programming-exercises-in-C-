#include<iostream>
#include<cstdlib>
#include<typeinfo>
#define DIM 50

using namespace std;

class A{

    private:
        char *str;
        short len;

    
    public:
        A(short m,string source) : len(m){
            string voc="";
            string cons="";
            string tot="";
            str=new char[m];
                for (int i=0; i<source.length(); i++){
                    switch (source[i]){
                        case 'a':
                        case 'e':
                        case 'i':
                        case 'o':
                        case 'u':{
                                voc+=source[i];
                                break;
                            }
                        default:
                                cons+=source[i];  
                    }
                }
            tot=voc+cons;
            for (int i=0; i<m; i++)
                str[i]=tot[i];
        }

        virtual string func(short k) = 0;

        short getLen(){
            return len;
        }

        virtual ostream &print(ostream &os){
            os<<", str = ";
            for (int i=0; i<len; i++)
                os<<str[i];
            os<<" , ";
            return os;
        }

        string operator ()(int i1, int i2){
            string temp="";
            for (int i=0; i<len; i++)
                temp += str[i];
            return temp.substr(i1,i2-i1+1);
        }


    protected:
        char get(short i){
            return str[i%len];
        }

};

ostream &operator <<(ostream &os, A &a){
    return a.print(os);
}



class B : public A {

    private:
        short q;


    public:
        B(short m, string source) : A(m,source) {
            q = 1+ rand()%getLen();
        }

        string func(short k){
            string inv="";
            for(int i=getLen()-1; i>=0; i--){
                inv+= get(i);
            }
            inv=inv.substr(0,k);
            return inv;
        }

        ostream &print(ostream &os){
            A::print(os);
            os<<"q="<<q<<", func(3)="<<func(3);
            return os;
        }

};



class C : public A{
    
    private:
        char y;

    
    public:
        C(short n, string source, char y) : A(n,source){
            this->y = y;
        }

        string func(short k){
            string inv="";
            string sottos="";
            //filippo
            for(int i=getLen()-1; i>=0; i--){
                inv+= get(i);
            }
            //oppilif
            for (int i=inv.length()-1-k; i<inv.length(); i++){
                sottos+=inv[i];
            }
            return sottos;
        }

        string g(char c){
            string temp="";
            for (int i=0; i<getLen(); i++)
                temp += get(i);
            return y + temp + c;
        }

        ostream &print(ostream &os){
            A::print(os);
            os<<"y="<<y<<", func(3)="<<func(3);
            return os;
        }
};






int main(){

    A*vett[DIM];
    srand(111222333);
    string S;

    short fa = 3;
    for (int i = 0; i < DIM; i++) {
        short n = 10 + rand() % 10;
        S = "";
        for (int k = 0; k < 20; k++)
            S += rand() % ('z' - 'a' + 1) + 'a';
        if (rand() % 2 == 0)
            vett[i] = new B(n, S);
        else
            vett[i] = new C(n, S, (char)(rand() % ('z' - 'a' + 1) + 'a'));
    }

    //Punto 1
    for (int i=0; i<DIM; i++){
        cout<<i<<")"<<typeid(*vett[i]).name();
        cout<<*vett[i]<<endl;
    }

    //Punto 2
    string rest="";
    for (int i=DIM; i>=0; i--){
        if (typeid(*vett[i]) == typeid(C)){
            rest+= (static_cast<C*> (vett[i])->g('X'));
            cout<<endl<<i<<"), ";
            break;
        }
    }

    cout<<"g('X') = "<<rest<<endl;

    //Punto 3
    cout<<*vett[3]<<endl;
    cout<<(*vett[3])(3,8);

}