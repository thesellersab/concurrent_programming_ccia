#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include <string>
#include <map>
#include <condition_variable>
#include <shared_mutex>

//  Example # 1 use of std::mutex and std::lock_gaurd for concurrent printing
using namespace std;
std::mutex lock_print;
void print_names(int times,std::string msg)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    int i=0;
    while(i<times)
    {
        if(i)
        { 
            std::lock_guard<std::mutex> lck(lock_print);
            std::cout << "--- Name Printer Thread Iteration: "<<i<<" Id:" << std::this_thread::get_id() << std::endl;
            std::cout << "--- Message I have is :"<< msg << std::endl;
        }
        i++;
        int rand_num = dist(gen);
        std::this_thread::sleep_for(std::chrono::milliseconds(rand_num));
    }
}

void printer_sharing()
{
    auto thread_handl1 = std::thread(print_names, 10, "Office");
    auto thread_handl2 = std::thread(print_names, 10, "Home");
    thread_handl1.join();
    thread_handl2.join();
}

// shared dictionary example
// Model three types of thread, insertion, deletion and reterival
map<string,int> shared_map;
std::shared_mutex map_lock;

void data_generator(string name)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1);
    int i=0;
    while(i<10)
    {
        if(i)
        {
            std::unique_lock<std::shared_mutex> lck(map_lock);
            shared_map["Key_"+ to_string(i)] = i;
            std::cout<<"-- Added Key:"<<"Key_"+ to_string(i)<<" By:"<<name<<std::endl;
        }
        i++;
        auto key = dist(gen);
        std::this_thread::sleep_for(std::chrono::milliseconds(key));
    }
}
void data_reader(string name)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1);
    int i=0;
    while(i<10)
    {
        if(i)
        {

            std::shared_lock<std::shared_mutex> read_lck(map_lock);
            for(auto &pair : shared_map)
            {
                std::cout<<"-- Reading Keys:"<<pair.first;
            }
            if(!shared_map.empty()) 
                std::cout<<std::endl;
        }
        if(!shared_map.empty() || i==0)
        {
            i++;
        }
        auto key = dist(gen);
        std::this_thread::sleep_for(std::chrono::milliseconds(key));
    }
}

void data_remover(string name)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1);
    int i=0;
    while(i<10)
    {
        if(i)
        {

            std::shared_lock<std::shared_mutex> read_lck(map_lock);
            for(auto &pair : shared_map)
            {
                std::cout<<"-- Reading Key:"<<pair.first<<" Value:"<<pair.second<<"By:"<<name<<std::endl;
            }
        }
        if(!shared_map.empty())
            i++;
        auto key = dist(gen);
        std::this_thread::sleep_for(std::chrono::milliseconds(key));
    }
}

void map_sharing()
{
    auto thread_handl1 = std::thread(data_generator, "Data Generator");
    auto thread_handl2 = std::thread(data_reader, "Data Reader");
    thread_handl1.join();
    thread_handl2.join();
}
int main(int argc, char* argv[]) {
    map_sharing();
    return 0;
}

