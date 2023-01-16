// Copyright (c) 2008-2023 the Urho3D project
// Copyright (c) 2022-2023 the Dviglo project
// License: MIT

#include <iostream>
#include <clocale>

void Test_Container_Str();
void Test_Math_BigInt();
void test_third_party_sdl();

void Run()
{
    Test_Container_Str();
    Test_Math_BigInt();
    test_third_party_sdl();
}

int main(int argc, char* argv[])
{
    Run();

    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::cout << "Все тесты пройдены успешно" << std::endl;

    return 0;
}
