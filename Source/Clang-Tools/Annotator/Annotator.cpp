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

static cl::OptionCategory AnnotatorCategory("Annotator options");

class BindingCallback : public MatchFinder::MatchCallback
{
public :
    virtual void run(const MatchFinder::MatchResult& result)
    {
        ASTContext* context = result.Context;
        const StringLiteral* stringLiteral = result.Nodes.getNodeAs<StringLiteral>("StringLiteral");
        if (stringLiteral)
            // TODO: Store the exposed class name in a global hashset
            outs() << stringLiteral->getString() << "\n";
    }

    virtual void onStartOfTranslationUnit()
    {
        outs() << '.';
    }
};

int main(int argc, const char** argv)
{
    CommonOptionsParser OptionsParser(argc, argv, AnnotatorCategory);
    ClangTool bindingExtractor(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    RefactoringTool annotator(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    BindingCallback bindingCallback;
    MatchFinder bindingFinder;
    bindingFinder.addMatcher(
        memberCallExpr(
            callee(
                methodDecl(hasName("RegisterObjectType"))),
            hasArgument(0, stringLiteral().bind("StringLiteral"))), &bindingCallback);
    bindingFinder.addMatcher(
        callExpr(
            hasDeclaration(
                functionDecl(hasParameter(1, hasName("className")))),
            hasArgument(1, stringLiteral().bind("StringLiteral"))), &bindingCallback);
    MatchFinder annotateFinder;
    return (outs() << "Extracting", true) &&
           bindingExtractor.run(newFrontendActionFactory(&bindingFinder).get()) == EXIT_SUCCESS &&
           (outs() << "\nAnnotating", true) &&
           annotator.runAndSave(newFrontendActionFactory(&annotateFinder).get()) == EXIT_SUCCESS &&
           (outs() << "\n", true) ? EXIT_SUCCESS : EXIT_FAILURE;
}
