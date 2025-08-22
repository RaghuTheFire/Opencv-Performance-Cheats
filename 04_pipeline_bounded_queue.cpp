// Build: g++ -O3 -std=c++17 04_pipeline_bounded_queue.cpp `pkg-config --cflags --libs opencv4` -lpthread -o demo04
#include <opencv2/opencv.hpp>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <optional>

template<class T>
class BoundedQ{
    std::queue<T> q; size_t cap; std::mutex m; std::condition_variable cv; bool stop=false;
public:
    BoundedQ(size_t c):cap(c){}
    void push(T v){ std::unique_lock<std::mutex> lk(m);
        cv.wait(lk,[&]{return q.size()<cap||stop;}); if(stop) return; q.push(std::move(v)); lk.unlock(); cv.notify_all();}
    std::optional<T> pop(){ std::unique_lock<std::mutex> lk(m);
        cv.wait(lk,[&]{return !q.empty()||stop;}); if(q.empty()) return std::nullopt; T v=std::move(q.front()); q.pop(); lk.unlock(); cv.notify_all(); return v;}
    void shutdown(){ std::lock_guard<std::mutex> lk(m); stop=true; cv.notify_all(); }
};

int main(){
    cv::VideoCapture cap(0);
    if(!cap.isOpened()) return 0;
    BoundedQ<cv::Mat> q1(4), q2(4);
    std::atomic<bool> alive{true};

    std::thread t1([&]{ cv::Mat f; while(alive){ if(!cap.read(f)) break; q1.push(f.clone()); } q1.shutdown(); });
    std::thread t2([&]{ while(alive){ auto m=q1.pop(); if(!m) break; cv::Mat g; cv::cvtColor(*m,g,cv::COLOR_BGR2GRAY); q2.push(std::move(g)); } q2.shutdown(); });
    std::thread t3([&]{ while(alive){ auto g=q2.pop(); if(!g) break; cv::imshow("out",*g); if(cv::waitKey(1)==27) {alive=false;break;} } });
    t1.join(); t2.join(); t3.join(); return 0;
}
