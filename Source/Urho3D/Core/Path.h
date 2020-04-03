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
	Path& operator=(const Path& other)=default;
	/// Move construct.
	Path(Path&& other): path_(std::move(other.path_)) {}
	/// Construct from the specified path string using the specified base path to resolve relative directories as needed.
	Path(const String& path, const Path& basePath = Path()): path_(MakePathStringInternal(path)) { ResolveRelativeTo(basePath); }
	/// Construct from the specified path string using the specified base path to resolve relative directories as needed.
	Path(const char* path, const Path& basePath = Path()): path_(MakePathStringInternal(path)) { ResolveRelativeTo(basePath); }

	/// Construct from the specified path string when the string is known not to contain self-resolvable relative components ("./" or "resolvable/../") and known to be in the internal representation
	static Path CreateFromResolvedInternalString(const String& path) { Path p; p.path_ = path; return p; }
	//TODO: ^ Consider renaming the above CreateFromRawString or the like so it's shorter


	//TODO: Wide strings
	/// Convert a path to the format required by the operating system in wide characters.
//	WPath GetWideNativePath();

	/// Raw appending to this path with the other path. "A/B" += "C/D.file" --> "A/BC/D.file"
	Path& operator+= (const Path& rhs)
	{
		path_ += rhs.path_;
		return *this;
	}
	/// Smart appending to this path with the other path.  "A/B" /= "C/D.file" --> "A/B/C/D.file" ; "A/B/" / "C/D.file" --> "A/B/C/D.file"
	Path& operator/= (const Path& rhs)
	{
		path_ += "/" + rhs.path_;
		path_.Replace("//","/");
		return *this;
	}

	/// Raw concatenation to this path with the other path. "A/B" + "C/D.file" --> "A/BC/D.file"
	Path operator+ (const Path& rhs) const
	{
		Path p{*this};
		p+=rhs;
		return p;
	}
	/// Smart concatenation to this path with the other path.  "A/B.ext" / "C/D.file" --> "A/B.ext/C/D.file" ; "A/B/" / "C/D.file" --> "A/B/C/D.file"
	Path operator/ (const Path& rhs) const
	{
		Path p{*this};
		p/=rhs;
		return p;
	}


	/// Return whether a path is absolute (starts with "/" on Unix or "[letter]:" on Windows)
	bool IsAbsolute() const
	{

		if (pathName.Empty())
			return false;

		String path = GetInternalPath(pathName);

		if (path[0] == '/')
			return true;

		#ifdef _WIN32
			if (path.Length() > 1 && IsAlpha(path[0]) && path[1] == ':')
				return true;
		#endif

			return false;
	}
	/// Returns true if the path is empty
	bool IsEmpty() const
	{
		return path_.Empty();
	}


	/// Resolves relative paths agains the base path. The base path may be a file, whose name will be trimmed, or a directory that must end in '/'.
	/// If requireRelativePrefix is true relative paths will only be resolved if they begin with './' or '../'.
	void ResolveRelativeTo(const Path& basePath, bool requireRelativePrefix = true)
	{
		// If this is an absolute path don't resolve it against the other
		if (IsAbsolute() || basePath.IsEmpty())
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


	/// Split a full path to path, filename and extension. The extension will be converted to lowercase by default.
	void Split(Path& pathName, String& fileName, String& extension, bool lowercaseExtension = true) const
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

	/// Return the path from a full path.
	Path GetDirectoryPath() const
	{
		// Shortcut if this is a directory path
		if (IsEmpty() || HasTrailingSlash())
			return *this;

		Path path; String file, extension;
		SplitPath(path, file, extension);
		return path;
	}
	/// Return the filename from a full path.
	String GetFileName() const
	{
		Path path; String file, extension;
		SplitPath(path, file, extension);
		return file;
	}
	/// Return the extension from a full path, converted to lowercase by default.
	String GetExtension(bool lowercaseExtension = true) const
	{
		Path path; String file, extension;
		SplitPath(path, file, extension, lowercaseExtension);
		return extension;
	}
	/// Return the filename and extension from a full path. The case of the extension is preserved by default, so that the file can be opened in case-sensitive operating systems.
	String GetFileNameAndExtension(String& fileName, bool lowercaseExtension = false) const
	{
		Path path; String file, extension;
		SplitPath(path, file, extension, lowercaseExtension);
		return file + extension;
	}

	/// Replace the extension of a file name with another.
	void ReplaceExtension(const String& newExtension)
	{
		Path path; String file, extension;
		SplitPath(path, file, extension);
		return Path::CreateFromResolvedInternalString(path + file + newExtension);
	}
	/// Copy and replace the extension of a file name with another.
	Path WithReplacedExtension(const String& newExtension) const
	{
		Path p{*this};
		p.ReplaceExtension(newExtension);
		return p;
	}

	/// Returns true if the path has a traling slash.
	bool HasTrailingSlash() const
	{
		return !path_.Empty() || path_.Back() == '/';
	}
	/// Add a slash at the end of the path if missing. Does not add a slash to an empty path.
	void AddTrailingSlash()
	{
		if (!IsEmpty() && !HasTrailingSlash())
			path_ += '/';
	}
	/// Remove the slash from the end of a path if it exists.
	void RemoveTrailingSlash()
	{
		if (HasTrailingSlash())
			path_.Resize(path_.Length() - 1);
	}
	/// Add a slash at the end of the path if missing and convert to internal format (use slashes).
	Path WithTrailingSlash() const
	{
		Path p{*this};
		p.WithTrailingSlash();
		return p;
	}
	/// Remove the slash from the end of a path if exists and convert to internal format (use slashes).
	Path WithoutTrailingSlash() const
	{
		Path p{*this};
		p.WithoutTrailingSlash();
		return p;
	}

	/// Return the parent path, or the path itself if not available.
	Path GetParentPath() const
	{
		unsigned pos = String.FindLast('/');
		if (pos != String::NPOS)
			return path.Substring(0, pos + 1);
		else
			return String();
	}

	/// Convert a path to internal format (use slashes).
	String GetInternalPathString() const;
	/// Convert a path to the format required by the operating system.
	String GetNativePathString() const;

	/// Convert a path to a string.
	String ToString() const { return GetInternalPathString(); }


private:

	/// The path.
	String path_;
	// TODO: UniquePtr Memo of the split path file extension and such, if such info was requested?


	static String MakePathStringInternal(const String& str)
	{
		String ret = str.Trimmed();
		ret.Replace('\\', '/');
		return ret;
	}


	void CompressRelativePath()
	{
		// Very fast checks
		if (IsEmpty() || path_ == ".")
			return;

		// Slightly slower huestic checks - may have false positive "relative" paths, no false negatives
		if (!path_.Contains("./") && !path_.EndsWith("..") && !path_.EndsWith("/."))
			return;

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
			ret = "../" + ret;

		if (ret.Empty())
			path_ = ".";
		else
			path_ = ret;
	}
};

}
