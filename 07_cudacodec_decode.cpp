// Build: g++ -O3 -std=c++17 07_cudacodec_decode.cpp `pkg-config --cflags --libs opencv4` -o demo07
// Requires OpenCV built with cudacodec; run with a file path argument.
#include <opencv2/cudacodec.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <iostream>
int main(int argc,char**argv){
    if(argc<2){ std::cerr<<"usage: ./demo07 video.mp4\n"; return 0; }
    auto reader = cv::cudacodec::createVideoReader(argv[1]);
    cv::cuda::GpuMat frame, gray;
    while(reader->nextFrame(frame)){
        cv::cuda::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        // keep on GPU for next steps...
    }
    return 0;
}
