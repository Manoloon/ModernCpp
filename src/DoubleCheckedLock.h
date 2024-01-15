// when doing lazy initialization , we need to do a double checked lock to avoid data race , but we can face another data race due to obj construct order.

#include <mutex>
#include <thread>

class Test{
	public:
    void Func(){ std::cout << "test func" << std::endl;}
    }
void Process(){
	Test ptest = nullptr; // lazy init.
    std::once_flag ptest_flag;
    std::mutex mutex;
    std::unique_lock uni_lck(mutex);
    if(!ptest){
    	std::call_once(ptest_flag[](){
            ptest = new Test;});
        uni_lck.unlock();
        ptest->Func();
        }
}