// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <Urho3D/LibraryInfo.h>
#include <iostream>

using namespace Urho3D;

int main(int argc, char* argv[])
{
    std::cout << GetRevision() << "\n" << GetCompilerDefines();
}
