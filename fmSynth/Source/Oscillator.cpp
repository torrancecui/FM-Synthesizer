/*
  ==============================================================================

    Oscillator.cpp
    Created: 20 Feb 2020 8:44:34pm
    Author:  Tom

  ==============================================================================
*/

#include "Oscillator.h"

//=====Generic Voice Implementation==========

void OscillatorVoice::isCarrier(bool carrier, AudioBuffer<float>* buffer)
{
    if(carrier && buffer) {
        this->carrier = true;
        ModBuffer = buffer;
    }
    else if(carrier && !buffer) {
        std::cerr <<  "when setting isCarrier to true, must pass in a valid AudioBuffer pointer!";
        exit(1);
    }
    else this->carrier = false;
}

void OscillatorVoice::setAngleDelta(float freq)
{
    auto cyclesPerSample = (float)pow(2, currentOctave-2) * freq / getSampleRate();
    angleDelta = cyclesPerSample * TWO_PI;
    delta = cyclesPerSample * 2.0;
}

/**
 This is where we set up all the parameters needed when a note is pressed.
 */
void OscillatorVoice::startNote(int midiNoteNumber, float velocity,
    SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    setADSRParameters();
    envelope.noteOn();

    previousAngle = 0.0;
    nextSample = 0.0;
    currentAngle = 0.0;
    hold = 0.0;
    level = velocity * 0.15;
    tailOff = 0.0;
    frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    noteToClear = true;
    
    float cyclesPerSecond;
    if (carrier)
    {
        auto octave = (float)pow(2, currentOctave-2);
        cyclesPerSecond = octave * frequency;
    }
    else cyclesPerSecond = frequency;
    
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();
    
    angleDelta = cyclesPerSample * TWO_PI;
    delta = cyclesPerSample * 2.0;
    
}

/**
 Little decay envelope, SEE MIDI Synth tutorial.
 */
void OscillatorVoice::stopNote(float /*velocity*/, bool allowTailOff)
{
    envelope.noteOff();
}

/**
 Render AUDIO for processing block.
 */
void OscillatorVoice::renderNextBlock(AudioBuffer<float>& outputBuffer,
    int startSample, int numSamples)
{
    if (angleDelta != 0.0)
    {
        parameterUpdatePerBlock();
 
        while (--numSamples >= 0)
        {
            parameterUpdatePerSample();
            
            if(carrier) setAngleDelta(frequency + ModBuffer->getSample(0,startSample));
            
            auto currentSample = (float)(generateSample(currentAngle) * level);

            if (carrier) {
                currentSample *= envelope.getNextSample();
            }
            
            if(!recycleOutput)
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);
            else {
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;) {
                    outputBuffer.clear(startSample,1);
                    outputBuffer.addSample(i, startSample, currentSample);
                }
            }
                

            currentAngle += angleDelta;
            angleCap();
            ++startSample;

            if (!envelope.isActive()) {
                if (noteToClear) {
                    clearCurrentNote();
                    noteToClear = false;
                }
            }
        }
    }
}

float OscillatorVoice::generateSample(float angle)
{
    switch (waveID)
    {
    case(SQUARE):
        return squareWave(angle);
    case(SAW):
        return sawWave(angle);
    case(TRI):
        return triangleWave(angle);
    case(NOISE):
        return noise(angle);
    case(SINE):
    default:
        return sineWave(angle);
    }
}
float OscillatorVoice::sineWave(float angle)
{
    return std::sin(angle);
}
float OscillatorVoice::squareWave(float angle)
{
    return std::tanh(std::sin(angle) * 30.0);
}
float OscillatorVoice::sawWave(float angle)
{
    if (angle <= previousAngle)
    {
        nextSample = -1.0;
        previousAngle = angle;
        return nextSample;
    }
    nextSample += delta;
    previousAngle = angle;
    return nextSample;
}
float OscillatorVoice::triangleWave(float angle)
{
    if(std::cos(angle) >= 0)
    {
        nextSample += (delta+delta);
    }
    else
    {
        nextSample -= (delta+delta);
    }
    
    return nextSample;
}

float OscillatorVoice::noise(float angle)
{
    if (angle <= previousAngle)
    {
        hold = 2.0*Random::getSystemRandom().nextFloat()-1.0;
        previousAngle = angle;
    }
    previousAngle = angle;
    return hold;
}


void OscillatorVoice::angleCap()
{
    if (currentAngle >= TWO_PI)
    {
        currentAngle -= TWO_PI;
    }
}

void OscillatorVoice::setADSRParameters() {
    
    adsr.attack = *(params->getRawParameterValue(ATTACK_ID));
    adsr.decay = *(params->getRawParameterValue(DECAY_ID));
    adsr.sustain = *(params->getRawParameterValue(SUSTAIN_ID));
    adsr.release = *(params->getRawParameterValue(RELEASE_ID));

    envelope.setParameters(adsr);
}
