#include "Stopwatch.h"
#include <chrono>
#include <ctime>

Stopwatch::Stopwatch(TimeUnit tu) : unit(tu), stopwatch_start_time(0), stopwatch_stop_time(0), _running(false), _reset(true) {}

void Stopwatch::setUnit(TimeUnit tu) {
    unit = tu;
}

void Stopwatch::start() {
    if (!_running) {
        _running = true;
        _reset = false;
        stopwatch_start_time = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
    }
}

void Stopwatch::reset() {
    _reset = true;
    _running = false;
    stopwatch_start_time = 0;
    stopwatch_stop_time = 0;
}

bool Stopwatch::running() const {
    return _running;
}

double Stopwatch::read() const {
    return read(unit);
}

double Stopwatch::read(TimeUnit tu) const {
    if (_running) {
        auto current_time = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
        return (current_time - stopwatch_start_time) / tu;
    }
    if (!_reset)
        return (stopwatch_stop_time - stopwatch_start_time) / tu;
    return 0;
}

double Stopwatch::stop() {
    return stop(unit);
}

double Stopwatch::stop(TimeUnit tu) {
    if (_running) {
        _running = false;
        stopwatch_stop_time = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
    }
    return read(tu);
}

void Stopwatch::reset_start() {
    reset();
    start();
}

double Stopwatch::stop_reset() {
    return stop_reset(unit);
}

double Stopwatch::stop_reset(TimeUnit tu) {
    double elapsed = stop(tu);
    reset();
    return elapsed;
}

double Stopwatch::stop_reset_start() {
    return stop_reset_start(unit);
}

double Stopwatch::stop_reset_start(TimeUnit tu) {
    double elapsed = stop(tu);
    reset_start();
    return elapsed;
}
