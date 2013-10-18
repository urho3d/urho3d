local toWrite = {}
local currentString = ''
local out
local WRITE, OUTPUT = write, output

_to_functions["HttpRequest"] = "tolua_tourho3dhttprequest"

_is_functions["const PODVector<IntVector2>"] = "not implemented"
_to_functions["const PODVector<IntVector2>"] = "not implemented"
_push_functions["const PODVector<IntVector2>"] = "tolua_pushurho3dconstpodvectorintvector2"

_is_functions["const PODVector<UIElement*>"] = "not implemented"
_to_functions["const PODVector<UIElement*>"] = "not implemented"
_push_functions["const PODVector<UIElement*>"] = "tolua_pushurho3dpodvectoruielement"

_is_functions["const PODVector<unsigned>"] = "tolua_isurho3dconstpodvectorunsigned"
_to_functions["const PODVector<unsigned>"] = "tolua_tourho3dconstpodvectorunsigned"
_push_functions["const PODVector<unsigned>"] = "tolua_pushurho3dconstpodvectorunsigned"

_is_functions["const Vector<String>"] = "tolua_isurho3dconstvectorstring"
_to_functions["const Vector<String>"] = "tolua_tourho3dconstvectorstring"
_push_functions["const Vector<String>"] = "tolua_pushurho3dconstvectorstring"

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
        --if k == 0 then print('Pattern not replaced', pattern) end
    end

    replace("\t", "  ")

    replace([[#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"]], [[//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "tolua++urho3d.h"]]
      )

    WRITE(result)
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
