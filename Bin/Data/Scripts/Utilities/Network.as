bool runServer = false;
bool runClient = false;
String serverAddress;
uint16 serverPort = 1234;
String userName;

void ParseNetworkArguments()
{
    uint index = 0;

    for (uint i = 0; i < arguments.length; ++i)
    {
        if (arguments[i][0] != '-')
        {
            if (arguments[i] == "server")
            {
                runServer = true;
                runClient = false;
                return;
            }
            else if (index == 1) // First parameter is script name, so skip that
            {
                runClient = true;
                serverAddress = arguments[i];
            }
            else if (index == 2 && runClient)
                userName = arguments[i];
            
            ++index;
        }
    }
}