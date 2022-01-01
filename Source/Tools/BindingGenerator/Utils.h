//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include <string>
#include <vector>
#include <algorithm>

#define CONTAINS(vec, val) (std::find(vec.begin(), vec.end(), val) != vec.end())

std::string Trim(const std::string& str);
bool StartsWith(const std::string& str, const std::string& value);
bool EndsWith(const std::string& str, const std::string& value);
std::string CutStart(const std::string& str, const std::string& value);
std::string CutEnd(const std::string& str, const std::string& value);
std::string GetFirstWord(const std::string& str);

std::string ReplaceAll(const std::string& src, const std::string& from, const std::string& to);
std::string RemoveAll(const std::string& src, const std::string& value);
std::string ReplaceFirst(const std::string& src, const std::string& from, const std::string& to);
std::string RemoveFirst(const std::string& src, const std::string& value);
std::vector<std::string> Split(const std::string& str, char delim);
std::vector<std::string> Split(const std::string& str, const std::string& delim);
std::string Join(const std::vector<std::string>& values, const std::string& separator);

bool Contains(const std::string& str, const std::string& substr);
bool Contains(const std::string& str, char c);

// Return all after last found substring
std::string CutToLast(const std::string& src, const std::string& value, bool inclusive);

// Return all after last /
std::string GetFileName(const std::string& path);

// Return all before last /
std::string WithoutFileName(const std::string& path);

// First letter to lower case. Works only for ASCII
std::string FirstCharToLower(const std::string& str);

std::string JoinNonEmpty(const std::vector<std::string>& strings, const std::string& separator);

std::string ToIdentifier(const std::string& str);
