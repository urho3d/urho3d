bool startServer = false;
bool startClient = false;
String serverAddress;
uint16 serverPort = 1234;

void ParseNetworkArguments()
{
    uint index = 0;

    for (uint i = 0; i < arguments.length; ++i)
    {
        if (arguments[i][0] != '-')
        {
            if (arguments[i] == "server")
            {
                startServer = true;
                startClient = false;
                return;
            }
            else if (index > 0) // First parameter is script name, so skip that
            {
                startClient = true;
                serverAddress = arguments[i];
            }
            
            ++index;
        }
    }
}