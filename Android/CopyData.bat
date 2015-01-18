:: Only call this when using "Android" as build tree and the host system does not have the capability to create symbolic link

md assets\Data
xcopy ..\bin\Data\*.* assets\Data /S /E /C /Y
md assets\CoreData
xcopy ..\bin\CoreData\*.* assets\CoreData /S /E /C /Y
rd /S /Q assets\CoreData\Shaders\HLSL
