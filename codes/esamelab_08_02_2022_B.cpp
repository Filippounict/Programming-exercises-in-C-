#include<iostream>
#include<cstdlib>
#include<cmath>
#include<typeinfo>
#define DIM 50

using namespace std;

class A{

    private:
        char *str;
        short len;


    public: 
        A(short w, char c1, char c2) : len(w){
            str = new char[w];
            for (int i=0; i<w; i++)
                str[i] = (char)(rand()%(c2-c1+1)+c1);
        }

        virtual short f(short k) = 0;

        virtual ostream &print(ostream &os){
            os<<"str=";
            for (int i=0; i<len; i++)   
                os<<str[i];
            os<<",";
            return os;
        }




    
    protected:
        string extract(short k){
            string temp = "";
            for (int i=0; i<len; i++)
                temp += str[i];

            if (k >= len)
                return temp;
            else    
                return temp.substr(temp.length()-k,k); 
        }
        //filippo
        //k=2

};

ostream &operator <<(ostream &os, A &a){
    return a.print(os);
}




class B : public A {

    private:  
        char z;

    
    public:
        B(short m, char c1, char c2) : A(m,c1,c2) {
            z = rand()%(extract(m/2+1).length());
        }

        short f(short k){
            short conta=0;
            string temp = extract(k);
            for (int i=0; i<temp.length(); i++){
                if (temp[i] <= z)
                    conta++;
            }
            return conta;
        }

        ostream &print(ostream &os){
            A:: print(os);
            os<<"z="<<z;
            return os;
        }

};



template <typename T>
class C : public A {

    private:
        T ss;
    

    public:
        C(short w, char c1, char c2) : A(w,c1,c2) {
            if(typeid(T) == typeid(string))
                ss = extract((w/2)+1);
            else    
                ss = w;
        }

        short f(short k){
            string temp = extract(k);
            for(int i=0; i<temp.length(); i++){
                if (temp[i]>='A' && temp[i]<='Z')
                    return true;
            }
            return 0;
        }

        T foo(short x){
            return pow(ss, x);
        }

        ostream &print(ostream &os){
            A:: print(os);
            os<<"ss="<<ss;
            return os;
        }

};




int main(){
    A* vec[DIM];
    srand(12345678);

    for (unsigned int i = 0; i < DIM; i++){
        int r = rand();
        if (r % 3 == 0) // B
            vec[i] = new B(rand() % 10 + 5, '0', '9');
        else if (r % 3 == 1)
            vec[i] = new C<string>(rand() % 10 + 5, 'a', 'z');
        else
            vec[i] = new C<short>(rand() % 20 + 10, 'A', 'Z');
    }

    //Punto 1
    cout<<endl<<"Punto 1:"<<endl;
    for (int i=0; i<DIM; i++){

    }
}