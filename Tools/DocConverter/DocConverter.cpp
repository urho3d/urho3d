//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Context.h"
#include "File.h"
#include "FileSystem.h"
#include "List.h"
#include "ProcessUtils.h"
#include "StringUtils.h"

#include <cstdio>
#include <cstring>

#ifdef WIN32
#include <windows.h>
#endif

#include "DebugNew.h"

using namespace Urho3D;

SharedPtr<Context> context_(new Context());
SharedPtr<FileSystem> fileSystem_(new FileSystem(context_));
String inDir_;
String outDir_;
String mainPageName_;
Vector<String> pageNames_;

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);
void ScanPageNames(const String& fileName);
void ProcessFile(const String& fileName);
String AssembleString(const Vector<String>& tokens, unsigned startIndex);
void RemoveAutoLinks(String& line);
bool IsPageName(const String& str, unsigned startIndex, unsigned endIndex);
bool IsUpperCamelCase(const String& str, unsigned startIndex, unsigned endIndex);

#define OUTPUTLINE(line) { if (outputFile.IsOpen()) outputFile.WriteLine(line); }

int main(int argc, char** argv)
{
    Vector<String> arguments;
    
    #ifdef WIN32
    arguments = ParseArguments(GetCommandLineW());
    #else
    arguments = ParseArguments(argc, argv);
    #endif
    
    Run(arguments);
    return EXIT_SUCCESS;
}

void Run(const Vector<String>& arguments)
{
    if (arguments.Size() < 3)
    {
        ErrorExit(
            "Usage: DocConverter <dox input path> <wiki output path> <mainpage name>"
        );
    }
    
    inDir_ = AddTrailingSlash(arguments[0]);
    outDir_ = AddTrailingSlash(arguments[1]);
    mainPageName_ = arguments[2];
    
    if (!fileSystem_->DirExists(outDir_))
        ErrorExit("Wiki output path does not exist, conversion was skipped.");
    
    Vector<String> docFiles;
    fileSystem_->ScanDir(docFiles, inDir_, "*.dox", SCAN_FILES, false);
    
    pageNames_.Push(mainPageName_);
    for (unsigned i = 0; i < docFiles.Size(); ++i)
        ScanPageNames(inDir_ + docFiles[i]);
    
    for (unsigned i = 0; i < docFiles.Size(); ++i)
        ProcessFile(inDir_ + docFiles[i]);
}

void ScanPageNames(const String& fileName)
{
    PrintLine("Scanning document file " + fileName + " for page names");
    
    File inputFile(context_, fileName);
    
    String outputFileName;
    File outputFile(context_);
    
    if (!inputFile.IsOpen())
    {
        PrintLine("WARNING: Failed to open input file " + fileName + ", skipping");
        return;
    }
    
    while (!inputFile.IsEof())
    {
        String line = inputFile.ReadLine();
        Vector<String> tokens = line.Split(' ');
        
        if (line.StartsWith("\\page") && tokens.Size() > 1)
            pageNames_.Push(tokens[1]);
    }
}

void ProcessFile(const String& fileName)
{
    PrintLine("Processing document file " + fileName);
    
    File inputFile(context_, fileName);
    
    String outputFileName;
    File outputFile(context_);
    bool inVerbatim = false;
    
    if (!inputFile.IsOpen())
    {
        PrintLine("WARNING: Failed to open input file " + fileName + ", skipping");
        return;
    }
    
    while (!inputFile.IsEof())
    {
        String line = inputFile.ReadLine();
        
        if (!inVerbatim)
        {
            if (line.StartsWith("{") || line.StartsWith("}") || line.StartsWith("namespace") || line.StartsWith("/*") ||
                line.StartsWith("*/"))
                continue;
            
            line.Replace("%", "");
            
            // Handle escapes
            line.Replace("*", "\x060*\x060");
            if (line.Find("http") == String::NPOS)
                line.Replace("_", "\x060_\x060");
            line.Replace("[", "\x060[\x060");
            line.Replace("]", "\x060]\x060");
            line.Replace("&auml;", "\x0c3\x0a4");
            line.Replace("&ouml;", "\x0c3\x0b6");
            line.Replace("&Auml;", "\x0c3\x084");
            line.Replace("&Ouml;", "\x0c3\x096");
            line.Replace("\\n", "<br>");
            
            // Replace links
            for (;;)
            {
                unsigned refIndex = line.Find("\\ref");
                if (refIndex != String::NPOS)
                {
                    Vector<String> refTokens = line.Substring(refIndex).Split(' ');
                    if (refTokens.Size() > 1)
                    {
                        String refTarget = refTokens[1];
                        unsigned refTargetBegin = refIndex + 5;
                        unsigned refTargetEnd = line.Find(' ', refTargetBegin  + refTarget.Length());
                        if (refTarget.EndsWith("."))
                        {
                            refTarget = refTarget.Substring(0, refTarget.Length() - 1);
                            refTargetEnd--;
                        }
                        unsigned refBeginQuote = line.Find('\"', refTargetEnd);
                        unsigned refEndQuote = line.Find('\"', refBeginQuote+1);
                        
                        if (IsPageName(refTarget, 0, refTarget.Length()))
                        {
                            if (refBeginQuote != String::NPOS && refEndQuote != String::NPOS)
                                line = line.Substring(0, refIndex) + "[" + refTarget + " " + line.Substring(refBeginQuote + 1,
                                refEndQuote - refBeginQuote - 1) + "]" + line.Substring(refEndQuote + 1);
                            else
                                line = line.Substring(0, refIndex) + "[" + refTarget + "]" + line.Substring(refTargetEnd);
                        }
                        else
                        {
                            // If link is not a valid page name, just output the link body as is
                            if (refBeginQuote != String::NPOS && refEndQuote != String::NPOS)
                            {
                                line = line.Substring(0, refIndex) + line.Substring(refBeginQuote + 1,
                                refEndQuote - refBeginQuote - 1) + line.Substring(refEndQuote + 1);
                            }
                            else
                                line = line.Substring(0, refIndex) + line.Substring(refTargetBegin);
                        }
                    }
                    else
                    {
                        PrintLine("WARNING: \\ref tag which could not be handled on line " + line);
                        break;
                    }
                }
                else
                    break;
            }
            
            // Remove automatic wiki link generation from words that are not actual page names
            RemoveAutoLinks(line);
            
            Vector<String> tokens = line.Split(' ');
            
            // Check page and section transitions and handle markup conversion
            if (line.StartsWith("\\mainpage") && tokens.Size() > 1)
            {
                outputFileName = outDir_ + mainPageName_ + ".wiki";
                if (!outputFile.Open(outputFileName, FILE_WRITE))
                    PrintLine("WARNING: Failed to open output file " + outputFileName);
                OUTPUTLINE("#labels featured")
                OUTPUTLINE("= " + AssembleString(tokens, 1) + " =")
            }
            else if (line.StartsWith("\\page") && tokens.Size() > 1)
            {
                outputFileName = outDir_ + tokens[1] + ".wiki";
                if (!outputFile.Open(outputFileName, FILE_WRITE))
                    PrintLine("WARNING: Failed to open output file " + outputFileName);
                if (tokens.Size() > 2)
                    OUTPUTLINE("= " + AssembleString(tokens, 2) + " =")
                else
                    OUTPUTLINE("= " + tokens[1] + " =")
            }
            else if (line.StartsWith("\\section"))
            {
                if (tokens.Size() > 2)
                    OUTPUTLINE("== " + AssembleString(tokens, 2) + " ==")
                else
                    OUTPUTLINE("== " + tokens[1] + " ==")
            }
            else if (line.StartsWith("\\verbatim") || line.StartsWith("\\code"))
            {
                OUTPUTLINE("{{{")
                inVerbatim = true;
            }
            else if (line.StartsWith("- "))
                OUTPUTLINE(" * " + line.Substring(2))
            else if (line.StartsWith("  - "))
                OUTPUTLINE("   * " + line.Substring(4))
            else if (line.StartsWith("-# "))
                OUTPUTLINE(" * " + line.Substring(3))
            else
                OUTPUTLINE(line)
            
        }
        else
        {
            if (line.StartsWith("\\endverbatim") || line.StartsWith("\\endcode"))
            {
                outputFile.WriteLine("}}}");
                inVerbatim = false;
            }
            else
                outputFile.WriteLine(line);
        }
    }
}

String AssembleString(const Vector<String>& tokens, unsigned startIndex)
{
    String ret;
    
    for (unsigned i = startIndex; i < tokens.Size(); ++i)
    {
        if (i > startIndex)
            ret += ' ';
        ret += tokens[i];
    }
    
    return ret;
}

void RemoveAutoLinks(String& line)
{
    bool inLink = false;
    bool inWord = false;
    bool inWebLink = false;
    unsigned wordStart = 0;
    
    for (unsigned i = 0; i < line.Length(); ++i)
    {
        if (line[i] == '[')
        {
            inLink = true;
            continue;
        }
        else if (line[i] == ']')
        {
            inLink = false;
            continue;
        }
        
        if (line.Substring(i, 4) == "http")
        {
            inWebLink = true;
            i += 3;
            continue;
        }
        else if (inWebLink && !isalpha(line[i]) && !isdigit(line[i]) && line[i] != '/' && line[i] != ':' && line[i] != '-' &&
            line[i] != '_' && line[i] != '.')
            inWebLink = false;
            
        else if (!inLink && !inWebLink)
        {
            if (!inWord && isalpha(line[i]))
            {
                inWord = true;
                wordStart = i;
            }
            else if (inWord && !isalpha(line[i]) && !isdigit(line[i]))
            {
                inWord = false;
                unsigned wordEnd = i;
                if (!IsPageName(line, wordStart, wordEnd) && IsUpperCamelCase(line, wordStart, wordEnd))
                {
                    line.Insert(wordStart, '!');
                    ++i;
                }
            }
        }
    }
    if (inWord && !inLink && !inWebLink && !IsPageName(line, wordStart, line.Length()) && IsUpperCamelCase(line,
        wordStart, line.Length()))
    {
        line.Insert(wordStart, '!');
    }
}

bool IsPageName(const String& str, unsigned startIndex, unsigned endIndex)
{
    String word = str.Substring(startIndex, endIndex - startIndex);
  
    for (unsigned i = 0; i < pageNames_.Size(); ++i)
    {
        if (word == pageNames_[i])
            return true;
    }
    
    return false;
}

bool IsUpperCamelCase(const String& str, unsigned startIndex, unsigned endIndex)
{
    if (endIndex - startIndex < 2)
        return false;
    if (!isupper(str[startIndex]))
        return false;
    if (!islower(str[startIndex + 1]))
        return false;
    
    unsigned transitions = 1;
    
    for (unsigned i = startIndex + 2; i < endIndex - 1; ++i)
    {
        if (isupper(str[i]) && isupper(str[i+1]))
            return false;
        
        if (isupper(str[i]) && (islower(str[i+1]) || isdigit(str[i+1])))
        {
            ++transitions;
            ++i;
        }
    }
    
    return transitions > 1;
}
