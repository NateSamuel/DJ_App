/*Student's work, using the juce tutorial to create a spectrum analyser, and adapting it: https://docs.juce.com/master/tutorial_spectrum_analyser.html
Student has changed the look of the visualiser so that it is not a single path being connected by points, but is now bars that have a gradient on them, gradiating from bass levels to treble levels.*/

#include <JuceHeader.h>
#include "FrequencyVisualiser.h"


FrequencyVisualiser::FrequencyVisualiser() : forwardFFT(fftOrder),
                                             window(fftSize,
                                             juce::dsp::WindowingFunction<float>::hann)
{
    /*Juce tutorial, implemented by student*/
    //setting background to be opaque, setting the boundary of the visualiser, setting the timer
    setOpaque(true);
    startTimerHz(30);
    setSize(getWidth(), getHeight());
}

FrequencyVisualiser::~FrequencyVisualiser()
{
}


void FrequencyVisualiser::FrequencyVisualiser::paint (juce::Graphics& g)
{
    /*Juce tutorial, implemented by student, drawing background*/
    g.fillAll(juce::Colours::black);
    g.setOpacity(1.0f);
    drawFrame(g);
}

void FrequencyVisualiser::resized()
{

}
void FrequencyVisualiser::timerCallback()
{
    /*Juce tutorial, implemented by student, every time the timer is called, drawNextFrameOFSpectrum is called and the canvas is repainted*/
    if (nextFFTBlockReady)
    {
        drawNextFrameOfSpectrum();
        nextFFTBlockReady = false;
        repaint();
    }
}
void FrequencyVisualiser::pushNextSampleIntoFifo(float sample)
{
    /*Juce tutorial, implemented by student*/
    // if the fifo contains enough data, set a flag to say that the next frame should now be rendered
    if (fifoIndex == fftSize)
    {
        if (!nextFFTBlockReady)
        {
            juce::zeromem(fftData, sizeof(fftData));
            memcpy(fftData, fifo, sizeof(fifo));
            nextFFTBlockReady = true;
        }

        fifoIndex = 0;
    }

    fifo[fifoIndex++] = sample;
}
void FrequencyVisualiser::drawNextFrameOfSpectrum()
{
    /*Juce tutorial implemented by student*/
    // FFT creates data throughout the spectrum over each timeframe
    // first apply a windowing function to our data
    window.multiplyWithWindowingTable(fftData, fftSize);

    // then render our FFT data..
    forwardFFT.performFrequencyOnlyForwardTransform(fftData);

    auto mindB = -100.0f;
    auto maxdB = 0.0f;

    for (int i = 0; i < scopeSize; ++i) 
    {
        //setting data from each instance of scopeSize using jlimit and jmap
        auto skewedProportionX = 1.0f - std::exp(std::log(1.0f - (float)i / (float)scopeSize) * 0.2f);
        auto fftDataIndex = juce::jlimit(0, fftSize / 2, (int)(skewedProportionX * (float)fftSize * 0.5f));
        auto level = juce::jmap(juce::jlimit(mindB, maxdB, juce::Decibels::gainToDecibels(fftData[fftDataIndex])
            - juce::Decibels::gainToDecibels((float)fftSize)),
            mindB, maxdB, 0.0f, 1.0f);

        scopeData[i] = level;
    }
}
void FrequencyVisualiser::drawFrame(juce::Graphics& g)
{
    /*Student's own work, creating the gradient bars*/

    //for each i in scopeSize, mapping the scope size (y axis) to each scopeData (x axis) to create each bar within the spectrum
    for (int i = 1; i < scopeSize; ++i)
    {
        auto width = getLocalBounds().getWidth();
        auto height = getLocalBounds().getHeight() * 3/4;

        g.setColour(juce::Colour(102,
                                i /2,
                                i /2));

        Rectangle<float> dialArea(juce::jmap(i - 1,
                                            0,
                                            scopeSize - 1,
                                            0, width),
                                  juce::jmap(scopeData[i - 1],
                                             0.0f,
                                             1.0f,
                                             (float)height, 0.0f),
                                  0.5,
                                  height - (juce::jmap(scopeData[i - 1],
                                                       0.0f,
                                                       1.0f,
                                                       (float)height,
                                                       0.0f)));
        g.fillRect(dialArea);



    }
}