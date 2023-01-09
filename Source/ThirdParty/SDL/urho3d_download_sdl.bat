:: Данный батник качает SDL нужной версии в папку repo

:: Меняем кодировку консоли на UTF-8
chcp 65001

:: Путь к git.exe
set "PATH=c:\program files\git\bin"

:: Качаем ветку SDL2 в папку repo
git clone --branch SDL2 https://github.com/libsdl-org/SDL repo

:: Возвращаем состояние репозитория к определённой версии
git -C repo reset --hard 0b0d256a69a57397c3aebaf086e567264a2629c2

:: Ждём нажатие Enter перед закрытием консоли
pause
