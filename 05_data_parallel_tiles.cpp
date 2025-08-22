// Build: g++ -O3 -std=c++17 05_data_parallel_tiles.cpp `pkg-config --cflags --libs opencv4` -o demo05
#include <opencv2/opencv.hpp>
#include <opencv2/core/parallel/parallel.hpp>
int main(){
    cv::Mat img(1080,1920,CV_8UC1, cv::Scalar(0));
    cv::parallel_for_(cv::Range(0, img.rows), [&](const cv::Range& r){
        for(int y=r.start; y<r.end; y+=256)
            for(int x=0; x<img.cols; x+=256){
                cv::Rect roi(x,y, std::min(256,img.cols-x), std::min(256,img.rows-y));
                cv::Mat patch = img(roi);
                cv::threshold(patch, patch, 128, 255, cv::THRESH_BINARY);
            }
    });
    return 0;
}
