#include "Anchor.h"
#include <iostream>

int main()
{

    Anchor a(" ", "b");
    std::cin >> a;
    std::cout << a;
    std::cout << a.file();

    return 0;
}
