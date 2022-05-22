#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include "Logger.h"

static int NUM_OF_THREADS = std::thread::hardware_concurrency();

bool isPrime(long long number){
    if(number <=1)
        return false;
    for(int divisor = 2; divisor <= number/2; divisor++)
        if(number%divisor==0)
            return false;
    return true;
}

void PrimesThreadLoop(std::vector<long long> &counting, std::vector<long long> &numbers, int index){
    long long prime_counter = 0;
    for(long long number : numbers)
        if(isPrime(number))
            prime_counter++;
    counting[index] = prime_counter;
}

void PrimesMT(long long max){
    std::vector<std::thread> threads;
    std::vector<std::vector<long long>> thread_vectors;
    std::vector<long long> prime_counting;
    threads.reserve(NUM_OF_THREADS);
    thread_vectors.reserve(NUM_OF_THREADS);
    for(int i = 0; i < NUM_OF_THREADS; i++)
        prime_counting.push_back(0);

    int cur_thread = 0;
    for(long long i = 2; i < max; i++){
        thread_vectors[cur_thread].push_back(i);
        cur_thread = (cur_thread >= NUM_OF_THREADS-1) ? 0 : cur_thread+1;
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (int index = 0; index < NUM_OF_THREADS; index++){
        threads.push_back(std::thread(PrimesThreadLoop, std::ref(prime_counting), std::ref(thread_vectors[index]), index));
    }
    for(std::thread& t: threads)
        t.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    long long time_elapse = elapsed.count();
    long long total_prime_count = 0;
    for(long long& prime_count : prime_counting)
        total_prime_count+=prime_count;
    Logger::LogInfo("Prime numbers found: " + std::to_string(total_prime_count));
    Logger::LogInfo("Time elapsed: " + std::to_string(time_elapse) + "ms");
    threads.clear();
}

int main(int argc, char *argv[], char* envp[]) {
    const std::string help1 = "-h", help2 = "--help";
    std::string arg1, arg2;
    int number = 250000;
    if(argc>3){
        Logger::LogError("More than two argument passed");
        return 1;
    }
    if(argc > 1 && (help1.compare(argv[1]) == 0 || help2.compare(argv[1]) == 0)){
        std::cout << "\033[38;5;252m" << "How to use:" << std::endl << "\t./test *Number*" << std::endl << "\t./test *Threads* *Number*" << "\033[0m" << std::endl;
        return 0;
    }
    if(argc==1)
        Logger::LogWarning("You should pass a number as argument, using default number (250000)");
    else if(argc==2){
        arg1 = argv[1];
        try {
            number = std::stoi(arg1);
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
            number = std::stoi(arg2);
        } catch(...){
            Logger::LogError("Arguments must be a number");
            return 1;
        }
    }
    Logger::LogInfo("Running on " + std::to_string(NUM_OF_THREADS) + " threads");
    Logger::LogInfo("Total numbers to check: " + std::to_string(number));

    PrimesMT(number);

    return 0;
}
