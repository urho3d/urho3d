-- Script to recursively compile lua files located in specified rootFolder to luc (bytecode)
-- Usage: require "LuaScripts/Utilities/LuaScriptCompiler"


-- Set root folder containing lua files to convert
local rootFolder = "Data/LuaScripts/" -- Starting from bin folder
if not fileSystem:DirExists(rootFolder) then log:Write(LOG_WARNING, "Cannot find " .. rootFolder) return end -- Ensure that rootFolder exists

-- Get lua files recursively
local files = fileSystem:ScanDir(fileSystem:GetProgramDir() .. rootFolder, "*.lua", SCAN_FILES, true)
if table.maxn(files) == 0 then log:Write(LOG_WARNING, "No lua file found in " .. rootFolder .. " and subfolders") return end -- Ensure that at least one file was found

-- Compile each lua file found in rootFolder and subfolders to luc
for i=1, table.maxn(files) do
    local filename = rootFolder .. files[i] -- Get file with its path
    if not fileSystem:FileExists(filename) then log:Write(LOG_WARNING, "Cannot find " .. filename) return end
    print(filename .. "\n")
    local args = {"-b", filename, ReplaceExtension(filename, ".luc")} -- Set arguments to pass to the luajit command line app
    fileSystem:SystemRun(fileSystem:GetProgramDir() .. "luajit", args) -- Compile lua file to luc
end
