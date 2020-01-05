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

import org.gradle.internal.io.NullOutputStream
import java.io.ByteArrayOutputStream

plugins {
    base
    // For some reasons the lint task requires bintray plugin to be declared here too in order to work as expected
    id("com.jfrog.bintray") apply false
}

allprojects {
    group = "com.github.urho3d"
    version = determineVersion()
    description = """Urho3D is a free lightweight,
                    |cross-platform 2D and 3D game engine implemented in C++ and released under the MIT license.
                    |Greatly inspired by OGRE and Horde3D.""".trimMargin().replace('\n', ' ')
    repositories {
        google()
        jcenter()
    }
}

/**
 * Find the most recent tag that is reachable from a commit and use that to set the Gradle's project version.
 *
 * e.g. commit described as "1.7-664-g34b1" will be mapped to "1.8-ROLLING" (rolling upgrades for the next version)
 *      tag "1.8" will be mapped to "1.8" as is (point release version), so does tag "1.8-RC" (release candidate)
 */
fun determineVersion(): String {
    // If it is explicitly specified then let return it instead
    System.getenv("GRADLE_PROJECT_VERSION")?.let { return it }
    // If it is on CI server then unshallow the clone's repo when necessary
    if (System.getenv("CI") != null && System.getenv("RELEASE_TAG") == null) unshallowClone()
    val desc = describeCommit(System.getenv("TRAVIS_COMMIT") ?: System.getenv("APPVEYOR_REPO_COMMIT"))
    return Regex("^(.+?)-\\d").find(desc)?.destructured?.component1()?.let { "${bumpSemVer(it, 1)}-ROLLING" } ?: desc
}

/**
 * Unshallow the clone's repository and fetch all the tags.
 */
fun unshallowClone() = exec {
    commandLine = listOf("git", "fetch", "--tags", "--unshallow")
    standardOutput = NullOutputStream.INSTANCE
    errorOutput = NullOutputStream.INSTANCE
    isIgnoreExitValue = true
}

/**
 * Find the most recent tag that is reachable from a commit.
 */
fun describeCommit(sha: String? = null) = ByteArrayOutputStream().also {
    exec {
        commandLine = listOf("git", "describe", "--tags", sha ?: "--dirty")
        standardOutput = it
        errorOutput = NullOutputStream.INSTANCE
        isIgnoreExitValue = true    // In case no GIT command line tool or not a GIT repository
    }
}.toString().trim().let { if (it.isBlank()) "Unversioned" else it }

/**
 * Bump the semantic versioning on the specified index, 0 for major version, 1 for minor version, and so on.
 */
fun bumpSemVer(version: String, index: Int) = version
        .split('.')
        .mapIndexed { i: Int, s: String ->
            when {
                i < index -> s
                i == index -> if (s.contains('-')) s else (s.toInt() + 1).toString()
                else -> "0"
            }
        }
        .joinToString(".")
