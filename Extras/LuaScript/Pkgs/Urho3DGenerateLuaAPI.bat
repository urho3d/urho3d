del ..\*LuaAPI.cpp

tolua++.exe -L basic.lua -o ../AudioLuaAPI.cpp Audio.pkg
tolua++.exe -L basic.lua -o ../ContainerLuaAPI.cpp Container.pkg
tolua++.exe -L basic.lua -o ../CoreLuaAPI.cpp Core.pkg
tolua++.exe -L basic.lua -o ../EngineLuaAPI.cpp Engine.pkg
tolua++.exe -L basic.lua -o ../GraphicsLuaAPI.cpp Graphics.pkg
tolua++.exe -L basic.lua -o ../InputLuaAPI.cpp Input.pkg
tolua++.exe -L basic.lua -o ../IOLuaAPI.cpp IO.pkg
tolua++.exe -L basic.lua -o ../MathLuaAPI.cpp Math.pkg
tolua++.exe -L basic.lua -o ../NavigationLuaAPI.cpp Navigation.pkg
tolua++.exe -L basic.lua -o ../NetworkLuaAPI.cpp Network.pkg
tolua++.exe -L basic.lua -o ../PhysicsLuaAPI.cpp Physics.pkg
tolua++.exe -L basic.lua -o ../ResourceLuaAPI.cpp Resource.pkg
tolua++.exe -L basic.lua -o ../SceneLuaAPI.cpp Scene.pkg
tolua++.exe -L basic.lua -o ../UILuaAPI.cpp UI.pkg

tolua++.exe -L basic.lua -o ../LuaScriptLuaAPI.cpp LuaScript.pkg