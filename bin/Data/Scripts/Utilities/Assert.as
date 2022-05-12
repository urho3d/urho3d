void Assert(bool condition)
{
    if (!condition)
    {
        PrintCallStack();
        ErrorDialog("Assert", "Call stack is printed to log");
        engine.Exit();
    }
}
