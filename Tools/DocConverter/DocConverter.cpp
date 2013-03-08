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

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);
void ProcessFile(const String& fileName);
String AssembleString(const Vector<String>& tokens, unsigned startIndex);

int main(int argc, char** argv)
{
    Vector<String> arguments;
    
    #ifdef WIN32
    arguments = ParseArguments(GetCommandLineW());
    #else
    arguments = ParseArguments(argc, argv);
    #endif
    
    Run(arguments);
    return 0;
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
    
    Vector<String> docFiles;
    fileSystem_->ScanDir(docFiles, inDir_, "*.dox", SCAN_FILES, false);
    for (unsigned i = 0; i < docFiles.Size(); ++i)
        ProcessFile(inDir_ + docFiles[i]);
}

void ProcessFile(const String& fileName)
{
    PrintUnicodeLine("Processing document file " + fileName);
    
    File inputFile(context_, fileName);
    
    String outputFileName;
    File outputFile(context_);
    bool inVerbatim = false;
    
    if (!inputFile.IsOpen())
    {
        PrintUnicodeLine("WARNING: Failed to open input file " + fileName + ", skipping");
        return;
    }
    
    while (!inputFile.IsEof())
    {
        String line = inputFile.ReadLine();
        line.Replace("%", "");
        Vector<String> tokens = line.Split(' ');
        
        if (!inVerbatim)
        {
            // Replace links
            for (;;)
            {
                unsigned refIndex = line.Find("\\ref");
                if (refIndex != String::NPOS)
                {
                    //PrintUnicodeLine("Handling \\ref on line " + line);
                    Vector<String> refTokens = line.Substring(refIndex).Split(' ');
                    if (refTokens.Size() > 1)
                    {
                        String refTarget = refTokens[1];
                        unsigned refTargetEnd = line.Find(' ', refIndex + 5 + refTarget.Length());
                        if (refTarget.EndsWith("."))
                        {
                            refTarget = refTarget.Substring(0, refTarget.Length() - 1);
                            refTargetEnd--;
                        }
                        unsigned refBeginQuote = line.Find('\"', refTargetEnd);
                        unsigned refEndQuote = line.Find('\"', refBeginQuote+1);
                        if (refTarget.Find("::") == String::NPOS)
                        {
                            if (refBeginQuote != String::NPOS && refEndQuote != String::NPOS)
                                line = line.Substring(0, refIndex) + "[" + refTarget + " " + line.Substring(refBeginQuote + 1, refEndQuote - refBeginQuote - 1) + "]" + line.Substring(refEndQuote + 1);
                            else
                                line = line.Substring(0, refIndex) + "[" + refTarget + "]" + line.Substring(refTargetEnd);
                        }
                        else
                        {
                            String refClass = refTarget.Substring(0, refTarget.Find("::"));
                            line = line.Substring(0, refIndex) + line.Substring(refBeginQuote + 1, refEndQuote - refBeginQuote - 1) + line.Substring(refEndQuote + 1);
                        }
                    }
                    else
                    {
                        PrintUnicodeLine("WARNING: \\ref tag which could not be handled");
                        break;
                    }
                    
                    //PrintUnicodeLine("Line after ref handling: " + line);
                }
                else
                    break;
            }
            
            if (line.StartsWith("\\mainpage") && tokens.Size() > 1)
            {
                outputFileName = outDir_ + mainPageName_ + ".wiki";
                if (!outputFile.Open(outputFileName, FILE_WRITE))
                    PrintUnicodeLine("WARNING: Failed to open output file " + outputFileName);
                outputFile.WriteLine("#labels featured");
                outputFile.WriteLine("= " + AssembleString(tokens, 1) + " =");
            }
            else if (line.StartsWith("\\page") && tokens.Size() > 1)
            {
                outputFileName = outDir_ + tokens[1] + ".wiki";
                if (!outputFile.Open(outputFileName, FILE_WRITE))
                    PrintUnicodeLine("WARNING: Failed to open output file " + outputFileName);
                if (tokens.Size() > 2)
                    outputFile.WriteLine("= " + AssembleString(tokens, 2) + " =");
                else
                    outputFile.WriteLine("= " + tokens[1] + " =");
            }
            else if (line.StartsWith("\\section"))
            {
                if (tokens.Size() > 2)
                    outputFile.WriteLine("== " + AssembleString(tokens, 2) + " ==");
                else
                    outputFile.WriteLine("== " + tokens[1] + " ==");
            }
            else if (line.StartsWith("\\verbatim") || line.StartsWith("\\code"))
            {
                outputFile.WriteLine("{{{");
                inVerbatim = true;
            }
            else if (line.StartsWith("- "))
                outputFile.WriteLine(" * " + line.Substring(2));
            else if (line.StartsWith("{") || line.StartsWith("}") || line.StartsWith("namespace") || line.StartsWith("/*") || line.StartsWith("*/"))
                continue;
            else
                outputFile.WriteLine(line);
            
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
