#include "../include/head.h"

using namespace std;
mutex mtx;
condition_variable cond;
string data;
bool bisReady = false;
bool bisProcessed = false;

void worker(){
    std::unique_lock<mutex> lock(mtx); 
    cond.wait(lock, []{return bisReady;});
    cout << "工作线程正在处理数据" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    data += "已完成处理";
    bisProcessed = true;
    cout << "工作线程已完成处理" << endl;
    lock.unlock();
    cond.notify_one();
}

int main(){

    thread workThread(worker);
    {
        lock_guard<mutex> lock(mtx);
        cout << "主线程正在准备数据" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        data = "样本数据";
        bisReady = true;
        cout << "主线程数据准备完毕" << endl;
    }

    cond.notify_one();

    {
        std::unique_lock<mutex> lock(mtx);
        cond.wait(lock, []{return bisProcessed;});
    }

    cout << "回到主线程， 数据为 ： " << data << endl;

    workThread.join();
    return 0;
}