:: To avoid cacophony of multiple background music when testing with multiple connections on the same test machine,
:: start all the other non-headless connections with '-nobgm' argument.
:: E.g. 1 - headless server
::   Start the server with "NinjaSnowWar -headless -server"
::   Start the first client with "NinjaSnowWar -w -address <put-your-host-name-here>"
::   Start the subsequent clients on the same host with "NinjaSnowWar -w -nobgm -address <put-your-host-name-here>"
::
:: E.g. 2 - non-headless server
::   Start the server with "NinjaSnowWar -w -server"
::   Start the client on the same host with "NinjaSnowWar -w -nobgm -address <put-your-host-name-here>"
::
@echo off
setlocal
set "dirname=%~dp0"
if %0 == "%~dpnx0" where /q "%cd%:%~nx0" && set "dirname=%cd%\"
if exist "%dirname%Urho3DPlayer.exe" (set "DEBUG=") else (set "DEBUG=_d")
"%dirname%Urho3DPlayer%DEBUG%" Scripts/NinjaSnowWar.as %*
