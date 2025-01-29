#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void prime_finder(vector<int> &primes, int range_start, int range_end)
{
    for (int num = range_start; num <= range_end; ++num) {
        bool is_prime = true;
        if (num <= 1) {
            continue;
        }
        for (int i = 2; i * i <= num; ++i) {
            if (num % i == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            primes.push_back(num);
        }
    }
}

int main(int argc, char *argv[])
{
    int start = 1<<10;
    int end = 1<<16;
    int concurrency = 4;
    std::cout<<"Searching for primes in range ["<<start<<", "<<end<<"]"<<"using single thread"<<std::endl;
    vector<int> primes_ref;
    vector<int> primes_res;
    prime_finder(primes_ref,start,end);
    std::vector<std::thread> threads;
    vector<vector<int>> primes(concurrency);
    auto num_rnage = (end-start);
    auto interval_size = num_rnage/concurrency;
    for(int t=0;t<concurrency;t++)
    {
        threads.push_back(std::thread(prime_finder,std::ref(primes[t]),start +(t*interval_size),start + ((t+1)*interval_size)));
    }
    for(auto &t:threads)
    {
        t.join();
    }
    for(auto &p:primes)
    {
        primes_res.insert(primes_res.end(),p.begin(),p.end());
    }
    std::cout<<"Number of primes found using single thread: "<<primes_ref.size()<<std::endl;
    std::cout<<"Number of primes found using multiple threads: "<<primes_res.size()<<std::endl;
    std::equal(primes_ref.begin(),primes_ref.end(),primes_res.begin())?std::cout<<"Both results are Ssame\n":std::cout<<"Results are different\n";
    std::cout<<"Exiting the program"<<std::endl;
    return 0;
}
