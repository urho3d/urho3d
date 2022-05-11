// Copyright (c) 2008-2022 the Urho3D project
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

    std::cout << "All tests success" << std::endl;

    return 0;
}
