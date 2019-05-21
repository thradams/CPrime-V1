 
 REM GERA TODOS ARQUIVOS EM Generated
 call "Release\CPrimeWindows.exe" -config "vs2017.h"  -outDir "Generated" -build "Build.h"

 REM GERA AMALGAMATION
 call "Release\CPrimeWindows.exe" -config "vs2017.h"  -a CPrime.c -o ".\Generated\out.c"

 REM GERA JS
call "C:\Users\thiago\Source\Repos\emsdk\emsdk_env.bat"
call emcc "Generated\out.c"  -o "Web\cprime.js"  -s WASM=0 -s EXPORTED_FUNCTIONS="['_CompileText']"  -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']"