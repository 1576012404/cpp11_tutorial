
#include <atomic>
#include <iostream>
#include <vector>
#include <future>
#include <condition_variable>
#include <queue>

using namespace std;
std::condition_variable cv;
std::mutex mutex_;
std::queue<promise<int>> tasks;
std::vector<promise<int>> tasks2;


void infer(){
    cout<<"enter_infer"<<endl;
    int batch_size=4;
    bool timeout=false;

    vector<promise<int>> promises;
    while (promises.size()<batch_size && !timeout){
        std::unique_lock<std::mutex> ulock(mutex_);
        if(cv.wait_for(ulock,1ms,[]{return tasks.size()>0;}))
        {
            auto task=std::move(tasks.front());
            promises.emplace_back(std::move(task));
            tasks.pop();
        }
    }

    for (unsigned int i = 0; i < promises.size(); i++) {
        int temp=i;
        promises[i].set_value(std::move(temp));
    }
}


int main()
{
    std::unique_ptr<std::thread> loop;
    loop = std::make_unique<std::thread>([] {
        while (true) {
            infer();
        }
    });
    for (int i=0;i<4;i++){
    std::promise<int> promise;
    auto ret=promise.get_future();
    tasks.emplace(std::move(promise));
    if (i==3){
        cout<<"last:"<<ret.get()<<endl;
    }

    }
}

