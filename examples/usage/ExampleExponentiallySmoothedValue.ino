// Example usage for ExponentiallySmoothedValue library by rvnash.

#include "ExponentiallySmoothedValue.h"

// This code simulates a signal that starts at 0.0, and steps instantly to 1.0
// after 10 seconds.

// The Time Constant of this exponentially smoothed value is 20 seconds.
// This means it will reach approx 0.632 in 20 seconds.
ExponentiallySmoothedValue val(20.0f);

// Here is the output from this sample program:
// 1: Time: 1, Signal: 0.000, Smoothed: 0.000
// 2: Time: 2, Signal: 0.000, Smoothed: 0.000
// 3: Time: 3, Signal: 0.000, Smoothed: 0.000
// 4: Time: 4, Signal: 0.000, Smoothed: 0.000
// 5: Time: 5, Signal: 0.000, Smoothed: 0.000
// 6: Time: 6, Signal: 0.000, Smoothed: 0.000
// 7: Time: 7, Signal: 0.000, Smoothed: 0.000
// 8: Time: 8, Signal: 0.000, Smoothed: 0.000
// 9: Time: 9, Signal: 0.000, Smoothed: 0.000
// 10: Time: 10, Signal: 0.000, Smoothed: 0.000     <-- Transition from 0 here to 1.0 at 11 seconds
// 11: Time: 11, Signal: 1.000, Smoothed: 0.049
// 12: Time: 12, Signal: 1.000, Smoothed: 0.095
// 13: Time: 13, Signal: 1.000, Smoothed: 0.139
// 14: Time: 14, Signal: 1.000, Smoothed: 0.181
// 15: Time: 15, Signal: 1.000, Smoothed: 0.221
// 16: Time: 16, Signal: 1.000, Smoothed: 0.259
// 17: Time: 17, Signal: 1.000, Smoothed: 0.295
// 18: Time: 18, Signal: 1.000, Smoothed: 0.330
// 19: Time: 19, Signal: 1.000, Smoothed: 0.362
// 20: Time: 20, Signal: 1.000, Smoothed: 0.393
// 21: Time: 21, Signal: 1.000, Smoothed: 0.423
// 22: Time: 22, Signal: 1.000, Smoothed: 0.451
// 23: Time: 23, Signal: 1.000, Smoothed: 0.478
// 24: Time: 24, Signal: 1.000, Smoothed: 0.503
// 25: Time: 25, Signal: 1.000, Smoothed: 0.528
// 26: Time: 26, Signal: 1.000, Smoothed: 0.551
// 27: Time: 27, Signal: 1.000, Smoothed: 0.573
// 28: Time: 28, Signal: 1.000, Smoothed: 0.593
// 29: Time: 29, Signal: 1.000, Smoothed: 0.613
// 30: Time: 30, Signal: 1.000, Smoothed: 0.632     <-- Reached 1-1/e of signal in 20 seconds
// 31: Time: 31, Signal: 1.000, Smoothed: 0.650
// 32: Time: 32, Signal: 1.000, Smoothed: 0.667

float signal;
int count;
int nextTime;
int startTime;

void setup()
{
  Serial.begin(9600);
  signal = 0.0f;
  // The first sample just becomes the starting point of the smoothed value
  val.newSample(signal);
  count = 0;
  startTime = Time.now();
  nextTime = startTime + 1;
}

void loop()
{
  int now = Time.now();
  if (now >= nextTime) {
    nextTime += 1;
    count++;
    if (now-startTime > 10) signal = 1.0f;
    // Add a new sample
    val.newSample(signal);
    float smoothedValue = val.val(); // Get smoothed value
    Serial.printf("%3d: Time: %d, Signal: %0.3f, Smoothed: %.3f\n", count, now-startTime, signal, smoothedValue);
  }
}
