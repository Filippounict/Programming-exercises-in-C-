#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <cmath>
#define DIM 50

using namespace std;

class A
{
private:
    int *vec;
    short len;

public:
    A(short m, int a, int b)
    {
        this->len = m;
        vec = new int[m];
        for (int i = 0; i < m; i++)
            vec[i] = a + rand() % (b - a + 1);
    }

    virtual double foo(short a) = 0;

    short getLen()
    {
        return len;
    }

    virtual ostream &print(ostream &os)
    {
        os << "vec = [";
        for (int i = 0; i < len; i++)
            os << vec[i] << " ";

        os << "], ";
        return os;
    }

    int operator() (int i1, int i2){
        double sum=0;
        for(int i=i1; i<=i2 && i<len; i++)
            sum+=vec[i];
        
        return sum;
    }
protected:
    int get(short i)
    {
        return vec[i % len];
    }
};

ostream &operator<<(ostream &os, A &a)
{
    return a.print(os);
}

class B : public A
{
private:
    int p;

public:
    B(short m, int x, int y) : A(m, x, y)
    {
        p = get(rand() % getLen());
    }

    double foo(short a)
    {
        return prod(a) / (double)(p);
    }

    ostream &print(ostream &os)
    {
        A::print(os);
        os << " p= " << p << ", "
           << "foo(3)= " << foo(3) << endl;

        return os;
    }

protected:
    int prod(short s)
    {
        int molt = 1;
        for (int i = s; i < getLen(); i++)
            molt *= get(i);
        return molt;
    }
};

template <typename T>
class C : public A
{
private:
    T x;

public:
    C(short n, int a, int b) : A(n, a, b)
    {
        if (typeid(T) == typeid(short))
            x = n;
        else
            x = log(1 + pow(sin(n), 2));
    }

    double foo(short r)
    {
        return g(r);
    }

    T g(T k)
    {
        return 2 * x * (k + 1);
    }

    ostream &print(ostream &os)
    {
        A::print(os);
        os << " x= " << x << ", "
           << "foo(3)= " << foo(3) << endl;
           
        return os;
    }
};

int main()
{
    srand(111222333);

    A *vett[DIM];

    for (int i = 0; i < DIM; i++){
        short n = 1 + rand() % 10;
        switch (rand() % 3) {
        case 0:
            vett[i] = new B(n, rand() % 5 + 1, rand() % 10 + 5);
            break;
        case 1:
            vett[i] = new C<double>(n, rand() % 5 + 1, rand() % 10 + 5);
            break;
        case 2:
            vett[i] = new C<short>(n, rand() % 5 + 1, rand() % 10 + 5);
        }
    }

    //*****Punto 1
   for (int i=0; i < DIM; i++){
        cout<<i<<") "<<typeid(*vett[i]).name();
     /*   cout<<i<<") ";
        if (typeid(*vett[i]) == typeid(B))
            cout<<"B, ";
        else if (typeid(*vett[i]) == typeid(C<double>))
                cout<<"C<double>, ";
        else if (typeid(*vett[i]) == typeid(C<short>))
                cout<<"C<int>, ";
*/
        cout<<*vett[i]<<" foo(5)= "<<vett[i]->foo(5);
        cout<<endl;
    }


    //****Punto 2
    cout<<endl;
    double max = vett[0]->foo(3);
    for(int i=1; i<DIM; i++){
        if ((vett[i]->foo(3)) > max)
            max = vett[i]->foo(3);
    }
/*****STATIC_CAST
    double media=-1;
    double sum=0;
    int count=0;
    for(int i=0; i<DIM; i++){
        if(typeid(*vett[i]) == typeid(C<double>)){
            sum += (static_cast <C<double>*> (vett[i])->g(5));
            count++;
        }
    }

    media= sum/(count*1.0);
    cout<<"Max = "<<max<< " , Media = "<< media<<endl;
*/

//DYNAMIC_CAST
    double media=-1;
    double sum=0;
    int count=0;
    C<double>* ptr;
    for(int i=0; i<DIM; i++){
        ptr = dynamic_cast<C<double>*>(vett[i]);
        if (ptr){
            sum += ptr->g(5);
            count++;
        }
    }
    media= sum/(count*1.0);
    cout<<"Max = "<<max<< " , Media = "<< media<<endl;
    
//*****Punto 3
    cout<<endl<<"vett[10] = "<<*vett[10]<<endl;
    cout<<"Somma da indice 4 a 8 = "<<(*vett[10])(4,8)<<endl;

    return 0;
}