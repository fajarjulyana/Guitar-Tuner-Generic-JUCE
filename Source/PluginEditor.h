#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class TunerGitarChromaticAudioProcessorEditor : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    TunerGitarChromaticAudioProcessorEditor(TunerGitarChromaticAudioProcessor&);
    ~TunerGitarChromaticAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    TunerGitarChromaticAudioProcessor& processor;
    juce::Label frequencyLabel;
    juce::Label noteLabel;
};
