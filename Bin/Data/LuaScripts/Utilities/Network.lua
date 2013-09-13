runServer = false
runClient = true
serverAddress = ''
serverPort = 1234
userName = ''
nobgm = false

function ParseNetworkArguments()
    local index = 0
    local arguments = GetArguments()
    for i, argument in ipairs(arguments) do
        if string.sub(argument, 1, 1) ~= '-'  then
            if argument == "server" then
                runServer = true
                runClient = false
                return
            elseif index == 1 then -- First parameter is script name, so skip that
                runClient = true
                serverAddress = argument
            elseif index == 2 and runClient then
                userName = argument
            end
            index = index + 1
        else
            argument = string.lower(string.sub(argument, 2))
            if argument == "nobgm" then
                nobgm = true
            end
        end
    end
end

