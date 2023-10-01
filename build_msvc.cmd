mkdir build_msvc
cd build_msvc
cmake ../vs20xxTest
cmake --build . --target chess_board --config Release
cd  Release
for /r %%a in (*.exe) do copy %%a "./../../"
cd ../..
