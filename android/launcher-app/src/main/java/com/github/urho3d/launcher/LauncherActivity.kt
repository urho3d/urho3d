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

import android.app.ExpandableListActivity
import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.ExpandableListView
import android.widget.SimpleExpandableListAdapter
import com.github.urho3d.UrhoActivity

class LauncherActivity : ExpandableListActivity() {

    // Filter to only include filename that has an extension
    private fun getScriptNames(path: String) = assets.list(path).filter { it.contains('.') }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Only the sample library is selectable, excluding Urho3DPlayer which is handled separately
        val regex = Regex("^(?:Urho3D.*|.+_shared)\$")
        val libraryNames = UrhoActivity.getLibraryNames(this)
        val items = mutableMapOf("C++" to libraryNames.filterNot { regex.matches(it) }.sorted())
        if (libraryNames.find { it == "Urho3DPlayer" } != null) {
            items.putAll(mapOf(
                    // FIXME: Should not assume both scripting subsystems are enabled in the build
                    "AngelScript" to getScriptNames("Data/Scripts"),
                    "Lua" to getScriptNames("Data/LuaScripts")
            ))
        }
        items.filterValues { it.isEmpty() }.forEach { items.remove(it.key) }

        setListAdapter(SimpleExpandableListAdapter(this,
                items.map {
                    mapOf("api" to it.key, "info" to "Click to expand/collapse")
                },
                android.R.layout.simple_expandable_list_item_2,
                arrayOf("api", "info"),
                intArrayOf(android.R.id.text1, android.R.id.text2),
                items.map {
                    it.value.map { name ->
                        mapOf("item" to name)
                    }
                },
                R.layout.launcher_list_item,
                arrayOf("item"),
                intArrayOf(android.R.id.text1)
        ))
        setContentView(R.layout.activity_launcher)

        // Pass the argument to the main activity, if any
        launch(intent.getStringExtra(MainActivity.argument))
    }

    override fun onChildClick(parent: ExpandableListView?, v: View?, groupPos: Int, childPos: Int,
                              id: Long): Boolean {
        @Suppress("UNCHECKED_CAST")
        launch((expandableListAdapter.getChild(groupPos, childPos) as Map<String, String>)["item"])
        return true
    }

    private fun launch(argument: String?) {
        if (argument != null) {
            startActivity(Intent(this, MainActivity::class.java)
                    .putExtra(MainActivity.argument,
                            if (argument.contains('.')) {
                                if (argument.endsWith(".as")) "Urho3DPlayer:Scripts/$argument"
                                else "Urho3DPlayer:LuaScripts/$argument"
                            } else argument
                    )
            )
        }
    }

}
