#include "format.hpp" 

void Test1(){
    auto text= format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
    std::cout << "Test1 Passed" << std::endl;
}

void Test2(){
    auto text = format("{0}*{1} = {0}", 0, "one");
    assert(text == "0*one = 0");
    std::cout << "Test2 Passed" << std::endl;
}

void Test3(){
    auto text = format("{0}", 100500);
    assert(text == "100500");
    std::cout << "Test3 Passed" << std::endl;
}

void Test4(){
    auto text = format("technosphere");
    assert(text == "technosphere");
    std::cout << "Test4 Passed" << std::endl;
}

void Test5(){
    auto text = format("И {1} меня, и {1} меня В звенящую снежную даль {0} {3} коня, эх, {2} {3} коня Декабрь, {4}февраль{5}", "Три","уносят", "3", "белых", "январь и ", "!");
    assert(text == "И уносят меня, и уносят меня В звенящую снежную даль Три белых коня, эх, 3 белых коня Декабрь, январь и февраль!");
    std::cout << "Test5 Passed" << std::endl;
}

void Test6(){
    try{
        auto text = format("{0} + {1}} = {2}", 10, 5, 15);
    } catch (FormatError& error){
        std::string a = error.what();
        assert(a == "invalid format");
    }
    std::cout << "Test6 Passed" << std::endl;
}

void Test7(){
    try{
        auto text = format("{0} + {{1} = {2}", 10, 5, 15);
    } catch(FormatError& error){
        std::string a = error.what();
        assert(a == "invalid format");
    }
    std::cout << "Test7 Passed" << std::endl;
}

void Test8(){
    try{
        auto text = format("{0} + {1} = {2}", 10, 5, 15, 16);
    } catch(FormatError& error){
        std::string a = error.what();
        assert(a == "invalid format");
    }
    std::cout << "Test8 Passed" << std::endl;
}

void Test9(){
    try{
        auto text = format("{t} + {1} = {2}", 10, 5, 15);
    } catch (FormatError& error){
        std::string a = error.what();
        assert(a == "invalid format");
    }
    std::cout << "Test9 Passed" << std::endl;
}

void Test10(){
    try{
        auto text = format("0 + 1 = 2{");
    } catch (FormatError& error){
        std::string a = error.what();
        assert(a == "invalid format");
    }
    std::cout << "Test10 Passed" << std::endl;
}

void Test11(){
    try{
        auto text = format("}0 + 1 = 2");
    } catch (FormatError& error){
        std::string a = error.what();
        assert(a == "invalid format");
    }
    std::cout << "Test11 Passed" << std::endl;
}

void Test12(){
    try{
        auto text = format("{0} + {1} = {}", 5, 6, 11);
    } catch (FormatError& error){
        std::string a = error.what();
        assert(a == "invalid format");
    }
    std::cout << "Test12 Passed" << std::endl;
}

int main(){
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    Test10();
    Test11();
    Test12();
}
