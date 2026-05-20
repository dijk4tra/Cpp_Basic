#include <iostream>
#include <memory>

class B;

class A {
public:
    std::shared_ptr<B> bptr;

    A() {
        std::cout << "A constructed\n";
    }

    ~A() {
        std::cout << "A destructed\n";
    }
};

class B {
public:
    std::weak_ptr<A> aptr;  // 改成 weak_ptr

    B() {
        std::cout << "B constructed\n";
    }

    ~B() {
        std::cout << "B destructed\n";
    }
};

int main() {
    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();

        a->bptr = b;
        b->aptr = a;

        std::cout << "a.use_count() = " << a.use_count() << '\n';
        std::cout << "b.use_count() = " << b.use_count() << '\n';
    }

    std::cout << "main end\n";

    return 0;
}