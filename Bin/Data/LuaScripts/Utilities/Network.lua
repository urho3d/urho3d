runServer = false
runClient = false
serverAddress = ''
serverPort = 1234
userName = ''
nobgm = false

function ParseNetworkArguments()
    local arguments = GetArguments()
    local skipNext = false
    for i, argument in ipairs(arguments) do
        if skipNext == false and string.sub(argument, 1, 1) == '-'  then
            argument = string.lower(string.sub(argument, 1))
            if argument == "server" then
                runServer = true
                runClient = false
            elseif argument == "address" then
                runClient = true
                runServer = false
                serverAddress = arguments[i + 1]
                skipNext = true
            elseif argument == "username" then
                userName = arguments[i + 1]
                skipNext = true
            elseif argument == "nobgm" then
                nobgm = true
            end
        end
        skipNext = false
    end
end

