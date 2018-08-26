//
// Copyright (c) 2008-2018 the Urho3D project.
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

import org.gradle.api.Project
import org.gradle.kotlin.dsl.DependencyHandlerScope
import org.gradle.kotlin.dsl.dependencies
import org.gradle.kotlin.dsl.kotlin
import org.gradle.kotlin.dsl.project
import java.io.File

const val androidToolsVersion = "3.2.0-beta04"
const val kotlinVersion = "1.2.61"
const val junitVersion = "4.12"
const val testRunnerVersion = "1.0.2"
const val testEspressoVersion = "3.0.2"

/**
 * Prepare the module as Android Application with Urho3D AAR dependency.
 */
@Suppress("unused")
fun Project.urhoAndroidModule() {
    dependencies {
        "implementation"(fileTree(mapOf("dir" to "libs", "include" to listOf("*.jar"))))
        "implementation"(project(":android:urho3d-lib"))
        kotlinAndroidDependencies()
    }
}

/**
 * Add default dependencies for Android/Kotlin module.
 */
@Suppress("unused")
fun DependencyHandlerScope.kotlinAndroidDependencies() {
    "implementation"(kotlin("stdlib-jdk8", kotlinVersion))
    "testImplementation"("junit:junit:$junitVersion")
    "androidTestImplementation"("com.android.support.test:runner:$testRunnerVersion")
    "androidTestImplementation"("com.android.support.test.espresso:espresso-core:$testEspressoVersion")
}

/**
 * Naive implementation of "touch" command.
 */
@Suppress("unused")
fun File.touch() = createNewFile() || setLastModified(System.currentTimeMillis())
