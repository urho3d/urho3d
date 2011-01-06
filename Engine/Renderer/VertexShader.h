//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#ifndef RENDERER_VERTEXSHADER_H
#define RENDERER_VERTEXSHADER_H

#include "GPUObject.h"
#include "Resource.h"
#include "ShaderDefs.h"

#include <map>
#include <string>

class Deserializer;

//! Vertex shader resource
class VertexShader : public Resource, public GPUObject
{
    DEFINE_TYPE(VertexShader);
    
    friend unsigned getVSRegister(VSParameter param);
    
public:
    //! Construct with renderer subsystem pointer and name
    VertexShader(Renderer* renderer, const std::string& name);
    //! Destruct
    virtual ~VertexShader();
    
    //! Load resource. Throw exception on error
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    
    //! Return shader hash for state sorting
    unsigned short getHash() const { return mHash; }
    //! Return whether uses a specific shader parameter
    bool hasParameter(VSParameter parameter) const { return mUseParameter[parameter]; }
    //! Return whether is Shader Model 3 format
    bool isSM3() const { return mIsSM3; }
    
    //! Check whether a shader parameter needs update
    bool needParameterUpdate(VSParameter parameter, const void* source)
    {
        if ((mUseParameter[parameter]) && (sLastParameterSources[parameter] != source))
        {
            sLastParameterSources[parameter] = source;
            return true;
        }
        return false;
    }
    
    //! Return shader parameter index by name
    static VSParameter getParameter(const std::string& name);
    //! Clear remembered shader parameter sources
    static void clearLastParameterSources();
    
private:
    //! Release shader
    void release();
    //! Load parameters from an XML file
    void loadParameters(ResourceCache* cache);
    //! Initialize parameter map with known values
    static void initializeParameters();
    
    //! Shader hash
    unsigned short mHash;
    //! Parameter use flags
    bool mUseParameter[MAX_VS_PARAMETERS];
    //! Shader Model 3 flag
    bool mIsSM3;
    
    //! Parameter mappings
    static std::map<std::string, VSParameter> sParameters;
    //! Constant register mappings
    static unsigned sRegisters[MAX_VS_PARAMETERS];
    //! Last parameter sources per parameter
    static const void* sLastParameterSources[MAX_VS_PARAMETERS];
    //! Parameters initialized flag
    static bool sInitialized;
};

//! Return constant register by parameter
inline unsigned getVSRegister(VSParameter param) 
{
    return VertexShader::sRegisters[param]; 
}

#endif // RENDERER_VERTEXSHADER_H
