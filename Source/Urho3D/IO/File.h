//
// Copyright (c) 2008-2017 the Urho3D project.
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

#include "../Container/ArrayPtr.h"
#include "../Core/Object.h"
#include "../IO/AbstractFile.h"

namespace Urho3D
{

/// File open mode.
enum FileMode
{
    FILE_READ = 0,
    FILE_WRITE,
    FILE_READWRITE
};

class FileSource;

/// Base class for files, physical or archived.
class URHO3D_API File : public Object, public AbstractFile
{
    URHO3D_OBJECT(File, Object);

public:
    /// Construct.
    File(Context* context);
    //TODO: Should these be for derived class to implement? What is Constructor call order? Base Initilization->Derived Init-> Base Function->Derived function?
    /// Construct and open a filesystem file.
    File(Context* context, const String& fileName, FileMode mode = FILE_READ);
    /// Construct and open from a package file.
    File(Context* context, FileSource* source, const String& fileName, FileMode mode = FILE_READ);
    /// Destruct. Derived class must close the file if open.
    virtual ~File() override { }

    /* From Deserializer
    /// Read bytes from the stream. Return number of bytes actually read.
    virtual unsigned Read(void* dest, unsigned size) = 0;
    /// Set position from the beginning of the stream. Return actual new position.
    virtual unsigned Seek(unsigned position) = 0;
    /// Return a checksum if applicable.
    virtual unsigned GetChecksum();
    /// Return whether the end of stream has been reached.
    virtual bool IsEof() const { return position_ >= size_; } */

    /// Return name of the stream.
    virtual const String& GetName() const override { return fileName_; }


    // File Specific things
    /// Open a file with the default FileSource for this file kind of file, as registered in the resource cache. Return true if successful.
    virtual bool Open(const String& fileName, FileMode mode = FILE_READ);
    /// Open from within a given file source. Return true if successful. FileModes beyond FILE_READ may not be supported.
    virtual bool Open(FileSource* source, const String& fileName, FileMode mode = FILE_READ) = 0;
    /// Close the file.
    virtual void Close() = 0;
    /// Flush any buffered output to the file.
    virtual void Flush() = 0;
    /// Return whether is open.
    virtual bool IsOpen() const = 0;
    /// Return a derived-class determined file handle, if appropriate.
    virtual void* GetHandle() const { return nullptr; }

    /// Change the file name. Used by the resource system.
    void SetName(const String& name);
    /// Return the open mode.
    FileMode GetMode() const { return mode_; }

    /// Returns the file's FileSource

protected:
    /// File name.
    String fileName_;
    /// Open mode.
    FileMode mode_;
};

}
