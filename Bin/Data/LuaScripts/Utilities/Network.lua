runServer = false
runClient = false
serverAddress = ''
serverPort = 1234
userName = ''
nobgm = false

function ParseNetworkArguments()
    local index = 0
    local arguments = GetArguments()
    for i = 1, arguments:Size() do
        local argument = arguments[i-1]
        if argument[0] ~= '-' then
            if argument:Eq("server") then
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
            argument = argument:Substring(1):ToLower()
            if argument:Eq("nobgm") then
                nobgm = true
            end
        end
    end
end

