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

#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Driver/Options.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>

#include <Mustache/mustache.hpp>

#include <unordered_set>

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;

static cl::extrahelp commonHelp(CommonOptionsParser::HelpMessage);
static cl::extrahelp moreHelp(
    "\tFor example, to run AutoBinder on all files in a subtree of the\n"
    "\tsource tree, use:\n"
    "\n"
    "\t  find path/in/substree -name '*.cpp'|xargs AutoBinder -p build/path \\\n"
    "\t  -t template/path -o output/path -s script0 -s script1\n"
    "\n"
    "\tNote, that path/in/subtree and current directory should follow the\n"
    "\trules described above.\n"
    "\n"
    "Most probably you want to invoke 'autobinder' built-in target instead of invoking this tool\n"
    "directly. The 'autobinder' target invokes this tool in a right context prepared by build system.\n"
    "\n"
);

static cl::OptionCategory autobinderCategory("AutoBinder options");
static std::unique_ptr<opt::OptTable> options(createDriverOptTable());
static cl::opt<std::string> templatePath("t", cl::desc("Template path"), cl::cat(autobinderCategory));
static cl::opt<std::string> outputPath("o", cl::desc("Output path"), cl::cat(autobinderCategory));
static cl::list<std::string> scripts("s", cl::desc("Script subsystems"), cl::cat(autobinderCategory));

struct Data
{
    std::unordered_set<std::string> symbols_;
};

static const std::string categories_[] = {"class", "enum"};
static std::unordered_map<std::string, Data> categoryData_;

class ExtractCallback : public MatchFinder::MatchCallback
{
public :
    virtual void run(const MatchFinder::MatchResult& result)
    {
        for (auto& i: categories_)
        {
            auto symbol = result.Nodes.getNodeAs<StringLiteral>(i);
            if (symbol)
                categoryData_[i].symbols_.insert(symbol->getString());
        }
    }

    virtual void onStartOfTranslationUnit()
    {
        static unsigned count = sizeof("Extracting") / sizeof(char) - 1;
        outs() << '.' << (++count % 100 ? "" : "\n");   // Sending a heart beat
    }
};

static int BindingGenerator()
{
    // TODO: WIP
    return EXIT_SUCCESS;
}

int main(int argc, const char** argv)
{
    // Parse the arguments and pass them to the the internal sub-tools
    CommonOptionsParser optionsParser(argc, argv, autobinderCategory);
    ClangTool bindingExtractor(optionsParser.getCompilations(), optionsParser.getSourcePathList());

    // Setup finder to match against AST nodes from Urho3D library source files
    ExtractCallback extractCallback;
    MatchFinder bindingFinder;
    // Find exported class declarations with Urho3D namespace
    bindingFinder.addMatcher(
        recordDecl(
            unless(hasAttr(attr::Annotate)),
#ifndef _MSC_VER
            hasAttr(attr::Visibility),
#else
            hasAttr(attr::DLLExport),
#endif
            matchesName("^::Urho3D::")).bind("class"), &extractCallback);
    // Find enum declarations with Urho3D namespace
    bindingFinder.addMatcher(
        enumDecl(
            unless(hasAttr(attr::Annotate)),
            matchesName("^::Urho3D::")).bind("enum"), &extractCallback);

    // Unbuffered stdout stream to keep the Travis-CI's log flowing and thus prevent it from killing a potentially long running job
    outs().SetUnbuffered();

    // Success when both sub-tools are run successfully
    return (outs() << "Extracting", true) &&
           bindingExtractor.run(newFrontendActionFactory(&bindingFinder).get()) == EXIT_SUCCESS &&
           (outs() << "\nBinding", true) &&
           BindingGenerator() == EXIT_SUCCESS &&
           (outs() << "\n", true) ?
        EXIT_SUCCESS : EXIT_FAILURE;
}
