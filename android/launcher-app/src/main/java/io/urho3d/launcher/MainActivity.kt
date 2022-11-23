// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

package io.urho3d.launcher

import io.urho3d.UrhoActivity

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
