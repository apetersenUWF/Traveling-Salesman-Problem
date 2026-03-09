#include <chrono>
class StopWatch {
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;
    public:
        StopWatch();
        void start();//start timing
        void stop();//stop timing
        double getElapsedTime();//gets the difference between start time and stop time in seconds
};