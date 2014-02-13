local classes = {}
local enumerates = {}
local globalConstants = {}
local globalFunctions = {}
local globalProperties = {}
local currentClass = nil
local currentFunction = nil

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

function printFunction(self,ident,close)
  local func = {}
  func.mod  = self.mod
  func.type = self.type
  func.ptr  = self.ptr
  func.name = self.name
  func.lname = self.lname
  func.const = self.const
  func.cname = self.cname
  func.lname = self.lname

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
      func.type = ""
      func.name = currentClass.name
    end

    if func.name == "delete" then
      func.name = "~" .. currentClass.name
    end
    if currentClass.functions == nil then
      currentClass.functions = { func }
    else
      table.insert(currentClass.functions, func)
    end
  end
end

function classFunction:print(ident,close)
  printFunction(self,ident,close)
end

function classOperator:print(ident,close)
  printFunction(self,ident,close)
end

function classVariable:print(ident,close)
  local property = {}
  property.mod  = self.mod
  property.type = self.type
  property.ptr  = self.ptr
  property.name = self.name
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

function writeClasses(file)
  sortByName(classes)

  file:write("\n\\section LuaScriptAPI_Classes Classes\n\n")
  for i, class in ipairs(classes) do
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
  -- write function begin
  local func_str = "- "

  if func.type ~= "" then
    func_str = func_str .. func.type
  end

  if func.ptr ~= "" then
    func_str = func_str .. func.ptr
  end

  func_str = func_str .. " " .. func.name .. "("
  file:write(func_str)

  -- write parameters
  if func.declarations ~= nil then
    local count = table.maxn(func.declarations)
    for i = 1, count do
      local declaration = func.declarations[i]
      if declaration.type ~= "void" then
        -- add paramter type
        local param_str = declaration.type
        -- add pointer or reference
        if declaration.ptr ~= "" then
          param_str = param_str .. declaration.ptr
        end
        -- add paramter name
        param_str = param_str .. " " .. declaration.name
        -- add paramter default value
        if declaration.def ~= "" then
          param_str = param_str .. " = " .. declaration.def
        end
        file:write(param_str)
      end
      if i ~= count then
        file:write(", ")
      end
    end
  end

  -- write function end
  if func.const == "" then
    file:write(")\n")
  else
    file:write(") " .. func.const .. "\n")
  end
end

function writeGlobalConstants(file)
  sortByName(globalConstants)

  file:write("\n\\section LuaScriptAPI_GlobalConstants Global constants\n")
  for i, constant in ipairs(globalConstants) do
    local const_str = "- " .. constant.type:gsub("const ", "")
    if constant.ptr ~= "" then
      const_str = const_str .. constant.ptr
    end
    const_str = const_str .. " " .. constant.name;
    file:write(const_str .. "\n")
  end
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

function writeGLobalProperties(file)
  file:write("\n\\section LuaScriptAPI_GlobalProperties Global properties\n")
  for i, property in ipairs(globalProperties) do
    writeProperty(file, property)
  end
end

function writeProperty(file, property)
  property.name = property.name:gsub("_", "")
  file:write("- " .. property.type .. property.ptr .. " " .. property.name)
  if property.mod:find("tolua_readonly") == nil then
    file:write("\n")
  else
    file:write(" (readonly)\n")
  end
end

function classPackage:print()
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
  file:write("\\page LuaScriptAPI Lua Scripting API\n")

  local i = 1
  while self[i] do
    self[i]:print("","")
    i = i + 1
  end

  writeClasses(file)
  writeEnumerates(file)
  writeGlobalFunctions(file)
  writeGLobalProperties(file)
  writeGlobalConstants(file)
  
  file:write("*/\n")
  file:write("\n")
  file:write("}\n")

  file:close()
end
