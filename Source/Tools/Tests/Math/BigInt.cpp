// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../ForceAssert.h"

#include <Urho3D/Container/Str.h>
#include <Urho3D/Math/BigInt.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

void Test_Math_BigInt()
{
    // ToString()
    assert(BigInt().ToString() == "0");
    assert(BigInt("0").ToString() == "0");
    assert(BigInt("-0").ToString() == "0");
    assert(BigInt("3").ToString() == "3");
    assert(BigInt("-7").ToString() == "-7");
    assert(BigInt("123456789").ToString() == "123456789");
    assert(BigInt("-123456789").ToString() == "-123456789");
    assert(BigInt("123000789").ToString() == "123000789");
    assert(BigInt("-1230000").ToString() == "-1230000");
    assert(BigInt("0001230000").ToString() == "1230000");
    assert(BigInt("-0001230000").ToString() == "-1230000");

    // Comparison
    assert(BigInt("0") == BigInt("-0"));
    assert(BigInt("10") < BigInt("100"));
    assert(BigInt("10") > BigInt("-100"));

    // Sum of values with same sign
    assert((BigInt("1") + BigInt("2")).ToString() == "3");
    assert((BigInt("1000") + BigInt("200")).ToString() == "1200");
    assert((BigInt("-1000") + BigInt("-234")).ToString() == "-1234");
    assert((BigInt("-1000") - BigInt("234")).ToString() == "-1234");
    assert((BigInt("-1000") - BigInt("0")).ToString() == "-1000");

    assert((BigInt("1000") - BigInt("1000")).ToString() == "0");
    assert((BigInt("000") - BigInt("000")).ToString() == "0");
    assert((BigInt("000") + BigInt("000")).ToString() == "0");

    // Sum of values with opposite sign
    assert((BigInt("1000") - BigInt("234")).ToString() == "766");
    assert((BigInt("234") - BigInt("1000")).ToString() == "-766");
    assert((BigInt("1000") - BigInt("0")).ToString() == "1000");
    assert((BigInt("0") - BigInt("034005")).ToString() == "-34005");
}
