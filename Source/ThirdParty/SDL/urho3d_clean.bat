:: Этот батник удаляет лишние файлы и папки после скачивания SDL

:: Меняем кодировку консоли на UTF-8
chcp 65001

:: В корне удаляем ненужные папки
rd /s /q .git
rd /s /q .github
rd /s /q acinclude
:: android-project
rd /s /q android-project-ant
rd /s /q build-scripts
:: cmake
rd /s /q docs
:: include
rd /s /q mingw
:: src
rd /s /q test
rd /s /q VisualC
rd /s /q VisualC-GDK
rd /s /q VisualC-WinRT
rd /s /q visualtest
:: wayland-protocols
rd /s /q Xcode
rd /s /q Xcode-iOS

:: В корне удаляем ненужные файлы
del .clang-format
del .editorconfig
del .gitignore
del .wikiheaders-options
del configure
del configure.ac
del *.in
del sdl2.m4
del README.md
del Makefile.*
del Android.mk
del autogen.sh
del BUGS.txt
:: CMakeLists.txt
:: CREDITS.txt
del INSTALL.txt
:: LICENSE.txt
:: README-SDL.txt
del TODO.txt
:: WhatsNew.txt

:: Удаление всяких скриптов
del /s *.pl
del /s *.py
del /s *.sh

:: В папке android-project удаляем ненужное
:: app
rd /s /q android-project\gradle
del android-project\gradlew
del android-project\gradlew.bat
del android-project\build.gradle
del android-project\settings.gradle
del android-project\gradle.properties

:: В папке android-project\app удаляем ненужное
rd /s /q android-project\app\jni
:: src
del android-project\app\build.gradle
del android-project\app\proguard-rules.pro

:: В папке android-project\app\src\main удаляем ненужное
:: java
rd /s /q android-project\app\src\main\res
:: AndroidManifest.xml

:: Удаляем все тесты
rd /s /q cmake\test
del include\SDL_test*.h
rd /s /q src\test

:: Удаляем все конфигурационные h-файлы из папки include, так как
:: файл SDL_config.h генерируется с помощью SDL_config.h.cmake
del include\SDL_config*.h

:: Ждём нажатие Enter перед закрытием консоли
pause
