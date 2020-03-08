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

-- Highly based on "ToDoxHook.lua", adjusted for Zerobrane Studio API format.
-- Compatible with Zerobrane Studio 0.41+ (Zerobrane Studio 0.40 and below may have issues)

--[[ Copy result in your Zerobrane Studio's folder "api/lua" and set it in your 
     "interpreters" file with the filename (excluding it's lua extension) into the 
     "api" table variable. ]]--

require "ToDoxHook"

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
 
 
-- Workaround for Zerobrane Studio's tool-tip with overloaded functions
function adjustClassesOverloadFuncs()
  for i, class in ipairs(classes) do
    if classes[i].functions ~= nil then
      for j, func in ipairs(classes[i].functions) do
        for k, searchfunc in ipairs(classes[i].functions) do
          -- don't apply on same
          if k ~= j and func.name == searchfunc.name then
            if classes[i].functions[j].overloads == nil then
              classes[i].functions[j].overloads = {}
            end
            table.insert(classes[i].functions[j].overloads, searchfunc)
            table.remove(classes[i].functions, k)
            adjustClassesOverloadFuncs()
            return
          end
        end
      end
    end
  end
end

function writeFunctionArgs(file, declarations)
  local count = table.maxn(declarations)
  for i = 1, count do
    local declaration = declarations[i]
    if declaration.type ~= "void" then
      -- add parameter type
      local param_str = declaration.type
      -- add pointer or reference
      if declaration.ptr ~= "" then
        param_str = param_str .. declaration.ptr
      end
      -- add parameter name
      param_str = param_str .. " " .. declaration.name
      -- add parameter default value
      if declaration.def ~= "" then
        param_str = param_str .. " = " .. declaration.def
      end
      local fixedParamStr = param_str:gsub([[(")]], [[\%1]])
      file:write(fixedParamStr)
    end
    if i ~= count then
      file:write(", ")
    end
  end
end

function writeFunctionReturn(file, func)
  local return_str = ""
  if func.type ~= "" and func.type ~= "void" then
    return_str = return_str .. func.type
  end
  if func.ptr ~= "" then
    if func.type == "" and classname ~= nil then
      return_str = return_str .. classname
    end
  return_str = return_str .. func.ptr
  end
  file:write(return_str)
end

function writeInheritances(file, classname)
  for i, inheritance in ipairs(classes) do
    if inheritance.name == classname then
      if inheritance.functions ~= nil then
        for j, func in ipairs(inheritance.functions) do
          writeFunction(file, func, classname, true)
        end
      end
      if inheritance.properties ~= nil then
        for j, property in ipairs(inheritance.properties) do
          writeProperty(file, property)
        end
      end
      -- append inheritance functions & properties
      if inheritance.base ~= "" then
        writeInheritances(file, inheritance.base)
      end
    end
  end
end
 
function writeClasses(file)
  sortByName(classes)
  adjustClassesOverloadFuncs()
 
  file:write("\n\n  -- Classes")
  for i, class in ipairs(classes) do
    file:write("\n  " .. class.name .. " = {")
               
    if class.functions ~= nil or class.properties ~= nil then
      file:write("\n    childs = {")
    end
               
    if class.functions ~= nil then
      for i, func in ipairs(class.functions) do
          writeFunction(file, func, class.name)
      end
    end
               
    if class.properties ~= nil then
      for i, property in ipairs(class.properties) do
        writeProperty(file, property)
      end
    end
               
    -- append inheritance functions & properties
    if class.base ~= "" then
      writeInheritances(file, class.base)
    end
                               
    if class.functions ~= nil or class.properties ~= nil then
      file:write("\n    },")
    end
 
    file:write("\n    type = \"class\"")
    file:write("\n  },")
  end
end
 
function writeEnumerates(file)
  sortByName(enumerates)
  file:write("\n\n  -- Enumerations\n")
 
  for i, enumerate in ipairs(enumerates) do
    for i, value in ipairs(enumerate.values) do
      file:write("\n      " .. value .. " = {")
      file:write("\n        description = \"(Readonly) int for '" .. enumerate.name .. "'\",")
      file:write("\n        type = \"value\"")
      file:write("\n      },")
    end
  end
end
 
function writeFunction(file, func, classname, isInheritance, asFunc)
  -- ignore operators
  if func.name:find("^operator[=%+%-%*%(%)\\</]") == nil then
 
    -- ignore new/delete object if from inheritance
    if not ((func.name == classname or func.name == "new" or func.name == "delete") and isInheritance == true) then
   
      -- write function begin
      file:write("\n      " .. func.name .. " = {")
 
      -- write parameters
      file:write("\n        args = \"(")
      if func.declarations ~= nil then
        writeFunctionArgs(file, func.declarations)
      end
      file:write(")\",")
     
      -- write description preparation
      local isFirstDescription = true
      if func.overloads ~= nil or func.descriptions ~= nil then
        file:write("\n        description = \"")
      end
      -- write overloaded parameters in description, if any
      if func.overloads ~= nil then
        for i, overload in ipairs(func.overloads) do
          if isFirstDescription == false then
            file:write(",\\n")
          else
            isFirstDescription = false
          end
          file:write("(")
          writeFunctionReturn(file, overload)
          file:write(") "..overload.name.." (")
          writeFunctionArgs(file, overload.declarations)
          file:write(")")
        end
      end
      -- write description
      if func.descriptions ~= nil then
        for i, description in ipairs(func.descriptions) do
          if isFirstDescription == false then
            file:write("\\n")
          else
            isFirstDescription = false
          end
          local fixedDescription = description:gsub([[(")]], [[\%1]])
          file:write(fixedDescription)
        end
      end
      -- write description end
      if func.overloads ~= nil or func.descriptions ~= nil then
        file:write("\",")
      end
      
      -- write returns
      if func.type ~= "" or func.ptr ~= "" then
        file:write("\n        returns = \"(")
        writeFunctionReturn(file, func)
        file:write(")\",")
      end
 
      -- write valuetype
      if func.ptr ~= "" then
        if func.type ~= "" then
          file:write("\n        valuetype = \"" .. func.type:gsub("(const%s+)","") .. "\",")
        elseif classname ~= nil then
          file:write("\n        valuetype = \"" .. classname .. "\",")
        end
      end
         
      -- write function end
      if asFunc == true then
        file:write("\n        type = \"function\"") -- accepts auto-completion with ".", ":" and global
      else
        file:write("\n        type = \"method\"") -- accepts auto-completion only with ":"
      end
      file:write("\n      },")
    end
  end
end
 
function writeGlobalConstants(file)
  sortByName(globalConstants)
 
  file:write("\n\n  -- Global Constants\n")
  for i, constant in ipairs(globalConstants) do
    file:write("\n      " .. constant.name .. " = {")
   
    -- write valuetype
    if constant.ptr ~= "" then
      if constant.type ~= "" then
        file:write("\n        valuetype = \"" .. constant.type:gsub("(const%s+)","") .. "\",")
      end
    end
   
    -- write description (type)
    file:write("\n        description = \"" .. constant.type .. constant.ptr .. "\",")
   
    -- write constant end
    file:write("\n        type = \"value\"")
    file:write("\n      },")
  end
end
 
function writeGlobalConstants(file)
  sortByName(globalConstants)
 
  file:write("\n\n  -- Global Constants\n")
  for i, constant in ipairs(globalConstants) do
    file:write("\n      " .. constant.name .. " = {")
   
    -- write valuetype
    if constant.ptr ~= "" then
      if constant.type ~= "" then
        file:write("\n        valuetype = \"" .. constant.type:gsub("(const%s+)","") .. "\",")
      end
    end
   
    -- write description (type)
    file:write("\n        description = \"" .. constant.type .. constant.ptr .. "\",")
   
    -- write constant end
    file:write("\n        type = \"value\"")
    file:write("\n      },")
  end
end
 
function writeGlobalFunctions(file) 
  sortByName(globalFunctions)
 
  file:write("\n\n  -- Global Functions\n")
  for i, func in ipairs(globalFunctions) do
    writeFunction(file, func, nil, nil, true)
  end
end
 
function writeGlobalProperties(file)
  file:write("\n")
  for i, property in ipairs(globalProperties) do
    writeProperty(file, property)
  end
end
 
function writeProperty(file, property)
  file:write("\n      " .. property.name .. " = {")
 
  -- write valuetype
  if property.ptr ~= "" then
    if property.type ~= "" then
      file:write("\n        valuetype = \"" .. property.type:gsub("(const%s+)","") .. "\",")
    end
  end
 
  -- write description (type)
  if property.mod:find("tolua_readonly") == nil then
    file:write("\n        description = \"" .. property.type  .. property.ptr .. "")
  else
    file:write("\n        description = \"(Readonly) " .. property.type .. property.ptr .. "")
  end
  -- write description
  if property.descriptions ~= nil then
    for i, description in ipairs(property.descriptions) do
      local fixedDescription = description:gsub([[(")]], [[\%1]])
      file:write("\\n" .. fixedDescription)
    end
  end
  file:write("\",")
  
  -- write property end
  file:write("\n        type = \"value\"")
  file:write("\n      },")
end
 
function classPackage:print()
  curDir = getCurrentDirectory()
  
  if flags.o == nil then
    print("Invalid output filename");
    return
  end
 
  local filename = flags.o
  local file = io.open(filename, "wt")
 
  file:write("-- Urho3D API generated on "..os.date('%Y-%m-%d'))
  file:write("\n\nlocal api = {")
 
  local i = 1
  while self[i] do
    self[i]:print("","")
    i = i + 1
  end
  printDescriptionsFromPackageFile(flags.f)
 
  writeClasses(file)
  writeEnumerates(file)
  writeGlobalFunctions(file)
  writeGlobalProperties(file)
  writeGlobalConstants(file)
 
  file:write("\n}\nreturn api\n")
 
  file:close()
end
