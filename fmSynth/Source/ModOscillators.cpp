//
//  ModOscillators.cpp
//  fmSynth
//
//  Created by Jack Kilgore on 2/21/20.
//

#include "ModOscillators.h"

void ModOscVoice_0::startNote(int midiNoteNumber, float velocity,
    SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    setADSRParameters();
    envelope.noteOn();
    noteToClear = true;

    rawMultiple = (int)(*params->getRawParameterValue(MOD_MULTIPLE_ID));
    if(rawMultiple < 0)
      multipleOfCarrier = -1 * 1/(float)rawMultiple;
    else multipleOfCarrier = rawMultiple;
    detune = *params->getRawParameterValue(MOD_DETUNE_ID);

    amount = *params->getRawParameterValue(MOD_AMT_ID);
    
    currentOctave = (int)(*params->getRawParameterValue(OCTAVE_ID));
    
    waveID = (int)(*params->getRawParameterValue(MOD_WAVE_ID));

    previousAngle = 0.0;
    nextSample = 0.0;
    currentAngle = 0.0;
    setLevel(amount);
    tailOff = 0.0;
    carrierFrequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    frequency = carrierFrequency * multipleOfCarrier + detune;
    setAngleDelta(frequency);
}


void ModOscVoice_0::parameterUpdatePerBlock()
{
    int change;
    float changeF;
       
    change = (int)(*params->getRawParameterValue(MOD_WAVE_ID)) - waveID;
    if (change != 0)
        waveID = change + waveID;
    
    change = (int)(*params->getRawParameterValue(MOD_MULTIPLE_ID)) - rawMultiple;
    
    if (change != 0)
    {
        rawMultiple = (int)(*params->getRawParameterValue(MOD_MULTIPLE_ID));
        if(rawMultiple < 0)
            multipleOfCarrier = -1 * 1/(float)rawMultiple;
        else multipleOfCarrier = rawMultiple;
        frequency = carrierFrequency * multipleOfCarrier + detune;
        setAngleDelta(frequency);
    }
    
    changeF = (*params->getRawParameterValue(MOD_DETUNE_ID)) - detune;
    if (changeF != 0)
    {
        detune = *params->getRawParameterValue(MOD_DETUNE_ID);
        frequency = carrierFrequency * multipleOfCarrier + detune;
        setAngleDelta(frequency);
    }
    
    changeF = (*params->getRawParameterValue(MOD_AMT_ID)) - amount;
    if (changeF != 0)
    {
        amount = *params->getRawParameterValue(MOD_AMT_ID);
        frequency = carrierFrequency * multipleOfCarrier + detune;
        setAngleDelta(frequency);
    }
}


void ModOscVoice_1::startNote(int midiNoteNumber, float velocity,
    SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    setADSRParameters();
    envelope.noteOn();
    noteToClear = true;

    rawMultiple = (int)(*params->getRawParameterValue(MOD_MULTIPLE_1_ID));
    if(rawMultiple < 0)
      multipleOfCarrier = -1 * 1/(float)rawMultiple;
    else multipleOfCarrier = rawMultiple;
    detune = *params->getRawParameterValue(MOD_DETUNE_1_ID);

    amount = *params->getRawParameterValue(MOD_AMT_1_ID);
    
    currentOctave = (int)(*params->getRawParameterValue(OCTAVE_ID));
    
    waveID = (int)(*params->getRawParameterValue(MOD_WAVE_1_ID));

    previousAngle = 0.0;
    nextSample = 0.0;
    currentAngle = 0.0;
    setLevel(amount);
    tailOff = 0.0;
    carrierFrequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    frequency = carrierFrequency * multipleOfCarrier + detune;
    setAngleDelta(frequency);
}


void ModOscVoice_1::parameterUpdatePerBlock()
{
    int change;
    float changeF;
       
    change = (int)(*params->getRawParameterValue(MOD_WAVE_1_ID)) - waveID;
    if (change != 0)
        waveID = change + waveID;
    
    change = (int)(*params->getRawParameterValue(MOD_MULTIPLE_1_ID)) - rawMultiple;
    
    if (change != 0)
    {
        rawMultiple = (int)(*params->getRawParameterValue(MOD_MULTIPLE_1_ID));
        if(rawMultiple < 0)
            multipleOfCarrier = -1 * 1/(float)rawMultiple;
        else multipleOfCarrier = rawMultiple;
        frequency = carrierFrequency * multipleOfCarrier + detune;
        setAngleDelta(frequency);
    }
    
    changeF = (*params->getRawParameterValue(MOD_DETUNE_1_ID)) - detune;
    if (changeF != 0)
    {
        detune = *params->getRawParameterValue(MOD_DETUNE_1_ID);
        frequency = carrierFrequency * multipleOfCarrier + detune;
        setAngleDelta(frequency);
    }
    
    changeF = (*params->getRawParameterValue(MOD_AMT_1_ID)) - amount;
    if (changeF != 0)
    {
        amount = *params->getRawParameterValue(MOD_AMT_1_ID);
        frequency = carrierFrequency * multipleOfCarrier + detune;
        setAngleDelta(frequency);
    }
}
