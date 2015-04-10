![My logo](https://raw.githubusercontent.com/299299/Urho3D/master/Docs/logo.jpg)

#Android 环境手顺

## Android PC win 7环境配置

  **1. 环境包下载：**

   下载地址 http://pan.baidu.com/s/1jGoZbMm 我的百度共享

  可以选择都安装到比如 F:\Android 目录下

  **2.配置windows环境变量：**

  JAVA_HOME = F:\Android\Java\jdk1.8.0_40

  Path变量追加 F:\Android\android-ndk\prebuilt\windows-x86_64\bin;F:\Android\android-sdk\tools;F:\Android\android-sdk\platform-tools;F:\Android\apache-ant-1.9.4\bin

  注意这个是为了能使用 1. ant命令 2. android的make命令

  **3.下载android的SDK Tools：**

  执行Android SDK Manager 根据调试手机选择你要的API Target包

  (Optionally, also install Eclipse ADT plugin for building and deployment via Eclipse.)

  **4.代码编译部署：**

  1. 控制台执行 当前目录下的 make_android.bat (前提是NDK的环境变量都已配好)
  2. cd .build/android ---> 进入目录
  3. android update project -p . -t TARGET_ID  --->  这里TARGET_ID 是通过命令android list targets得到的 我的是android-16
  4. make -j8 --->  第一次编译很慢
  5. ant debug (或者release) ---> .build\android\bin 这里会生成一个apk包 ！
  6. adb install 生成的apk包 就可以部署到手机里了

   (

    By default the Android package for Urho3D is com.googlecode.urho3d. For a real application you must replace this with your own package name. The Urho3D activity subclasses the SDLActivity from org.libsdl.app package, whose name (or the JNI code from SDL library) does not have to be changed.

    Note that the native code is built by default for armeabi-v7a ABI. To make your program compatible also with old Android devices, build also an armeabi version by executing the CMake batch file again with the build option "-DANDROID_ABI=armeabi" added, then execute make again in the build directory. Similarly, the native code can be built using 64-bit ABI by changing the value of this build option. See Build options for all the possible values.

    You can also build and deploy using Eclipse IDE with ADT plugin. To do that, after setting the ANDROID_NDK environment variable then run cmake_eclipse.sh. Import "Existing Android Code into Workspace" from the CMake generated Eclipse's project found in the android-Build directory. Switch Eclipse IDE to use Java Perspective. Update project properties to choose the desired Android API target and that's it. Just choose "Run" to let ADT automatically build and deploy the application to Android (virtual) device.
   ) 这里懒的翻译了


   其他的平台可以参考 http://urho3d.github.io/documentation/1.32/_building.html


   后续: 因为包太大 可以考虑 删除部分不必要的组件 比如脚本


   这里提供一个android4.2 API编译的测试apk http://pan.baidu.com/s/1sj0qdkD 可以尝试跑一下该引擎以及示例

   第一个游戏例子截图
   ![screen shot](https://raw.githubusercontent.com/299299/Urho3D/master/Docs/shot1.jpg)
