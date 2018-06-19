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

import java.nio.file.Files
import org.jetbrains.kotlin.config.KotlinCompilerVersion

plugins {
    id("com.android.library")
    id("kotlin-android")
    id("kotlin-android-extensions")
}

android {
    compileSdkVersion(27)
    defaultConfig {
        minSdkVersion(17)
        targetSdkVersion(27)
        versionCode = 1
        versionName = "1.0"
        testInstrumentationRunner = "android.support.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                arguments.addAll(
                        listOf(
                                "ANDROID_CCACHE=${System.getenv("ANDROID_CCACHE")}",
                                "URHO3D_LIB_TYPE=SHARED",
                                "URHO3D_LUAJIT=1",
                                "URHO3D_LUAJIT_AMALG=1",
                                "URHO3D_SAMPLES=1"
                        ).map { "-D$it" }
                )
            }
        }
        splits {
            abi {
                isEnable = project.hasProperty("abi")
                reset()
                include(if (isEnable) project.property("abi") as String else "")
            }
        }
    }
    buildTypes {
        getByName("release") {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android.txt"), "proguard-rules.pro")
        }
    }
    externalNativeBuild {
        cmake {
            path = project.file("../../CMakeLists.txt")
        }
    }
    sourceSets {
        getByName("main") {
            assets.srcDir(project.file("../../bin"))
        }
    }
}

dependencies {
    implementation(fileTree(mapOf("dir" to "libs", "include" to listOf("*.jar"))))
    implementation(kotlin("stdlib-jdk8", KotlinCompilerVersion.VERSION))
    testImplementation("junit:junit:4.12")
    androidTestImplementation("com.android.support.test:runner:1.0.2")
    androidTestImplementation("com.android.support.test.espresso:espresso-core:3.0.2")
}

// This is a hack - workaround Android plugin for Gradle's bug where it erroneously dereference
// the symlink causing the actual file being deleted when it attempts to remove stale contents
afterEvaluate {
    val symlinkDirs = listOf("include")       // This list is specific to Urho3D
    tasks {
        "generateJsonModelDebug" {
            doFirst { symlinkWorkaround("debug", true, symlinkDirs) }
            doLast { symlinkWorkaround("debug", false, symlinkDirs) }
        }
        "generateJsonModelRelease" {
            doFirst { symlinkWorkaround("release", true, symlinkDirs) }
            doLast { symlinkWorkaround("release", false, symlinkDirs) }
        }
    }
}
//
fun symlinkWorkaround(config: String, keep: Boolean, symlinkDirs: List<String>) {
    val stagingDir = android.externalNativeBuild.cmake.buildStagingDirectory
            ?: project.file(".externalNativeBuild")
    val oriDir = File(stagingDir, "cmake/$config")
    val bakDir = File(stagingDir, ".cmake-$config")
    bakDir.mkdir()
    oriDir.list().forEach { abi ->
        symlinkDirs.forEach { dir ->
            if (keep) {
                // Keep the dir somewhere else that the original Gradle task doesn't touch it
                File(oriDir, "$abi/$dir").renameTo(File(bakDir, "$abi-$dir"))
            } else {
                // It is OK to fail here because the dir might get regenerated back by CMake
                File(bakDir, "$abi-$dir").renameTo(File(oriDir, "$abi/$dir"))
            }
        }
    }
    if (!keep) {
        // Whatever remaining in the backup dir must be disposed of with respect to symlink
        bakDir.walkBottomUp()
                .filterNot { it.parentFile.isSymlink() }
                .forEach { Files.delete(it.toPath()) }
    }
}
//
fun File.isSymlink() = absoluteFile != canonicalFile
