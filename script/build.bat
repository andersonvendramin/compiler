@echo off

pushd %~dp0
if not exist "..\build" (md "..\build")
set common_compiler_flags=/MTd /nologo /Od /W4 /Z7 /wd4100 /wd4101 /wd4189 /wd4201
set common_linker_flags=/DEBUG:FASTLINK /INCREMENTAL:NO /OPT:REF
pushd "..\build"
cls
if %errorlevel% == 0 (cl /LD %common_compiler_flags% "..\source\library\base.c" /link %common_linker_flags%)
if %errorlevel% == 0 (cl /LD %common_compiler_flags% "..\source\library\platform.c" /link %common_linker_flags% "base.lib")
if %errorlevel% == 0 (cl /LD %common_compiler_flags% "..\source\library\string.c" /link %common_linker_flags% "base.lib")
if %errorlevel% == 0 (cl %common_compiler_flags% "..\source\compiler.c" /link %common_linker_flags% "base.lib" "string.lib" "platform.lib")
if %errorlevel% == 0 (cl %common_compiler_flags% "..\source\unity\library\unity_base.c" /link %common_linker_flags% "base.lib" "string.lib")
if %errorlevel% == 0 (cl %common_compiler_flags% "..\source\unity\library\unity_platform.c" /link %common_linker_flags% "base.lib" "string.lib" "platform.lib")
popd
popd