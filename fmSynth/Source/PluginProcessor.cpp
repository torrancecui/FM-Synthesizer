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
    valTreeState(*this, nullptr, "PARAMETERS", createParameterLayout()),
    synth(keyboardState)
#endif
{
    valTreeState.state = ValueTree("savedParams");
}

FmSynthAudioProcessor::~FmSynthAudioProcessor()
{
}

//==============================================================================

AudioProcessorValueTreeState::ParameterLayout FmSynthAudioProcessor::createParameterLayout()
{
    // all the parameters should be set here!

    NormalisableRange<float> cutoffRange(0.0, 20000.0, 1.0, .3, false);

    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    auto gain = std::make_unique<AudioParameterFloat>(GAIN_ID,GAIN_NAME,
                                                      NormalisableRange<float>(0.0f,1.5f,0.01f,0.75f),1.0f);
    
    auto cutoff = std::make_unique<AudioParameterFloat>(FILTER_CUTOFF_ID,FILTER_CUTOFF_NAME,
                                                      NormalisableRange<float>(30.0f,20000.0f,1.0f,0.2f),20000.0f);
    
    auto resonance = std::make_unique<AudioParameterFloat>(FILTER_RES_ID,FILTER_RES_NAME,
                                                        NormalisableRange<float>(1.0f,15.0f,0.01f,1.0f),1.0f);
    
    auto filterSelectType = std::make_unique<AudioParameterInt>(FILTER_TYPE_ID, FILTER_TYPE_NAME, 1, 5, 1);
    
    auto carrierWave = std::make_unique<AudioParameterInt>(CARRIER_WAVE_ID, CARRIER_WAVE_NAME, 1, 5, 1);
    
    auto carrierOctave = std::make_unique<AudioParameterInt>(OCTAVE_ID, OCTAVE_NAME, 1, 4, 2);
    
    auto modWave = std::make_unique<AudioParameterInt>(MOD_WAVE_ID, MOD_WAVE_NAME, 1, 5, 1);
    
    auto modMultiple = std::make_unique<AudioParameterInt>(MOD_MULTIPLE_ID, MOD_MULTIPLE_NAME, -9, 5, 2);
    
    auto modDetune = std::make_unique<AudioParameterFloat>(MOD_DETUNE_ID,MOD_DETUNE_NAME,
                                                      NormalisableRange<float>(-120.0f,120.0f,0.001f,0.3f,true),0.0f);
    
    auto modAmt = std::make_unique<AudioParameterFloat>(MOD_AMT_ID,MOD_AMT_NAME,
                                                           NormalisableRange<float>(0.0f,1000.0f,0.01f,0.6f,true),20.0f);
    
    auto modWave_1 = std::make_unique<AudioParameterInt>(MOD_WAVE_1_ID, MOD_WAVE_1_NAME, 1, 5, 1);
    
    auto modMultiple_1 = std::make_unique<AudioParameterInt>(MOD_MULTIPLE_1_ID, MOD_MULTIPLE_1_NAME, -9, 5, 0);
    
    auto modDetune_1 = std::make_unique<AudioParameterFloat>(MOD_DETUNE_1_ID,MOD_DETUNE_1_NAME,
                                                         NormalisableRange<float>(-120.0f,120.0f,0.001f,0.3f,true),0.0f);
    
    auto modAmt_1 = std::make_unique<AudioParameterFloat>(MOD_AMT_1_ID,MOD_AMT_1_NAME,
                                                              NormalisableRange<float>(0.0f,1000.0f,0.01f,0.6f,true),20.0f);
        
    auto attack = std::make_unique<AudioParameterFloat>(ATTACK_ID,ATTACK_NAME,
                                                        NormalisableRange<float>(0.001f,10.0f,0.001f,0.3f),0.01f);
    
    auto decay = std::make_unique<AudioParameterFloat>(DECAY_ID,DECAY_NAME,
                                                       NormalisableRange<float>(0.001f,5.0f,0.001f,0.3f),0.01f);
    
    auto sustain = std::make_unique<AudioParameterFloat>(SUSTAIN_ID,SUSTAIN_NAME,
                                                         NormalisableRange<float>(0.0f,1.5f,0.01f,0.9f),1.0f);
    
    auto release = std::make_unique<AudioParameterFloat>(RELEASE_ID,RELEASE_NAME,
                                                         NormalisableRange<float>(0.001f,10.0f,0.001f,0.3f),0.01f);
    
    params.push_back(std::move(gain));
    params.push_back(std::move(cutoff));
    params.push_back(std::move(resonance));
    params.push_back(std::move(filterSelectType));
    params.push_back(std::move(carrierWave));
    params.push_back(std::move(carrierOctave));
    params.push_back(std::move(modWave));
    params.push_back(std::move(modMultiple));
    params.push_back(std::move(modDetune));
    params.push_back(std::move(modAmt));
    params.push_back(std::move(modWave_1));
    params.push_back(std::move(modMultiple_1));
    params.push_back(std::move(modDetune_1));
    params.push_back(std::move(modAmt_1));
  
    params.push_back(std::move(attack));
    params.push_back(std::move(decay));
    params.push_back(std::move(sustain));
    params.push_back(std::move(release));

    return {params.begin(), params.end()};
}


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
    synth.prepareToPlay(sampleRate, samplesPerBlock);
    /**
     Clear Voice and Sound Buffer for polySynth instance.
     */
    synth.clearVoices();
    synth.clearSounds();

    synth.addVoice<FMVoice, FMSound>(12, &valTreeState);
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

    /**
        Render poly synth. NOTE does not support parameter changes of anything but pitch... YET
     */
    synth.renderNextAudioBlock(buffer, 0, buffer.getNumSamples(), midiMessages);

    filterCutoff = *valTreeState.getRawParameterValue(FILTER_CUTOFF_ID);
    filterType = *valTreeState.getRawParameterValue(FILTER_TYPE_ID);
    res = *valTreeState.getRawParameterValue(FILTER_RES_ID);
    if (filterType == 1) {
        filterL.setCoefficients(IIRCoefficients::makeLowPass(getSampleRate(), filterCutoff, res));
        filterR.setCoefficients(IIRCoefficients::makeLowPass(getSampleRate(), filterCutoff, res));
    }
    else if (filterType == 2){
        filterL.setCoefficients(IIRCoefficients::makeHighPass(getSampleRate(), filterCutoff, res));
        filterR.setCoefficients(IIRCoefficients::makeHighPass(getSampleRate(), filterCutoff, res));
    }
    else if (filterType == 3) {
        filterL.setCoefficients(IIRCoefficients::makeBandPass(getSampleRate(), filterCutoff, res));
        filterR.setCoefficients(IIRCoefficients::makeBandPass(getSampleRate(), filterCutoff, res));
    }
    else if (filterType == 4){
        filterL.setCoefficients(IIRCoefficients::makeNotchFilter(getSampleRate(), filterCutoff, res));
        filterR.setCoefficients(IIRCoefficients::makeNotchFilter(getSampleRate(), filterCutoff, res));
    }
    else if (filterType == 5) {
        filterL.setCoefficients(IIRCoefficients::makeAllPass(getSampleRate(), filterCutoff, res));
        filterR.setCoefficients(IIRCoefficients::makeAllPass(getSampleRate(), filterCutoff, res));
    }
    filterL.processSamples(buffer.getWritePointer(0, 0), buffer.getNumSamples());
    filterR.processSamples(buffer.getWritePointer(1, 0), buffer.getNumSamples());
    
    filterBrickWallL.setCoefficients((IIRCoefficients::makeHighPass(getSampleRate(), 27.0, 1.0)));
    filterBrickWallR.setCoefficients((IIRCoefficients::makeHighPass(getSampleRate(), 27.0, 1.0)));
    filterBrickWallL.processSamples(buffer.getWritePointer(0, 0), buffer.getNumSamples());
    filterBrickWallR.processSamples(buffer.getWritePointer(1, 0), buffer.getNumSamples());

    //gain rescales the volume setting to be from 0 to 1
    gain = *valTreeState.getRawParameterValue(GAIN_ID);

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
    return new FmSynthAudioProcessorEditor(*this, valTreeState);
}

//==============================================================================
void FmSynthAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    std::unique_ptr<XmlElement> xml(valTreeState.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void FmSynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> params(getXmlFromBinary(data, sizeInBytes));
    if(params != nullptr) {
        if(params ->hasTagName(valTreeState.state.getType())) {
            valTreeState.state = ValueTree::fromXml(*params);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FmSynthAudioProcessor();
}
