#pragma once

#include "../Container/Str.h"

namespace Urho3D {

/// Class that represents a path to a file.
class URHO3D_API Path
{
public:
	/// Construct empty path.
	Path()=default;
	/// Copy construct.
	Path(const Path& other)=default;
	/// Copy.
    Path& operator =(const Path& other)=default;
	/// Move construct.
	Path(Path&& other): path_(std::move(other.path_)) {}
	/// Construct from the specified path string using the specified base path to resolve relative directories as needed.
    Path(const String& path, const Path& basePath = Path::EMPTY): path_(MakePathStringInternal(path)) { ResolveRelativeTo(basePath); }
	/// Construct from the specified path string using the specified base path to resolve relative directories as needed.
    Path(const char* path, const Path& basePath = Path::EMPTY): path_(MakePathStringInternal(path)) { ResolveRelativeTo(basePath); }
    /// Construct from the specified wide path string using the specified base path to resolve relative directories as needed.
    Path(const wchar_t* path, const Path& basePath = Path::EMPTY): path_(MakePathStringInternal(String(path))) { ResolveRelativeTo(basePath); }

	/// Construct from the specified path string when the string is known not to contain self-resolvable relative components ("./" or "resolvable/../") and known to be in the internal representation
	static Path CreateFromResolvedInternalString(const String& path) { Path p; p.path_ = path; return p; }
	//TODO: ^ Consider renaming the above CreateFromRawString or the like so it's shorter

	/// Raw appending to this path with the other path. "A/B" += "C/D.file" --> "A/BC/D.file"
    Path& operator +=(const Path& rhs)
	{
		path_ += rhs.path_;
		return *this;
	}
	/// Smart appending to this path with the other path.  "A/B" /= "C/D.file" --> "A/B/C/D.file" ; "A/B/" / "C/D.file" --> "A/B/C/D.file"
    Path& operator /=(const Path& rhs)
	{
		path_ += "/" + rhs.path_;
		path_.Replace("//","/");
		return *this;
	}

	/// Raw concatenation to this path with the other path. "A/B" + "C/D.file" --> "A/BC/D.file"
    Path operator +(const Path& rhs) const
	{
		Path p{*this};
		p+=rhs;
		return p;
	}
	/// Smart concatenation to this path with the other path.  "A/B.ext" / "C/D.file" --> "A/B.ext/C/D.file" ; "A/B/" / "C/D.file" --> "A/B/C/D.file"
    Path operator /(const Path& rhs) const
	{
		Path p{*this};
		p/=rhs;
		return p;
	}

    /// Raw concatenation to this path with the other path. "A/B" + "C/D.file" --> "A/BC/D.file"
    friend Path operator +(const String& lhs, const Path& rhs)
    {
        Path p{rhs};
        p.path_ = lhs + p.path_;
        return p;
    }
    /// Smart concatenation to this path with the other path.  "A/B.ext" / "C/D.file" --> "A/B.ext/C/D.file" ; "A/B/" / "C/D.file" --> "A/B/C/D.file"
    friend Path operator /(const String& lhs, const Path& rhs)
    {
        return Path{lhs} / rhs;
    }


    /// Case-sensitive equality test with the other past based on the internal path format.
    bool operator ==(const Path& rhs) const
    {
        return path_ == rhs.path_;
    }

    /// Case-sensitive inequality test with the other past based on the internal path format.
    bool operator !=(const Path& rhs) const
    {
        return path_ != rhs.path_;
    }

	/// Return whether a path is absolute (starts with "/" on Unix or "[letter]:" on Windows)
    bool IsAbsolute() const;

    /// Returns true if the path would go up a directory ("../" or "..")
    bool IsRequestingParentDirectory() const;

    /// Returns true if the path is explicitly relative (starts with "./" or "../")
    bool IsExplicitlyRelative() const;

	/// Returns true if the path is empty
    bool Empty() const
	{
		return path_.Empty();
	}
    /// Returns the length of the string
    unsigned Length() const
    {
        return path_.Length();
    }
    /// Makes the path empty.
    void Clear()
    {
        path_.Clear();
    }
    /// Return comparison result between two paths, optionally case insensitive.
    int Compare(const Path& rhs, bool caseSensitive = true) const
    {
        return path_.Compare(rhs.path_, caseSensitive);
    }

    //    /// Returns the number of segments in the path separated by "/". Trailing empty string is not counted.
    //    unsigned NumberOfSegments
    //    {
    //        return path_.Count('/') - HasTrailingSlash();
    //    }


    /// Splits the given path using the specified separator character, optionally preserving empty paths.
    static Vector<Path> SplitPathsStringStatic(const String& path, char separator = ';', bool keepEmptyPaths = false);

    /// Splits the path using the specified separator character, optionally preserving empty paths.
    Vector<Path> SplitPaths(char separator = ';', bool keepEmptyPaths = false) const
    {
        return SplitPathsStringStatic(path_);
    }


	/// Resolves relative paths agains the base path. The base path may be a file, whose name will be trimmed, or a directory that must end in '/'.
	/// If requireRelativePrefix is true relative paths will only be resolved if they begin with './' or '../'.
    void ResolveRelativeTo(const Path& basePath, bool requireRelativePrefix = true);

	/// Split a full path to path, filename and extension. The extension will be converted to lowercase by default.
    void Split(Path& pathName, String& fileName, String& extension, bool lowercaseExtension = true) const;

	/// Return the path from a full path.
    Path GetDirectoryPath() const;
	/// Return the filename from a full path.
    String GetFileName() const;
	/// Return the extension from a full path, converted to lowercase by default.
    String GetExtension(bool lowercaseExtension = true) const;
	/// Return the filename and extension from a full path. The case of the extension is preserved by default, so that the file can be opened in case-sensitive operating systems.
    String GetFileNameAndExtension(bool lowercaseExtension = false) const;

	/// Replace the extension of a file name with another.
    void ReplaceExtension(const String& newExtension);
	/// Copy and replace the extension of a file name with another.
    Path WithReplacedExtension(const String& newExtension) const;

	/// Returns true if the path has a traling slash.
    bool HasTrailingSlash() const;

	/// Add a slash at the end of the path if missing. Does not add a slash to an empty path.
    void AddTrailingSlash();
	/// Remove the slash from the end of a path if it exists.
    void RemoveTrailingSlash();

    /// Copy and add a slash at the end of the path if missing and convert to internal format (use slashes).
    Path WithTrailingSlash() const;
    /// Copy and remove the slash from the end of a path if exists and convert to internal format (use slashes).
    Path WithoutTrailingSlash() const;

	/// Return the parent path, or the path itself if not available.
    Path GetParentPath() const;

	/// Convert a path to internal format (use slashes).
    const String& GetInternalPathString() const
	{
		return path_;
    }


	//Question: Why doesn't GetNativePathString() just return a WString on Windows?
	// I believe the only time we don't just convert to a WString after that on Windows is in
	//		int DoSystemRun(const String& fileName, const Vector<String>& arguments)
	// in which I would be fine with having to move fixedFileName into the #ifdef code
	// One more in bool LuaScript::LoadRawFile(const String& fileName)
	// which should probably be re-written using luaL_loadbuffer instead of luaL_loadfile
	// Another couple for Image:
	//      return stbi_write_tga(GetNativePath(fileName).CString(), width_, height_, components_, data_.Get()) != 0;
	//      return stbi_write_jpg(GetNativePath(fileName).CString(), width_, height_, components_, data_.Get(), quality) != 0;
	// As such I support switching to a [W]String GetNativePathString()
	//									String GetNativePathStringNarrow() that can hopefully be removed in the future.
	// This may sound unreasonable, but if you check stb_image_write.h, we might as well just make it use a wide character string instead
    //    static int stbi__start_write_file(stbi__write_context *s, const char *filename)
    //    {
    //       FILE *f;
    //       // Urho3D: proper UTF8 handling for Windows, requires Urho3D WString class
    //    #ifndef _WIN32
    //       f = fopen(filename, "wb");
    //    #else
    //       Urho3D::WString wstr(filename);
    //    #ifdef STBI_MSC_SECURE_CRT
    //       if (_wfopen_s(&f, wstr.CString(), L"wb")   // NOTE: This line doesn't even match parentheses
    //          f = NULL;
    //    #else
    //       f = _wfopen(wstr.CString(), L"wb");
    //    #endif
    // It may be better to preserve the stb API, though, in case the user has other code that use it


    /// Convert a path to the wide character string format required by the operating system.
    WString GetWideNativePathString() const;

    /// Convert a path to the string format required by the operating system.
    String GetNativePathString() const;


    // TODO: Evaluate AutoNativePathString
#ifdef _WIN32
	using NativeString = WString;
#else
	using NativeString = const String&;
#endif
    /// Convert a path to the string format required by the operating system with platform-dependent character width.
    NativeString GetAutoNativePathString() const;

	/// Convert a path to a string.
	const String& ToString() const { return GetInternalPathString(); }

    /// Return hash value for HashSet & HashMap.
    unsigned ToHash() const { return GetInternalPathString().ToHash(); }

#ifdef URHO3D_PATH_BACKWARDS_COMPATABILITY
    /// DEPRECATED: Returns the char* representation of the path. Provided only for backwards compatibility.
    URHO3D_DEPRECATED
    const char* CString() const { return path_.CString(); }

    /// DEPRECATED: Implicit conversion to string
    URHO3D_DEPRECATED
    operator String() const { return path_; }

    /// DEPRECATED: Removal of operator String() should eliminate the need for this. Raw concatenation to this path with a string. "A/B" + "../C/D.file" --> "A/B../C/D.file"
    URHO3D_DEPRECATED Path operator +(const String& rhs) const
    {
        return *this + CreateFromResolvedInternalString(rhs);
    }
    /// DEPRECATED: Removal of operator String() should eliminate the need for this. Raw String to this path with the other path. "A/B" += ../C/D.file" --> "A/B../C/D.file"
    URHO3D_DEPRECATED Path& operator +=(const String& rhs)
    {
        path_ += rhs;
        return *this;
    }
    /// DEPRECATED: Removal of operator String() should eliminate the need for this. Raw concatenation to this path with a string. "A/B" + "../C/D.file" --> "A/B../C/D.file"
    URHO3D_DEPRECATED Path operator +(const char* rhs) const
    {
        return *this + CreateFromResolvedInternalString(rhs);
    }
    /// DEPRECATED: Removal of operator String() should eliminate the need for this. Raw String to this path with the other path. "A/B" += ../C/D.file" --> "A/B../C/D.file"
    URHO3D_DEPRECATED Path& operator +=(const char* rhs)
    {
        path_ += rhs;
        return *this;
    }
    /// DEPRECATED: Removal of operator String() should eliminate the need for this. Raw concatenation to this path with the other path. "A/B" + "C/D.file" --> "A/BC/D.file"
    URHO3D_DEPRECATED friend Path operator +(const char* lhs, const Path& rhs)
    {
        Path p{rhs};
        p.path_ = lhs + p.path_;
        return p;
    }
    /// DEPRECATED: Removal of operator String() should eliminate the need for this. Smart concatenation to this path with the other path.  "A/B.ext" / "C/D.file" --> "A/B.ext/C/D.file" ; "A/B/" / "C/D.file" --> "A/B/C/D.file"
    URHO3D_DEPRECATED friend Path operator /(const char* lhs, const Path& rhs)
    {
        return Path{lhs} / rhs;
    }
#endif

    /// Empty path.
    static const Path EMPTY;

private:
    /// Moves all relative path segments to the front of the path (e.g. "A/../../" --> "../"
    void CompressRelativePath();

    /// Trims and converts the string to the internal format (forward slashes).
    static String MakePathStringInternal(const String& str);

	/// The path.
	String path_;

	// TODO: UniquePtr Memo of the split path file extension and such, if such info was requested?
    //      Would mean that sizeof(Path) != sizeof(String)

};

/// Enum controlling the behavior of the GLOB Matching
enum GLOB_STAR_MODE
{
    /// "*" will match "/"
    GS_REQUIRE_SINGLE_STAR,
    /// "**" will match "/", "*" will not
    GS_REQUIRE_DOUBLE_STAR,
    /// "/" will not be matched
    GS_DISABLE_RECURSION
};

/// Test a path against the specified GLOB pattern path. Returns true for a match.
URHO3D_API bool GLOBMatches(const Path& globPattern, const Path& path, GLOB_STAR_MODE mode = GLOB_STAR_MODE::GS_REQUIRE_DOUBLE_STAR);

}
