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

#pragma once

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define CONTAINS(vec, val) (find(vec.begin(), vec.end(), val) != vec.end())

string Trim(const string& str);
bool StartsWith(const string& str, const string& value);
bool EndsWith(const string& str, const string& value);
string CutStart(const string& str, const string& value);
string CutEnd(const string& str, const string& value);
string GetFirstWord(const string& str);

string ReplaceAll(const string& src, const string& from, const string& to);
string RemoveAll(const string& src, const string& value);
string ReplaceFirst(const string& src, const string& from, const string& to);
string RemoveFirst(const string& src, const string& value);
vector<string> Split(const string& str, char delim);
vector<string> Split(const string& str, const string& delim);
string Join(const vector<string>& values, const string& separator);
bool Contains(const string& str, const string& substr);

// Return all after last found substring
string CutToLast(const string& src, const string& value, bool inclusive);

// Return all after last /
string GetFileName(const string& path);

// Return all before last /
string WithoutFileName(const string& path);

// First letter to lower case. Works only for ASCII
string FirstCharToLower(const string& str);

string GetLastErrorMessage();
void SetLastErrorMessage(const string& message);

string JoinNonEmpty(const vector<string>& strings, const string& separator);

string ToIdentifier(const string& str);
