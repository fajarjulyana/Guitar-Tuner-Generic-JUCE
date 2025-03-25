#pragma once

#include <JuceHeader.h>

class TunerGitarChromaticAudioProcessor : public juce::AudioProcessor
{
public:
    TunerGitarChromaticAudioProcessor();
    ~TunerGitarChromaticAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    float getDetectedFrequency() const { return detectedFrequency; }

private:
    // FFT Configuration
    static constexpr int fftOrder = 11;  // 2^11 = 2048 sample FFT size
    static constexpr int fftSize = 1 << fftOrder;

    juce::dsp::FFT fft;
    juce::dsp::WindowingFunction<float> window;

    float fifo[fftSize] = { 0 };
    float fftData[2 * fftSize] = { 0 };
    int fifoIndex = 0;
    double sampleRate_ = 44100.0;
    float detectedFrequency = 0.0f;

    void pushNextSampleIntoFifo(float sample);
    void analyzeFFT();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TunerGitarChromaticAudioProcessor)
};
