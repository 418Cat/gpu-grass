clear
cd build
cmake -B . ..
cmake --build .
cp ./compile_commands.json ..
./src/main
