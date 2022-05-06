// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <Urho3D/Core/ProcessUtils.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <Urho3D/DebugNew.h>

#include <iostream>

using namespace Urho3D;

void Test_Container_Str();

void Run()
{
    Test_Container_Str();
}

int main(int argc, char* argv[])
{
    Run();

    std::cout << "All tests success" << std::endl;

    return 0;
}
