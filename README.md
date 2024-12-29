# Snake-in-CPP
Snake in C++ 
Dependentcies: open-gl/freeglut,vckpg,nlohmann/json.hpp(installed via vcpkg). to install vckg 
1. Get the zip file from the github: https://github.com/microsoft/vcpkg
2. unzip the file and plce it in the root of the main driv(C:/)
3. run bootstrap-vcpkg.bat

the snake.cpp, snake_game.exe,libfreeglut.dll are meant for windows to compile the c++ file run the command below in the directory of the file.
g++ -o snake_game snake.cpp -I C:/msys64/mingw64/include -I C:/vcpkg/installed/x64-windows/include -L C:/msys64/mingw64/lib -L C:/vcpkg/installed/x64-windows/lib -lfreeglut -lopengl32 -lglu32
for mac:
clang++ snake.cpp -o snakeApp -framework Cocoa -framework OpenGL -lglut -std=c++17

freeglut windows in Mingw
pacman -S mingw-w64-x86_64-freeglut
mac:
pacman -S mingw-w64-x86_64-freeglut
To install nlohmann:
vcpkg install nlohmann-json
