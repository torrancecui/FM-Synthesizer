/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FmSynthAudioProcessorEditor::FmSynthAudioProcessorEditor (FmSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    setSize (700, 400);

    processor.filterCutoff = 20000.0;
    cutoffSlider.setSliderStyle(Slider::LinearBarVertical);
    cutoffSlider.setRange(0.1, 20000.0, 1.0);
    cutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    cutoffSlider.setPopupDisplayEnabled(true, false, this);
    cutoffSlider.setValue(processor.filterCutoff);
    cutoffSlider.setSkewFactorFromMidPoint(1000);
    addAndMakeVisible(cutoffSlider);
    cutoffSlider.addListener(this); // If preferred, statements like these can be replaced with callbacks like how carWaveSelect is done

    //volumeSlider parameters
    processor.minVolume = .1;
    processor.maxVolume = 1500.0;
    processor.noteOnVel = 1.0;

    volumeSlider.setSliderStyle(Slider::LinearBarVertical);
    volumeSlider.setRange(processor.minVolume, processor.maxVolume, 1.0);
    volumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    volumeSlider.setPopupDisplayEnabled(true, false, this);
    volumeSlider.setValue(processor.noteOnVel);
    addAndMakeVisible(volumeSlider);
    volumeSlider.addListener(this);

    octaveKnob.setSliderStyle(Slider::Rotary);
    octaveKnob.setTextBoxStyle(Slider::TextBoxBelow, true, 90, 25);
    octaveKnob.setRange(2, 18, 2);
    octaveKnob.setValue(10);
    addAndMakeVisible(octaveKnob);
    octaveKnob.addListener(this);

    cmRatioKnob.setSliderStyle(Slider::Rotary);
    cmRatioKnob.setTextBoxStyle(Slider::TextBoxBelow, true, 90, 25);
    cmRatioKnob.setRange(0, 1, 0.01);
    cmRatioKnob.setValue(0.5);
    addAndMakeVisible(cmRatioKnob);
    cmRatioKnob.addListener(this);

    modAmtKnob.setSliderStyle(Slider::Rotary);
    modAmtKnob.setTextBoxStyle(Slider::TextBoxBelow, true, 90, 25);
    modAmtKnob.setRange(0, 1, 0.01);
    modAmtKnob.setValue(0.5);
    addAndMakeVisible(modAmtKnob);
    modAmtKnob.addListener(this);

    processor.currCarWave = 1;
    addAndMakeVisible(carWaveSelect);
    carWaveSelect.addItem("Sine", 1);
    carWaveSelect.addItem("Square", 2);
    carWaveSelect.addItem("Saw", 3);
    carWaveSelect.onChange = [this] { WaveSelectChanged(); };
    carWaveSelect.setSelectedId(processor.currCarWave);

    processor.currModWave = 1;
    addAndMakeVisible(modWaveSelect);
    modWaveSelect.addItem("Sine", 1);
    modWaveSelect.addItem("Square", 2);
    modWaveSelect.addItem("Saw", 3);
    modWaveSelect.setSelectedId(processor.currModWave);

}

FmSynthAudioProcessorEditor::~FmSynthAudioProcessorEditor()
{
}

void FmSynthAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    //When a slider value changes, check which slider was changed
    //and update the correct processor variable accordingly.
    if (slider == &cutoffSlider)
        processor.filterCutoff = slider->getValue();
    else if (slider == &volumeSlider)
        processor.noteOnVel = slider->getValue();
}

void FmSynthAudioProcessorEditor::WaveSelectChanged() {
    processor.synth.clearVoices();
    processor.synth.clearSounds();
    processor.currCarWave = carWaveSelect.getSelectedId();
    switch (carWaveSelect.getSelectedId()) {
    case 1: processor.synth.addVoice<SineVoice, SineSound>(12); break;
    case 2: processor.synth.addVoice<SquareVoice, SquareSound>(12); break;
    case 3: processor.synth.addVoice<SawVoice, SawSound>(12); break;
    }
}

//==============================================================================
void FmSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (18.0f);

    g.drawFittedText("Filter Cutoff", 480, 20, getWidth(), 30, Justification::left, 1);
    g.drawFittedText("Volume", 600, 20, getWidth(), 30, Justification::left, 1);
    g.drawFittedText("Modulator", 60, 20, getWidth(), 30, Justification::left, 1);
    g.drawFittedText("Carrier", 305, 20, getWidth(), 30, Justification::left, 1);

    g.setColour(Colours::grey);

    Line<float> line1(Point<float>(220, 0), Point<float>(220, 400));
    g.drawLine(line1, 2.0f);

    Line<float> line2(Point<float>(440, 0), Point<float>(440, 400));
    g.drawLine(line2, 2.0f);
}

void FmSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    cutoffSlider.setBounds(520, 50, 20, 300);
    volumeSlider.setBounds(620, 50, 20, 300);
    octaveKnob.setBounds(275, 130, 120, 120);
    cmRatioKnob.setBounds(50, 130, 120, 120);
    modAmtKnob.setBounds(50, 260, 120, 120);
    modWaveSelect.setBounds(50, 50, 100, 20);
    carWaveSelect.setBounds(280, 50, 100, 20);
}
