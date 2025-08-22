// Build: g++ -O3 -std=c++17 12_tickmeter_nvtx.cpp `pkg-config --cflags --libs opencv4` -o demo12 -lnvToolsExt
#include <opencv2/opencv.hpp>
#include <nvtx3/nvToolsExt.h>
int main(){
    cv::TickMeter tm; tm.start();
    nvtxRangePushA("work");
    cv::Mat a(1000,1000,CV_32F, 1.0f), b, c;
    cv::GaussianBlur(a,b,cv::Size(9,9),1.5);
    cv::Sobel(b,c,CV_32F,1,0);
    nvtxRangePop();
    tm.stop();
    std::cout<<"elapsed ms: "<<tm.getTimeMilli()<<'\n';
    return 0;
}
