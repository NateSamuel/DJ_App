/* Teachers work, student has only changed the sizes and colours of the design. Creates waveform display when track is loaded into DeckGUI player*/
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class WaveformDisplay : public Component,
    public ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
                    AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay();
    /*Teachers initialisations - student has only altered the paint function*/
    void paint(Graphics&) override;
    void resized() override;

    void changeListenerCallback(ChangeBroadcaster* source) override;
    void loadURL(URL audioURL);

    //set the relative position of the playhead
    void setPositionRelative(double pos);

private:
    //used to create the waveform
    AudioThumbnail audioThumb;
    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
