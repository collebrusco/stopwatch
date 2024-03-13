//
//  Stopwatch.h
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/13/23.
//
//

#ifndef Stopwatch_h
#define Stopwatch_h

#include <chrono>
#include <ctime>
enum TimeUnit {
    SECONDS = 1000000000,
    MILLISECONDS = 1000000,
    MICROSECONDS = 1000,
    NANOSECONDS = 1
};
double since_launch(TimeUnit);          // return time since launch
// stopwatch
void global_stopwatch_start();                 // start stopwatch
double global_stopwatch_stop(TimeUnit); // stop & read stopwatch
double global_stopwatch_read(TimeUnit); // read stopwatch, safe even after stop
double global_stopwatch_stopstart(TimeUnit); // stop, read, and restart stopwatch.
                                             // do this at the end of a loop to read dt

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
    Stopwatch();
    Stopwatch(TimeUnit);
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
