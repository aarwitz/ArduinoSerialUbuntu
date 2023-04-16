#include "../third-party/include/serial/serial.h"
#include <iostream>
#include "thread"
#include <fstream>

int main()
{
    serial::Serial my_serial("/dev/ttyACM0", 19200, serial::Timeout::simpleTimeout(3000));

    if (my_serial.isOpen())
    {
        std::cout << "Port opened succesfully" << std::endl;
    }
    else
    {
        std::cout << "Port failed to open" << std::endl;
    }
    my_serial.flushOutput();

    // Creating a file to write Arduino data into
    std::ofstream MyFile("ArduinoData.txt");


    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    int count = 10;
    while (count>0) {
        count--;
        my_serial.flushInput();
        std::string response = my_serial.read(6);
        std::cout << "Arduino: " << response;
        MyFile << response;
        // To convert into a float:
        // std::cout << std::stof(response) * 5 << std::endl;
    }

    MyFile.close();
}