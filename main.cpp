#include <iostream>
#include "Platform.h"

int main(int argc, char* argv[]) {
    Platform platform;
    for(int i = 0; i < 100; ++i){
        platform.registerViewer("viewer" + std::to_string(i), "Name" + std::to_string(i), Date());
        platform.registerStreamer("streamer" + std::to_string(i), "Streamer Name" + std::to_string(i), Date());
    }
    std::cout << "StreamZ" << std::endl;
    return 0;
}