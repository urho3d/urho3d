--
-- Copyright (c) 2008-2016 the Urho3D project.
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

local toWrite = {}
local currentString = ''
local out
local WRITE, OUTPUT = write, output

function output(s)
    out = _OUTPUT
    output = OUTPUT -- restore
    output(s)
end

function write(a)
    if out == _OUTPUT then
        currentString = currentString .. a
        if string.sub(currentString,-1) == '\n'  then
            toWrite[#toWrite+1] = currentString
            currentString = ''
        end
    else
        WRITE(a)
    end
end

function post_output_hook(package)
    local result = table.concat(toWrite)
    local function replace(pattern, replacement)
        local k = 0
        local nxt, currentString = 1, ''
        repeat
            local s, e = string.find(result, pattern, nxt, true)
            if e then
                currentString = currentString .. string.sub(result, nxt, s-1) .. replacement
                nxt = e + 1
                k = k + 1
            end
        until not e
        result = currentString..string.sub(result, nxt)
    end

    replace("\t", "  ")
    replace([[#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"]], [[//
// Copyright (c) 2008-2016 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Precompiled.h"

#include <toluapp/tolua++.h>
#include "LuaScript/ToluaUtils.h"

#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#endif]])
    if not _extra_parameters["Urho3D"] then
        replace([[#include "LuaScript/ToluaUtils.h"]], [[#include <Urho3D/LuaScript/ToluaUtils.h>]])
    end

    -- Special handling for vector to table conversion which would simplify the implementation of the template functions
    result = string.gsub(result, "ToluaIs(P?O?D?)Vector([^\"]-)\"c?o?n?s?t? ?P?O?D?Vector<([^*>]-)%*?>\"", "ToluaIs%1Vector%2\"%3\"")
    result = string.gsub(result, "ToluaPush(P?O?D?)Vector([^\"]-)\"c?o?n?s?t? ?P?O?D?Vector<([^*>]-)%*?>\"", "ToluaPush%1Vector%2\"%3\"")
    result = string.gsub(result, "@1%(", "(\"\",")      -- is_pointer overload uses const char* as signature
    result = string.gsub(result, "@2%(", "(0.f,")       -- is_arithmetic overload uses double as signature

    WRITE(result)
    WRITE([[
#if __clang__
#pragma clang diagnostic pop
#endif]])
end

_push_functions['Component'] = "ToluaPushObject"
_push_functions['Resource'] = "ToluaPushObject"
_push_functions['UIElement'] = "ToluaPushObject"

-- Is Urho3D Vector type.
function urho3d_is_vector(t)
    return t:find("Vector<") ~= nil
end

-- Is Urho3D PODVector type.
function urho3d_is_podvector(t)
    return t:find("PODVector<") ~= nil
end

local old_get_push_function = get_push_function
local old_get_to_function = get_to_function
local old_get_is_function = get_is_function

function is_pointer(t)
    return t:find("*>")
end

function is_arithmetic(t)
    for _, type in pairs({ "char", "short", "int", "unsigned", "long", "float", "double", "bool" }) do
        _, pos = t:find(type)
        if pos ~= nil and t:sub(pos + 1, pos + 1) ~= "*" then return true end
    end
    return false
end

function overload_if_necessary(t)
    return is_pointer(t) and "@1" or (is_arithmetic(t) and "@2" or "")
end

function get_push_function(t)
    if not urho3d_is_vector(t) then
        return old_get_push_function(t)
    end

    local T = t:match("<.*>")
    if not urho3d_is_podvector(t) then
        return "ToluaPushVector" .. T
    else
        return "ToluaPushPODVector" .. T .. overload_if_necessary(T)
    end
end

function get_to_function(t)
    if not urho3d_is_vector(t) then
        return old_get_to_function(t)
    end

    local T = t:match("<.*>")
    if not urho3d_is_podvector(t) then
        return "ToluaToVector" .. T
    else
        return "ToluaToPODVector" .. T .. overload_if_necessary(T)
    end
end

function get_is_function(t)
    if not urho3d_is_vector(t) then
        return old_get_is_function(t)
    end

    local T = t:match("<.*>")
    if not urho3d_is_podvector(t) then
        return "ToluaIsVector" .. T
    else
        return "ToluaIsPODVector" .. T .. overload_if_necessary(T)
    end
end

function get_property_methods_hook(ptype, name)
    if ptype == "get_set" then
        local Name = string.upper(string.sub(name, 1, 1))..string.sub(name, 2)
        return "Get"..Name, "Set"..Name
    end

    if ptype == "is_set" then
        local Name = string.upper(string.sub(name, 1, 1))..string.sub(name, 2)
        return "Is"..Name, "Set"..Name
    end

    if ptype == "has_set" then
        local Name = string.upper(string.sub(name, 1, 1))..string.sub(name, 2)
        return "Has"..Name, "Set"..Name
    end

    if ptype == "no_prefix" then
        local Name = string.upper(string.sub(name, 1, 1))..string.sub(name, 2)
        return Name, "Set"..Name
    end
end

-- Rudimentary checker to prevent function overloads being declared in a wrong order
-- The checker assumes function overloads are declared in group one after another within a same pkg file
-- The checker only checks for single argument function at the moment, but it can be extended to support more when it is necessary
local overload_checker = {name="", has_number=false}
function pre_call_hook(self)
    if table.getn(self.args) ~= 1 then return end
    if overload_checker.name ~= self.name then
        overload_checker.name = self.name
        overload_checker.has_number = false
    end
    local t = self.args[1].type
    if overload_checker.has_number then
        if t:find("String") or t:find("char*") then warning(self:inclass() .. ":" .. self.name .. " has potential binding problem: number overload becomes dead code if it is declared before string overload") end
    else
        overload_checker.has_number = t ~= "bool" and is_arithmetic(t)
    end
end
