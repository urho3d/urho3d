//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Math/Random.h"

#include "../DebugNew.h"

namespace Urho3D
{

static unsigned randomSeed = 1;

void SetRandomSeed(unsigned seed)
{
    randomSeed = seed;
}

unsigned GetRandomSeed()
{
    return randomSeed;
}

int Rand()
{
    randomSeed = randomSeed * 214013 + 2531011;
    return (randomSeed >> 16) & 32767;
}

float RandStandardNormal()
{
    float val = 0.0f;
    for (int i = 0; i < 12; i++)
        val += Rand() / 32768.0f;
    val -= 6.0f;

    // Now val is approximatly standard normal distributed
    return val;
}

}
