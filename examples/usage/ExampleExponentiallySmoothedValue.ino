//
//    ExampleExponentiallySmoothedValue.ino
//    Purpose: Example usage for ExponentiallySmoothedValue library
//
//    Author: Richard Nash
//    Version: 1.0.0

#include "ExponentiallySmoothedValue.h"

// This code simulates a signal that starts at 0.0, and steps instantly to 1.0
// after 10 seconds.

// The Time Constant of this exponentially smoothed value is 20 seconds.
// This means it will reach approx 0.632 in 20 seconds.
ExponentiallySmoothedValue val(20.0f);

// Here is the output from this sample program:
// Time: 1, Signal: 0.000, Smoothed: 0.000
// Time: 2, Signal: 0.000, Smoothed: 0.000
// Time: 3, Signal: 0.000, Smoothed: 0.000
// Time: 4, Signal: 0.000, Smoothed: 0.000
// Time: 5, Signal: 0.000, Smoothed: 0.000
// Time: 6, Signal: 0.000, Smoothed: 0.000
// Time: 7, Signal: 0.000, Smoothed: 0.000
// Time: 8, Signal: 0.000, Smoothed: 0.000
// Time: 9, Signal: 0.000, Smoothed: 0.000
// Time: 10, Signal: 0.000, Smoothed: 0.000     <-- Transition from 0.0 here to 1.0 at 10 seconds
// Time: 11, Signal: 1.000, Smoothed: 0.049
// Time: 12, Signal: 1.000, Smoothed: 0.095
// Time: 13, Signal: 1.000, Smoothed: 0.139
// Time: 14, Signal: 1.000, Smoothed: 0.181
// Time: 15, Signal: 1.000, Smoothed: 0.221
// Time: 16, Signal: 1.000, Smoothed: 0.259
// Time: 17, Signal: 1.000, Smoothed: 0.295
// Time: 18, Signal: 1.000, Smoothed: 0.330
// Time: 19, Signal: 1.000, Smoothed: 0.362
// Time: 20, Signal: 1.000, Smoothed: 0.393
// Time: 21, Signal: 1.000, Smoothed: 0.423
// Time: 22, Signal: 1.000, Smoothed: 0.451
// Time: 23, Signal: 1.000, Smoothed: 0.478
// Time: 24, Signal: 1.000, Smoothed: 0.503
// Time: 25, Signal: 1.000, Smoothed: 0.528
// Time: 26, Signal: 1.000, Smoothed: 0.551
// Time: 27, Signal: 1.000, Smoothed: 0.573
// Time: 28, Signal: 1.000, Smoothed: 0.593
// Time: 29, Signal: 1.000, Smoothed: 0.613
// Time: 30, Signal: 1.000, Smoothed: 0.632     <-- Reached (1-1/e) of signal at 30 seconds
// Time: 31, Signal: 1.000, Smoothed: 0.650
// Time: 32, Signal: 1.000, Smoothed: 0.667

float signal; // The current signal

int nextTime;
int startTime;

void setup()
{
  Serial.begin(9600);
  signal = 0.0f;
  val.newSample(signal);  // The first sample just becomes the starting point of the smoothed value
  startTime = Time.now();
  nextTime = startTime + 1;
}

void loop()
{
  int now = Time.now();
  if (now >= nextTime) {
    nextTime += 1;
    if (now-startTime > 10) signal = 1.0f;  // At 10 seconds the signal steps to 1.0
    val.newSample(signal);  // Add a new sample. Note the time is kept by the object itself.
    float smoothedValue = val.val(); // Get smoothed value
    Serial.printf("Time: %d, Signal: %0.3f, Smoothed: %.3f\n", now-startTime, signal, smoothedValue);
  }
}
