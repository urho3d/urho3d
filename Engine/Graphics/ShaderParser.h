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
class ShaderParser
{
public:
    /// Parse from an XML element. Return true if successful.
    bool Parse(ShaderType type, const XMLElement& element, const Vector<String>& globalDefines = Vector<String>(), const Vector<String>& globalDefineValues = Vector<String>());
    
    /// Return error message if parsing failed.
    String GetErrorMessage() const { return errorMessage_; }
    /// Return number of combinations.
    unsigned GetNumCombinations() const { return combinations_.Size(); }
   /// Return all combinations.
    const HashMap<String, unsigned>& GetAllCombinations() const { return combinations_; }
    /// Return whether a shader combination exists.
    bool HasCombination(const String& name) const;
    /// Return a combination by name.
    ShaderCombination GetCombination(const String& name) const;
    
private:
    /// Parse options for a shader.
    bool ParseOptions(const XMLElement& element);
    /// Construct shader combinations from the options.
    void BuildCombinations();
    
    /// Error message.
    String errorMessage_;
    /// Global defines.
    Vector<String> globalDefines_;
    /// Global define values.
    Vector<String> globalDefineValues_;
    /// Shader options.
    Vector<ShaderOption> options_;
    /// Available combinations.
    HashMap<String, unsigned> combinations_;
};

}
