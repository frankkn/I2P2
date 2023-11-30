#include <iostream>
using namespace std;

class D{
    public:
        void out_protect() { cout << _d << "\n"; }
        void out_private() { cout << __d << "\n"; }
        int d;
    protected:
        int _d;
    private:
        int __d;
};
D object_D;

// private 繼承D
class B: private D{
    public:
        void out_protect_B() { cout << _d << "\n"; }
};
B object_B;

int main(){
    // cout << object_B.d << "\n"; // X
    // cout << object_B._d << "\n"; // X
    // cout << object_B.__d << "\n"; // X
    // object_B.out_protect(); // X, out_protect() 變成 protected
    object_B.out_protect_B(); // O
    // object_B.out_private(); // X
    return 0;
}