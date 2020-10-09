//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Path.h"

namespace Urho3D
{

const Path Path::EMPTY{};



bool Path::IsAbsolute() const
{

    if (path_.Empty())
        return false;

    if (path_[0] == '/')
        return true;

#ifdef _WIN32
    if (path_.Length() > 1 && IsAlpha(path_[0]) && path_[1] == ':')
        return true;
#endif

    return false;
}

bool Path::IsRequestingParentDirectory() const
{
    // Min length is 2 "..", and "..weird_name.txt" does not go up a directory"
    return path_.Length() >= 2 && path_.StartsWith("..") && (path_.Length() == 2 || path_[2] =='/');
}

bool Path::IsExplicitlyRelative() const
{
    if (path_.Length() == 1)
        return path_.Front() == '.';
    else if (path_.Length() == 2)
        return path_[0] == '.' && (path_[1] == '.' || path_[1] == '/');
    else if (path_.Length() > 2)
        return path_[0] == '.' && (path_[1] == '/' || (path_[1] == '.' && path_[2] == '/'));

    return false;
}

Vector<Path> Path::SplitPathsStringStatic(const String& path, char separator, bool keepEmptyPaths)
{
    Vector<String> split = path.Split(separator,keepEmptyPaths);
    Vector<Path> paths;
    paths.Reserve(split.Size());
    for (auto& p : split)
    {
        paths.EmplaceBack(p);
        if (!keepEmptyPaths && paths.Back().Empty())
            paths.Pop();
    }
    return paths;
}

void Path::ResolveRelativeTo(const Path& basePath, bool requireRelativePrefix)
{
    // If this is an absolute path don't resolve it against the other
    if (IsAbsolute() || basePath.Empty())
    {
        CompressRelativePath();
        return;
    }

    // If we require the relative prefix then we
    if (requireRelativePrefix)
    {
        if (path_.Empty())
        {
            // We don't allow relative paths without the prefix, so just return the empty path
            return;
        }
        else if (path_[0] == '.')
        {
            if (path_.Length() == 1)
            {
                path_ = basePath.path_;
                // Base path has already been compressed
                return;
            }
            else if (path_[1] == '/')
            {
                path_ = basePath.GetDirectoryPath().path_ + path_.Substring(2);
                // Compress later
            }
            else if (path_[1] == '.')
            {
                if (path_.Length() == 2)
                {
                    if (basePath.HasTrailingSlash())
                    {
                        path_ = basePath.path_ + path_;
                        // Compress later
                    }
                    else
                    {
                        path_ = basePath.GetDirectoryPath().path_ + path_;
                        // Compress later
                    }
                }
                else if (path_[2] == '/')
                {
                    //Parse relative path from the basePath directory
                    if (basePath.path_.Empty())
                    {
                        // Compress Later
                    }
                    else if (basePath.HasTrailingSlash())
                    {
                        path_ = basePath.path_ + path_;
                        // Compress later
                    }
                    else
                    {
                        path_ = basePath.GetDirectoryPath().path_ + path_;
                        // Compress later
                    }
                }
                else
                {
                    // Relative is actually an absolute path that happens to begin with .. (e.g. "..odd_name/"
                    // Compress later
                }
            }
            else
            {
                // Relative is treated as an absolute path that happens to begin with . (e.g. ".cache/")
                // Compress later
            }
        }
        else
        {
            // Relative is treated an absolute path
            // Compress later
        }

    }
    else
    {
        path_ = basePath.GetParentPath().path_ + path_;
        // Compress later
    }

    CompressRelativePath();
}

void Path::Split(Path& pathName, String& fileName, String& extension, bool lowercaseExtension) const
{
    String fullPathCopy = GetInternalPathString();

    unsigned extPos = fullPathCopy.FindLast('.');
    unsigned pathPos = fullPathCopy.FindLast('/');

    if (extPos != String::NPOS && (pathPos == String::NPOS || extPos > pathPos))
    {
        extension = fullPathCopy.Substring(extPos);
        if (lowercaseExtension)
            extension = extension.ToLower();
        fullPathCopy = fullPathCopy.Substring(0, extPos);
    }
    else
        extension.Clear();

    pathPos = fullPathCopy.FindLast('/');
    if (pathPos != String::NPOS)
    {
        fileName = fullPathCopy.Substring(pathPos + 1);
        pathName = Path::CreateFromResolvedInternalString(fullPathCopy.Substring(0, pathPos + 1));
    }
    else
    {
        fileName = fullPathCopy;
        pathName = Path();
    }
}

Path Path::GetDirectoryPath() const
{
    // Shortcut if this is a directory path
    if (Empty() || HasTrailingSlash())
        return *this;

    Path path; String file, extension;
    Split(path, file, extension);
    return path;
}

String Path::GetFileName() const
{
    Path path; String file, extension;
    Split(path, file, extension);
    return file;
}

String Path::GetExtension(bool lowercaseExtension) const
{
    Path path; String file, extension;
    Split(path, file, extension, lowercaseExtension);
    return extension;
}

String Path::GetFileNameAndExtension(bool lowercaseExtension) const
{
    Path path; String file, extension;
    Split(path, file, extension, lowercaseExtension);
    return file + extension;
}

void Path::ReplaceExtension(const String& newExtension)
{
    Path path; String file, extension;
    Split(path, file, extension);
    path_ = path.path_ + file + newExtension;
}

Path Path::WithReplacedExtension(const String& newExtension) const
{
    Path p{*this};
    p.ReplaceExtension(newExtension);
    return p;
}

bool Path::HasTrailingSlash() const
{
    return !path_.Empty() && path_.Back() == '/';
}

void Path::AddTrailingSlash()
{
    if (!Empty() && !HasTrailingSlash())
        path_ += '/';
}

void Path::RemoveTrailingSlash()
{
    if (HasTrailingSlash())
        path_.Resize(path_.Length() - 1);
}

Path Path::WithTrailingSlash() const
{
    Path p{*this};
    p.AddTrailingSlash();
    return p;
}

Path Path::WithoutTrailingSlash() const
{
    Path p{*this};
    p.RemoveTrailingSlash();
    return p;
}

Path Path::GetParentPath() const
{
    // TODO: This should really be alot more complex
    // Checking for root directory (parent of root is root
    // if (!check.path_.EndsWith("..")), etc.
    Path check = WithoutTrailingSlash();
    unsigned pos = check.path_.FindLast('/');
    if (pos != String::NPOS)
        return CreateFromResolvedInternalString(check.path_.Substring(0, pos + 1));
    else
        return {};
}

WString Path::GetWideNativePathString() const
{
#ifdef _WIN32
    return WString(path_.Replaced('/', '\\'));
#else
    return WString(path_);
#endif
}

String Path::GetNativePathString() const
{
#ifdef _WIN32
    return String(path_.Replaced('/', '\\'));
#else
    return path_;
#endif
}

Path::NativeString Path::GetAutoNativePathString() const
{
#ifdef _WIN32
    return NativeString(path_.Replaced('/', '\\'));
#else
    return path_;
#endif
}

void Path::CompressRelativePath()
{
    // Very fast checks
    if (Empty() || path_ == ".")
        return;

    // Slightly slower huestic checks - may have false positive "relative" paths, no false negatives
    if (!path_.Contains("./") && !path_.EndsWith("..") && !path_.EndsWith("/."))
        return;

    bool wasExplicitlyRelative = IsExplicitlyRelative();
    bool hadTrailingSlash = HasTrailingSlash();

    Vector<String> paths = path_.Split('/', true);
    String ret;
    unsigned skip = 0;
    for (int i = paths.Size() - 1; i >= 0; --i)
        if (paths[i].Empty() || paths[i] == ".")
            continue;
        else if (paths[i] == "..")
            ++skip;
        else if (skip)
            --skip;
        else if (ret.Empty())
            ret = paths[i];
        else
            ret = paths[i] + "/" + ret;

    //NOTE: have elected to prepend ../../ ... according to the remaining skip count.
    //      This will mean CompressRelativePath("../../Texture.png") will return "../../Texture.png"

    for (int i = 0; i < skip; ++i)
        if (ret.Empty())
            ret = "..";
        else
            ret = "../" + ret;


    if (ret.Empty())
        path_ = ".";
    else
        path_ = ret;

    if (wasExplicitlyRelative && !IsExplicitlyRelative())
        path_ = "./" + path_;

    if (hadTrailingSlash && !HasTrailingSlash())
        path_ += "/";
}

String Path::MakePathStringInternal(const String& str)
{
    String ret = str.Trimmed();
    ret.Replace('\\', '/');
    return ret;
}

bool GLOBMatches(const Path& globPattern, const Path& path, GLOB_STAR_MODE mode)
{

}

}
