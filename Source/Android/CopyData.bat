md assets\Data
xcopy ..\..\Bin\Data\*.* assets\Data /S /E /C /Y
md assets\CoreData
xcopy ..\..\Bin\CoreData\*.* assets\CoreData /S /E /C /Y
md assets\Extra
xcopy ..\..\Bin\Extra\*.* assets\Extra /S /E /C /Y
del assets\Extra\placeholder.txt /Q
rd /S /Q assets\CoreData\Shaders\HLSL
