// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include <iostream>

void Test_Container_Str();
void Test_Math_BigInt();

void Run()
{
    Test_Container_Str();
    Test_Math_BigInt();
}

int main(int argc, char* argv[])
{
    Run();

    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::cout << "Все тесты пройдены успешно" << std::endl;

    return 0;
}
