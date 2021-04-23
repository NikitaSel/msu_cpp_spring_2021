#include "BigInt.hpp"

int main()
{
    BigInt myInt1(std::string("123456789123456789123456789"));
    BigInt myInt2(std::string("123456789"));
    std::cout << myInt1 << std::endl;
    myInt2 = myInt1; // оператор копирования
    std::cout << "оператор копирования " << myInt2 << std::endl;
    BigInt myInt3 = myInt2; // конструктор копирования 
    std::cout << "конструктор копирования " << myInt2 << std::endl;

    std::cout << "унарный плюс " << +myInt2 << std::endl;
    std::cout << "унарный минус " << -myInt2 << std::endl;
    std::cout << "после него " << myInt2 << std::endl;

    std::cout << "(+) + (+)  " << myInt1 + myInt2 << std::endl;
    BigInt myInt4(std::string("888888888"));
    BigInt myInt5(std::string("222222222"));
    std::cout << "check overflow " << myInt4 + myInt5 << std::endl;

    std::cout << " == (-)" << (myInt4 == myInt5 ? "nope" : "ok") << std::endl;
    std::cout << " == (+)" << (myInt4 == myInt4 ? "ok" : "nope") << std::endl;
    std::cout << " == (-)" << (myInt4 == -myInt4 ? "nope" : "ok") << std::endl;
    std::cout << " == (-)" << (-myInt4 == myInt4 ? "nope" : "ok") << std::endl;
 
    std::cout << " != (-)" << (myInt4 != myInt4 ? "nope" : "ok") << std::endl;
    std::cout << " != (+)" << (myInt4 != myInt5 ? "ok" : "nope") << std::endl;
    std::cout << " >  (+)" << (myInt4 > myInt5 ? "ok" : "nope") << std::endl;
    std::cout << " >  (-)" << (myInt5 > myInt4 ? "nope" : "ok") << std::endl;
    std::cout << " >  (-)" << (myInt4 > myInt4 ? "nope" : "ok") << std::endl;
    
    std::cout << " <  (+)" << (myInt4 > myInt5 ? "ok" : "nope") << std::endl;
    std::cout << " <  (-)" << (myInt5 > myInt4 ? "nope" : "ok") << std::endl;
    std::cout << " <  (-)" << (myInt4 < myInt4 ? "nope" : "ok") << std::endl;

    std::cout << " - " << myInt4 - myInt5 << std::endl;
    std::cout << " - " << myInt5 - myInt4 << std::endl;
    BigInt myInt6(std::string("112"));
    BigInt myInt7(std::string("15"));
    std::cout << " - " << myInt6 - myInt7 << std::endl;
    std::cout << " * " << myInt6 * myInt7 << std::endl;
    std::cout << " * " << myInt6 * -myInt7 * myInt6 * myInt7 << std::endl;
    std::cout << " - " << myInt1 - int32_t(11111111) << std::endl;
}