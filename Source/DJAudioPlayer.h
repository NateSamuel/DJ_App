#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public AudioSource {
public:

    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer();
    /*Teacher's work*/
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void loadURL(URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);

    /*Student's work*/
    void setBass(double bassSliderVal, double samplesget);
    void setTreble(double trebleSliderVal, double samplesget);

    /*Teacher's work*/
    double getSampleRate = 0;
    void start();
    void stop();
    /** get the relative position of the playhead */
    double getPositionRelative();
    double getLengthInSeconds();

private:
    /*Teacher's work*/
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;

    /*Student's work*/
    AudioTransportSource transportSource;
    IIRFilterAudioSource filterSource{ &transportSource, false };

    /*Teacher's work*/
    MixerAudioSource mixerSource;
    ResamplingAudioSource resampleSource{ &mixerSource,false, 2 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DJAudioPlayer)
};
