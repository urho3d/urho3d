//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "ShaderParser.h"
#include "XMLElement.h"

namespace Urho3D
{

ShaderParser::ShaderParser() :
    maxCombinations_(0),
    numVariationGroups_(0),
    builtAll_(false)
{
}

bool ShaderParser::Parse(ShaderType type, const XMLElement& element, bool buildAll, const Vector<String>& globalDefines, const Vector<String>& globalDefineValues)
{
    if (globalDefines.Size() != globalDefineValues.Size())
    {
        errorMessage_ = "Amount of global define names and values does not match";
        return false;
    }
    
    globalDefines_ = globalDefines;
    globalDefineValues_ = globalDefineValues;
    errorMessage_.Clear();
    options_.Clear();
    combinations_.Clear();
    usedCombinations_.Clear();
    failedCombinations_.Clear();
    nameToIndex_.Clear();
    
    XMLElement shader = element.GetChild("shader");
    while (shader)
    {
        String typeName = String(shader.GetAttribute("type")).ToLower();
        if (typeName.Empty() || (type == VS && typeName == "vs") || (type == PS && typeName == "ps"))
        {
            if (!ParseOptions(shader))
                return false;
            if (buildAll)
                BuildCombinations();
            return true;
        }
        
        shader = shader.GetNext("shader");
    }
    
    return true;
}

bool ShaderParser::HasCombination(const String& name)
{
    if (builtAll_)
        return combinations_.Contains(name);
    else
    {
        if (combinations_.Contains(name))
            return true;
        else
            return BuildCombination(name);
    }
}

ShaderCombination ShaderParser::GetCombination(const String& name)
{
    ShaderCombination dest;
    
    if (!builtAll_ && !combinations_.Contains(name))
    {
        if (!BuildCombination(name))
            return dest;
    }

    HashMap<String, unsigned>::ConstIterator i = combinations_.Find(name);
    if (i != combinations_.End())
    {
        dest.name_ = name;
        
        for (unsigned j = 0; j < options_.Size(); ++j)
        {
            if (i->second_ & (1 << j))
            {
                for (unsigned k = 0; k < options_[j].defines_.Size(); ++k)
                {
                    dest.defines_.Push(options_[j].defines_[k]);
                    dest.defineValues_.Push(options_[j].defineValues_[k]);
                }
            }
        }
        for (unsigned j = 0; j < globalDefines_.Size(); ++j)
        {
            dest.defines_.Push(globalDefines_[j]);
            dest.defineValues_.Push(globalDefineValues_[j]);
        }
    }

    return dest;
}

bool ShaderParser::ParseOptions(const XMLElement& element)
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
            
            #ifdef RASPI
            newOption.defines_.Push("RASPI");
            newOption.defineValues_.Push("1");
            #endif

            options_.Push(newOption);
            if (options_.Size() > 31)
            {
                errorMessage_ = "Maximum of 31 shader options exceeded";
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
    
    maxCombinations_ = 1;
    numVariationGroups_ = 0;

    // Build search index of option names
    for (unsigned i = 0; i < options_.Size(); ++i)
    {
        ShaderOption& option = options_[i];

        maxCombinations_ *= 2;
        nameToIndex_[option.name_] = i;
        if (option.isVariation_ && (i == 0 || !options_[i - 1].isVariation_))
            ++numVariationGroups_;
    }
    
    // Preprocess includes/excludes/requires for faster combination handling
    for (unsigned i = 0; i < options_.Size(); ++i)
    {
        ShaderOption& option = options_[i];

        option.isDummySeparator_ = option.name_.Empty() && !option.isVariation_ && option.defines_.Empty();

        option.excludeBits_ = 0;
        option.includeBits_ = 0;
        for (unsigned j = 0; j < option.excludes_.Size(); ++j)
            option.excludeBits_ |= 1 << nameToIndex_[option.excludes_[j]];
        for (unsigned j = 0; j < option.includes_.Size(); ++j)
            option.includeBits_ |= 1 << nameToIndex_[option.includes_[j]];

        option.variationGroupBits_ = 0;
        if (option.isVariation_)
        {
            for (unsigned j = i - 1; j < options_.Size(); --j)
            {
                if (options_[j].isVariation_)
                    option.variationGroupBits_ |= 1 << j;
                else
                    break;
            }
            for (unsigned j = i + 1; j < options_.Size(); ++j)
            {
                if (options_[j].isVariation_)
                    option.variationGroupBits_ |= 1 << j;
                else
                    break;
            }
        }
        
        for (unsigned j = 0; j < option.requires_.Size(); ++j)
        {
            unsigned bits = 0;
            for (unsigned l = 0; l < options_.Size(); ++l)
            {
                if (l != i)
                {
                    if (options_[l].name_ == option.requires_[j])
                        bits |= 1 << l;
                    else
                    {
                        for (unsigned m = 0; m < options_[l].defines_.Size(); ++m)
                        {
                            if (options_[l].defines_[m] == option.requires_[j])
                            {
                                bits |= 1 << l;
                                break;
                            }
                        }
                    }
                }
            }
            
            // If requirements are not satisfied by any option, check global defines
            if (!bits)
            {
                for (unsigned l = 0; l < globalDefines_.Size(); ++l)
                {
                    if (globalDefines_[l] == option.requires_[j])
                    {
                        bits |= 0x80000000;
                        break;
                    }
                }
            }
            
            option.requirementBits_.Push(bits);
        }
    }
    
    return true;
}

void ShaderParser::BuildCombinations()
{
    for (unsigned i = 0; i < maxCombinations_; ++i)
        BuildCombination(i);

    builtAll_ = true;
}

bool ShaderParser::BuildCombination(unsigned active)
{
    unsigned variationsActive = 0;
    
    // Check for excludes & includes first
    for (unsigned i = 0; i < options_.Size(); ++i)
    {
        if ((active >> i) & 1)
        {
            ShaderOption& option = options_[i];
            
            active |= option.includeBits_;
            active &= ~option.excludeBits_;
            
            // Skip dummy separators (options without name and defines)
            if (option.isDummySeparator_)
                active &= ~(1 << i);
            
            // If it's a variation, exclude all other variations in the same group
            if (option.isVariation_)
            {
                active &= ~options_[i].variationGroupBits_;
                ++variationsActive;
            }
        }
    }
    
    // Check that combination is correct: a variation chosen from all groups, and is unique
    if (variationsActive < numVariationGroups_ || usedCombinations_.Contains(active))
        return false;
    
    // Check for required defines, which may yet cause this combination to be skipped
    unsigned compareBits = active | 0x80000000;
    for (unsigned i = 0; i < options_.Size(); ++i)
    {
        if (active & (1 << i))
        {
            ShaderOption& option = options_[i];
            
            for (unsigned j = 0; j < option.requirementBits_.Size(); ++j)
            {
                if (!(compareBits & option.requirementBits_[j]))
                    return false;
            }
        }
    }
    
    String combinationName;
    
    // Build shader combination name from active options
    for (unsigned i = 0; i < options_.Size(); ++i)
    {
        if (active & (1 << i))
            combinationName += options_[i].name_;
    }
    
    combinations_[combinationName] = active;
    usedCombinations_.Insert(active);
    return true;
}

bool ShaderParser::BuildCombination(const String& name)
{
    // Do not attempt again if already failed
    if (failedCombinations_.Contains(name))
        return false;

    // Decode active bits from the name
    unsigned active = 0;
    String nameCopy = name;
    for (unsigned i = 0; i < options_.Size(); ++i)
    {
        // Option
        if (!options_[i].isVariation_)
        {
            if (!options_[i].name_.Empty() && nameCopy.StartsWith(options_[i].name_))
            {
                /// \todo Hack fix for options like Alpha & AlphaMask appearing in that order. Not a 100% general fix
                if (i < options_.Size() - 1 && nameCopy.StartsWith(options_[i + 1].name_))
                    continue;

                active |= 1 << i;
                nameCopy = nameCopy.Substring(options_[i].name_.Length());
            }
        }
        // Variation, must choose only one from the group, furthermore there can be empty variations with defines
        else
        {
            bool emptyFirstVariation = options_[i].name_.Empty();
            bool variationFound = false;
            unsigned j = i;
            for (; j < options_.Size(); ++j)
            {
                // Reach end of group?
                if (!options_[j].isVariation_)
                    break;
                if (!variationFound && !options_[j].name_.Empty() && nameCopy.StartsWith(options_[j].name_))
                {
                    variationFound = true;
                    active |= 1 << j;
                    nameCopy = nameCopy.Substring(options_[j].name_.Length());
                }
            }
            // If no other variation was found, must choose the empty first variation, as it may have defines
            if (emptyFirstVariation && !variationFound)
                active |= 1 << i;
            // Skip past the group
            i = j - 1;
        }
    }

    bool success = BuildCombination(active);
    if (!success)
        failedCombinations_.Insert(name);

    return success;
}

}
