// Build: g++ -O3 -std=c++17 10_zero_copy_shared.cpp `pkg-config --cflags --libs opencv4` -o demo10
#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>
int main(){
    // Zero-copy/shared mapping (best on iGPU/Jetson)
    cv::cuda::HostMem shared(cv::Size(640,480), CV_8UC3, cv::cuda::HostMem::SHARED);
    cv::Mat  h = shared.createMatHeader();
    cv::cuda::GpuMat d = shared.createGpuMatHeader(); // same memory
    h.setTo(cv::Scalar(50,100,150)); // CPU write
    cv::cuda::GpuMat gray;
    cv::cuda::cvtColor(d, gray, cv::COLOR_BGR2GRAY); // GPU reads without explicit upload
    return 0;
}
