# stopwatch
It's really just a stopwatch: call one of `start(); stop(); read(); reset();`      
       
`stop()` and `read()` both return the time and can be passed units.        
       
Combinations of these simple controls are given, `stop_reset_start()` is particularly useful for timing loops       
           
I just wanted nothing more than a literal stopwatch in code that's a little easier to use than        
```c++
double time = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
```
