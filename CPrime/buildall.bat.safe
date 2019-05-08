 call "Release\CPrimeWindows.exe" -config "vs2017.h"  -cxe -outDir "Generated" -build "Build.h" -o "out.c"

call "C:\Users\thiago\Source\Repos\emsdk\emsdk_env.bat"
call emcc "Generated\out.c"  -o "Web\cprime.js"  -s EXPORTED_FUNCTIONS="['_CompileText']"  -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']"
