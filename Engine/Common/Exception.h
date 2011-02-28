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

#ifndef COMMON_EXCEPTION_H
#define COMMON_EXCEPTION_H

#include <stdexcept>
#include <string>

#ifdef _DEBUG
#define EXCEPTION(what) throw Exception(what, __FILE__, __LINE__)
#define SAFE_EXCEPTION(what) { checkAndThrowException(what, __FILE__, __LINE__); return; }
#define SAFE_EXCEPTION_RET(what, ret) { checkAndThrowException(what, __FILE__, __LINE__); return ret; }
#else
#define EXCEPTION(what) (throw Exception(what))
#define SAFE_EXCEPTION(what) { checkAndThrowException(what); return; }
#define SAFE_EXCEPTION_RET(what, ret) { checkAndThrowException(what); return ret; }
#endif
#define SAFE_RETHROW(e) { checkAndRethrowException(e); return; }
#define SAFE_RETHROW_RET(e, ret) { checkAndRethrowException(e); return ret; }
#define TRY_SAFE_RETHROW(operation) try { operation; } catch (Exception& e) { checkAndRethrowException(e); return; }
#define TRY_CONSTRUCT(operation) try { return operation; } catch (Exception& e) { checkAndRethrowException(e); return 0; }

//! Urho3D exception class
class Exception : public std::exception
{
public:
    //! Construct with exception reason
    Exception(const std::string& what);
    //! Destruct
    virtual ~Exception() throw();
    #ifdef _DEBUG
    //! Construct with exception reason and location information
    Exception(const std::string& what, const char* file, int line);
    #endif
    
    //! Return exception reason
    const char* what() const throw();
    //! Return exception reason as string
    const std::string& whatStr() const throw() { return mWhat; }
    
private:
    //! Exception reason
    std::string mWhat;
};

//! Throw a script-safe exception (set a script exception instead of throwing if a script is running)
void checkAndThrowException(const std::string& what);
#ifdef _DEBUG
//! Throw a script-safe exception with location information
void checkAndThrowException(const std::string& what, const char* file, int line);
#endif
//! Rethrow an exception as script-safe
void checkAndRethrowException(const Exception& e);

#endif // COMMON_EXCEPTION_H
