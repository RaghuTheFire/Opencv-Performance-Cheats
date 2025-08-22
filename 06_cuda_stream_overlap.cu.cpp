// Build (with CUDA OpenCV): g++ -O3 -std=c++17 06_cuda_stream_overlap.cu.cpp `pkg-config --cflags --libs opencv4` -o demo06
#include <opencv2/opencv.hpp>
#include <opencv2/cudaimgproc.hpp>
int main(){
    cv::Mat h1(720,1280,CV_8UC3), h2(720,1280,CV_8UC3);
    cv::cuda::GpuMat d1,d2,g1,g2;
    cv::cuda::Stream s1,s2;
    d1.upload(h1, s1);
    cv::cuda::cvtColor(d1,g1,cv::COLOR_BGR2GRAY,0,s1);
    d2.upload(h2, s2);
    cv::cuda::GaussianBlur(d2,g2,cv::Size(7,7),1.5,1.5,cv::BORDER_DEFAULT,s2);
    s1.waitForCompletion(); s2.waitForCompletion();
    return 0;
}
