// Build: g++ -O3 -std=c++17 11_end_to_end_overlap.cpp `pkg-config --cflags --libs opencv4` -lpthread -o demo11
#include <opencv2/opencv.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <atomic>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
template<class T> struct BQ{ std::queue<T> q; size_t cap; std::mutex m; std::condition_variable cv; bool stop=false;
    BQ(size_t c):cap(c){} void push(T v){ std::unique_lock<std::mutex>lk(m); cv.wait(lk,[&]{return q.size()<cap||stop;}); if(stop)return; q.push(std::move(v)); lk.unlock(); cv.notify_all(); }
    bool pop(T& out){ std::unique_lock<std::mutex>lk(m); cv.wait(lk,[&]{return !q.empty()||stop;}); if(q.empty()) return false; out=std::move(q.front()); q.pop(); lk.unlock(); cv.notify_all(); return true; }
    void shutdown(){ std::lock_guard<std::mutex>lk(m); stop=true; cv.notify_all(); }};

int main(){
    cv::VideoCapture cap(0); if(!cap.isOpened()) return 0;
    BQ<cv::Mat> qH(4); BQ<cv::cuda::GpuMat> qG(4); BQ<cv::cuda::GpuMat> qP(4);
    std::atomic<bool> alive{true};

    std::thread tCap([&]{ cv::Mat f; while(alive){ if(!cap.read(f)) break; qH.push(f.clone()); } qH.shutdown(); });
    std::thread tUp([&]{ cv::cuda::Stream st; cv::cuda::GpuMat d; cv::Mat h; while(alive){ if(!qH.pop(h)) break; d.upload(h,st); st.waitForCompletion(); qG.push(d); } qG.shutdown(); });
    std::thread tGPU([&]{ cv::cuda::Stream st; cv::cuda::GpuMat g; cv::cuda::GpuMat r; while(alive){ if(!qG.pop(g)) break; cv::cuda::cvtColor(g,r,cv::COLOR_BGR2GRAY,0,st); st.waitForCompletion(); qP.push(r); } qP.shutdown(); });
    std::thread tShow([&]{ cv::cuda::GpuMat r; while(alive){ if(!qP.pop(r)) break; cv::Mat out; r.download(out); cv::imshow("out", out); if(cv::waitKey(1)==27){alive=false;break;} } });
    tCap.join(); tUp.join(); tGPU.join(); tShow.join(); return 0;
}
