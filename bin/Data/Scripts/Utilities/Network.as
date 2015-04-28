bool runServer = false;
bool runClient = false;
String serverAddress;
uint16 serverPort = 1234;
String userName;
bool nobgm = false;

void ParseNetworkArguments()
{
    Array<String>@ arguments = GetArguments();
    
    for (uint i = 0; i < arguments.length; ++i)
    {
        String argument = arguments[i].ToLower();
        if (argument[0] == '-')
        {
            argument = argument.Substring(1);
            if (argument == "server")
            {
                runServer = true;
                runClient = false;
            }
            else if (argument == "address")
            {
                runClient = true;
                runServer = false;
                serverAddress = arguments[i + 1];
                ++i;
            }
            else if (argument == "username")
            {
                userName = arguments[i + 1];
                ++i;
            }
            else if (argument == "nobgm")
                nobgm = true;
        }
    }
}
