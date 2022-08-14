// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

plugins {
    id("com.android.application")
    kotlin("android")
    kotlin("android.extensions")
}

val kotlinVersion: String by ext
val ndkSideBySideVersion: String by ext
val cmakeVersion: String by ext
val buildStagingDir: String by ext

android {
    ndkVersion = ndkSideBySideVersion
    compileSdkVersion(30)
    defaultConfig {
        minSdkVersion(18)
        targetSdkVersion(30)
        applicationId = "io.urho3d.launcher"
        versionCode = 1
        versionName = project.version.toString()
        testInstrumentationRunner = "android.support.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                arguments.apply {
                    System.getenv("ANDROID_CCACHE")?.let { add("-D ANDROID_CCACHE=$it") }
                    add("-D BUILD_STAGING_DIR=${findProject(":android:urho3d-lib")!!.projectDir}/$buildStagingDir")
                    add("-D URHO3D_PLAYER=1")
                    // Skip building samples for 'STATIC' lib type to reduce the spacetime requirement
                    add("-D URHO3D_SAMPLES=${if (System.getenv("URHO3D_LIB_TYPE") == "SHARED") "1" else "0"}")
                    // Pass along matching env-vars as CMake build options
                    addAll(project.file("../../script/.build-options")
                        .readLines()
                        .filterNot { listOf("URHO3D_PLAYER", "URHO3D_SAMPLES").contains(it) }
                        .mapNotNull { variable -> System.getenv(variable)?.let { "-D $variable=$it" } }
                    )
                }
            }
        }
        splits {
            abi {
                isEnable = project.hasProperty("ANDROID_ABI")
                reset()
                include(
                    *(project.findProperty("ANDROID_ABI") as String? ?: "")
                        .split(',')
                        .toTypedArray()
                )
            }
        }
    }
    buildTypes {
        named("release") {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
        }
    }
    lintOptions {
        isAbortOnError = false
    }
    externalNativeBuild {
        cmake {
            version = cmakeVersion
            path = project.file("CMakeLists.txt")
            buildStagingDirectory(buildStagingDir)
        }
    }
}

dependencies {
    implementation(project(":android:urho3d-lib"))
    implementation(fileTree(mapOf("dir" to "libs", "include" to listOf("*.jar", "*.aar"))))
    implementation("org.jetbrains.kotlin:kotlin-stdlib-jdk8:$kotlinVersion")
    implementation("androidx.core:core-ktx:1.3.2")
    implementation("androidx.appcompat:appcompat:1.2.0")
    implementation("androidx.constraintlayout:constraintlayout:2.0.2")
    testImplementation("junit:junit:4.13.1")
    androidTestImplementation("androidx.test:runner:1.3.0")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.3.0")
}

afterEvaluate {
    android.buildTypes.forEach {
        val config = it.name.capitalize()
        tasks {
            "externalNativeBuild$config" {
                mustRunAfter(":android:urho3d-lib:externalNativeBuild$config")
            }
        }
    }
}

tasks {
    register<Delete>("cleanAll") {
        dependsOn("clean")
        delete = setOf(android.externalNativeBuild.cmake.buildStagingDirectory)
    }
}
