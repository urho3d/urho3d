// Test AS bindings

#include "Tests/Math/BigInt.as"
#include "Tests/Str/format.as"

void Start()
{
    Test_Math_BigInt();
    Test_Str_Format();
    log.Info("Success!");
    engine.Exit();
}
