#include "serializer.hpp"
#include <cassert>
#include <sstream>
template<class X=uint64_t, class Y=bool, class Z=uint64_t>
struct Data{

    X a;
    Y b;
    Z c;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer){
        return deserializer(a, b, c);
    }
};

template<class X=uint64_t, class Y=bool, class Z=uint64_t, class U=bool, class V=uint64_t>
struct Data2{

    X a;
    Y b;
    Z c;
    U d;
    V i;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c, d, i);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer){
        return deserializer(a, b, c, d, i);
    }
};

void DefaultTest(){

    Data<> x { 1, true, 2 }, y {0, false, 0};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_ser = serializer.save(x);
    
    Deserializer deserializer(stream);
    const Error err_des = deserializer.load(y);

    assert(err_ser == Error::NoError);
    assert(err_des == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    std::cout << "Test 1.0 Passed" << std::endl;
}

void BadTypeDesseriakizerTest2_1(){
    
    Data<> x { 1, true, 2};
    Data<std::string> y {"desserializer", true, 20};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_ser = serializer.save(x);

    Deserializer deserializer(stream);
    const Error err_des = deserializer.load(y);

    assert(err_ser == Error::NoError);
    assert(err_des == Error::CorruptedArchive);
    assert(x.b == y.b);
    assert(x.c != y.c);
    std::cout << "Test 2.1 Passed" << std::endl;
}

void BadTypeDesseriakizerTest2_2(){

    Data<> x { 100, true, 2};
    Data<uint64_t, std::string> y {0, "desserializer", 20};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_ser = serializer.save(x);

    Deserializer deserializer(stream);
    const Error err_des = deserializer.load(y);

    assert(err_ser == Error::NoError);
    assert(err_des == Error::CorruptedArchive);
    assert(x.a == y.a);
    assert(x.c != y.c);
    std::cout << "Test 2.2 Passed" << std::endl;
}

void BadTypeDesseriakizerTest2_3(){

    Data<> x { 100, true, 2};
    Data<int> y {2, false, 2};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_ser = serializer.save(x);

    Deserializer deserializer(stream);
    const Error err_des = deserializer.load(y);

    assert(err_ser == Error::NoError);
    assert(err_des == Error::CorruptedArchive);
    assert(x.b != y.b);
    assert(x.c == y.c);
    std::cout << "Test 2.3 Passed" << std::endl;
}

void BadTypeDesseriakizerTest2_4(){

    Data<> x { 100, true, 2};
    Data<uint64_t, bool, uint32_t> y {2, false, 200};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_ser = serializer.save(x);

    Deserializer deserializer(stream);
    const Error err_des = deserializer.load(y);

    assert(err_ser == Error::NoError);
    assert(err_des == Error::CorruptedArchive);
    assert(x.a == y.a);
    assert(x.b == y.b);
    std::cout << "Test 2.4 Passed" << std::endl;
}

void BadTypeSerrializerTest3_1(){

    Data<std::string> x {"serrializer", true, 20};
    Data<> y { 1, true, 2};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_ser = serializer.save(x);

    Deserializer deserializer(stream);
    const Error err_des = deserializer.load(y);

    assert(err_ser == Error::CorruptedArchive);
    assert(err_des == Error::CorruptedArchive);
    assert(y.a == 1);
    assert(y.b == true);
    assert(y.c == 2);
    std::cout << "Test 3.1 Passed" << std::endl;
}

void BadTypeSerrializerTest3_2(){

    Data<std::string, uint64_t, bool> x {"serrializer", 20, false};
    Data<> y { 1, true, 2};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_ser = serializer.save(x);

    Deserializer deserializer(stream);
    const Error err_des = deserializer.load(y);

    assert(err_ser == Error::CorruptedArchive);
    assert(err_des == Error::CorruptedArchive);
    assert(y.a == 1);
    assert(y.b == true);
    assert(y.c == 2);
    std::cout << "Test 3.2 Passed" << std::endl;
}

void DifferentDimentionsTest4_1(){

    Data2<> x {2, false, 10, true, 100};
    Data<> y { 1, true, 2};

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_ser = serializer.save(x);

    Deserializer deserializer(stream);
    const Error err_des = deserializer.load(y);

    assert(err_ser == Error::NoError);
    assert(err_des == Error::CorruptedArchive);
    assert(y.a == 2);
    assert(y.b == false);
    assert(y.c == 10);
    std::cout << "Test 4.1 Passed" << std::endl;
}

void DifferentDimentionsTest4_2(){

    Data<> x { 1, true, 2}; 
    Data2<> y {2, false, 10, true, 100};

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_ser = serializer.save(x);

    Deserializer deserializer(stream);
    const Error err_des = deserializer.load(y);

    assert(err_ser == Error::NoError);
    assert(err_des == Error::CorruptedArchive);
    assert(y.a == 1);
    assert(y.b == true);
    assert(y.c == 2);
    std::cout << "Test 4.2 Passed" << std::endl;
}

void MoreDimsTest(){

    Data2<> x { 1, true, 10, true, 500}; 
    Data2<> y {20, false, 10, true, 100};

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_ser = serializer.save(x);

    Deserializer deserializer(stream);
    const Error err_des = deserializer.load(y);

    assert(err_ser == Error::NoError);
    assert(err_des == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    assert(x.d == y.d);
    assert(x.i == y.i);
    std::cout << "Test 5.0 Passed" << std::endl;
}

void NoSerializer(){
    Data<> y {20, false, 10};

    std::stringstream stream;

    Deserializer deserializer(stream);
    const Error err_des = deserializer.load(y);

    assert(err_des == Error::CorruptedArchive);
    std::cout << "Test 6.0 Passed" << std::endl;
    assert(y.a == 20);
    assert(y.b == false);
    assert(y.c == 10);
}

int main(){

    DefaultTest();

    BadTypeDesseriakizerTest2_1();
    BadTypeDesseriakizerTest2_2();
    BadTypeDesseriakizerTest2_3();
    BadTypeDesseriakizerTest2_4();

    BadTypeSerrializerTest3_1();
    BadTypeSerrializerTest3_2();

    DifferentDimentionsTest4_1();
    DifferentDimentionsTest4_2();

    MoreDimsTest();

    NoSerializer();

}