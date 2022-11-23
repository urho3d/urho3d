// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Graphics/Graphics.h"
#include "../../GraphicsAPI/GraphicsImpl.h"
#include "../../GraphicsAPI/OpenGL/OGLShaderProgram.h"
#include "../../GraphicsAPI/Shader.h"
#include "../../GraphicsAPI/ShaderVariation.h"
#include "../../Graphics/Renderer.h"
#include "../../IO/Log.h"
#include "../../IO/FileSystem.h"
#include "../../IO/File.h"
#include "../../Core/Context.h"

#include "../../DebugNew.h"

namespace Urho3D
{

const char* ShaderVariation::elementSemanticNames_OGL[] =
{
    "POS",
    "NORMAL",
    "BINORMAL",
    "TANGENT",
    "TEXCOORD",
    "COLOR",
    "BLENDWEIGHT",
    "BLENDINDICES",
    "OBJECTINDEX"
};

void ShaderVariation::OnDeviceLost_OGL()
{
    if (object_.name_ && !graphics_->IsDeviceLost())
        glDeleteShader(object_.name_);

    GPUObject::OnDeviceLost();

    compilerOutput_.Clear();
}

void ShaderVariation::Release_OGL()
{
    if (object_.name_)
    {
        if (!graphics_)
            return;

        if (!graphics_->IsDeviceLost())
        {
            if (type_ == VS)
            {
                if (graphics_->GetVertexShader() == this)
                    graphics_->SetShaders(nullptr, nullptr);
            }
            else
            {
                if (graphics_->GetPixelShader() == this)
                    graphics_->SetShaders(nullptr, nullptr);
            }

            glDeleteShader(object_.name_);
        }

        object_.name_ = 0;
        graphics_->CleanupShaderPrograms_OGL(this);
    }

    compilerOutput_.Clear();
}

bool ShaderVariation::Create_OGL()
{
    Release_OGL();

    if (!owner_)
    {
        compilerOutput_ = "Owner shader has expired";
        return false;
    }
    
    object_.name_ = glCreateShader(type_ == VS ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    if (!object_.name_)
    {
        compilerOutput_ = "Could not create shader object";
        return false;
    }
    String shaderCode;
    FileSystem* fs = owner_->GetContext()->GetSubsystem<FileSystem>();
    String dirName = String("Data/Shaders/opt/") + graphics_->GetApiName() + "/";
    String pathName = fs->GetProgramDir() + dirName;
    String fileName = name_ + "_";
    fileName += defines_.Replaced(' ', '_').Replaced('=', '-');
    fileName += type_ == VS ? "_vs_" : "_fs_";
    String fullName = pathName + fileName + ".glsl";
    if (fs->FileExists(fullName))
    {
        File file(owner_->GetContext(), fullName);
        shaderCode = file.ReadString();
    }
    else
    {
        const String& originalShaderCode = owner_->GetSourceCode(type_);
        // Check if the shader code contains a version define
        unsigned verStart = originalShaderCode.Find('#');
        unsigned verEnd = 0;
        if (verStart != String::NPOS)
        {
            if (originalShaderCode.Substring(verStart + 1, 7) == "version")
            {
                verEnd = verStart + 9;
                while (verEnd < originalShaderCode.Length())
                {
                    if (IsDigit((unsigned) originalShaderCode[verEnd]))
                        ++verEnd;
                    else
                        break;
                }
                // If version define found, insert it first
                String versionDefine = originalShaderCode.Substring(verStart, verEnd - verStart);
                shaderCode += versionDefine + "\n";
            }
        }
        // Force GLSL version 150 if no version define and GL3 is being used
        if (!verEnd && Graphics::GetGL3Support())
        {
        #ifdef GL_ES_VERSION_3_0
            shaderCode += "#version 300 es\n";
        #else
            shaderCode += "#version 150\n";
        #endif
        }
    #if defined(DESKTOP_GRAPHICS)
        shaderCode += "#define DESKTOP_GRAPHICS\n";
    #elif defined(MOBILE_GRAPHICS)
        shaderCode += "#define MOBILE_GRAPHICS\n";
    #endif

        // Distinguish between VS and PS compile in case the shader code wants to include/omit different things
        shaderCode += type_ == VS ? "#define COMPILEVS\n" : "#define COMPILEPS\n";

        // Add define for the maximum number of supported bones
        shaderCode += "#define MAXBONES " + String(Graphics::GetMaxBones()) + "\n";

        // Prepend the defines to the shader code
        Vector<String> defineVec = defines_.Split(' ');
        for (unsigned i = 0; i < defineVec.Size(); ++i)
        {
            // Add extra space for the checking code below
            String defineString = "#define " + defineVec[i].Replaced('=', ' ') + "\n";
            shaderCode += defineString;

            // In debug mode, check that all defines are referenced by the shader code
        #ifdef _DEBUG
            int spPos = defineString.Find(' ', 8);
            String defineCheck;
            if (spPos == String::NPOS)
                defineCheck = defineString.Substring(8);
            else
                defineString = defineString.Substring(8, spPos - 8);
            if (originalShaderCode.Find(defineCheck) == String::NPOS)
                URHO3D_LOGWARNING("Shader " + GetFullName() + " does not use the define " + defineCheck);
        #endif
        }

    #ifdef RPI
        if (type_ == VS)
            shaderCode += "#define RPI\n";
    #endif
    #ifdef __EMSCRIPTEN__
        shaderCode += "#define WEBGL\n";
    #endif
        if (Graphics::GetGL3Support())
            shaderCode += "#define GL3\n";

        // When version define found, do not insert it a second time
        if (verEnd > 0)
            shaderCode += (originalShaderCode.CString() + verEnd);
        else
            shaderCode += originalShaderCode;
    #ifndef __ANDROID__
        pathName = fs->GetProgramDir();
    #else
        pathName = "/sdcard/Urho3D/";
    #endif
        pathName += dirName;
        if (fs->DirExists(pathName)) 
        {
            File file(owner_->GetContext(), pathName + fileName + ".lslg", FILE_WRITE);
            file.WriteString(shaderCode);
        }
    }

    const char* shaderCStr = shaderCode.CString();

    glShaderSource(object_.name_, 1, &shaderCStr, nullptr);
    glCompileShader(object_.name_);

    int compiled, length;
    glGetShaderiv(object_.name_, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        glGetShaderiv(object_.name_, GL_INFO_LOG_LENGTH, &length);
        compilerOutput_.Resize((unsigned)length);
        int outLength;
        glGetShaderInfoLog(object_.name_, length, &outLength, &compilerOutput_[0]);
        glDeleteShader(object_.name_);
        object_.name_ = 0;
    }
    else
        compilerOutput_.Clear();

    return object_.name_ != 0;
}

void ShaderVariation::SetDefines_OGL(const String& defines)
{
    defines_ = defines;
}

}
