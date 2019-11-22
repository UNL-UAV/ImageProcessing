#don't forget to chmod a+x!
g++ main.cpp -o output `pkg-config --cflags --libs opencv`
./output
exit 0