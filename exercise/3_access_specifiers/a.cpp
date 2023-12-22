#include <iostream>
#include <typeinfo>
using namespace std;

class D{
    public:
        void out_protect() { cout << typeid(*this).name() << "," << _d << "\n"; }
        void out_private() { cout << typeid(*this).name() << "," << __d << "\n"; }
        int d;
    protected:
        int _d;
    private:
        int __d;
};
D object_D;

class B: public D{
    public:
        void out_protect_B() { cout << typeid(*this).name() << "," << _d << "\n"; }
};
B object_B;

int main(){
    cout << object_D.d << "\n"; // O
    // cout << object_D._d; // X
    // cout << object_D.__d; // X
    object_D.out_protect(); // O
    object_D.out_private(); // O
    cout << object_B.d << "\n"; // O
    // cout << object_B._d; // X
    // cout << object_B.__d; // X
    object_B.out_protect(); // O
    object_B.out_protect_B(); // O
    object_B.out_private(); // O
    return 0;
}