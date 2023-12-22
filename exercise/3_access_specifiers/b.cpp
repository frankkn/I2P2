#include <iostream>
#include <typeinfo>
using namespace std;

class D{
    public:
        void out_protect() { cout << typeid(*this).name() << "," << _d << "\n"; }
        void out_private() { 
            cout << typeid(*this).name() << "," << __d << "\n"; 
        }
        int d;
    protected:
        int _d;
    private:
        int __d;
};
D object_D;

// protected 繼承D
class B: protected D{
    public:
        void out_protect_B() { cout << typeid(*this).name() << "," << _d << "\n"; }
};
B object_B;

int main(){
    // cout << object_B.d << "\n"; // X 由於類別 B 使用了 protected 繼承 D，object_B.d 變成了 protected 成員，因此在 main 函數中無法直接訪問。
    // cout << object_B._d << "\n"; // X
    // cout << object_B.__d << "\n"; // X
    // object_B.out_protect(); // X, out_protect() 變成 protected
    object_B.out_protect_B(); // O
    // object_B.out_private(); // X 由於類別 B 使用了 protected 繼承 D，out_private() 變成了 protected 成員，因此在 main 函數中無法直接訪問。
    return 0;
}