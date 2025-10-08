#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "OtherLookAndFeel.h"
#include "Turntable.h"


//==============================================================================
/*
Class creating buttons and sliders for the GUI, student and teacher's work
*/

class DeckGUI : public Component,
                public Button::Listener,
                public Slider::Listener,
                public FileDragAndDropTarget,
                public Timer

{
public:
    DeckGUI(DJAudioPlayer* player,
        AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse);
    ~DeckGUI();

    /* DeckGUI base component functions*/
    void paint(Graphics&) override;
    void resized() override;
    
    /* Student's work, Initialising DeckGUI class variables that change depending on if mirrored and if the track is playing or not */
    int isMirrored = 0;
    bool isPlaying = false;

    /*Teacher's work, implement Button::Listener */
    void buttonClicked(Button*) override;

    /*Teacher's work implement Slider::Listener */
    void sliderValueChanged(Slider* slider) override;

    /*Teacher's work implementing file drag onto load button */
    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

    /*Teacher's work*/
    void timerCallback() override;

    /* Student's work, separate function made to pass in URL's from the playlist component*/
    void loadFileToDeck(juce::URL audioURL);

private:
    void setSliderStyles();
    //Initialisation of Image button classes
    /* Student's work*/
    ImageButton playButton{ "PLAY" };
    ImageButton stopButton{ "STOP" };
    ImageButton loadButton{ "LOAD" };

    //Implementation of sliders
    /* Student's work*/
    Slider volSlider;
    Label  volLabel;
    Slider speedSlider;
    Label speedLabel;
    Slider posSlider;
    Label posLabel;
    Slider bassSlider;
    Label bassLabel;
    Slider trebleSlider;
    Label trebleLabel;
    Label trackTitleLabel;
    Slider invisibleSlider;

    int invisSliderCounter = 1;

    /* Teacher's work, Calling the DJAudioPlayer, WaveformDisplay, and FileChooser */
    FileChooser fChooser{ "Select a file..." };
    WaveformDisplay waveformDisplay;
    DJAudioPlayer* player;

    /* Student's work, calling a look and feel class to alter the designs of the sliders*/
    OtherLookAndFeel otherLookAndFeel;

    /* Student's work, calling a turntable class that deals with the turntable component*/
    Turntable turntable;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
