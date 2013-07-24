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

#pragma once

#include "Context.h"
#include "Engine.h"

#include "Main.h"
#include "DebugNew.h"

/// Templated entry-point common to all samples. This function expects T to be a
/// subclass of Object, whose constructor performs any and all setup code
/// necessary to run.
/// After instantiating said subclass, this function will enter a main loop and
/// kee[ running for as long as while Engine exit has not been requested.
/// Consequently, any such subclass _must_ provide a means to request engine
/// shutdown. Failure to do so will result in a program that can't be
/// stopped graciously and has to be killed by the user.
///
/// Usage:  simply add the line \code DEFINE_MAIN(Run<T>()) \endcode
///         in the subclass' implementation, where T equals subclass type.
template<class T> int Run()
{
    // Construct a new execution Context
    SharedPtr<Context> context(new Context());
    // Construct the Urho3D engine, setting up other subsystems in the process
    SharedPtr<Engine> engine(new Engine(context));

    // Let engine parse command-line parameters, set window title and log file
    // to use based on specified template's typename
    VariantMap engineParameters = Engine::ParseParameters(GetArguments());
    String typeName(T::GetTypeNameStatic());

    engineParameters["WindowTitle"] = typeName;
    engineParameters["LogName"]     = typeName.Append(".log");
    engineParameters["FullScreen"]  = false;

    // Initialize the Engine according to desired parameters
    engine->Initialize(engineParameters);

    // Construct Sample instance
    SharedPtr<T> t(new T(context));

    // Run main loop while the engine is not exiting
    while (!engine->IsExiting())
        engine->RunFrame();

    return EXIT_SUCCESS;
}


