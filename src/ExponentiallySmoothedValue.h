#pragma once
#include <math.h>

class ExponentiallySmoothedValue
{
public:
    // No default constructor. You have to choose a time constant and specify it in the constructor
    ExponentiallySmoothedValue() = delete;

    // Time constant in seconds.
    // The time constant of an exponential moving average is the amount of time
    // for the smoothed response of a unit step function to reach aproximagely 1-1/e or (63.2%) of the stepped signal.
    // See the wikipedia page here: https://en.wikipedia.org/wiki/Exponential_smoothing
    // timeConstant - Must be > 0.0, otherwise this code may throw math errors like divide by zero.
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
    // sample: The sampled value.
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
      bool initialized;
      float currentValue;
      float tau;
      unsigned long lastSample;
};
