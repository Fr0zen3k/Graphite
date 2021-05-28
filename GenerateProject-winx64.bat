call vendor\bin\Premake\premake5.exe vs2019
xcopy /s /y /v Graphite\vendor\assimp\build\bin\Debug\assimp-vc142-mtd.dll bin\Debug-windows-x86_64\Sandbox
xcopy /s /y /v Graphite\vendor\assimp\build\bin\Debug\assimp-vc142-mtd.dll bin\Dist-windows-x86_64\Sandbox
xcopy /s /y /v Graphite\vendor\assimp\build\bin\Debug\assimp-vc142-mtd.dll bin\Release-windows-x86_64\Sandbox
PAUSE