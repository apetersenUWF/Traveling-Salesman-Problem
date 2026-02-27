#include <chrono>
class StopWatch {
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;
    public:
        StopWatch();
        void start();
        void stop();
        double getElapsedTime();
};