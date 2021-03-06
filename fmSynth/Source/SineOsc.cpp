/*
  ==============================================================================

    SineOsc.cpp
    Created: 10 Feb 2020 9:48:07pm
    Author:  Torrance Cui

  ==============================================================================
*/

#include "SineOsc.h"

//=====SineVoice Implementation==========

/**
 This is where we set up all the parameters needed when a note is pressed.
 */
void SineVoice::startNote (int midiNoteNumber, float velocity,
                SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    currentAngle = 0.0;
    level = velocity * 0.15;
    tailOff = 0.0;

    auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();

    twoPi = 2.0 * MathConstants<double>::pi;
    angleDelta = cyclesPerSample * twoPi;
}

/**
 Little decay envelope, SEE MIDI Synth tutorial.
 */
void SineVoice::stopNote (float /*velocity*/, bool allowTailOff)
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

/**
 Render AUDIO for processing block.
 */
void SineVoice::renderNextBlock (AudioBuffer<float>& outputBuffer,
                      int startSample, int numSamples)
{
    if (angleDelta != 0.0)
    {
        if (tailOff > 0.0) // [7]
        {
            while (--numSamples >= 0)
            {
                auto currentSample = (float) (std::sin (currentAngle) * level * tailOff);
                
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                
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
                auto currentSample = (float) (std::sin (currentAngle) * level);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);

                currentAngle += angleDelta;
                angleCap();
                ++startSample;
            }
        }
    }
}

void SineVoice::angleCap()
{
    if (currentAngle >= twoPi)
    {
        currentAngle -= twoPi;
    }
}