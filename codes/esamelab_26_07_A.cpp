#include<iostream>
#include<cstdlib>
#include<string>
#define DIM 50

using namespace std;

class A{
    private:
        char * str;
        short len;

    public:
        A(short m, string source){
            this->len=m;
            this->str=new char[this->len];
            for (int i=0; i<this->len; i++)
                str[i]=source[rand()%source.length()];
        }
        virtual char func(short i)=0;

        short getLen(){
            return this->len;
        }
    protected:
        char get(short i){
            return str[i%len];
        }
};

class B : public A{
    private:
        short p;

    public:
        B(short m, string source) : A(m,source){
            this->p=1;
            for (int i=0; i<getLen();i++){
                switch(get(i)){
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                            {
                             this->p++;
                             break;
                    }
                }
            }
         }
         char func(short i){
            char caratt='X';
            for (int ind=i;ind<getLen() && caratt=='X'; ind++){
                switch (get(ind)){
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                        break;
                    default:
                        caratt=get(ind);
                }
            }
            return caratt;
         }    
};

class C:public A{
    private:
        char x;
    public:
        C(short n, string source, char y): A(n,source){
            this->x=y;
        }

        char func (short i){
            for (int ind=i; ind<getLen(); ind++)
                {
                    if (get(ind) > this->x)
                        return get(ind);    
                }
             return this->x;
        }

       string g(char c){
        string temp="";
        temp+=x;
        for (int i=0; i<getLen(); i++)
            temp+=get(i);
       
       temp+=c;
       return temp;
       }
};



int main(){
   srand(111222333);
A *vett[DIM];

string S = "supercalifragilistichespiralidoso";

for (int i = 0; i < DIM; i++) {
  short n = 3 + rand() % 10;
  if (rand() % 2 == 0)
    vett[i] = new B(n, S);
  else
    vett[i] = new C(n, S, (char)(rand() % ('z' - 'a' + 1) + 'a'));
}
}