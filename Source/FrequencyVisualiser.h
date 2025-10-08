/*Student's work, using the juce tutorial to create a spectrum analyser, and adapting it: https://docs.juce.com/master/tutorial_spectrum_analyser.html
Student has changed the look of the visualiser so that it is not a single path being connected by points, but is now bars that have a gradient on them, gradiating from bass levels to treble levels.*/

/*Juce tutorial, implemented by student as a header and cpp file.*/
#pragma once
#include <JuceHeader.h>


class FrequencyVisualiser : public juce::Component,
                             private juce::Timer

{
public:

    FrequencyVisualiser();
    ~FrequencyVisualiser() override;
    //implement required component and timer functions
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

    //additional functions to deal with FFT and draw each bar throughout the spectrum
    void pushNextSampleIntoFifo(float sample);
    void drawNextFrameOfSpectrum();
    void drawFrame(juce::Graphics& g);

    //enums for FFT
    enum
    {
        fftOrder = 11,
        fftSize = 1 << fftOrder,
        scopeSize = 512
    };

private:

    //using DSP additional module to get FFT
    juce::dsp::FFT forwardFFT;
    juce::dsp::WindowingFunction<float> window;

    //variables to change aspects of the FFT and spectrum
    float fifo[fftSize];
    float fftData[2 * fftSize];
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;
    float scopeData[scopeSize];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrequencyVisualiser)
};
