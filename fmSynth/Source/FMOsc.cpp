//
//  FMOsc.cpp
//  fmSynth
//
//  Created by Jack Kilgore on 2/19/20.
//

#include "FMOsc.h"
/**
 This is where we set up all the parameters needed when a note is pressed.
 */
void FMVoice::startNote (int midiNoteNumber, float velocity,
                SynthesiserSound* sound, int currentPitchWheelPosition)
{
    mModulator.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    
    mModulator_1.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    
    mCarrier.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
   
}

/**
 Render AUDIO for processing block.
 */
void FMVoice::renderNextBlock (AudioBuffer<float>& outputBuffer,
                      int startSample, int numSamples)
{
    ModBuffer.clear();
    mModulator.renderNextBlock(ModBuffer, startSample, numSamples);
    mModulator_1.renderNextBlock(ModBuffer, startSample, numSamples);
    mCarrier.renderNextBlock(ModBuffer, startSample, numSamples);

    for (int sample = 0; sample < numSamples; ++sample) {
        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
            outputBuffer.addSample(channel, startSample, ModBuffer.getSample(0, startSample));
        }
        ++startSample;
    }
}


void FMVoice::stopNote (float velocity, bool allowTailOff)
{
    mModulator.stopNote(velocity, allowTailOff);
    mCarrier.stopNote(velocity, allowTailOff);
}

