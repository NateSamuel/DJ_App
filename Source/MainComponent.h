
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "BackgroundGraphics.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "FrequencyVisualiser.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public AudioAppComponent

{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    /*Teacher's Work, calling all required functions*/
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint(Graphics& g) override;
    void resized() override;

private:

    /*Teacher's Work, calling all other classes*/
    BackgroundGraphics backgroundGraphics;
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 100 };

    DJAudioPlayer player1{ formatManager };
    DeckGUI deckGUI1{ &player1, formatManager, thumbCache};


    DJAudioPlayer player2{ formatManager };
    DeckGUI deckGUI2{ &player2, formatManager, thumbCache};

    MixerAudioSource mixerSource;
    DJAudioPlayer playerForParsingMetaData{ formatManager };

    //student added reference to DeckGUI's in playlistComponent
    PlaylistComponent playlistComponent{ &deckGUI1, &deckGUI2 };

    /* student's Work, calling frequency visualiser */
    FrequencyVisualiser frequencyVisualiser;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
