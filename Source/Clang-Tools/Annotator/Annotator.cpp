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
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Refactoring.h>

#include <unordered_set>

using namespace clang;
using namespace clang::ast_matchers;
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
    "Most probably you want to invoke 'annotate' built-in target instead of invoking this tool\n"
    "directly. The 'annotate' target invokes this tool in a right context prepared by build system.\n"
    "\n"
);

static cl::OptionCategory annotatorCategory("Annotator options");

// ClangTool only takes a reference to the array list without owning it, so we need to keep the filtered list ourselves
class PathFilter
{
public:
    template <typename Fn>
    PathFilter(const std::vector<std::string> sourcePaths, Fn fn)
    {
        std::copy_if(sourcePaths.begin(), sourcePaths.end(), std::back_inserter(pathList_), fn);
    }

    std::vector<std::string> GetPathList() {
        return pathList_;
    }

private:
    std::vector<std::string> pathList_;
};

static std::unordered_set<std::string> classNames_;

class ExtractCallback : public MatchFinder::MatchCallback
{
public :
    virtual void run(const MatchFinder::MatchResult& result)
    {
        auto className = result.Nodes.getNodeAs<StringLiteral>("className");
        if (className)
            classNames_.insert(className->getString());
    }

    virtual void onStartOfTranslationUnit()
    {
        outs() << '.';      // Sending a heart beat
    }
};

static std::unordered_set<std::string> annotatedClassNames_;

class AnnotateCallback : public MatchFinder::MatchCallback
{
public :
    AnnotateCallback(Replacements& replacements) :
        replacements_(replacements)
    {
    }

    virtual void run(const MatchFinder::MatchResult& result)
    {
        auto className = result.Nodes.getNodeAs<RecordDecl>("className");
        if (className && annotatedClassNames_.find(className->getName()) == annotatedClassNames_.end() &&
            classNames_.find(className->getName()) == classNames_.end())
        {
            replacements_.insert(Replacement(*result.SourceManager, className->getLocation(), 0, "NONSCRIPTABLE "));
            annotatedClassNames_.insert(className->getName());
        }
    }

    virtual void onStartOfTranslationUnit()
    {
        static unsigned count = sizeof("Annotating") / sizeof(char) - 1;
        outs() << '.' << (++count % 100 ? "" : "\n");
    }

private:
    Replacements& replacements_;
};

int main(int argc, const char** argv)
{
    // Parse the arguments and pass them to the the internal sub-tools
    CommonOptionsParser optionsParser(argc, argv, annotatorCategory);
    PathFilter bindingPathFilter
        (optionsParser.getSourcePathList(), [](const std::string& path) { return path.find("API.cpp") != std::string::npos; });
    PathFilter nonBindingPathFilter
        (optionsParser.getSourcePathList(), [](const std::string& path) { return path.find("API.cpp") == std::string::npos; });
    ClangTool bindingExtractor(optionsParser.getCompilations(), bindingPathFilter.GetPathList());
    RefactoringTool annotator(optionsParser.getCompilations(), nonBindingPathFilter.GetPathList());

    // Setup finder to match against AST nodes from existing AngelScript binding source files
    ExtractCallback extractCallback;
    MatchFinder bindingFinder;
    // Find exposed class names (they are registered through RegisterObjectType(), RegisterRefCounted(), RegisterObject(), etc)
    bindingFinder.addMatcher(
        memberCallExpr(
            callee(
                methodDecl(hasName("RegisterObjectType"))),
            hasArgument(0, stringLiteral().bind("className"))), &extractCallback);
    bindingFinder.addMatcher(
        callExpr(
            hasDeclaration(
                functionDecl(hasParameter(1, hasName("className")))),
            hasArgument(1, stringLiteral().bind("className"))), &extractCallback);

    // Setup finder to match against AST nodes for annotating Urho3D library source files
    AnnotateCallback annotateCallback(annotator.getReplacements());
    MatchFinder annotateFinder;
    // Find exported class declaration with Urho3D namespace
    annotateFinder.addMatcher(
        recordDecl(
#ifndef _MSC_VER
            hasAttr(attr::Visibility),
#else
            hasAttr(attr::DLLExport),
#endif
            matchesName("^::Urho3D::")).bind("className"), &annotateCallback);

    // Unbuffered stdout stream to keep the Travis-CI's log flowing and thus prevent it from killing a potentially long running job
    outs().SetUnbuffered();

    // Success when both sub-tools are run successfully
    return (outs() << "Extracting", true) &&
           bindingExtractor.run(newFrontendActionFactory(&bindingFinder).get()) == EXIT_SUCCESS &&
           (outs() << "\nExtracted " << classNames_.size() << " bound class names\n"
            << "Annotating", true) &&
           annotator.runAndSave(newFrontendActionFactory(&annotateFinder).get()) == EXIT_SUCCESS &&
           (outs() << "\nAnnotated " << annotatedClassNames_.size() << " exported class names as non-scriptable\n", true) ?
        EXIT_SUCCESS : EXIT_FAILURE;
}
