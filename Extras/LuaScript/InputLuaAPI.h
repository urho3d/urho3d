//
// Copyright (c) 2008-2013 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "Context.h"
#include "Input.h"
#include "LuaScript.h"

namespace Urho3D
{
    static const int KEY_A = 'A';
    static const int KEY_B = 'B';
    static const int KEY_C = 'C';
    static const int KEY_D = 'D';
    static const int KEY_E = 'E';
    static const int KEY_F = 'F';
    static const int KEY_G = 'G';
    static const int KEY_H = 'H';
    static const int KEY_I = 'I';
    static const int KEY_J = 'J';
    static const int KEY_K = 'K';
    static const int KEY_L = 'L';
    static const int KEY_M = 'M';
    static const int KEY_N = 'N';
    static const int KEY_O = 'O';
    static const int KEY_P = 'P';
    static const int KEY_Q = 'Q';
    static const int KEY_R = 'R';
    static const int KEY_S = 'S';
    static const int KEY_T = 'T';
    static const int KEY_U = 'U';
    static const int KEY_V = 'V';
    static const int KEY_W = 'W';
    static const int KEY_X = 'X';
    static const int KEY_Y = 'Y';
    static const int KEY_Z = 'Z';

    Input* GetInput()
    {
        return GetLuaScriptContext()->GetSubsystem<Input>();
    }
}