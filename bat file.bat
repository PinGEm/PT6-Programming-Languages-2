@echo on

g++ -m64 -Wall -O2 -std=c++17 -c main.cpp
g++ -m64 -Wall -O2 -std=c++17 main.o -o temperature_predicter

pause
exit