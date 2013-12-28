//
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

#pragma once

#include "GraphicsDefs.h"
#include "HashMap.h"
#include "HashSet.h"

namespace Urho3D
{

class XMLElement;

/// Option definition and combination rules for constructing shader variations.
struct ShaderOption
{
    /// Variation name.
    String name_;
    /// Defines to use in compiling.
    Vector<String> defines_;
    /// Define values to use in compiling.
    Vector<String> defineValues_;
    /// Other variations to exclude.
    Vector<String> excludes_;
    /// Other variations to include.
    Vector<String> includes_;
    /// Required defines for variation to be compiled.
    Vector<String> requires_;
    /// Exclude indices.
    PODVector<unsigned> excludeIndices_;
    /// Include indices.
    PODVector<unsigned> includeIndices_;
    /// Option(s) which satisfy the requirements.
    PODVector<unsigned> requirementBits_;
    /// Variation flag. A variation excludes all other variations, unless in a separate group.
    bool isVariation_;
};

/// Combination of shader options, used for compiling a shader variation.
struct ShaderCombination
{
    /// Shader variation name.
    String name_;
    /// Defines to use in compiling.
    Vector<String> defines_;
    /// Define values to use in compiling.
    Vector<String> defineValues_;
};

/// %Shader definition parser. Constructs a list of shader variations from the definition.
class URHO3D_API ShaderParser
{
public:
    /// Construct with defaults.
    ShaderParser();

    /// Parse from an XML element. Return true if successful.
    bool Parse(ShaderType type, const XMLElement& element, bool buildAll = false, const Vector<String>& globalDefines = Vector<String>(), const Vector<String>& globalDefineValues = Vector<String>());
    
    /// Return error message if parsing failed.
    String GetErrorMessage() const { return errorMessage_; }
    /// Return all combinations. Should only be called after building all combinations, because otherwise it only returns combinations built so far.
    const HashMap<String, unsigned>& GetAllCombinations() const { return combinations_; }
    /// Return whether a shader combination exists. Will be built on demand if all combinations not yet built.
    bool HasCombination(const String& name);
    /// Return a combination by name. Will be built on demand if all combinations not yet built.
    ShaderCombination GetCombination(const String& name);
    
private:
    /// Parse options for a shader, then preprocess them for building combinations.
    bool ParseOptions(const XMLElement& element);
    /// Construct all shader combinations from the options. This is potentially slow
    void BuildCombinations();
    /// Construct one shader combination on demand based on active option bitmask. Return true if was valid.
    bool BuildCombination(unsigned active);
    /// Construct one shader combination on demand based on the name. Return true if was valid.
    bool BuildCombination(const String& name);
    
    /// Error message.
    String errorMessage_;
    /// Global defines.
    Vector<String> globalDefines_;
    /// Global define values.
    Vector<String> globalDefineValues_;
    /// Shader options.
    Vector<ShaderOption> options_;
    /// Option name to index mapping.
    HashMap<String, unsigned> nameToIndex_;
    /// Available combinations.
    HashMap<String, unsigned> combinations_;
    /// Combinations that were attempted to be built, but were not found.
    HashSet<String> failedCombinations_;
    /// Bitmasks of already built valid combinations.
    HashSet<unsigned> usedCombinations_;
    /// Total number of possible combinations, including invalid ones.
    unsigned maxCombinations_;
    /// Number of variation groups.
    unsigned numVariationGroups_;
    /// All combinations built flag.
    bool builtAll_;
};

}
