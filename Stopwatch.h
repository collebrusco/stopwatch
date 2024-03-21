#ifndef Stopwatch_h
#define Stopwatch_h

enum TimeUnit {
    SECONDS = 1000000000,
    MILLISECONDS = 1000000,
    MICROSECONDS = 1000,
    NANOSECONDS = 1
};

// construct these as little simple timers
// init with time unit, default is nanoseconds
class Stopwatch {
private:
    TimeUnit unit;
    double epoch_to_construct_nanos;
    double stopwatch_start_time;
    double stopwatch_stop_time;
    bool _running;
    bool _reset;
public:
    Stopwatch(TimeUnit tu = SECONDS);
    void setUnit(TimeUnit);
    void start();
    void reset();
    bool running() const;
    double read() const;
    double read(TimeUnit) const;
    double stop();
    double stop(TimeUnit);
    void reset_start();
    double stop_reset();
    double stop_reset(TimeUnit);
    double stop_reset_start();
    double stop_reset_start(TimeUnit);

};


#endif /* Stopwatch_h */
