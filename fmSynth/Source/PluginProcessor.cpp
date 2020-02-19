/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FmSynthAudioProcessor::FmSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
    synth(keyboardState)
#else
    : synth(keyboardState)
#endif
{
    /**
     Clear Voice and Sound Buffer for polySynth instance.
     */
    synth.clearVoices();
    synth.clearSounds();

    /**
     Add the voices found in the SqaureOsc files.
     */
    synth.addVoice<SineVoice, SineSound>(12);
}

FmSynthAudioProcessor::~FmSynthAudioProcessor()
{
}

//==============================================================================
const String FmSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FmSynthAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool FmSynthAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool FmSynthAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double FmSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FmSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FmSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FmSynthAudioProcessor::setCurrentProgram(int index)
{
}

const String FmSynthAudioProcessor::getProgramName(int index)
{
    return {};
}

void FmSynthAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void FmSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    this->sampleRate = sampleRate;
    synth.prepareToPlay(sampleRate);
}

void FmSynthAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FmSynthAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void FmSynthAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

    buffer.clear();

    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; i++)
        buffer.clear(i, 0, buffer.getNumSamples());

    // WIP, NOT GENERAL ENOUGH -- Will be used to pass parameters to PolySynth.
    for (auto i = 0; i < synth.getNumVoices(); i++)
    {
        if ((tempVoice = dynamic_cast<SineVoice*>(synth.getVoice(i))))
        {
        }
    }

    /**
        Render poly synth. NOTE does not support parameter changes of anything but pitch... YET
     */
    synth.renderNextAudioBlock(buffer, 0, buffer.getNumSamples(), midiMessages);

    filterL.setCoefficients(IIRCoefficients::makeLowPass(getSampleRate(), filterCutoff));
    filterR.setCoefficients(IIRCoefficients::makeLowPass(getSampleRate(), filterCutoff));
    filterL.processSamples(buffer.getWritePointer(0, 0), buffer.getNumSamples());
    filterR.processSamples(buffer.getWritePointer(1, 0), buffer.getNumSamples());

    //gain rescales the volume setting to be from 0 to 1
    gain = (noteOnVel) / 1000.0;
    //loop through every channel and then each buffer to adjust the volume
    for (auto channel = 0; channel < buffer.getNumChannels(); channel++) {
        auto* channelBuffer = buffer.getWritePointer(channel);

        for (auto sample = 0; sample < buffer.getNumSamples(); sample++) {
            channelBuffer[sample] *= gain;
        }
    }
}

//==============================================================================
bool FmSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FmSynthAudioProcessor::createEditor()
{
    return new FmSynthAudioProcessorEditor(*this);
}

//==============================================================================
void FmSynthAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FmSynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FmSynthAudioProcessor();
}
