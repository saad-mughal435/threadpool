#include <future>
#include <iostream>
#include <vector>

#include "tp/thread_pool.hpp"

int main() {
    tp::ThreadPool pool;
    std::cout << "ThreadPool with " << pool.size() << " worker threads\n";

    const long n = 1'000'000;
    const int chunks = 8;
    std::vector<std::future<long>> parts;
    for (int c = 0; c < chunks; ++c) {
        parts.push_back(pool.submit([c, chunks, n] {
            long sum = 0;
            for (long i = c * (n / chunks) + 1; i <= (c + 1) * (n / chunks); ++i) sum += i;
            return sum;
        }));
    }

    long total = 0;
    for (std::future<long>& f : parts) total += f.get();
    std::cout << "Parallel sum of 1.." << n << " = " << total << "\n";
    return 0;
}
