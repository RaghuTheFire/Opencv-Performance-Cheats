// Build: g++ -O3 -std=c++17 08_dnn_cuda.cpp `pkg-config --cflags --libs opencv4` -o demo08
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
int main(int argc,char**argv){
    if(argc<2){ std::cerr<<"usage: ./demo08 model.onnx\n"; return 0; }
    cv::dnn::Net net = cv::dnn::readNet(argv[1]);
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
    cv::Mat frame(640,640,CV_8UC3);
    cv::Mat blob = cv::dnn::blobFromImage(frame, 1/255.0, {640,640}, cv::Scalar(), true, false);
    net.setInput(blob);
    cv::Mat out = net.forward();
    std::cout<<"out shape: "<<out.size<<'\n';
    return 0;
}
