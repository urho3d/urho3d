#include "Scripts/Utilities/Assert.as"

void Test_Math_BigInt()
{
    Assert(BigInt().ToString() == "0");
    Assert(BigInt("9999999999999").ToString() == "9999999999999");

    {
        BigInt bi1("9999999999999");
        BigInt bi2("1");
        Assert((bi1 + bi2).ToString() == "10000000000000");
    }

    {
        BigInt bi("9999999999999");
        Assert((bi += 1).ToString() == "10000000000000");
    }
}
