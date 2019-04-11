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

import org.gradle.internal.io.NullOutputStream
import org.gradle.internal.os.OperatingSystem

plugins {
    id("com.android.library")
    kotlin("android")
    kotlin("android.extensions")
    `maven-publish`
}

android {
    compileSdkVersion(27)
    defaultConfig {
        minSdkVersion(17)
        targetSdkVersion(27)
        versionCode = 1
        versionName = project.version.toString()
        testInstrumentationRunner = "android.support.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                arguments.apply {
                    System.getenv("ANDROID_CCACHE")?.let { add("-DANDROID_CCACHE=$it") }
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
                        .split(',')
                        .toTypedArray())
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
            setVersion(cmakeVersion)
            setPath(project.file("../../CMakeLists.txt"))
        }
    }
}

dependencies {
    implementation(fileTree(mapOf("dir" to "libs", "include" to listOf("*.jar"))))
    implementation(kotlin("stdlib-jdk8", kotlinVersion))
    testImplementation("junit:junit:$junitVersion")
    androidTestImplementation("com.android.support.test:runner:$testRunnerVersion")
    androidTestImplementation("com.android.support.test.espresso:espresso-core:$testEspressoVersion")
}

lateinit var docABI: String

afterEvaluate {
    // Part of the our external native build tree resided in Gradle buildDir
    // When the buildDir is cleaned then we need a way to re-configure that part back
    // It is achieved by ensuring that CMake configuration phase is rerun
    tasks {
        getByName("clean") {
            doLast {
                android.externalNativeBuild.cmake.path?.touch()
            }
        }
    }

    // This is a hack - workaround Android plugin for Gradle not providing way to bundle extra "stuffs"
    android.buildTypes.forEach { buildType ->
        val config = buildType.name.capitalize()
        tasks {
            create<Zip>("zipBuildTree$config") {
                archiveClassifier.set(buildType.name)
                archiveExtension.set("aar")
                dependsOn("zipBuildTreeConfigurer$config", "bundle${config}Aar")
                from(zipTree(getByName("bundle${config}Aar").outputs.files.first()))
            }
            create("zipBuildTreeConfigurer$config") {
                val externalNativeBuildDir = File(buildDir, "tree/$config")
                doLast {
                    val zipTask = getByName<Zip>("zipBuildTree$config")
                    externalNativeBuildDir.list()?.forEach { abi ->
                        listOf("include", "lib").forEach {
                            zipTask.from(File(externalNativeBuildDir, "$abi/$it")) {
                                into("tree/$config/$abi/$it")
                            }
                        }
                        if (config == "Release") {
                            docABI = abi
                        }
                    }
                }
            }
        }
    }
}

tasks {
    create<Jar>("sourcesJar") {
        archiveClassifier.set("sources")
        from(android.sourceSets.getByName("main").java.srcDirs)
    }
    create<Exec>("makeDoc") {
        // Ignore the exit status on Windows host system because Doxygen may not return exit status correctly on Windows
        isIgnoreExitValue = OperatingSystem.current().isWindows
        standardOutput = NullOutputStream.INSTANCE
        args("--build", ".", "--target", "doc")
        dependsOn("makeDocConfigurer")
        mustRunAfter("zipBuildTreeRelease")
    }
    create<Zip>("documentationZip") {
        archiveClassifier.set("documentation")
        dependsOn("makeDoc")
    }
    create("makeDocConfigurer") {
        doLast {
            val buildTree = File(cmakeStagingDir(), "cmake/release/$docABI")
            getByName<Exec>("makeDoc") {
                // This is a hack - expect the first line to contain the path to the embedded CMake executable
                executable = File(buildTree, "cmake_build_command.txt").readLines().first().split(":").last().trim()
                workingDir = buildTree
            }
            getByName<Zip>("documentationZip") {
                from(File(buildTree, "Docs/html")) {
                    into("docs")
                }
            }
        }
    }
}

publishing {
    (publications) {
        create<MavenPublication>("mavenAndroid") {
            artifactId = "${project.name}-${project.libraryType}"
            afterEvaluate {
                android.buildTypes.forEach {
                    artifact(tasks.getByName("zipBuildTree${it.name.capitalize()}"))
                }
            }
            artifact(tasks.getByName("sourcesJar"))
            artifact(tasks.getByName("documentationZip"))
        }
    }
}

fun cmakeStagingDir() = android.externalNativeBuild.cmake.buildStagingDirectory ?: project.file(".cxx")

val Project.libraryType: String
    get() = if (hasProperty("URHO3D_LIB_TYPE")) property("URHO3D_LIB_TYPE") as String else "STATIC"
