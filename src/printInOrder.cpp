#include "head.h"

using namespace std;

class Foo {
public:
    Foo() {
        mtx_1.lock();
        mtx_2.lock();
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }

    mutex mtx_1;
    mutex mtx_2;
};