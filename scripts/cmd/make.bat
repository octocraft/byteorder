mkdir build
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
cl /Wall /permissive- test/byteorder_test.c /Fe:build/byteorder_test.exe