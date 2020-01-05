--
-- Copyright (c) 2008-2020 the Urho3D project.
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.
--

classes = {}
enumerates = {}
globalConstants = {}
globalFunctions = {}
globalProperties = {}
currentClass = nil
currentFunction = nil
curDir = nil

function classClass:print(ident,close)
  local class = {}
  class.name = self.name
  class.base = self.base
  class.lname = self.lname
  class.type = self.type
  class.btype = self.btype
  class.ctype = self.ctype

  currentClass = class
  local i = 1
  while self[i] do
    self[i]:print(ident.." ",",")
    i = i + 1
  end
  currentClass = nil

  table.insert(classes, class)
end

function classCode:print(ident,close)
end

function classDeclaration:print(ident,close)
  local declaration = {}
  declaration.mod  = self.mod
  declaration.type = self.type
  declaration.ptr  = self.ptr
  declaration.name = self.name
  declaration.dim  = self.dim
  declaration.def  = self.def
  declaration.ret  = self.ret

  if currentFunction ~= nil then
    if currentFunction.declarations == nil then
      currentFunction.declarations = { declaration }
    else
      table.insert(currentFunction.declarations, declaration)
    end
  end
end

function classEnumerate:print(ident,close)
  local enumerate = {}
  enumerate.name = self.name

  local i = 1
  while self[i] do
    if self[i] ~= "" then
      if enumerate.values == nil then
        enumerate.values = { self[i] }
      else
        table.insert(enumerate.values, self[i])
      end
    end
    i = i + 1
  end

  if enumerate.values ~= nil then
    table.insert(enumerates, enumerate)
  end
end

function deepCopy(t)
  if type(t) ~= "table" then
    return t
  end

  local mt = getmetatable(t)
  local ret = {}
  for k, v in pairs(t) do
    if type(v) == "table" then
      v = deepCopy(v)
    end
    ret[k] = v
  end
  setmetatable(ret, mt)

  return ret
end

function printFunction(self,ident,close,isfunc)
  local func = {}
  func.mod  = self.mod
  func.type = self.type
  func.ptr  = self.ptr
  func.name = self.name
  func.lname = self.lname
  func.const = self.const
  func.cname = self.cname
  func.lname = self.lname

  if isfunc then
    func.name = func.lname
  end

  currentFunction = func
  local i = 1
  while self.args[i] do
    self.args[i]:print(ident.."  ",",")
    i = i + 1
  end
  currentFunction = nil

  if currentClass == nil then
    table.insert(globalFunctions, func)
  else
    if func.name == "new" then
      -- add construct function
      local ctor = deepCopy(func)
      ctor.type = ""
      ctor.ptr = ""
      ctor.name = currentClass.name
      ctor.lname = currentClass.name
      ctor.const = "(GC)"
      ctor.cname = currentClass.name
      ctor.lname = currentClass.name

      if currentClass.functions == nil then
        currentClass.functions = { ctor }
      else
        table.insert(currentClass.functions, ctor)
      end
    end

    if func.name == "delete" then
      func.type = "void"
    end

    if currentClass.functions == nil then
      currentClass.functions = { func }
    else
      table.insert(currentClass.functions, func)
    end
  end
end

function classFunction:print(ident,close)
  printFunction(self,ident,close, true)
end

function classOperator:print(ident,close)
  printFunction(self,ident,close, false)
end

function classVariable:print(ident,close)
  local property = {}
  property.mod  = self.mod
  property.type = self.type
  property.ptr  = self.ptr
  property.name = self.lname
  property.def  = self.def
  property.ret  = self.ret

  if currentClass == nil then
    if property.mod:find("tolua_property__") == nil then
      table.insert(globalConstants, property)
    else
      table.insert(globalProperties, property)
    end
  else
    if currentClass.properties == nil then
      currentClass.properties = { property }
    else
      table.insert(currentClass.properties, property)
    end
  end
end

function classVerbatim:print(ident,close)
end

function sortByName(t)
  table.sort(t, function(a, b) return a.name < b.name end)
end

function getCurrentDirectory()
  local separator = (package.config):gsub("\n.*","")
  local path = ""
  local tmpFile = os.tmpname()
  if separator == "\\" then
    -- Workaround broken os.tmpname() on Windows platform
    tmpFile = os.getenv('TMP') .. tmpFile
    os.execute("cd > " .. tmpFile)
  else
    os.execute("pwd > " .. tmpFile)
  end
  local tmpHandler = io.open(tmpFile, "r")
  path = tmpHandler:read("*a"):gsub("\n.*","")
  tmpHandler:close()
  os.remove(tmpFile)
  return {path = path, separator = separator}
end

function isTypeEquivalent(headerType, packageType)
  -- {["headerType"] = {"packageType1", "packageType2", ...}}
  --local equivalenceTable = {["StringHash"] = {"const String"}}
  if headerType == packageType then
    return true
  else
    if equivalenceTable ~= nil then
      for headerEqType, packageEqTypes in pairs(equivalenceTable) do
        if headerEqType == headerType then
          if packageEqTypes ~= nil then
            for i, packageEqType in ipairs(packageEqTypes) do
              if packageEqType == packageType then
                return true
              end
            end
          end
          return false
        end
      end
    end
  end
  return false
end

function isSameFilename(str1, str2, excludeExtensions)
  str1 = str1:gsub("^.*" .. curDir.separator.. "(.*)$", "%1", 1)
  str2 = str2:gsub("^.*" .. curDir.separator.. "(.*)$", "%1", 1)
  if excludeExtensions == true then
    str1 = str1:gsub("^(.*)%..*$", "%1", 1)
    str2 = str2:gsub("^(.*)%..*$", "%1", 1)
  end
  if str1 == str2 then
    return true
  else
    return false
  end
end

function isSameFunction(headerFunc, packageFunc, strict)
  if headerFunc.name == packageFunc.name then
    if strict == true then
      if headerFunc.declarations ~= nil and packageFunc.declarations ~= nil then
        --for _, decl in ipairs(headerFunc.declarations) do print("FuncHeader  Param: \""..decl.type.."\", \""..decl.ptr.."\", \""..decl.name.."\", \""..decl.def.."\"") end
        --for _, decl in ipairs(packageFunc.declarations) do print("FuncPackage Param: \""..decl.type.."\", \""..decl.ptr.."\", \""..decl.name.."\", \""..decl.def.."\"") end
        for i, headerDecl in ipairs(headerFunc.declarations) do
      if packageFunc.declarations[i] ~= nil then
        if not isTypeEquivalent(headerDecl.type, packageFunc.declarations[i].type) then
          return false
        end
      else
        if headerDecl.def == "" then
          return false
        end
      end
    end
        return true
      else
        return true
      end
    else
      return true
    end
  end
  return false
end

function printDescriptionsFromPackageFile(filename, directory)
  for line in io.lines(filename) do
    line = line:gsub("%c", "")
    if line:find("^%s*%$pfile%s+\"(.+)\"") ~= nil then
      -- If it's another package file, load it (recursive)
      local nextPath = curDir.path .. curDir.separator
      nextPath = nextPath .. line:gsub("^%s*%$pfile%s+\"(.+)\"", "%1", 1):gsub("/", curDir.separator)
      local nextDirectory = line:gsub("^%s*%$pfile%s+\"(.+)\"", "%1", 1):gsub("/.*$", ""):gsub("/", curDir.separator)
      printDescriptionsFromPackageFile(nextPath, nextDirectory)
    elseif line:find("^%s*%$#include%s+\"(.+)\"") ~= nil then
      -- If it's an include, load it to fetch the descriptions
      local nextFilename = line:gsub("^%s*%$#include%s+\"(.+)\"", "%1", 1):gsub("/", curDir.separator)
      if isSameFilename(filename, nextFilename, true) then
        -- Must be same as Package Name
        printDescriptions(nextFilename, directory)
      end
    end
  end
end

function printDescriptions(filename, directory)
  -- Search Descriptions
  local className = nil
  local classScope = nil
  local description = nil
  local sourceEnginePath = curDir.path .. curDir.separator .. ".." .. curDir.separator .. ".." .. curDir.separator
  for line in io.lines(sourceEnginePath .. filename) do
    line = line:gsub("%c", "")
    -- Entering Class
    if line:find("^%s*[Cc]lass%s+(.+)") ~= nil then
      local classDefine = line:gsub("^%s*[Cc]lass%s+([%w_][^:;]*)%s*:*.*", "%1")
      className = classDefine:gsub("[%w_]+%s+([%w_]+).*", "%1")
    -- Struct Defined (same as Class)
    elseif line:find("^%s*[Ss]truct%s+(.+)") ~= nil then
      local classDefine = line:gsub("^%s*[Ss]truct%s+([%w_][^:;]*)%s*:*.*", "%1")
      className = classDefine:gsub("[%w_]+%s+([%w_]+).*", "%1")
    elseif className ~= nil then
      -- Detecting Scope
      if line:find("^%s*(%w+)%s*:%s*$") ~= nil then
        classScope = line:gsub("^%s*(%w)%s*:%s*$", "%1")
      -- Leaving Class
      elseif line:find("^%s*}%s*$") ~= nil then
        className = nil
        classScope = nil
        description = nil
      -- Gather Informations
      elseif className ~= nil and classScope ~= nil then
        -- Line stating with "///" (Description)
        if line:find("^%s*///") ~= nil then
          description = line:gsub("^%s*///%s*", "")
        -- Not Empty Line (Function)
        elseif line:find("^%s*$") == nil and description ~= nil then
          printElementDescription(className, classScope, line, description)
          description = nil
        end
      end
    end
  end
end

function getElementFromLine(line)
  local element = {}
  element.name = nil
  element.params = nil
  element.type = nil
  -- Type Detect (Function)
  if line:find("^.*%s*([%w_~]+)%s*%(.*%).*$") ~= nil then
    element.name = line:gsub("^.*%s+([%w_~]+)%s*%(.*%).*$", "%1")
    element.type = "functions"
    if line:find("^.+%(.*%)") ~= nil then
      element.params = {}
      local params_str = line:gsub("^.+%((.*)%).*$", "%1", 1)
      --print("Current Params: "..params_str)
      if params_str ~= "" then
        for param_str in params_str:gmatch("[^,;]+") do
          local param = {}
          param.type = ""
          if param_str:find("^%s*(const%s+)") ~= nil then
            param.type = "const "
            param_str = param_str:gsub("^%s*((const%s+)", "")
          end
          param.type = param.type..param_str:gsub("^%s*([%w_]+).*$", "%1")
          param.ptr = param_str:gsub("^%s*[%w_]+([%*&]?).*$", "%1")
          param.name = param_str:gsub("^%s*[%w_]+[%*&]?%s+([%w_]+).*$", "%1")
          param.def = ""
          if param_str:find(".+=.+") then
            param.def = param_str:gsub("^.*=%s*(.*)$", "%1")
          end
          table.insert(element.params, param)
        end
      else
        local param = {}
        param.type = "void"
        param.ptr = ""
        param.name = ""
        param.def = ""
        table.insert(element.params, param)
      end
    end
  -- Type Detect (Property)
  elseif line:find("^.*%s+([%w_]+)%s*.*;%s*$") ~= nil then
    element.name = line:gsub("^.*%s+([%w_]+)%s*.*;%s*$", "%1")
    element.type = "properties"
  end
  return element
end

function printElementDescription(className, classScope, line, description)
  if description ~= "" then
    local currentElement = getElementFromLine(line)
    -- Search Class & Function/Property, Then Map
    if currentElement.name ~= nil and currentElement.type ~= nil then
      --print("Name: " .. currentElement.name)
      --print("ok (name = \"" .. currentElement.name .. "\", type = \"" .. currentElement.type .. "\", className = \"" .. className .. "\")")
      for i, class in ipairs(classes) do
        if class.name == className then
          --print("Class: "..class.name.." = "..className)
          if class[currentElement.type] ~= nil then
            for j, storedElement in ipairs(class[currentElement.type]) do
              local isSameName = false
              if storedElement.name == currentElement.name then
                isSameName = true
              -- Consider that the name is the same if it has an additionnal "_" at the end and if it's a property
              elseif storedElement.name .. "_" == currentElement.name and currentElement.type == "properties" then
                isSameName = true
              end
              if isSameName == true then
                --print("Element: " .. storedElement.name .. " = " .. currentElement.name)
                -- Confirm that the function is the same and not an overloading one
                local isSameElement = true
                if currentElement.type == "functions" then
                  local candidateElement = {declarations = currentElement.params}
                  candidateElement.name = currentElement.name
                  isSameElement = isSameFunction(candidateElement, storedElement, true)
                  --if isSameElement == true then print("Is same element? True") else print("Is same element? False") end
                end
                if isSameElement == true then
                  --print("Element: " .. storedElement.name .. " = " .. currentElement.name)
                  if storedElement.descriptions == nil then
                    --print("[New description table]")
                    classes[i][currentElement.type][j].descriptions = {}
                  end
                  --print("Description: "..description)
                  --print("")
                  table.insert(classes[i][currentElement.type][j].descriptions, description)
                  return
                end
              end
            end
          end
        end
      end
      --print("")
    end
  end
end

function writeClass(file, class)
  file:write("<a name=\"Class_" .. class.name .. "\"></a>\n")
  if class.base == "" then
    file:write("### " .. class.name .. "\n\n")
  else
    file:write("### " .. class.name .. " : " .. class.base .. "\n")
  end

  if class.functions ~= nil then
    file:write("\nMethods:\n\n")
    for i, func in ipairs(class.functions) do
        writeFunction(file, func)
    end
  end

  if class.properties ~= nil then
    file:write("\nProperties:\n\n")
    for i, property in ipairs(class.properties) do
      writeProperty(file, property)
    end
  end

  file:write("\n")
end

function writeTableOfContents(file)
  file:write("\n\\section LuaScriptAPI_TableOfContents Table of contents\n\n")
  file:write("\\ref LuaScriptAPI_ClassList \"Class list\"<br>\n")
  file:write("\\ref LuaScriptAPI_Classes \"Classes\"<br>\n")
  file:write("\\ref LuaScriptAPI_Enums \"Enumerations\"<br>\n")
  file:write("\\ref LuaScriptAPI_toluaFunctions \"tolua functions\"<br>\n")
  file:write("\\ref LuaScriptAPI_GlobalFunctions \"Global functions\"<br>\n")
  file:write("\\ref LuaScriptAPI_GlobalProperties \"Global properties\"<br>\n")
  file:write("\\ref LuaScriptAPI_GlobalConstants \"Global constants\"<br>\n")
end

function writeClassList(file)
  sortByName(classes)
  file:write("\n\\section LuaScriptAPI_ClassList Class list\n\n")

  for i, class in ipairs(classes) do
    file:write("<a href=\"#Class_" .. class.name .. "\"><b>" .. class.name .. "</b></a>\n")
  end
end

function writeClasses(file)
  file:write("\n\\section LuaScriptAPI_Classes Classes\n\n")

  for i, class in ipairs(classes) do
    writeClass(file, class)
  end

end

function writeEnumerates(file)
  sortByName(enumerates)
  file:write("\\section LuaScriptAPI_Enums Enumerations\n\n")

  for i, enumerate in ipairs(enumerates) do
    file:write("### " .. enumerate.name .. "\n\n")
    for i, value in ipairs(enumerate.values) do
      file:write("- int " .. value .. "\n")
    end
    file:write("\n")
  end
end

function writeFunction(file, func)
  if func.name:match("^_") then
    -- Skip internal functions
    return
  end
  local line = "- "
  -- construct function
  if func.type == "" and func.ptr == "" then
    line = line .. func.name .. "("
  else
    line = line .. func.type .. func.ptr .. " " .. func.name .. "("
  end

  -- write parameters
  if func.declarations ~= nil then
    local count = table.maxn(func.declarations)
    for i = 1, count do
      local declaration = func.declarations[i]
      if declaration.type ~= "void" then
        line = line .. declaration.type .. declaration.ptr .. " " .. declaration.name
        -- add parameter default value
        if declaration.def ~= "" then
          line = line .. " = " .. declaration.def
        end
      end

      if i ~= count then
        line = line .. ", "
      end
    end
  end

  line = line .. ")"
  -- add const
  if func.const ~= "" then
    line = line .. " " .. func.const
  end

  file:write(line .. "\n")
end

function writeGlobalConstants(file)
  sortByName(globalConstants)
  file:write("\n\\section LuaScriptAPI_GlobalConstants Global constants\n")

  for i, constant in ipairs(globalConstants) do
    local line = "- " .. constant.type:gsub("const ", "") .. constant.ptr .. " " .. constant.name
    file:write(line .. "\n")
  end

  file:write("\n")
end

function writeToluaFunctions(file)
  file:write("\n\\section LuaScriptAPI_toluaFunctions tolua functions\n")

  file:write("- lua_usertype cast(lua_usertype object, const char* typename)\n")
  file:write("- lua_table getpeer(lua_userdata object)\n")
  file:write("- void inherit(lua_table table, lua_usertype c_instance)\n")
  file:write("- bool releaseownership(lua_usertype object)\n")
  file:write("- void setpeer(lua_userdata object, lua_table table)\n")
  file:write("- bool takeownership(lua_usertype object)\n")
  file:write("- const char* type(lua_object object)\n")

  file:write("\n")
end

function writeGlobalFunctions(file)
  sortByName(globalFunctions)
  file:write("\n\\section LuaScriptAPI_GlobalFunctions Global functions\n")

  for i, func in ipairs(globalFunctions) do
    writeFunction(file, func)
  end

  file:write("\n")
end

function writeGlobalProperties(file)
  sortByName(globalProperties)
  file:write("\n\\section LuaScriptAPI_GlobalProperties Global properties\n")

  for i, property in ipairs(globalProperties) do
    writeProperty(file, property)
  end

end

function writeProperty(file, property)
  file:write("- " .. property.type .. property.ptr .. " " .. property.name)
  if property.mod:find("tolua_readonly") == nil then
    file:write("\n")
  else
    file:write(" (readonly)\n")
  end
end

function classPackage:print()
  curDir = getCurrentDirectory()

  if flags.o == nil then
    print("Invalid output filename");
    return
  end

  local filename = flags.o
  local file = io.open(filename, "wt")

  file:write("namespace Urho3D\n")
  file:write("{\n")
  file:write("\n")
  file:write("/**\n")
  file:write("\\page LuaScriptAPI Lua scripting API\n")

  local i = 1
  while self[i] do
    self[i]:print("","")
    i = i + 1
  end
  printDescriptionsFromPackageFile(flags.f)

  writeTableOfContents(file)
  writeClassList(file)
  writeClasses(file)
  writeEnumerates(file)
  writeToluaFunctions(file)
  writeGlobalFunctions(file)
  writeGlobalProperties(file)
  writeGlobalConstants(file)

  file:write("*/\n")
  file:write("\n")
  file:write("}\n")

  file:close()
end
