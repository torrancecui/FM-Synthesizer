/*
  ==============================================================================

    SawOsc.cpp
    Created: 10 Feb 2020 9:47:20pm
    Author:  Torrance Cui

  ==============================================================================
*/

#include "SawOsc.h"

//=====SawVoice Implementation==========

void SawVoice::startNote (int midiNoteNumber, float velocity,
                SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    resetCheck = 0;
    nextSample = 0.0;
    currentAngle = 0.0;
    level = velocity * 0.15;
    tailOff = 0.0;

    auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();

    delta = cyclesPerSample * 2.0;
    twoPi = 2.0 * MathConstants<double>::pi;
    angleDelta = cyclesPerSample * twoPi;
}

void SawVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (tailOff == 0.0)
            tailOff = 1.0;
    }
    else
    {
        clearCurrentNote();
        angleDelta = 0.0;
    }
}

void SawVoice::renderNextBlock (AudioBuffer<float>& outputBuffer,
                      int startSample, int numSamples)
{
    if (angleDelta != 0.0)
    {
        if (tailOff > 0.0) // [7]
        {
            while (--numSamples >= 0)
            {
                auto currentSample = (float)(saw(currentAngle) * level * tailOff);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);

                currentAngle += angleDelta;
                angleCap();
                ++startSample;

                tailOff *= 0.99; // [8]

                if (tailOff <= 0.005)
                {
                    clearCurrentNote(); // [9]

                    angleDelta = 0.0;
                    break;
                }
            }
        }
        else
        {
            while (--numSamples >= 0) // [6]
            {
                auto currentSample = (float)(saw(currentAngle) * level);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);

                currentAngle += angleDelta;
                angleCap();
                ++startSample;
            }
        }
    }
}

float SawVoice::saw(float angle)
{
    // TODO: easier way to do this just using currentAngle
    //       if currentAngle value decreases, wave must have restarted
    if (!resetCheck)
    {
        if (std::sin(angle) < 0 && std::cos(angle) >= 0) // negative and increasing
        {
            resetCheck = 1;
        }
    }
    else if (std::sin(angle) > 0 && std::cos(angle) >= 0) // positive and increasing
    {
        // sin wave just cycled, reset saw wave to -1.0
        nextSample = -1.0;
        resetCheck = 0;
        return nextSample;
    }
    nextSample += delta;
    return nextSample;

}

void SawVoice::angleCap()
{
    if (currentAngle >= twoPi)
    {
        currentAngle -= twoPi;
    }
}