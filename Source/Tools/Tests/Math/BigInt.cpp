// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../ForceAssert.h"

#include <Urho3D/Container/Str.h>
#include <Urho3D/Math/BigInt.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

void Test_Math_BigInt()
{
    // Constructors
    assert(BigInt().ToString() == "0");
    assert(BigInt(0x7FFFFFFF).ToString() == "2147483647"); // BigInt(i32)
    assert(BigInt(0x80000000).ToString() == "2147483648"); // BigInt(u32)
    assert(BigInt(0xFFFFFFFF).ToString() == "4294967295"); // BigInt(u32)
    assert(BigInt(0x7FFFFFFFFFFFFFFF).ToString() == "9223372036854775807"); // BigInt(i64)
    assert(BigInt(0x8000000000000000).ToString() == "9223372036854775808"); // BigInt(u64)
    assert(BigInt(0xFFFFFFFFFFFFFFFF).ToString() == "18446744073709551615"); // BigInt(u64)
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
