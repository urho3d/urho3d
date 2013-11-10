-- Generate dox from pkg file
if #arg == 0 then
    print("Usage: lua pkgToDox.lua <output file name> <input pkg file name> ...")
    os.exit(1)
end

pkgFiles = {}
enums = {}
classes = {}
globalConstants = {}
globalFunctions = {}

-- trim string.
function trim(s)
    return (s:gsub("^%s*(.-)%s*$", "%1"))
end

-- check is embed code.
inEmbed = false
function isEmbedLine(line)
    if string.sub(line, 1, 2) == "$#" then
        return true
    end
    
    if not inEmbed then
        if string.find(line, "${") ~= nil or string.find(line, "$[[]") ~= nil then
            inEmbed = true
            return true
        end
    else
        if string.find(line, "$}") ~= nil or string.find(line, "$[]]") ~= nil then
            inEmbed = false
            return true
        end
    end
    
    return inEmbed
end

-- check is comment.
inComment = false
function isCommentLine(line)
    if line:find("//") ~= nil then
        return true
    end
    
    if inComment then
        if line:find("[*]/") ~= nil then
            inComment = false
            return true
        end
    else
        if line:find("/[*]") ~= nil then
            inComment = true
            return true
        end
    end
    return inComment
end

-- check is valid line.
function isValidLine(line)
    if #line < 2 then
        return fasle
    end
   
    if isEmbedLine(line) then
        return false
    end
    
    if isCommentLine(line) then
        return false
    end
    
    -- Declaration line.
    if (string.find(line, "enum ")  ~= nil or string.find(line, "class ")  ~= nil or
        string.find(line, "struct ") ~= nil ) and string.find(line, "}") ~= nil then
        return false
    end
    
    return true
end

local ENUM   = 1 -- line is enum code.
local CLASS  = 2 -- line is class code.
local GLOBAL = 3 -- line is global code.

local type = GLOBAL -- current line type.

function handleLine(line)
    if type == ENUM then
        if line:find("};") ~= nil then  -- end of enum.
            type = GLOBAL
        else
            table.insert(enums, line)
        end
        return
    end
    
    if type == CLASS then
        if line:find("};") ~= nil then  -- end of class or struct.
            type = GLOBAL
        else
            table.insert(classes, line)
        end
        return
    end
    
    if type == GLOBAL then
        if line:find("enum ") ~= nil then
            type = ENUM
            return
        end
        
        if line:find("class ") ~= nil or line:find("struct ") ~= nil then -- begin of class or struct.
            type = CLASS
            table.insert(classes, line)
            return
        end
        
        if line:find(")") == nil then -- global function.
            table.insert(globalConstants, line)
        else
            table.insert(globalFunctions, line)
        end
        
        return
    end
end

function gatherPkgFile(apiFile)
    local file = io.open(apiFile)
    if file == nil then
        return
    end

    local line = file:read()
    while line ~= nil do
        line = trim(line)
        local i, _, pkgFile = line:find("$pfile \"(.+)\"")
        if i ~= nil then -- begin of pkg file.
            table.insert(pkgFiles, pkgFile)
        end
        line = file:read()
    end
    file:close()
end

function handlePkgFile(pkgFile)
    local file = io.open(pkgFile)
    if file == nil then
        return
    end
    
    type = GLOBAL
    
    local line = file:read()
    while line ~= nil do
        line = trim(line)
        if isValidLine(line) then
            handleLine(line)
        end
        line = file:read()
    end
    file:close()
end

for i=2,#arg do
    gatherPkgFile(arg[i])
end

for _, pkgFile in ipairs(pkgFiles) do
    handlePkgFile(pkgFile)
end

function writeGlobalFunctions(ofile)
    ofile:write("\\section LuaScriptAPI_GlobalFunctions Global functions\n")
    for _, line in ipairs(globalFunctions) do
        line = line:gsub("%a @ ", "")
        line = line:gsub(";", "")
        ofile:write("- " .. line .. "\n")
    end
    
    ofile:write("\n")
end

function writeGlobalConstants(ofile)
    ofile:write("\\section LuaScriptAPI_GlobalConstants Global constants\n")
    for _, line in ipairs(globalConstants) do
        line = line:gsub("static ", "")
        line = line:gsub("const ", "")
        line = line:gsub(";", "")
        ofile:write("- " .. line .. "\n")
    end
        
    for _, line in ipairs(enums) do
        line = line:gsub(",", "")
        line = line:gsub(" = .*", "")
        ofile:write("- int " .. line .. "\n")
    end
    
    ofile:write("\n")
end 

function writeClasses(ofile)
    ofile:write("\\section LuaScriptAPI_Classes Classes\n")
    local firstProperty = true
    for _, line in ipairs(classes) do
        if line:find("class ") ~= nil or line:find("struct ") ~= nil then
            line = line:gsub("class ", "")
            line = line:gsub("struct ", "")
            line = line:gsub("public ", "")
            ofile:write("\n### " .. line .. "\n\nMethods:\n\n")
            firstProperty = true
        else
            line = line:gsub(";", "")
            if line:find(")") ~= nil then
                line = line:gsub(" %w+ @ ", " ")
                line = line:gsub("explicit ", "")
                line = line:gsub("tolua_outside ", "")
                ofile:write("- " .. line .. "\n")
            else
                if firstProperty then
                    firstProperty = false
                    ofile:write("\nProperties:\n\n")
                end
                line = line:gsub(" %w+_ @ ", " ")
                line = line:gsub("tolua_property__get_set ", "")
                line = line:gsub("tolua_property__is_set ", "")
                line = line:gsub("tolua_property__has_set ", "")
                line = line:gsub("tolua_property__no_prefix ", "")
                if line:find("tolua_readonly") == nil then
                    ofile:write("- " .. line .. "\n")
                else
                    line = line:gsub("tolua_readonly ", "")
                    ofile:write("- " .. line .. " (readonly)\n")
                end
            end
        end
    end
end

ofile = io.open(arg[1], "w")
ofile:write([[
namespace Urho3D
{

/**
\page LuaScriptAPI Lua Scripting API
]])
ofile:write("\n")

writeClasses(ofile)
writeGlobalFunctions(ofile)
writeGlobalConstants(ofile)

ofile:write([[
*/

}
]])