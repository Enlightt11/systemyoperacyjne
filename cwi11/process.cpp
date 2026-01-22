#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pthread.h>
#include <cmath>
#include <cctype>
#include <cstring>

using namespace std;
#define LETTER_COUNT 26

struct context {
    pthread_mutex_t mutex;
    unsigned long count[LETTER_COUNT];
    double sum;
};

int main(int argc, char* argv[]) {
    int processCount = (argc >= 3) ? stoi(argv[2]) : sysconf(_SC_NPROCESSORS_ONLN);

    if (processCount < 1)
        processCount = 1;

    int fd = open(argv[1], O_RDONLY);

    struct stat st;
    fstat(fd, &st);
    size_t length = st.st_size;

    char* content = (char*)mmap(nullptr, length, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);

    context* ctx = (context*)mmap(
        nullptr, sizeof(context),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1, 0
    );

    memset(ctx->count, 0, sizeof(ctx->count));
    ctx->sum = 0.0;

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&ctx->mutex, &attr);

    size_t chunkSize = length / processCount;

    for (int i = 0; i < processCount; ++i) {
        if (fork() == 0) {
            size_t begin = i * chunkSize;
            size_t end = (i == processCount - 1) ? length : begin + chunkSize;

            unsigned long localCount[LETTER_COUNT] = {0};
            double localSum = 0.0;

            for (size_t j = begin; j < end; ++j) {
                unsigned char c = content[j];

                localSum += sqrt((double)c);

                if (isalpha(c)) {
                    c = tolower(c);
                    localCount[c - 'a']++;
                }
            }

            pthread_mutex_lock(&ctx->mutex);
            for (int k = 0; k < LETTER_COUNT; ++k)
                ctx->count[k] += localCount[k];
            ctx->sum += localSum;
            pthread_mutex_unlock(&ctx->mutex);

            _exit(0);
        }
    }

    for (int i = 0; i < processCount; ++i)
        wait(nullptr);

    for (int i = 0; i < LETTER_COUNT; ++i) {
        cout << char('a' + i)
            << ": " << ctx->count[i] << "\n";
    }

    cout << "Suma pierwiastków kodów ASCII: "
        << ctx->sum << "\n";

    pthread_mutex_destroy(&ctx->mutex);
    munmap(ctx, sizeof(context));
    munmap(content, length);

    return 0;
}