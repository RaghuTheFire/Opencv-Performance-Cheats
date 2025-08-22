// Build: g++ -O3 -std=c++17 03_stable_color_format.cpp `pkg-config --cflags --libs opencv4` -o demo03
#include <opencv2/opencv.hpp>
int main(){
    cv::Mat bgr(480,640,CV_8UC3);
    cv::Mat gray; cv::cvtColor(bgr, gray, cv::COLOR_BGR2GRAY); // one conversion
    // Keep downstream in gray to avoid BGR<->RGB<->GRAY ping-pong
    cv::Mat edges; cv::Canny(gray, edges, 50, 150);
    return 0;
}
