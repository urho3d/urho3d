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
    assert(BigInt(0).ToString() == "0");
    assert(BigInt((i32)0x7FFFFFFF).ToString() == "2147483647");
    assert(BigInt((u32)0x80000000).ToString() == "2147483648");
    assert(BigInt((u32)0xFFFFFFFF).ToString() == "4294967295");
    assert(BigInt((i64)0x7FFFFFFFFFFFFFFF).ToString() == "9223372036854775807"); // (i64) need for macOS
    assert(BigInt((u64)0x8000000000000000).ToString() == "9223372036854775808"); // (u64) need for macOS
    assert(BigInt((u64)0xFFFFFFFFFFFFFFFF).ToString() == "18446744073709551615"); // (u64) need for macOS
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
    
    {
        BigInt bi{"-99999999999999999999999999999999999999999999999999999999999999999999"
                  "999999999999999999999999999999999999999999999999999999999999999999999"
                  "999999999999999999999999999999999999999999999999999999999999999999999"};
        
        assert(bi.ToString() ==
               "-99999999999999999999999999999999999999999999999999999999999999999999"
               "999999999999999999999999999999999999999999999999999999999999999999999"
               "999999999999999999999999999999999999999999999999999999999999999999999");
    }

    // Comparison
    assert(BigInt("0") == BigInt("-0"));
    assert(BigInt("10") < BigInt("100"));
    assert(BigInt("10") > BigInt("-100"));
    assert(BigInt("-10") > BigInt("-100"));

    // Sum of values with same sign
    assert((BigInt("0") + BigInt("0")).ToString() == "0");
    assert((BigInt("000") + BigInt("000")).ToString() == "0");
    assert((BigInt("1") + BigInt("2")).ToString() == "3");
    assert((BigInt("1000") + BigInt("200")).ToString() == "1200");
    assert((BigInt("-1000") + BigInt("-234")).ToString() == "-1234");
    assert((BigInt("-1000") - BigInt("234")).ToString() == "-1234");
    assert((BigInt("-1000") - BigInt("0")).ToString() == "-1000");
    assert((BigInt("9999999999999999999999") + BigInt("9999999999999999999999")).ToString() == "19999999999999999999998");
    assert((BigInt("9999999999999999999999") + BigInt("1")).ToString() == "10000000000000000000000");

    // Sum of values with opposite sign
    assert((BigInt("000") - BigInt("000")).ToString() == "0");
    assert((BigInt("1000") - BigInt("1000")).ToString() == "0");
    assert((BigInt("1000") - BigInt("234")).ToString() == "766");
    assert((BigInt("234") - BigInt("1000")).ToString() == "-766");
    assert((BigInt("1000") - BigInt("0")).ToString() == "1000");
    assert((BigInt("0") - BigInt("034005")).ToString() == "-34005");
    assert((BigInt("10000000000000000000000") - BigInt("1")).ToString() == "9999999999999999999999");
    assert((BigInt("-10000000000000000000000") + BigInt("1")).ToString() == "-9999999999999999999999");

    // Multiply
    assert((BigInt("0") * BigInt("0")).ToString() == "0");
    assert((BigInt("1") * BigInt("1")).ToString() == "1");
    assert((BigInt("1") * BigInt("9999999999999999999999")).ToString() == "9999999999999999999999");
    assert((BigInt("0") * BigInt("9999999999999999999999")).ToString() == "0");
    assert((BigInt("10") * BigInt("2")).ToString() == "20");
    assert((BigInt("-99999") * BigInt("99999")).ToString() == "-9999800001");
    
    {
        BigInt bi1{"-99999999999999999999999999999999999999999999999999999999999999999999"};
        BigInt bi2{"99999999999999999999999999999999999999999999999999999999999999999999"};
        String str = (bi1 * bi2).ToString();
        
        assert(str == "-99999999999999999999999999999999999999999999999999999999999999999998"
                      "00000000000000000000000000000000000000000000000000000000000000000001");
    }

    // Divison
    assert((BigInt("0") / BigInt("-0")).ToString() == "0");
    assert((BigInt("0") % BigInt("0")).ToString() == "0");
    assert((BigInt("999999") / 1234).ToString() == "810");
    assert((BigInt("999999") % 1234).ToString() == "459");
    assert(1234 / BigInt("999999") == 0);
    assert(1234 % BigInt("999999") == 1234);

    {
        // https://en.cppreference.com/w/cpp/language/operator_arithmetic
        // (a/b)*b + a%b == a
        BigInt a("9999999843");
        BigInt b("99999998");
        assert(a/b*b + a%b == a);

        a = {"-9999999843"};
        b = {"99999998"};
        assert(a/b*b + a%b == a);

        a = {"9999999843"};
        b = {"-99999998"};
        assert(a/b*b + a%b == a);

        a = {"-9999999843"};
        b = {"-99999998"};
        assert(a/b*b + a%b == a);
    }

#if false // Current division implementation too slow
    {
        BigInt num{"-99999999999999999999999999999999999999999999999999999999999999999998"
                   "00000000000000000000000000000000000000000000000000000000000000000001"};
            
        BigInt denom{"-99999999999999999999999999999999999999999999999999999999999999999999"};
        String str = (num / denom).ToString();
        assert(str == "99999999999999999999999999999999999999999999999999999999999999999999");
        str = (num % denom).ToString();
        assert(str == "0");
    }
#else
    {
        BigInt num{"-999998"
                   "000001"};
            
        BigInt denom{"-999999"};
        String str = (num / denom).ToString();
        assert(str == "999999");
        str = (num % denom).ToString();
        assert(str == "0");
    }
#endif

    // Additional operators
    {
        BigInt bi{(i32)1};
        assert((bi++).ToString() == "1");
        assert(bi.ToString() == "2");
        assert((++bi).ToString() == "3");
        assert(bi.ToString() == "3");
        assert((bi--).ToString() == "3");
        assert(bi.ToString() == "2");
        assert((--bi).ToString() == "1");
        assert(bi.ToString() == "1");
        assert((bi += 10).ToString() == "11");
        assert((bi -= 2).ToString() == "9");
        assert((bi *= 2).ToString() == "18");
    }
}
