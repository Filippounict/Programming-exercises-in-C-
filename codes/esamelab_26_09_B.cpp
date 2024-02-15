#include<iostream>
#include<cstdlib>
#include<cstring>
#define DIM 50

using namespace std;

class A{

    private:
        char *s;
        short len;

    
    public:
        A(short m): len(m) {
            s=new char[m];
            for (int i=0; i<m; i++)
                s[i]=(char) (rand()%('z'-'a'+1)+'a');
        }

        virtual double elab(short a) = 0;

        short getLen(){
            return len;
        }

        virtual ostream &print(ostream &os){
            os<<"s= ";
            for (int i=0; i<len; i++)
                os<<s[i];
            os<<", ";
            return os;
        }

    

    protected:
        char get(short i){
            return s[i%len];
        }

};

ostream &operator<<(ostream &os, A&a){
    return a.print(os);
}



class B : public A {

    private:
        int p;


    public:
        B(short m, int x) : A(m) {
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
                        case 'u':{
                                voc++;
                                break;
                        }
                        default:
                            cons++;
                    }
            }
          return voc/(cons+1*1.0);
        }

        ostream &print(ostream &os){
            A:: print(os);
            os<<"p="<<p<<", elab(3)="<<elab(3);
            return os;
        }

        B operator ++(int){
            B aux = *this;
            ++p;
            return aux;
        }

    
    protected:
        bool test(){
            for (int i=0; i<4; i++){
                 switch(get(i)){
                     case 'a':
                     case 'e':
                     case 'i':
                     case 'o':
                     case 'u':
                         return true;
                  }  
            }
          return false;
        }

};




class C : public A {

    private:
        char x;

    
    public:
        C(short n, char c) : A(n){
            x = c;
        }

        double elab(short r){
            int count=0;
            for (int i=r%getLen(); i<getLen(); i++){
                if(get(i)>= x)
                    count++;
            }
            return count/(getLen()*1.0);
        }

        string g(char c){
            string temp="";
            return temp+x+c;
        }

        ostream &print(ostream &os){
            A:: print(os);
            os<<"x="<<x<<", elab(3)="<<elab(3);
            return os;
        }
};





int main(){

    A *vett[DIM];
       srand(111222333);

      for(int i=0; i<DIM; i++) {
	short n=1+rand()%10;
	if(rand()%2==0)
	  vett[i]= new B(n, rand()%10 + 1);
	else
	  vett[i]= new C (n, (char) (rand()%((int) 'z' - (int) 'a' + 1) + (int) 'a'));
	}


    //Punto 1
    cout<<"Punto 1:"<<endl;
    for (int i=0; i<DIM; i++){
        cout<<i<<")"<<typeid(*vett[i]).name()<<", ";
        cout<<*vett[i]<<endl;
    }

    //Punto 2
    double sum=0;
    string concat="";
    for (int i=0; i<DIM; i++){
        sum += vett[i]->elab(3);

        if (typeid(*vett[i])==typeid(C)){
            concat += (static_cast<C*>(vett[i])->g('h'));
        }
    }

    cout<<endl<<"Punto 2:"<<endl;
    cout<<"Avg="<<sum/(DIM*1.0)<<","<<endl;
    cout<<"Concat="<<concat<<endl;

    //Punto 3
    cout<<endl<<"Punto 3:"<<endl;
    /*
     B b(3,8);
    cout<<"0): "<<typeid(b).name()<<", "<<(b)<<endl;
    (b)++;
    cout<<"0): "<<typeid(b).name()<<", "<<(b)<<endl;
    */
    cout<<"0): "<<typeid(*vett[0]).name()<<", "<<(*vett[0])<<endl;
    (vett[0])++;
    cout<<"0): "<<typeid(*vett[0]).name()<<", "<<(*vett[0])<<endl;
    
   

}