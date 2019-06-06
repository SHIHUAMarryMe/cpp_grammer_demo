#include <iostream>
#include <bitset>


int func(int x)
{ 

int countx = 0; 

while(x) 

{ 
countx ++; 

std::cout << std::bitset<32>{x}.to_string() << " " << x << std::endl;
std::cout << std::bitset<32>{x-1}.to_string() << " " << x-1 << std::endl;
x = x&(x-1); 
std::bitset<32> set{x};
std::cout << set.to_string() << " " << x << std::endl;
std::cout << std::endl;


} 

return countx; 
} 


int main()
{
    int number{9999};
    func(number);
    return 0;
}