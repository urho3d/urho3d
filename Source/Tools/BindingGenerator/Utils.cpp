// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "Utils.h"

#include <cassert>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

using namespace std;

string Trim(const string& str)
{
    size_t trimStart = 0;
    size_t trimEnd = str.length();

    while (trimStart < trimEnd)
    {
        char c = str.c_str()[trimStart];
        if (c != ' ' && c != 9)
            break;
        ++trimStart;
    }

    while (trimEnd > trimStart)
    {
        char c = str.c_str()[trimEnd - 1];
        if (c != ' ' && c != 9)
            break;
        --trimEnd;
    }

    return str.substr(trimStart, trimEnd - trimStart);
}

string GetFileName(const string& path)
{
    size_t pos = path.find_last_of("/");
    assert(pos != string::npos);
    return path.substr(pos + 1);
}

string CutToLast(const string& src, const string& value, bool inclusive)
{
    size_t pos = src.find_last_of(value);

    if (pos == string::npos)
        return src;

    if (inclusive)
        return src.substr(pos + 1);

    return src.substr(pos + 1 - value.length());
}

string WithoutFileName(const string& path)
{
    size_t pos = path.find_last_of("/");
    assert(pos != string::npos);
    return path.substr(0, pos);
}

bool StartsWith(const string& str, const string& value)
{
    return str.rfind(value, 0) == 0;
}

bool EndsWith(const string& str, const string& value)
{
    if (value.size() > str.size())
        return false;

    return equal(value.rbegin(), value.rend(), str.rbegin());
}

string GetFirstWord(const string& str)
{
    size_t pos = str.find(' ');

    if (pos == string::npos)
        return str;

    return str.substr(0, pos);
}

string ReplaceAll(const string& src, const string& from, const string& to)
{
    string ret;

    size_t lastPos = 0;
    size_t findPos = src.find(from, lastPos);

    while (findPos != string::npos)
    {
        ret.append(src, lastPos, findPos - lastPos);
        ret += to;
        lastPos = findPos + from.length();
        findPos = src.find(from, lastPos);
    }

    ret += src.substr(lastPos);

    return ret;
}

string RemoveAll(const string& src, const string& value)
{
    return ReplaceAll(src, value, "");
}

string ReplaceFirst(const string& src, const string& from, const string& to)
{
    size_t findPos = src.find(from, 0);

    if (findPos == string::npos)
        return src;

    return src.substr(0, findPos) + to + src.substr(findPos + from.length());
}

string RemoveFirst(const string& src, const string& value)
{
    size_t findPos = src.find(value, 0);

    if (findPos == string::npos)
        return src;

    return src.substr(0, findPos) + src.substr(findPos + value.length());
}

vector<string> Split(const string& str, char delim)
{
    stringstream ss(str);
    string item;
    vector<string> result;

    while (getline(ss, item, delim))
        result.push_back(move(item));

    return result;
}

vector<string> Split(const string& str, const string& delim)
{
    vector<string> result;
    size_t lastPos = 0;
    size_t findPos = str.find(delim, lastPos);

    while (findPos != string::npos)
    {
        result.push_back(str.substr(lastPos, findPos - lastPos));
        lastPos = findPos + delim.length();
        findPos = str.find(delim, lastPos);
    }

    result.push_back(str.substr(lastPos));

    return result;
}

string CutStart(const string& str, const string& value)
{
    if (!StartsWith(str, value))
        return str;

    return str.substr(value.length());
}

string CutEnd(const string& str, const string& value)
{
    if (!EndsWith(str, value))
        return str;

    return str.substr(0, str.length() - value.length());
}

bool Contains(const string& str, const string& substr)
{
    return str.find(substr) != string::npos;
}

bool Contains(const string& str, char c)
{
    return str.find(c) != string::npos;
}

string FirstCharToLower(const string& str)
{
    if (str.empty())
        return str;

    string result = str;
    result[0] = tolower(str[0]);

    return result;
}

string Join(const vector<string>& values, const string& separator)
{
    string result;

    for (const string& value : values)
    {
        if (!result.empty())
            result += separator;

        result += value;
    }

    return result;
}

string JoinNonEmpty(const vector<string>& strings, const string& separator)
{
    string result;

    for (const string& str : strings)
    {
        if (str.empty())
            continue;

        if (!result.empty())
            result += separator;

        result += str;
    }

    return result;
}

string ToIdentifier(const string& str)
{
    string result = ReplaceAll(str, ", ", "_comma_");
    result = ReplaceAll(result, "<", "_leftAngleBracket_");
    result = ReplaceAll(result, ">", "_rightAngleBracket_");
    return result;
}

static string RemoveTrailingSlash(const string& pathName)
{
    string ret = Trim(pathName);
    ret = ReplaceAll(ret, "\\", "/");
    ret = CutEnd(ret, "/");
    return ret;
}

static string GetParentPath(const string& path)
{
    size_t pos = RemoveTrailingSlash(path).find_last_of("/");

    if (pos != string::npos)
        return path.substr(0, pos + 1);
    else
        return string();
}

// setlocale(LC_ALL, "en_US.utf8") is required
wstring ToWide(const string& multi)
{
    std::wstring ret;
    wchar_t w;
    mbstate_t mb{};

    size_t n = 0;
    size_t len = multi.length() + 1;

    while (size_t res = mbrtowc(&w, multi.c_str() + n, len - n, &mb))
    {
        if (res == static_cast<size_t>(-1) || res == static_cast<size_t>(-2))
            throw "Invalid encoding";

        n += res;
        ret += w;
    }

    return ret;
}

bool DirExists(const string& pathName)
{
#ifndef _WIN32
    // Always return true for the root directory
    if (pathName == "/")
        return true;
#endif

    string fixedName = RemoveTrailingSlash(pathName);

#ifdef _WIN32
    DWORD attributes = GetFileAttributesW(ToWide(fixedName).c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES || !(attributes & FILE_ATTRIBUTE_DIRECTORY))
        return false;
#else
    struct stat st {};
    if (stat(fixedName.c_str(), &st) || !(st.st_mode & S_IFDIR))
        return false;
#endif

    return true;
}

bool CreateDir(const string& pathName)
{
    // Create each of the parents if necessary
    string parentPath = GetParentPath(pathName);
    if (parentPath.length() > 1 && !DirExists(parentPath))
    {
        if (!CreateDir(parentPath))
            return false;
    }

#ifdef _WIN32
    bool success = (CreateDirectoryW(ToWide(RemoveTrailingSlash(pathName)).c_str(), nullptr) == TRUE) ||
        (GetLastError() == ERROR_ALREADY_EXISTS);
#else
    bool success = mkdir(RemoveTrailingSlash(pathName).c_str(), S_IRWXU) == 0 || errno == EEXIST;
#endif

    return success;
}
