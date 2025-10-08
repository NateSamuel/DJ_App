/*Class made initially by teacher but adapted and built on by student to implement a playlist from local files and add them to the player 1 and player 2*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"


PlaylistComponent::PlaylistComponent(DeckGUI* _deckGUI1,
                                    DeckGUI* _deckGUI2) : 
                                    deckGUI1(_deckGUI1),
                                    deckGUI2(_deckGUI2)
{

    /*Teacher's work*/
    //make tableComponent visible
    addAndMakeVisible(tableComponent);

    //assign columns and widths to tableComponent
    /*Teacher's work*/
    tableComponent.getHeader().addColumn("Track title",
                                         1,
                                         400);
    tableComponent.getHeader().addColumn("Load",
                                          2,
                                          100);
    /*Student's work*/
    tableComponent.getHeader().addColumn("Player 1",
                                          3,
                                          100);
    tableComponent.getHeader().addColumn("Player 2",
                                          4,
                                          100);
    tableComponent.getHeader().addColumn("Del from playlist",
                                         5,
                                         100);
    tableComponent.setModel(this);
    /*Student's work, change row height*/
    tableComponent.setRowHeight(35);

    /*Student's work, add initial row data to trackLibrary vector class*/
    trackLibrary.push_back(TrackLibrary{ "No Track",
                                         "Track 1",
                                         false });
    trackLibrary.push_back(TrackLibrary{ "No Track",
                                         "Track 2",
                                         false });
    trackLibrary.push_back(TrackLibrary{ "No Track",
                                         "Track 3",
                                         false });
    trackLibrary.push_back(TrackLibrary{ "No Track",
                                         "Track 4",
                                         false });
    trackLibrary.push_back(TrackLibrary{ "No Track",
                                         "Track 5",
                                         false });
    trackLibrary.push_back(TrackLibrary{ "No Track",
                                         "Track 6",
                                         false });

    

}

PlaylistComponent::~PlaylistComponent()
{
    /*Teacher's work*/
    tableComponent.setModel(nullptr);
}

void PlaylistComponent::paint(juce::Graphics& g)
{

    /*Student's work*/
    //change colours and font sizes
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colour(181,
                             250,
                             255));
    g.drawRect(getLocalBounds(),
               1);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);

    /*Teacher's work*/
    g.drawText("PlaylistComponent",
               getLocalBounds(),
               juce::Justification::centred,
               true);   // draw some placeholder text
}
/*Teacher's work*/
void PlaylistComponent::resized()
{
    tableComponent.setBounds(0,
                             0,
                             getWidth(),
                             getHeight());
}

int PlaylistComponent::getNumRows()
{
    /*Student's work, changed to trackLibrary vector class*/
    return trackLibrary.size();
}

void PlaylistComponent::paintRowBackground(Graphics& g,
                                           int rowNumber,
                                           int width,
                                           int height,
                                           bool rowIsSelected)
{
    /*Student's work, changed colour of selected row*/
    // just highlight selected rows
    if (rowIsSelected)
    {
        g.fillAll(juce::Colour(80,
                               200,
                               235));
    }
    else {
        g.fillAll(juce::Colour(181,
                               250,
                               255));
    }
}

void PlaylistComponent::paintCell(Graphics& g,
                                  int rowNumber,
                                  int columnId,
                                  int width,
                                  int height,
                                  bool rowIsSelected)
{
    /*Teachers initial work, Student's edit to change to trackLibrary so that when loaded the track name pops up*/

    g.drawText(trackLibrary[rowNumber].trackName, // the important bit
               2,
               0,
               width - 4,
               height,
               Justification::centredLeft,
               true);
}
/*Teacher's work*/
void PlaylistComponent::cellClicked(int rowNumber, 
                                    int columnId,
                                    const MouseEvent&)
{

}
/*Student's work, creates imageButtons and listeners of load button, leftLoadButton, rightLoadButton, delete button and creates ids for them to be used in the buttonClicked function*/
Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                                      int columnId,
                                                      bool isRowSelected,
                                                      Component* existingComponentToUpdate)
{
    if (columnId == 2) //load button
    {
        if (existingComponentToUpdate == nullptr)
        {
            //creates image button
            ImageButton* loadButton = new ImageButton("choose audio...");
            auto loadImage = juce::ImageCache::getFromMemory(BinaryData::loadButton_png,
                                                             BinaryData::loadButton_pngSize);

            loadButton->setImages(true,
                                  true, 
                                  true, 
                                  loadImage,
                                  0.5f,
                                  juce::Colours::transparentBlack, 
                                  loadImage,
                                  1.0f, 
                                  juce::Colours::transparentBlack,
                                  loadImage,
                                  0.5f,
                                  juce::Colours::transparentBlack,
                                  0.0f);

            //sets button id
            String id{ std::to_string(rowNumber) };
            loadButton->setComponentID("2" + id);
            loadButton->addListener(this);
            existingComponentToUpdate = loadButton;
        }
    }
    if (columnId == 3) //load into player 1 button
    {
        if (existingComponentToUpdate == nullptr)
        {
            //creates image button
            ImageButton* leftLoadButton = new ImageButton("deck 1 load");
            auto leftLoadImage = juce::ImageCache::getFromMemory(BinaryData::leftButton_png,
                                                                 BinaryData::leftButton_pngSize);

            leftLoadButton->setImages(true,
                                      true,
                                      true,
                                      leftLoadImage,
                                      0.5f,
                                      juce::Colours::transparentBlack,
                                      leftLoadImage,
                                      1.0f,
                                      juce::Colours::transparentBlack,
                                      leftLoadImage,
                                      0.5f,
                                      juce::Colours::transparentBlack,
                                      0.0f);
            //sets button id
            String id{ std::to_string(rowNumber) };
            leftLoadButton->setComponentID("3" + id);
            leftLoadButton->addListener(this);
            existingComponentToUpdate = leftLoadButton;
        }
    }
    if (columnId == 4) //load into player 2 button
    {
        if (existingComponentToUpdate == nullptr)
        {
            //creates image button
            ImageButton* rightLoadButton = new ImageButton("deck 2 load");
            auto rightLoadImage = juce::ImageCache::getFromMemory(BinaryData::rightButton_png, 
                                                                  BinaryData::rightButton_pngSize);

            rightLoadButton->setImages(true,
                                       true,
                                       true,
                                       rightLoadImage,
                                       0.5f,
                                       juce::Colours::transparentBlack,
                                       rightLoadImage,
                                       1.0f, 
                                       juce::Colours::transparentBlack,
                                       rightLoadImage,
                                       0.5f,
                                       juce::Colours::transparentBlack,
                                       0.0f);
            //sets button id
            String id{std::to_string(rowNumber)};
            rightLoadButton->setComponentID("4" + id);
            rightLoadButton->addListener(this);
            existingComponentToUpdate = rightLoadButton;
        }
    }

    if (columnId == 5) // delete button
    {
        if (existingComponentToUpdate == nullptr)
        {
            //creates image button
            ImageButton* deleteButton = new ImageButton("delete");
            auto deleteImage = juce::ImageCache::getFromMemory(BinaryData::deleteButton_png,
                                                               BinaryData::deleteButton_pngSize);

            deleteButton->setImages(true,
                                    true,
                                    true,
                                    deleteImage,
                                    0.5f,
                                    juce::Colours::transparentBlack,
                                    deleteImage,
                                    1.0f, juce::Colours::transparentBlack,
                                    deleteImage,
                                    0.5f,
                                    juce::Colours::transparentBlack,
                                    0.0f);
            //sets button id
            String id{ std::to_string(rowNumber) };
            deleteButton->setComponentID("5" + id);
            deleteButton->addListener(this);
            existingComponentToUpdate = deleteButton;
        }
    }

    return existingComponentToUpdate;
}

/*Student's work, using the button ids from refreshComponentForCell, to load, put track into player 1 or 2, or delete from playlist*/
void PlaylistComponent::buttonClicked(Button* button)
{

    id = std::stoi(button->getComponentID().toStdString());

    //if specific button is clicked, the button is loaded into the specified row in the playlist by replacing the previous data for that specific row in trackLibrary with the new URL
    if (id == 20 || id == 21 || id == 22 || id == 23 || id == 24 || id == 25)
    {
        id -= 20;
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags,
                             [this](const FileChooser& chooser)
        {
            File trackURLFile{ chooser.getResult() };

            String trackURLString{ URL{trackURLFile}.toString(false) };
            trackStdString = trackURLString.toStdString();

            String trackURLFileName = trackURLFile.getFileName();
            trackstdStrFileName = trackURLFileName.toStdString();
            for (auto i = 0; i < 6; ++i)
            {
                if (id == i)
                trackLibrary[i] = TrackLibrary{ trackStdString, 
                                                trackstdStrFileName,
                                                true };
                repaint();
                DBG("ready for input");
            }
        });
    }
    //if specific button is selected, the row's track is pushed into the player 1
    if (id == 30 || id == 31 || id == 32 || id == 33 || id == 34 || id == 35)
    {
        id -= 30;
        for (auto i = 0; i < 6; ++i)
        {
            if (id == i && trackLibrary[i].isTrackLoaded)
            {
                deckGUI1->loadFileToDeck(URL(trackLibrary[i].urlString));
            }
        }
    }
    //if specific button is selected, the row's track is pushed into the player 2
    if (id == 40 || id == 41 || id == 42 || id == 43 || id == 44 || id == 45)
    {
        id -= 40;
        for (auto i = 0; i < 6; ++i)
        {
            if (id == i && trackLibrary[i].isTrackLoaded)
            {
                deckGUI2->loadFileToDeck(URL(trackLibrary[i].urlString));
            }
        }
    }
    //if specific button is selected, the row's track is removed and replaced with the placeholder 'Track' plus number of row instead of URL
    if (id == 50 || id == 51 || id == 52 || id == 53 || id == 54 || id == 55)
    {
        id -= 50;
        for (auto i = 0; i < 6; ++i)
        {
            if (id == i)
            {
                std::string trackNum;
                trackNum = std::to_string(i + 1);
                trackLibrary[i] = TrackLibrary{ "No Track",
                                                "Track " + trackNum,
                                                false };
                repaint();
            }
        }
    }

}