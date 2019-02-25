//
// Copyright (c) 2008-2019 the Urho3D project.
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

package com.github.urho3d.launcher

import com.github.urho3d.UrhoActivity

class MainActivity : UrhoActivity() {

    companion object {
        const val argument = "argument"
    }

    private lateinit var arguments: List<String>

    override fun getArguments() = arguments.toTypedArray()

    override fun onLoadLibrary(libraryNames: MutableList<String>) {
        // All runtime shared libraries must always be loaded if available
        val regex = Regex("^(?:Urho3D|.+_shared)\$")
        libraryNames.retainAll { regex.matches(it) }

        // Parse the argument string
        val argumentString = intent.getStringExtra(argument)
        if (argumentString != null) arguments = argumentString.split(':')
        else throw IllegalArgumentException("The MainActivity requires an argument to start")

        // Must add the chosen sample library to the last of the list
        libraryNames.add(arguments[0])

        super.onLoadLibrary(libraryNames)
    }

}
