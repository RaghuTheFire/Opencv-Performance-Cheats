// Build: g++ -O3 -std=c++17 09_pinned_memory_pagelocked.cpp `pkg-config --cflags --libs opencv4` -o demo09
#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>
int main(){
    cv::cuda::HostMem h(cv::Size(1280,720), CV_8UC3, cv::cuda::HostMem::PAGE_LOCKED);
    cv::Mat host = h.createMatHeader();
    host.setTo(cv::Scalar(0,0,0));
    cv::cuda::GpuMat d;
    cv::cuda::Stream st;
    d.upload(host, st); // faster async upload from pinned memory
    st.waitForCompletion();
    return 0;
}
