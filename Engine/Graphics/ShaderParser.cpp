//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Map.h"
#include "Set.h"
#include "ShaderParser.h"
#include "XMLElement.h"

bool ShaderParser::Parse(ShaderType type, const XMLElement& element, const Vector<String>& globalDefines, const Vector<String>& globalDefineValues)
{
    if (globalDefines.Size() != globalDefineValues.Size())
    {
        errorMessage_ = "Amount of global define names and values does not match";
        return false;
    }
    
    errorMessage_.Clear();
    combinations_.Clear();
    
    Vector<ShaderOption> options;
    
    XMLElement shader = element.GetChild("shader");
    while (shader)
    {
        String typeName = String(shader.GetAttribute("type")).ToLower();
        if (typeName.Empty() || (type == VS && typeName == "vs") || (type == PS && typeName == "ps"))
        {
            if (!ParseOptions(options, shader))
                return false;
            BuildCombinations(options, globalDefines, globalDefineValues);
            return true;
        }
        
        shader = shader.GetNext("shader");
    }
    
    // If no shader sub-elements, check also the element itself
    String typeName = String(element.GetAttribute("type")).ToLower();
    if (typeName.Empty() || (type == VS && typeName == "vs") || (type == PS && typeName == "ps"))
    {
        if (!ParseOptions(options, element))
            return false;
        BuildCombinations(options, globalDefines, globalDefineValues);
        return true;
    }
    
    errorMessage_ = "No shader definitions";
    return false;
}

bool ShaderParser::ParseOptions(Vector<ShaderOption>& dest, const XMLElement& element)
{
    XMLElement option = element.GetChild();
    while (option)
    {
        String value = option.GetName().ToLower();
        if (value == "variation" || value == "option")
        {
            String name = option.GetAttribute("name");
            
            ShaderOption newOption;
            newOption.name_ = name;
            newOption.isVariation_ = value == "variation";
            
            String simpleDefine = option.GetAttribute("define");
            if (!simpleDefine.Empty())
            {
                Vector<String> nameAndValue = simpleDefine.Split('=');
                if (nameAndValue.Size() == 2)
                {
                    newOption.defines_.Push(nameAndValue[0]);
                    newOption.defineValues_.Push(nameAndValue[1]);
                }
                else
                {
                    newOption.defines_.Push(simpleDefine);
                    newOption.defineValues_.Push("1");
                }
            }
            
            String simpleExclude = option.GetAttribute("exclude");
            if (!simpleExclude.Empty())
                newOption.excludes_.Push(simpleExclude);
            
            String simpleInclude = option.GetAttribute("include");
            if (!simpleInclude.Empty())
                newOption.includes_.Push(simpleInclude);
            
            String simpleRequire = option.GetAttribute("require");
            if (!simpleRequire.Empty())
                newOption.requires_.Push(simpleRequire);
            
            XMLElement define = option.GetChild("define");
            while (define)
            {
                String defineName = define.GetAttribute("name");
                Vector<String> nameAndValue = defineName.Split('=');
                if (nameAndValue.Size() == 2)
                {
                    newOption.defines_.Push(nameAndValue[0]);
                    newOption.defineValues_.Push(nameAndValue[1]);
                }
                else
                {
                    newOption.defines_.Push(defineName);
                    newOption.defineValues_.Push("1");
                }
                define = define.GetNext("define");
            }
            
            XMLElement exclude = option.GetChild("exclude");
            while (exclude)
            {
                newOption.excludes_.Push(exclude.GetAttribute("name"));
                exclude = exclude.GetNext("exclude");
            }
            
            XMLElement include = option.GetChild("include");
            while (include)
            {
                newOption.includes_.Push(include.GetAttribute("name"));
                include = include.GetNext("include");
            }
            
            XMLElement require = option.GetChild("require");
            while (require)
            {
                newOption.requires_.Push(require.GetAttribute("name"));
                require = require.GetNext("require");
            }
            
            dest.Push(newOption);
            if (dest.Size() > 32)
            {
                errorMessage_ = "Maximum of 32 shader options exceeded";
                return false;
            }
        }
        else
        {
            errorMessage_ = "Unrecognized element " + value + " in shader definition";
            return false;
        }
        
        option = option.GetNext();
    }
    
    return true;
}

void ShaderParser::BuildCombinations(Vector<ShaderOption>& options, const Vector<String>& globalDefines, const Vector<String>& globalDefineValues)
{
    unsigned combinations = 1;
    unsigned numVariationGroups = 0;
    Set<unsigned> usedCombinations;
    Map<String, unsigned> nameToIndex;
    
    for (unsigned i = 0; i < options.Size(); ++i)
    {
        combinations *= 2;
        nameToIndex[options[i].name_] = i;
        if (options[i].isVariation_ && (i == 0 || !options[i - 1].isVariation_))
            ++numVariationGroups;
    }
    
    for (unsigned i = 0; i < combinations; ++i)
    {
        // Variations/options active on this particular combination
        unsigned active = i;
        unsigned variationsActive = 0;
        bool skipThis = false;
        
        // Check for excludes/includes/requires
        for (unsigned j = 0; j < options.Size(); ++j)
        {
            if ((active >> j) & 1)
            {
                for (unsigned k = 0; k < options[j].includes_.Size(); ++k)
                {
                    if (nameToIndex.Contains(options[j].includes_[k]))
                        active |= (1 << nameToIndex[options[j].includes_[k]]);
                }
                
                for (unsigned k = 0; k < options[j].excludes_.Size(); ++k)
                {
                    if (nameToIndex.Contains(options[j].excludes_[k]))
                        active &= ~(1 << nameToIndex[options[j].excludes_[k]]);
                }
                
                // Skip dummy separators (options without name and defines)
                if (options[j].name_.Empty() && !options[j].isVariation_ && options[j].defines_.Empty())
                    active &= ~(1 << j);
                
                // If it's a variation, exclude all other variations in the same group
                if (options[j].isVariation_)
                {
                    for (unsigned k = j - 1; k < options.Size(); --k)
                    {
                        if (options[k].isVariation_)
                            active &= ~(1 << k);
                        else
                            break;
                    }
                    for (unsigned k = j + 1; k < options.Size(); ++k)
                    {
                        if (options[k].isVariation_)
                            active &= ~(1 << k);
                        else
                            break;
                    }
                    
                    ++variationsActive;
                }
                
                for (unsigned k = 0; k < options[j].requires_.Size(); ++k)
                {
                    bool requireFound = false;
                    
                    for (unsigned l = 0; l < globalDefines.Size(); ++l)
                    {
                        if (globalDefines[l] == options[j].requires_[k])
                        {
                            requireFound = true;
                            break;
                        }
                    }
                    
                    if (!requireFound)
                    {
                        for (unsigned l = 0; l < options.Size(); ++l)
                        {
                            if ((active >> l) & 1 && l != j)
                            {
                                if (options[l].name_ == options[j].requires_[k])
                                {
                                    requireFound = true;
                                    break;
                                }
                                for (unsigned m = 0; m < options[l].defines_.Size(); ++m)
                                {
                                    if (options[l].defines_[m] == options[j].requires_[k])
                                    {
                                        requireFound = true;
                                        break;
                                    }
                                }
                            }
                            if (requireFound)
                                break;
                        }
                    }
                    
                    if (!requireFound)
                        skipThis = true;
                }
            }
        }
        
        // Check that combination is correct: a variation chosen from all groups, and is unique
        if (variationsActive < numVariationGroups || skipThis || usedCombinations.Contains(active))
            continue;
        
        ShaderCombination newCombination;
        
        // Build shader combination name & defines from active options
        for (unsigned j = 0; j < options.Size(); ++j)
        {
            if (active & (1 << j))
            {
                if (options[j].name_.Length())
                    newCombination.name_ += options[j].name_;
                for (unsigned k = 0; k < options[j].defines_.Size(); ++k)
                {
                    newCombination.defines_.Push(options[j].defines_[k]);
                    newCombination.defineValues_.Push(options[j].defineValues_[k]);
                }
                for (unsigned k = 0; k < globalDefines.Size(); ++k)
                {
                    newCombination.defines_.Push(globalDefines[k]);
                    newCombination.defineValues_.Push(globalDefineValues[k]);
                }
            }
        }
        
        combinations_.Push(newCombination);
        usedCombinations.Insert(active);
    }
}
