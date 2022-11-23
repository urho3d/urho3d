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

    {
        BigInt num("-999998"
                   "000001");

        BigInt denom("-999999");
        String str = (num / denom).ToString();
        Assert(str == "999999");
        str = (num % denom).ToString();
        Assert(str == "0");
    }

    // Additional operators
    {
        BigInt bi(int(1));
        Assert((bi++).ToString() == "1");
        Assert(bi.ToString() == "2");
        Assert((++bi).ToString() == "3");
        Assert(bi.ToString() == "3");
        Assert((bi--).ToString() == "3");
        Assert(bi.ToString() == "2");
        Assert((--bi).ToString() == "1");
        Assert(bi.ToString() == "1");
        Assert((bi += 10).ToString() == "11");
        Assert((bi -= 2).ToString() == "9");
        Assert((bi *= 2).ToString() == "18");
        Assert((bi /= 2).ToString() == "9");
        Assert((bi %= 2).ToString() == "1");
    }
}
