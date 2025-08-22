// Build: g++ -O3 -std=c++17 13_jetson_gstreamer_nvmm.cpp `pkg-config --cflags --libs opencv4` -o demo13
// Jetson example: use NVMM to keep frames in GPU-friendly memory.
// Requires proper GStreamer pipeline installed on device.
#include <opencv2/opencv.hpp>
int main(){
    std::string pipeline = 
        "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=1280, height=720, framerate=30/1 "
        "! nvvidconv ! video/x-raw, format=BGRx ! videoconvert ! appsink";
    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
    if(!cap.isOpened()){ std::cerr<<"Failed to open pipeline\n"; return 0; }
    cv::Mat f;
    while(cap.read(f)){ /* handoff to CUDA */ }
    return 0;
}
