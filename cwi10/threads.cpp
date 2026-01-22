#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#include <cctype>
#include <cmath>
#include <string>

#define LETTER_COUNT 26

struct context {
    std::string content;
    unsigned long count[LETTER_COUNT] = {0};
    double sumOfSquares = 0;
    std::mutex mutex;
};

void countLetters(context& ctx, size_t begin, size_t end) {
    unsigned long localCount[LETTER_COUNT] = {0};
    double localSum = 0.0;

    for (size_t i = begin; i < end; ++i) {
        unsigned char c = ctx.content[i];

        localSum += std::sqrt(static_cast<double>(c));

        if (std::isalpha(c)) {
            c = std::tolower(c);
            localCount[c - 'a']++;
        }
    }

    std::lock_guard<std::mutex> lock(ctx.mutex);
    for (int i = 0; i < LETTER_COUNT; ++i) {
        ctx.count[i] += localCount[i];
    }
    ctx.sumOfSquares += localSum;
}

int main(int argc, char* argv[]) {
    unsigned int threadCount = (argc >= 3) ? std::stoi(argv[2]) : std::thread::hardware_concurrency();

    if (threadCount < 1)
        threadCount = 1;

    context ctx;
    
    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Nie można otworzyć pliku\n";
        return 1;
    }

    ctx.content.assign(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );  

    size_t length = ctx.content.size();
    size_t chunkSize = length / threadCount;

    std::vector<std::thread> threads;

    for (unsigned int i = 0; i < threadCount; ++i) {
        size_t begin = i * chunkSize;
        size_t end = (i == threadCount - 1) ? length : begin + chunkSize;
        threads.push_back(std::thread(countLetters, std::ref(ctx), begin, end));
    }

    for (auto& t : threads) {
        t.join();
    }

    for (int i = 0; i < LETTER_COUNT; ++i) {
        std::cout << static_cast<char>('a' + i)
                  << ": " << ctx.count[i] << "\n";
    }

    std::cout << "Suma pierwiastków kodów ASCII: "
              << ctx.sumOfSquares << "\n";

    return 0;
}