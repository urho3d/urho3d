//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "clang/AST/ASTConsumer.h"
#include "clang/Driver/Options.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Rewrite/Frontend/FixItRewriter.h"
#include "clang/Rewrite/Frontend/FrontendActions.h"
#include "clang/StaticAnalyzer/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/Signals.h"

using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;

static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static cl::extrahelp MoreHelp(
    "\tFor example, to run Annotator on all files in a subtree of the\n"
        "\tsource tree, use:\n"
        "\n"
        "\t  find path/in/substree -name '*.cpp'|xargs Annotator -p build/path\n"
        "\n"
        "\tNote, that path/in/subtree and current directory should follow the\n"
        "\trules described above.\n"
        "\n"
);

static cl::OptionCategory AnnotatorCategory("Annotator options");
static std::unique_ptr<opt::OptTable> Options(createDriverOptTable());
static cl::opt<bool> ASTDump("ast-dump", cl::desc(Options->getOptionHelpText(options::OPT_ast_dump)), cl::cat(AnnotatorCategory));
static cl::opt<std::string> ASTDumpFilter
    ("ast-dump-filter", cl::desc(Options->getOptionHelpText(options::OPT_ast_dump_filter)), cl::cat(AnnotatorCategory));

class AnnotatorActionFactory
{
public:
    std::unique_ptr<clang::ASTConsumer> newASTConsumer()
    {
        if (ASTDump)
            return clang::CreateASTDumper(ASTDumpFilter, /*DumpDecls=*/true, /*DumpLookups=*/false);
        return llvm::make_unique<clang::ASTConsumer>();
    }
};

int main(int argc, const char** argv)
{
    llvm::sys::PrintStackTraceOnErrorSignal();
    CommonOptionsParser OptionsParser(argc, argv, AnnotatorCategory);
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    AnnotatorActionFactory annotatorFactory;
    return Tool.run(newFrontendActionFactory(&annotatorFactory).get());
}
