
#include <iostream>
#include <experimental/filesystem> // you must do this, in gcc 8.30

template<typename Ty>
struct Test
{
    Ty value_;
};

template<typename Ty>
struct Test1
{
    Test1(const Ty& value):value_{value}{}
    Ty value_;
};

template<typename Ty1, typename Ty2>
struct  Test2
{
    Test2(const Ty1& value1):value1_{value1}{}
    Test2(const Ty1& value1, const Ty2& value2)
        :value1_{value1},
         value2_{value2}{}

    Ty1 value1_;
    Ty2 value2_;
};

template<typename Ty1, typename Ty2>
struct Test3
{
    explicit Test3(Ty1&& value1, Ty2&& value2) //C1
            :value1_{std::forward<Ty1>(value1)},
             value2_{std::forward<Ty2>(value2)}
             {
                 std::cout << "Test3::C1" << std::endl;
             }

    Test3(const Ty1& value1, const Ty2& value2) //C2
            :value1_{value1},
             value2_{value2_}
             {
                 std::cout << "Test3::C2" << std::endl;
             }


    Ty1 value1_;
    Ty2 value2_;
};


template<class T> struct Test4 {
    explicit Test4(const T&, ...) noexcept{ std::cout << "Test4::C1" << std::endl; } // Test4::C1
    Test4(T&&, ...){ std::cout << "Test4::C2" << std::endl; }                        // Test4::C2
};
template<class T> Test4(const T&, const T&) -> Test4<T&>; // Test4::CC1
template<class T> explicit Test4(T&&, T&&)  -> Test4<T>;  // Test4::CC2


int main()
{
    // no type constraits.
    // 1:
    // Test t{ 1 }; //error! can not deduce the type from c-style initialization.
    // Test t_1(1); //error! the same as above.
    // Test t_2 = {1}; //error! the same as above.

    // 2:
    Test1 t1{1}; //ok!
    Test1 t1_1 = {1}; //ok!
    Test1 t1_2(1); //ok!

    // 3:
    // Test2 t2{1}; //error! we can not get the type of Ty2. you can Test<int, int> t2{1};
    Test2<int, int> t2_1{2}; //ok!
    Test2 t2_2{20, 20}; //ok!
    Test2 t2_3{20, 30.5}; //ok!
    Test2 t2_4 = {20, 30.5}; //ok! {20, 30.5} is equal to Test2{20, 30.5}; 
                             //because this constructor is imexplicit.


    // 4:
    int number1{1};
    int number2{2};
    Test3 t3{0, 3.5}; //ok! Test3::C1
    Test3 t3_1{number1, number2}; //ok! Test3::C2
    Test3 t3_2{number1, 3}; //ok! Test3::C2
    Test3 t3_3{3, number1}; //ok! Test3::C2
    Test3 t3_4 = {number2, 3}; //ok! Test3::C2
    // Test3 t3_5 = {0, 3.5}; //error! Test3::C1, C1 is more specilized, C1 is explicit,so can not initilize from a brace list.
    // Test3 t3_6 = {0, 1}; //error! the same as above.


    // 5:
    // Test4 t4{0, 0}; //ok! Test4::C2
    // Test4 t4_1{0, 3.5};//ok! Test4::C2
    // Test4 t4_2{0, number1};//error! will be deduced as Test4<int> and be contrained by Test4::CC1(Test<int&>), so it is wrong.
    // Test4 t4_3{number1, number2};//error! the same as above.
    // Test4 t4_5={0, 3.5}; //ok! maybe a complier bug.
    // Test4 t4_6={1, 1}; //error! it is contrained by Test4::CC2 but Test4::CC2 is explicit.
    Test4 t4_7={number1, number2};//error! be deduced by Test4::CC1(Test4<int>), but the constraint is Test4<int&>



    return 0;
}