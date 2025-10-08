/*Class made initially by teacher but adapted and built on by student to implement a playlist from local files and add them to the player 1 and player 2*/

#pragma once
#include <vector>
#include <string>
#include <JuceHeader.h>
#include "DeckGUI.h"
#include "DJAudioPlayer.h"
#include "TrackLibrary.h"

class PlaylistComponent : public juce::Component,
    public TableListBoxModel,
    public Button::Listener

{
public:
    /*Teachers initial code, student inputs within these functions are different*/
    //passing the two deckGUIs that have been created in to send URL's to for the two players
    PlaylistComponent(DeckGUI* _deckGUI1,
                      DeckGUI* _deckGUI2);
    ~PlaylistComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    //creating functionalities for the rows and cells of the table
    int getNumRows() override;
    void paintRowBackground(Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;
    void paintCell(Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;
    virtual void cellClicked(int rowNumber,
        int columnId,
        const MouseEvent&) override;

    Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        Component* existingComponentToUpdate) override;
    void buttonClicked(Button* button) override;

    /*Student's work*/
    //calling vector<class> which is used as a data structure for the tracks being loaded in
    std::vector<TrackLibrary> trackLibrary;

    FileChooser fChooser{ "Select a file..." };
private:
    /*Teacher's work*/
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
    TableListBox tableComponent;

    /*Student's work*/
    //id used for button listeners
    int id = 0;
    //DeckGUI required for passing URLs into the different players
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    //used to store juce::Strings and std::string of URLs
    std::string trackStdString;
    std::string trackstdStrFileName;

};