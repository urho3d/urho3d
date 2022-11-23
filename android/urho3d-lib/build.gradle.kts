// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

import org.gradle.internal.io.NullOutputStream
import org.gradle.internal.os.OperatingSystem

plugins {
    id("com.android.library")
    id("com.jfrog.bintray")
    kotlin("android")
    kotlin("android.extensions")
    `maven-publish`
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
        versionCode = 1
        versionName = project.version.toString()
        testInstrumentationRunner = "android.support.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                arguments.apply {
                    System.getenv("ANDROID_CCACHE")?.let { add("-D ANDROID_CCACHE=$it") }
                    // Pass along matching env-vars as CMake build options
                    addAll(project.file("../../script/.build-options")
                        .readLines()
                        .mapNotNull { variable -> System.getenv(variable)?.let { "-D $variable=$it" } }
                    )
                }
                targets.add("Urho3D")
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
    externalNativeBuild {
        cmake {
            version = cmakeVersion
            path = project.file("../../CMakeLists.txt")
            setBuildStagingDirectory(buildStagingDir)
        }
    }
    sourceSets {
        named("main") {
            java.srcDir("../../Source/ThirdParty/SDL/android-project/app/src/main/java")
        }
    }
}

dependencies {
    implementation(fileTree(mapOf("dir" to "libs", "include" to listOf("*.jar", "*.aar"))))
    implementation("org.jetbrains.kotlin:kotlin-stdlib-jdk8:$kotlinVersion")
    implementation("com.getkeepsafe.relinker:relinker:1.4.1")
    testImplementation("junit:junit:4.13.1")
    androidTestImplementation("androidx.test:runner:1.3.0")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.3.0")
}

android.libraryVariants.whenObjectAdded {
    val config = name
    packageLibraryProvider.get().apply {
        // Customize bundle task to also zip the Urho3D headers and libraries
        File(android.externalNativeBuild.cmake.buildStagingDirectory, "cmake/$config").list()?.forEach { abi ->
            listOf("include", "lib").forEach {
                from(File(android.externalNativeBuild.cmake.buildStagingDirectory, "cmake/$config/$abi/$it")) {
                    into("urho3d/$config/$abi/$it")
                }
            }
        }
    }
}

tasks {
    register<Delete>("cleanAll") {
        dependsOn("clean")
        delete = setOf(android.externalNativeBuild.cmake.buildStagingDirectory)
    }
    register<Jar>("sourcesJar") {
        archiveClassifier.set("sources")
        from(android.sourceSets.getByName("main").java.srcDirs)
    }
    register<Zip>("documentationZip") {
        archiveClassifier.set("documentation")
        dependsOn("makeDoc")
    }
    register<Exec>("makeDoc") {
        // Ignore the exit status on Windows host system because Doxygen may not return exit status correctly on Windows
        isIgnoreExitValue = OperatingSystem.current().isWindows
        standardOutput = NullOutputStream.INSTANCE
        args("--build", ".", "--target", "doc")
        dependsOn("makeDocConfigurer")
    }
    register<Task>("makeDocConfigurer") {
        dependsOn("generateJsonModelRelease")
        doLast {
            val abi = File(android.externalNativeBuild.cmake.buildStagingDirectory, "cmake/release").list()!!.first()
            val buildTree = File(android.externalNativeBuild.cmake.buildStagingDirectory, "cmake/release/$abi")
            named<Exec>("makeDoc") {
                // This is a hack - expect the first line to contain the path to the CMake executable
                executable = File(buildTree, "build_command.txt").readLines().first().split(":").last().trim()
                workingDir = buildTree
            }
            named<Zip>("documentationZip") {
                from(File(buildTree, "Docs/html")) {
                    into("docs")
                }
            }
        }
    }
}

publishing {
    publications {
        android.buildTypes.forEach {
            val config = it.name
            register<MavenPublication>("Urho${config.capitalize()}") {
                configure(config)
            }
        }
    }
    repositories {
        maven {
            name = "GitHubPackages"
            url = uri("https://maven.pkg.github.com/urho3d/Urho3D")
            credentials {
                username = System.getenv("GITHUB_ACTOR")
                password = System.getenv("GITHUB_TOKEN")
            }
        }
    }
}

bintray {
    user = System.getenv("BINTRAY_USER")
    key = System.getenv("BINTRAY_KEY")
    publish = true
    override = true
    setPublications("UrhoRelease", "UrhoDebug")
    pkg.apply {
        repo = "maven"
        name = project.name
        setLicenses("MIT")
        vcsUrl = "https://github.com/urho3d/Urho3D.git"
        userOrg = "urho3d"
        setLabels("android", "game-development", "game-engine", "open-source", "urho3d")
        websiteUrl = "https://urho3d.io/"
        issueTrackerUrl = "https://github.com/urho3d/Urho3D/issues"
        githubRepo = "urho3d/Urho3D"
        publicDownloadNumbers = true
        desc = project.description
        version.apply {
            name = project.version.toString()
            desc = project.description
        }
    }
}

fun MavenPublication.configure(config: String) {
    val libType = System.getenv("URHO3D_LIB_TYPE")?.toLowerCase() ?: "static"
    groupId = project.group.toString()
    artifactId = "${project.name}-$libType${if (config == "debug") "-debug" else ""}"
    afterEvaluate {
        from(components[config])
    }
    artifact(tasks["sourcesJar"])
    artifact(tasks["documentationZip"])
    pom {
        inceptionYear.set("2008")
        licenses {
            license {
                name.set("MIT License")
                url.set("https://github.com/urho3d/Urho3D/blob/master/LICENSE")
            }
        }
        developers {
            developer {
                name.set("Urho3D contributors")
                url.set("https://github.com/urho3d/Urho3D/graphs/contributors")
            }
        }
        scm {
            url.set("https://github.com/urho3d/Urho3D.git")
            connection.set("scm:git:ssh://git@github.com:urho3d/Urho3D.git")
            developerConnection.set("scm:git:ssh://git@github.com:urho3d/Urho3D.git")
        }
        withXml {
            asNode().apply {
                appendNode("name", "Urho3D")
                appendNode("description", project.description)
                appendNode("url", "https://urho3d.io/")
            }
        }
    }
}
