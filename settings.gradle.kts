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

pluginManagement {
    resolutionStrategy {
        eachPlugin {
            when {
                requested.id.id.startsWith("com.android.") ->
                    useModule("com.android.tools.build:gradle:3.5.3")
                requested.id.id.startsWith("org.jetbrains.kotlin.") ->
                    useVersion(embeddedKotlinVersion)
                requested.id.id == "com.jfrog.bintray" ->
                    useVersion("1.8.4")
            }
        }
    }
    repositories {
        @Suppress("UnstableApiUsage")
        gradlePluginPortal()
        google()
        jcenter()
    }
}

include(":android:urho3d-lib", ":android:launcher-app")
