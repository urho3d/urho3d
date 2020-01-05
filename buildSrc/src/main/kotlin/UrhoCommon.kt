//
// Copyright (c) 2008-2020 the Urho3D project.
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

import org.gradle.kotlin.dsl.embeddedKotlinVersion
import org.gradle.plugin.use.PluginDependenciesSpec
import org.gradle.plugin.use.PluginDependencySpec
import java.io.File

val kotlinVersion = embeddedKotlinVersion

const val androidToolsVersion = "3.5.0-alpha13"
const val bintrayVersion = "1.8.4"
const val cmakeVersion = "3.14.5+"
const val relinkerVersion = "1.3.1"
const val junitVersion = "4.12"
const val testEspressoVersion = "3.0.2"
const val testRunnerVersion = "1.0.2"

/**
 * Apply Urho3D custom plugin for the given platform.
 *
 * Current supported platforms: android.
 */
@Suppress("unused")
fun PluginDependenciesSpec.urho3d(platform: String): PluginDependencySpec =
        id("com.github.urho3d.$platform")

/**
 * Naive implementation of "touch" command.
 */
@Suppress("unused")
fun File.touch() = createNewFile() || setLastModified(System.currentTimeMillis())
