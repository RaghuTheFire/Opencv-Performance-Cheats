// Build: g++ -O3 -std=c++17 02_avoid_clone_keep_views.cpp `pkg-config --cflags --libs opencv4` -o demo02
#include <opencv2/opencv.hpp>
int main() {
    cv::Mat img(480,640,CV_8UC3, cv::Scalar(10,20,30));
    // Bad: cv::Mat copy = img.clone();  // deep copy
    // Good: create a header/view over ROI (no copy)
    cv::Rect roi(100,100,200,200);
    cv::Mat view = img(roi); // shares data
    view.setTo(cv::Scalar(0,255,0)); // modifies ROI in original
    return 0;
}
