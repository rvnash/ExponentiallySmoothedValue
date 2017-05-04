//
//    ExponentiallySmoothedValue.h
//    Purpose: ExponentiallySmoothedValue library header and implementation
//
//    Author: Richard Nash
//    Version: 1.0.0


#pragma once
#include "Particle.h" // Needed for millis()
#include <math.h>  // Needed for exp()

class ExponentiallySmoothedValue
{
public:
    // No default constructor. You have to choose a time constant and specify it in the constructor
    ExponentiallySmoothedValue() = delete;

    // Time constant in seconds.
    // The time constant of an exponential moving average is the amount of time
    // for the smoothed response of a unit step function to reach aproximagely 1-1/e or (63.2%) of the stepped signal.
    // See the wikipedia page here:
    //   https://en.wikipedia.org/wiki/Exponential_smoothing#Basic_exponential_smoothing
    // timeConstant - The time constant described in the above wikipedia article. The units are seconds. It
    // must be > 0.0, otherwise this code may throw math errors like divide by zero.
    ExponentiallySmoothedValue(float timeConstant)
    {
        tau = timeConstant;
        initialized = false;
    }

    // Resets the value so the next value is unfiltered.
    void reset()
    {
        initialized = false;
    }

    // Returns: the current filtered value.
    float val()
    {
        return currentValue;
    }

    // Sets a new time constant.
    // timeConstant - Must be > 0.0, otherwise this code may throw math errors like divide by zero.
    void setNewTimeConstant(float timeConstant)
    {
        tau = timeConstant;
    }

    // Adds a sample to the filtered value according to the time constant.
    // Note this class keeps internal track of the time (using millis()) of the last entry, and
    // gives more weight to samples that have taken a long time to arrive, based on the time
    // constant. In the limit, if a sample takes much longer than the time constant to arrive, then 
    // it will be essentially set as the current value. In the other limit, if a new entry takes a very
    // short amount of time to arrive compared to the time constant, it will recieve very little weight.
    //
    // Note also: Using millis() means that this function will be thrown off by sleep, since the internal
    // millis() counter is stopped during sleep.
    //
    // Finally note: this function does more floating point math than you might expect. It does
    // a conversion from float to double, a conversion from double to float, an exp() function on a double,
    // two float divides, two float multiplies, and 2 float add/subtracts. 
    //
    // Parameter
    //  sample: The sampled value.
    // Returns: The current value (same as val())
    float newSample(float sample)
    {
        unsigned long now = millis();
        if (!initialized) {
            currentValue = sample;
            lastSample = now;
            initialized = true;
            return val();
        } else {
            unsigned long msSinceLast = now - lastSample;
            float deltaT = (float)msSinceLast / 1000.0f;
            const float currentValueWeight = exp(-deltaT/tau);
            const float newSampleWeight = 1.0f - currentValueWeight;
            currentValue = newSampleWeight * sample + currentValueWeight * currentValue;
            lastSample = now;
            return val();
        }
    }

  private:
      bool initialized;  // Has a value been stored yet?
      float currentValue;  // The currrent internal smoothed value
      float tau; // The time constant.
      unsigned long lastSample;   // The millis() time the last sample was stored.
};
