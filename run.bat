REM call "Release\CPrime.exe" -config "Cprime\vs2017.h"  -outDir "Generated" -build "CPrime\Build.h" -o "out.c"

call "C:\Users\thiago\Source\Repos\emsdk\emsdk_env.bat"
call emcc "CPrime\Generated\out.c"  -o "Web\cprime.js" -o "index.html" -s EXPORTED_FUNCTIONS="['_CompileText']" 
