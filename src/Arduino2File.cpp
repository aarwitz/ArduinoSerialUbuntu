#include "../third-party/include/serial/serial.h"
#include <iostream>
#include "thread"
#include <fstream>
#include "socket.hpp"

int main()
{
    serial::Serial my_serial("/dev/ttyACM0", 19200, serial::Timeout::simpleTimeout(3000));
    
    Socket::Ptr server = std::make_shared<Socket>("127.0.0.1",12345);

    if (my_serial.isOpen())
    {
        std::cout << "Port opened succesfully" << std::endl;
    }
    else
    {
        std::cout << "Port failed to open" << std::endl;
    }
    my_serial.flushOutput();
    
    server->socket_connect();

    // Creating a file to write Arduino data into
   // std::ofstream MyFile("ArduinoData.txt");


    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    int count = 100;
    while (count>0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(4000));
        count--;
        my_serial.flushInput();
        std::string response;
       // std::string response = my_serial.read(20);
        response = my_serial.readline(20, "\n");
        std::cout << "Arduino: " << response;

		//std::string send_str = std::to_string(velocity);
		server->socket_send(response);
      // MyFile << response;
        // To convert into a float:
        // std::cout << std::stof(response) * 5 << std::endl;
    }

    //MyFile.close();
}
