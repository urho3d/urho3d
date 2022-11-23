// Test AS bindings

#include "Tests/Math/BigInt.as"

void Start()
{
    Test_Math_BigInt();
    log.Info("Success!");
    engine.Exit();
}
