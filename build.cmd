@REM 修改此处的python环境，以编译出对应python版本的pyd文件
CALL C:\ProgramData\anaconda3\Scripts\activate.bat X:/python_env
mkdir build
cd build
cmake ..
cmake --build . --target hello_world --config Release
cd  Release
for /r %%a in (*.pyd) do copy %%a "./../../"
cd ../..
@REM rmdir build /S /Q