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

#include "Precompiled.h"
#include "Exception.h"
#include "Log.h"
#include "StringUtils.h"

#include <angelscript.h>

#include "DebugNew.h"

Exception::Exception(const std::string& what) :
    mWhat(what)
{
    LOGERROR(what);
}

#ifdef _DEBUG
Exception::Exception(const std::string& what, const char* file, int line)
{
    mWhat = what + std::string(" at ") + std::string(file) + std::string(", line ") + toString(line);
    LOGERROR(what);
}
#endif

Exception::~Exception() throw()
{
}

const char* Exception::what() const throw()
{
    return mWhat.c_str();
}

void checkAndThrowException(const std::string& what)
{
    asIScriptContext* context = asGetActiveContext();
    if (context)
    {
        static std::string lastWhat;
        lastWhat = what;
        context->SetException(lastWhat.c_str());
        LOGERROR(what);
    }
    else
        throw Exception(what);
}

#ifdef _DEBUG
void checkAndThrowException(const std::string& what, const char* file, int line)
{
    asIScriptContext* context = asGetActiveContext();
    if (context)
    {
        static std::string lastWhat;
        lastWhat = what + std::string(" at ") + std::string(file) + std::string(", line ") + toString(line);
        context->SetException(lastWhat.c_str());
        LOGERROR(what);
    }
    else
        throw Exception(what, file, line);
}
#endif

void checkAndRethrowException(const Exception& e)
{
    asIScriptContext* context = asGetActiveContext();
    if (context)
    {
        static std::string lastWhat;
        lastWhat = e.whatStr();
        context->SetException(lastWhat.c_str());
    }
    else
        throw e;
}
