Utilizes https://github.com/jordansissel/xdotool
wayland must be disabled

mkdir build 
cd build 
cmake -G "Unix Makefiles" ../source 
cmake --build . --config Release --target bot