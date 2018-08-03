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
        versionName = "1.8-SNAPSHOT"
        testInstrumentationRunner = "android.support.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                arguments.apply {
                    add("-DANDROID_CCACHE=${System.getenv("ANDROID_CCACHE")}")
                    add("-DGRADLE_BUILD_DIR=$buildDir")
                    // Pass along matching Gradle properties as CMake build options
                    addAll(listOf(
                            "URHO3D_LIB_TYPE",
                            "URHO3D_ANGELSCRIPT",
                            "URHO3D_LUA",
                            "URHO3D_LUAJIT",
                            "URHO3D_LUAJIT_AMALG",
                            "URHO3D_IK",
                            "URHO3D_NETWORK",
                            "URHO3D_PHYSICS",
                            "URHO3D_NAVIGATION",
                            "URHO3D_URHO2D",
                            "URHO3D_PCH",
                            "URHO3D_DATABASE_SQLITE",
                            "URHO3D_WEBP",
                            "URHO3D_FILEWATCHER",
                            "URHO3D_PROFILING",
                            "URHO3D_LOGGING",
                            "URHO3D_THREADING")
                            .filter { project.hasProperty(it) }
                            .map { "-D$it=${project.property(it)}" }
                    )
                    // In order to get clean module segregation, always exclude player/samples from AAR
                    addAll(listOf(
                            "URHO3D_PLAYER",
                            "URHO3D_SAMPLES"
                    ).map { "-D$it=0" })
                }
                targets.add("Urho3D")
            }
        }
        splits {
            abi {
                isEnable = project.hasProperty("ANDROID_ABI")
                reset()
                include(*(if (isEnable) project.property("ANDROID_ABI") as String else "")
                        .split(',').toTypedArray())
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
}

dependencies {
    implementation(fileTree(mapOf("dir" to "libs", "include" to listOf("*.jar"))))
    implementation(kotlin("stdlib-jdk8", KotlinCompilerVersion.VERSION))
    testImplementation("junit:junit:4.12")
    androidTestImplementation("com.android.support.test:runner:1.0.2")
    androidTestImplementation("com.android.support.test.espresso:espresso-core:3.0.2")
}

afterEvaluate {
    // Part of the our external native build tree resided in Gradle buildDir
    // When the buildDir is cleaned then we need a way to re-configure that part back
    // It is achieved by ensuring that CMake configuration phase is rerun
    tasks {
        getByName("clean") {
            doLast {
                delete(android.externalNativeBuild.cmake.buildStagingDirectory
                        ?: project.file(".externalNativeBuild"))
            }
        }
    }

    // This is a hack - workaround Android plugin for Gradle not providing way to bundle extra "stuffs"
    android.buildTypes.forEach { buildType ->
        val config = buildType.name.capitalize()
        tasks {
            create<Zip>("zipBuildTree$config") {
                val aarDir = File(buildDir, "outputs/aar")
                val aarName = "${project.name}-${buildType.name}.aar"
                val aarFile = File(aarDir, aarName)
                archiveName = "$aarName.new"
                destinationDir = aarDir
                outputs.upToDateWhen { false }
                from(zipTree(aarFile))
                dependsOn("zipBuildTreeConfigurer$config")
                doLast { archivePath.renameTo(aarFile) }
            }
            create("zipBuildTreeConfigurer$config") {
                val externalNativeBuildDir = File(buildDir, "tree/$config")
                doLast {
                    tasks.getByName<Zip>("zipBuildTree$config") {
                        onlyIf { tasks["assemble$config"].state.executed }
                        externalNativeBuildDir.list()?.forEach { abi ->
                            listOf("include", "lib").forEach {
                                from(File(externalNativeBuildDir, "$abi/$it")) {
                                    into("tree/$config/$abi/$it")
                                }
                            }
                        }
                    }
                }
            }
            "assemble$config" { finalizedBy("zipBuildTree$config") }
        }
    }
}
