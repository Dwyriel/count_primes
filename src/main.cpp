#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <Stopwatch/stopwatch.h>
#include "Logger.h"

const int NUM_OF_THREADS_THRESHOLD = 9;
static unsigned int NUM_OF_THREADS = std::thread::hardware_concurrency();
static Stopwatch stopwatch;

bool isPrime(long long number){
    for(int divisor = 2; divisor <= number/2; divisor++)
        if(number%divisor==0)
            return false;
    return true;
}

void PrimesThreadLoop_BA(std::vector<long long> &counting, std::vector<long long> &numbers, int index){
    long long prime_counter = 0;
    for(long long number : numbers)
        if(isPrime(number))
            prime_counter++;
    counting[index] = prime_counter;
}

void Primes_BetterAssigning(long long max){
    stopwatch.start();
    std::vector<std::thread> threads;
    std::vector<std::vector<long long>> thread_numbers;
    std::vector<long long> prime_counting;
    threads.reserve(NUM_OF_THREADS);
    thread_numbers.reserve(NUM_OF_THREADS);
    prime_counting.reserve(NUM_OF_THREADS);
    for (int i = 0; i < NUM_OF_THREADS; i++) {
        prime_counting.push_back(0);
        thread_numbers.emplace_back(std::vector<long long>());
    }
    thread_numbers[0].push_back(2);
    int cur_thread = (NUM_OF_THREADS > 1) ? 1 : 0;
    for(long long i = 3; i <= max; i+=2){
        thread_numbers[cur_thread].push_back(i);
        cur_thread = (cur_thread >= NUM_OF_THREADS-1) ? 0 : cur_thread+1;
    }
    for (int index = 0; index < NUM_OF_THREADS; index++){
        threads.emplace_back(std::thread(PrimesThreadLoop_BA, std::ref(prime_counting), std::ref(thread_numbers[index]), index));
    }
    for(std::thread& t: threads)
        t.join();
    stopwatch.stop();
    long long total_prime_count = 0;
    for(long long& prime_count : prime_counting)
        total_prime_count+=prime_count;
    Logger::LogInfo("Prime numbers found: " + std::to_string(total_prime_count));
    Logger::LogInfo("Time elapsed: " + std::to_string(stopwatch.elapsedMilliseconds()) + "ms");
}

void PrimesThreadLoop_ED(std::vector<long long> &counting, const long long start, const long long end, int index){
    long long prime_counter = 0;
    for(long long number = start; number <= end ;number++)
        if(isPrime(number))
            prime_counter++;
    counting[index] = prime_counter;
}

void Primes_EquallyDividing(long long max){
    stopwatch.start();
    std::vector<std::thread> threads;
    threads.reserve(NUM_OF_THREADS);
    std::vector<long long> prime_counting;
    for(int i = 0; i < NUM_OF_THREADS; i++)
        prime_counting.push_back(0);
    long long chunk = max / NUM_OF_THREADS;
    long long prime_start = 0, prime_end = 1;
    for (int index = 0; index < NUM_OF_THREADS; index++){
        prime_start = prime_end+1;
        prime_end = (max-prime_start <= chunk) ? max : prime_start + chunk;
        threads.emplace_back(std::thread(PrimesThreadLoop_ED, std::ref(prime_counting), prime_start, prime_end, index));
    }
    for(std::thread& t: threads)
        t.join();
    stopwatch.stop();
    long long total_prime_count = 0;
    for(long long& prime_count : prime_counting)
        total_prime_count+=prime_count;
    Logger::LogInfo("Prime numbers found: " + std::to_string(total_prime_count));
    Logger::LogInfo("Time elapsed: " + std::to_string(stopwatch.elapsedMilliseconds()) + "ms");
    threads.clear();
}

int main(int argc, char *argv[], char* envp[]) {
    const std::string help1 = "-h", help2 = "--help";
    std::string arg1, arg2;
    long long number = 1000000;
    if(argc>3){
        Logger::LogError("More than two argument passed");
        return 1;
    }
    if(argc > 1 && (help1 == argv[1] || help2 == argv[1])){
        std::cout << "\033[38;5;252m" << "How to use:" << std::endl << "\tcount_primes *Number*" << std::endl << "\tcount_primes *Threads* *Number*" << "\033[0m" << std::endl;
        return 0;
    }
    if(argc==1)
        Logger::LogWarning("You should pass a number as argument, using default number (" + std::to_string(number) +")");
    else if(argc==2){
        arg1 = argv[1];
        try {
            number = std::stoll(arg1);
            if(number < 2){
                Logger::LogError("Number must bigger than 1");
                return 1;
            }
        } catch(...){
            Logger::LogError("Argument must be a number");
            return 1;
        }
    }
    else if(argc == 3){
        arg1 = argv[1];
        arg2 = argv[2];
        try{
            int temp_threads = std::stoi(arg1);
            if( temp_threads > NUM_OF_THREADS ||temp_threads < 1){
            Logger::LogError("Invalid number of threads, must be a value from 1 to " + std::to_string(NUM_OF_THREADS) + " (total threads in this system)");
                return 1;
            }
            NUM_OF_THREADS = temp_threads;
            number = std::stoll(arg2);
            if(number < 2){
                Logger::LogError("Number must bigger than 1");
                return 1;
            }
        } catch(...){
            Logger::LogError("Arguments must be a number");
            return 1;
        }
    }
    Logger::LogInfo("Running on " + std::to_string(NUM_OF_THREADS) + " threads");
    Logger::LogInfo("Total numbers to check: " + std::to_string(number));
    //magic
    NUM_OF_THREADS =  (NUM_OF_THREADS == NUM_OF_THREADS_THRESHOLD) ? NUM_OF_THREADS + 1 : (NUM_OF_THREADS > NUM_OF_THREADS_THRESHOLD) ? (unsigned int)(NUM_OF_THREADS * 1.1) : NUM_OF_THREADS;
    Primes_BetterAssigning(number);
    //Primes_EquallyDividing(number);

    return 0;
}
