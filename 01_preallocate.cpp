// Build: g++ -O3 -std=c++17 01_preallocate.cpp `pkg-config --cflags --libs opencv4` -o demo01
#include <opencv2/opencv.hpp>
int main() {
    cv::Mat frame(1080,1920,CV_8UC3);
    cv::Mat gray, tmp;                // predeclare once
    // Simulate many frames
    for (int i=0;i<300;i++) {
        frame.setTo(cv::Scalar(0,0,0));
        if (gray.empty()) gray.create(frame.rows, frame.cols, CV_8UC1);
        if (tmp.empty())  tmp.create(frame.rows, frame.cols, CV_8UC3);
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY); // reuses buffers
        cv::cvtColor(gray, tmp, cv::COLOR_GRAY2BGR);
    }
    return 0;
}
