//
//  CarrOscillators.cpp
//  fmSynth
//
//  Created by Jack Kilgore on 2/22/20.
//

#include "CarrOscillators.h"


void CarrOscVoice_0::startNote(int midiNoteNumber, float velocity,
             SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    setADSRParameters();
    envelope.noteOn();
    noteToClear = true;
    waveID = (int)(*params->getRawParameterValue(CARRIER_WAVE_ID));
    currentOctave = (int)(*params->getRawParameterValue(OCTAVE_ID));
    previousAngle = 0.0;
    nextSample = 0.0;
    currentAngle = 0.0;
    level = velocity * 0.15;
    tailOff = 0.0;
    frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    setAngleDelta(frequency);
}

void CarrOscVoice_0::parameterUpdatePerBlock()
{
    int change;

    change = (int)(*params->getRawParameterValue(CARRIER_WAVE_ID)) - waveID;
    if (change != 0)
        waveID = change + waveID;
    // check octave
    change = (int)(*params->getRawParameterValue(OCTAVE_ID)) - currentOctave;
    if (change != 0)
    {
        float adjustment = (float)pow(2, change);
        delta *= adjustment;
        angleDelta *= adjustment;
        currentOctave = change + currentOctave;
    }
}
