#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

TunerGitarChromaticAudioProcessor::TunerGitarChromaticAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::mono(), true)
                                     .withOutput("Output", juce::AudioChannelSet::mono(), true)),
      fft(fftOrder),
      window(fftSize, juce::dsp::WindowingFunction<float>::hann)
{
    std::cout << "TunerGitarChromaticAudioProcessor created" << std::endl;
}

TunerGitarChromaticAudioProcessor::~TunerGitarChromaticAudioProcessor() = default;

void TunerGitarChromaticAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    sampleRate_ = sampleRate;
}

void TunerGitarChromaticAudioProcessor::releaseResources() {}

void TunerGitarChromaticAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    auto* channelData = buffer.getReadPointer(0);
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        pushNextSampleIntoFifo(channelData[i]);
    }
}

void TunerGitarChromaticAudioProcessor::pushNextSampleIntoFifo(float sample)
{
    if (fifoIndex == fftSize)
    {
        memcpy(fftData, fifo, sizeof(fifo));
        window.multiplyWithWindowingTable(fftData, fftSize);
        fft.performFrequencyOnlyForwardTransform(fftData);
        analyzeFFT();
        fifoIndex = 0;
    }
    fifo[fifoIndex++] = sample;
}

void TunerGitarChromaticAudioProcessor::analyzeFFT()
{
    int maxIndex = 0;
    float maxMagnitude = 0.0f;

    for (int i = 1; i < fftSize / 2 - 1; ++i)
    {
        if (fftData[i] > maxMagnitude)
        {
            maxMagnitude = fftData[i];
            maxIndex = i;
        }
    }

    // Interpolasi Parabolik
    float alpha = fftData[maxIndex - 1];
    float beta  = fftData[maxIndex];
    float gamma = fftData[maxIndex + 1];

    float binOffset = (alpha - gamma) / (2.0f * (alpha - 2.0f * beta + gamma));
    float exactBin = maxIndex + binOffset;

    detectedFrequency = exactBin * (sampleRate_ / fftSize);
    juce::Logger::outputDebugString("Detected Frequency: " + juce::String(detectedFrequency));
}


juce::AudioProcessorEditor* TunerGitarChromaticAudioProcessor::createEditor()
{
    return new TunerGitarChromaticAudioProcessorEditor(*this);
}

bool TunerGitarChromaticAudioProcessor::hasEditor() const { return true; }

const juce::String TunerGitarChromaticAudioProcessor::getName() const { return "TunerGitarChromatic"; }

bool TunerGitarChromaticAudioProcessor::acceptsMidi() const { return false; }
bool TunerGitarChromaticAudioProcessor::producesMidi() const { return false; }
bool TunerGitarChromaticAudioProcessor::isMidiEffect() const { return false; }
double TunerGitarChromaticAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int TunerGitarChromaticAudioProcessor::getNumPrograms() { return 1; }
int TunerGitarChromaticAudioProcessor::getCurrentProgram() { return 0; }
void TunerGitarChromaticAudioProcessor::setCurrentProgram(int index) {}
const juce::String TunerGitarChromaticAudioProcessor::getProgramName(int index) { return {}; }
void TunerGitarChromaticAudioProcessor::changeProgramName(int index, const juce::String& newName) {}

void TunerGitarChromaticAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {}
void TunerGitarChromaticAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TunerGitarChromaticAudioProcessor();
}