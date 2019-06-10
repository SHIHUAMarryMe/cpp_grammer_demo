#include <iostream>

int main()
{
    char str_array[]{"shihuamarryme"};
    char* str_pointer{ "shihuamarryme" };

    str_array[0] = 'x';
    // str_pointer[0] = 'x'; //Segmentation fault, you can not modify an const string.

    std::cout << str_array << "  " << str_pointer << std::endl;

    return 0;
}