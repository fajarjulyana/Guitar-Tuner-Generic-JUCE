#include "PluginEditor.h"
#include <cfloat>
TunerGitarChromaticAudioProcessorEditor::TunerGitarChromaticAudioProcessorEditor(TunerGitarChromaticAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText("Frequency: ", juce::dontSendNotification);
    frequencyLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(noteLabel);
    noteLabel.setText("Note: ", juce::dontSendNotification);
    noteLabel.setJustificationType(juce::Justification::centred);

    startTimerHz(30);
    setSize(300, 200);
}

TunerGitarChromaticAudioProcessorEditor::~TunerGitarChromaticAudioProcessorEditor()
{
    stopTimer();
}

void TunerGitarChromaticAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawFittedText("Guitar Tuner", getLocalBounds(), juce::Justification::centredTop, 1);
}

void TunerGitarChromaticAudioProcessorEditor::resized()
{
    frequencyLabel.setBounds(50, 50, 200, 30);
    noteLabel.setBounds(50, 100, 200, 30);
}

void TunerGitarChromaticAudioProcessorEditor::timerCallback()
{
    float detectedFrequency = processor.getDetectedFrequency();
    frequencyLabel.setText("Frequency: " + juce::String(detectedFrequency) + " Hz", juce::dontSendNotification);

    // Daftar nada dengan frekuensi standar (A4 = 440 Hz)
    static const std::vector<std::pair<float, juce::String>> notes = {
        {82.41, "E2"}, {87.31, "F2"}, {92.50, "F#2"}, {98.00, "G2"}, {103.83, "G#2"},
        {110.00, "A2"}, {116.54, "A#2"}, {123.47, "B2"}, {130.81, "C3"}, {138.59, "C#3"},
        {146.83, "D3"}, {155.56, "D#3"}, {164.81, "E3"}, {174.61, "F3"}, {185.00, "F#3"},
        {196.00, "G3"}, {207.65, "G#3"}, {220.00, "A3"}, {233.08, "A#3"}, {246.94, "B3"},
        {261.63, "C4"}, {277.18, "C#4"}, {293.66, "D4"}, {311.13, "D#4"}, {329.63, "E4"}
    };

    juce::String closestNote = "Unknown";
    float minDiff = FLT_MAX;
    float closestFreq = 0.0f;

    for (const auto& note : notes)
    {
        float diff = std::abs(detectedFrequency - note.first);
        if (diff < minDiff)
        {
            minDiff = diff;
            closestNote = note.second;
            closestFreq = note.first;
        }
    }

    // Menghitung deviasi dalam cents
    float centsDiff = 1200.0f * std::log2(detectedFrequency / closestFreq);
    juce::String tuningInfo = (centsDiff > 0 ? "+" : "") + juce::String(centsDiff, 1) + " cents";

    noteLabel.setText("Note: " + closestNote + " (" + tuningInfo + ")", juce::dontSendNotification);
}

