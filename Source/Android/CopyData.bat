md assets\Data
xcopy ..\Bin\Data\*.* assets\Data /S /E /C /Y
md assets\CoreData
xcopy ..\Bin\CoreData\*.* assets\CoreData /S /E /C /Y
rd /S /Q assets\CoreData\Shaders\HLSL
