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

#include "Utils.h"

#include <cassert>
#include <sstream>

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
