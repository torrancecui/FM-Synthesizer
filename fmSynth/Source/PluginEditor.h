/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FmSynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    //FmSynthAudioProcessorEditor (FmSynthAudioProcessor&);
    FmSynthAudioProcessorEditor(FmSynthAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~FmSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FmSynthAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    Slider gainSlider;
    Slider cutoffKnob;
    Slider resKnob;
    Slider octaveKnob;
    Slider modMultipleKnob;
    Slider modDetuneKnob;
    Slider modAmtKnob;
    
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;
    
    Slider mod1MultipleKnob;
    Slider mod1DetuneKnob;
    Slider mod1AmtKnob;

    Label carrOctLabel, modMultLabel, modAmtLabel, modDetLabel, mod1MultLabel, mod1AmtLabel, mod1DetLabel;
    ComboBox modWaveSelect;
    ComboBox mod1WaveSelect;
    ComboBox carWaveSelect;
    ComboBox filterTypeSelect;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> resAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> carWaveAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> octAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> modWaveAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> modMultipleAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> modDetuneAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> modAmtAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> mod1WaveAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mod1MultipleAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mod1DetuneAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mod1AmtAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FmSynthAudioProcessorEditor)
};
