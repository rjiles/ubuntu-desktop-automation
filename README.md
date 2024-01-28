Utilizes https://github.com/jordansissel/xdotool
wayland must be disabled
sudo apt install xdotool
sudo apt install -y libopencv-dev

export DISPLAY=:0
mkdir build 
cd build 
cmake -G "Unix Makefiles" ../source 
cmake --build . --config Release --target ubuntuDesktopBot