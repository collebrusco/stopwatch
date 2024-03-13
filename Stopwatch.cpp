//
//  Stopwatch.cpp
//  graphics-library-interface
//
//  Created by Frank Collebrusco on 3/13/23.
//
//

#include "Stopwatch.h"

#include <chrono>
#include <ctime>

static std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
static auto duration = now.time_since_epoch();
static auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
static double epoch_to_launch_nanos = nanoseconds.count();

static double nanos(){
    now = std::chrono::system_clock::now();
    duration = now.time_since_epoch();
    nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    return (double)nanoseconds.count() - epoch_to_launch_nanos;
}
static double global_stopwatch_start_time = 0;
static double global_stopwatch_stop_time = 0;
static bool global_stopwatch_running = false;
double since_launch(TimeUnit u){
    return nanos() / (double)u;
}
void global_stopwatch_start(){
    global_stopwatch_running = true;
    global_stopwatch_start_time = nanos();
}

double global_stopwatch_stop(TimeUnit u){
    global_stopwatch_running = false;
    global_stopwatch_stop_time = nanos();
    return (global_stopwatch_stop_time - global_stopwatch_start_time) / (double)u;
}
double global_stopwatch_read(TimeUnit u){
    if (global_stopwatch_running){
        return (nanos() - global_stopwatch_start_time) / (double)u;
    }
    return (global_stopwatch_stop_time - global_stopwatch_start_time) / (double)u;
}

double global_stopwatch_stopstart(TimeUnit u){
    double dt = global_stopwatch_stop(NANOSECONDS);
    global_stopwatch_start();
    return dt / (double)u;
}

// ********************************STOPWATCH OBJ DEFNS********************************

Stopwatch::Stopwatch(){
    _reset = true;
    auto _now = std::chrono::system_clock::now();
    auto _duration = _now.time_since_epoch();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_duration);
    unit = NANOSECONDS;
    epoch_to_construct_nanos = ns.count();
}

Stopwatch::Stopwatch(TimeUnit u){
    _reset = true;
    unit = u;
    auto _now = std::chrono::system_clock::now();
    auto _duration = _now.time_since_epoch();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_duration);
    epoch_to_construct_nanos = ns.count();
}

void Stopwatch::setUnit(TimeUnit u){
    unit = u;
}

void Stopwatch::start(){
    if (_reset){
        _reset = false;
        stopwatch_start_time = nanos();
    }
    _running = true;
}

void Stopwatch::reset(){
    _reset = true;
}

bool Stopwatch::running() const {
    return _running;
}

double Stopwatch::read() const {
    return this->read(unit);
}

double Stopwatch::read(TimeUnit u) const {
    if (_running){
        return (nanos() - stopwatch_start_time) / (double)u;
    }
    return (stopwatch_stop_time - stopwatch_start_time) / (double)u;
}

double Stopwatch::stop(){
    return this->stop(unit);
}

double Stopwatch::stop(TimeUnit u){
    if (_running){
        _running = false;
        stopwatch_stop_time = nanos();
    }
    return (stopwatch_stop_time - stopwatch_start_time) / (double)u;
}

void Stopwatch::reset_start(){
    this->reset();
    this->start();
}

double Stopwatch::stop_reset(){
    return this->stop_reset(unit);
}

double Stopwatch::stop_reset(TimeUnit u){
    double r = this->stop(u);
    this->reset();
    return r;
}

double Stopwatch::stop_reset_start(){
    return this->stop_reset_start(unit);
}

double Stopwatch::stop_reset_start(TimeUnit u){
    double r = this->stop_reset(u);
    this->start();
    return r;
}
