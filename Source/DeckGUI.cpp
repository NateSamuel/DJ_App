
#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
/*Base setup of class teacher's work*/
DeckGUI::DeckGUI(DJAudioPlayer* _player,
    AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse) : player(_player),
    waveformDisplay(formatManagerToUse, cacheToUse)
{
    //add and make visible buttons and sliders
    /*teacher's work*/
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    /*student's work*/
    addAndMakeVisible(bassSlider);
    addAndMakeVisible(trebleSlider);
    addAndMakeVisible(trackTitleLabel);

    //add and make visible turntable and waveform display components 
    //invisible slider is used as part of turntable functionality to 'scratch' the record turntables
    /*student's work*/
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(turntable);
    addAndMakeVisible(invisibleSlider);

    /*student's work*/
    //sets slider data and label information etc.
    setSliderStyles();

    /*student's work*/
    //set slider look and feels
    volSlider.setLookAndFeel(&otherLookAndFeel);
    speedSlider.setLookAndFeel(&otherLookAndFeel);
    posSlider.setLookAndFeel(&otherLookAndFeel);
    bassSlider.setLookAndFeel(&otherLookAndFeel);
    trebleSlider.setLookAndFeel(&otherLookAndFeel);


    //set track title label style
    /*student's work*/
    trackTitleLabel.setText("Track Title", juce::dontSendNotification);
    trackTitleLabel.setFont(juce::Font(10.0f, juce::Font::bold));

    //add button listeners
    /*teacher's work*/
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    //add slider listeners
    /*teacher's work*/
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    /*student's work*/
    bassSlider.addListener(this);
    trebleSlider.addListener(this);

    //setting the ranges of the sliders
    /*teacher's work*/
    volSlider.setRange(0.01,
                       1.0);
    speedSlider.setRange(0.01,
                         3.0);
    posSlider.setRange(0.01,
                       1.0);
    /*student's work*/
    bassSlider.setRange(0.01,
                        3.0);
    trebleSlider.setRange(0.01,
                          3.0);

    //add image buttons for play, pause, load
    /*student's work,  I used this video as reference for adding the imageButtons:
    //https://www.youtube.com/watch?v=g_6UKygCp-0&t=14s.*/

    auto pauseImage = juce::ImageCache::getFromMemory(BinaryData::pauseButton_png,
                                                      BinaryData::pauseButton_pngSize);
    auto loadImage = juce::ImageCache::getFromMemory(BinaryData::loadButton_png,
                                                     BinaryData::loadButton_pngSize);
    auto playImage = juce::ImageCache::getFromMemory(BinaryData::playButton_png, 
                                                     BinaryData::playButton_pngSize);

    stopButton.setImages(true,
                         true,
                         true,
                         pauseImage,
                         0.5f,
                         juce::Colours::transparentBlack,
                         pauseImage, 1.0f,
                         juce::Colours::transparentBlack,
                         pauseImage,
                         0.5f,
                         juce::Colours::transparentBlack,
                         0.0f);
    loadButton.setImages(true,
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
    playButton.setImages(true,
                         true, 
                         true,
                         playImage,
                         0.5f,
                         juce::Colours::transparentBlack,
                         playImage,
                         1.0f,
                         juce::Colours::transparentBlack,
                         playImage,
                         0.5f,
                         juce::Colours::transparentBlack,
                         0.0f);
    /*teacher's work*/
    startTimer(50);
}

DeckGUI::~DeckGUI()
{
    /*teacher's work*/
    stopTimer();

}

void DeckGUI::paint(Graphics& g)
{

}

void DeckGUI::resized()
{
    //variables to mirror gui and incremental values to change depending on window size
    /*student's work*/
    double dialMirror = 0;
    double bassMirror = 0;
    double trebleMirror = 0;
    double volSliderMirror = 0;
    double speedSliderMirror = 0;
    double posSliderMirror = 0;

    double rowH = getHeight() / 14;
    double marginW = getWidth() / 24;
    double marginH = getHeight() / 36;
    double centreW = getWidth() / 2;

    //creating a mirrored GUI
    /*student's work*/
    if (DeckGUI::isMirrored == 1)
    {
        dialMirror = centreW - (2 * marginW);
        volSliderMirror = 0;
        speedSliderMirror = 3 * marginW;
        posSliderMirror = 6 * marginW;
        bassMirror = 2 * marginW;
        trebleMirror = 7 * marginW;
    }
    else if (DeckGUI::isMirrored == -1) {
        dialMirror = 2 * marginW;
        volSliderMirror = getWidth() - (3 * marginW);
        speedSliderMirror = getWidth() - (6 * marginW);
        posSliderMirror = getWidth() - (9 * marginW);
        bassMirror = getWidth() - (2 * marginW) - (getWidth() / 6);
        trebleMirror = getWidth() - (7 * marginW) - (getWidth() / 6);
    }

    //setting bounds for GUI buttons, sliders and components
    /*student's work*/
    waveformDisplay.setBounds(marginW,
                              marginH,
                              getWidth() - (marginW * 2),
                              (rowH * 2) - marginH);
    playButton.setBounds(marginW,
                         rowH * 2.5f,
                         getWidth()/3 - (marginW * 2),
                         rowH);
    stopButton.setBounds(getWidth() / 3 + marginW,
                        rowH * 2.5f,
                        getWidth()/3 - (marginW * 2),
                        rowH);
    loadButton.setBounds(2 * getWidth() / 3 + marginW,
                        rowH * 2.5f,
                        getWidth() / 3 - (marginW * 2),
                        rowH);
    volSlider.setBounds(volSliderMirror,
                        rowH * 9,
                        marginW * 3,
                        rowH * 5);
    speedSlider.setBounds(speedSliderMirror,
                            rowH * 9,
                            marginW * 3,
                            rowH * 5);
    posSlider.setBounds(posSliderMirror,
                        rowH * 9,
                        marginW * 3,
                        rowH * 5);
    bassSlider.setBounds(bassMirror,
                         getHeight() * 7/20,
                         getWidth() / 6,
                         rowH * 2);
    trebleSlider.setBounds(trebleMirror,
                           getHeight() * 7/20,
                           getWidth() / 6,
                           rowH * 2);
    turntable.setBounds(dialMirror,
                        rowH * 9,
                        getWidth() / 2,
                        rowH * 4);
    invisibleSlider.setBounds(dialMirror,
                                rowH * 9,
                                getWidth() / 2,
                                rowH * 4);
    trackTitleLabel.setBounds(trebleMirror,
                              getHeight() * 1 / 2,
                              getWidth() / 3,
                              rowH);
}

void DeckGUI::buttonClicked(Button* button)
{
    
    /*teacher's work, starting player if button clicked*/
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
        /*student addition , making turntable rotate*/
        turntable.refreshGraphics = true;
    }

    /*teacher's work, stopping player if button clicked*/
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();
        /*student addition, making turntable stop rotating*/
        turntable.refreshGraphics = false;
    }

    /*teacher's work, loading URL into player when load button is clicked*/
    if (button == &loadButton)
    {

        auto fileChooserFlags =
            FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags,
                             [this](const FileChooser& chooser)
        {
            player->loadURL(URL{ chooser.getResult() });
            // and now the waveformDisplay as well
            waveformDisplay.loadURL(URL{ chooser.getResult() });
            String trackURLFileName = chooser.getResult().getFileName();
            std::string trackstdStrFileName = trackURLFileName.toStdString();
            trackTitleLabel.setText(trackstdStrFileName, juce::dontSendNotification);
        });
    }
}

void DeckGUI::sliderValueChanged(Slider* slider)
{
    /*teacher's work, changing volume via slider value*/
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    /*teacher's work, changing speed via slider value*/
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }

    /*teacher's work, changing position via slider value*/
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }

    /*student addition, changing bass level via slider value*/
    if (slider == &bassSlider)
    {
        player->setBass(slider->getValue(),
                        player->getSampleRate);
    }

    /*student addition, changing treble level via slider value*/
    if (slider == &trebleSlider)
    {
        player->setTreble(slider->getValue(),
                          player->getSampleRate);
    }

    /*student addition*/
    //Changing angle of turntable rotation, or 'scratching' when slider is pushed forwards or backwards. 
    //Changing position by an increment each time the turntable is 'scratched'
    //invisSliderCounter used to break up the amount of calls made to the player to not overwhelm it.
    if (slider == &invisibleSlider)
    {
        if (slider->getValue() == 1.0 && (invisSliderCounter == 1 || invisSliderCounter == 2))
        {
            turntable.pushRecordBackward = true;
            player->setPositionRelative((posSlider.getValue() - 0.01));
            posSlider.setValue(posSlider.getValue() - 0.01);
            invisSliderCounter = invisSliderCounter + 1;
        }
        else if (slider->getValue() == 2.0 && (invisSliderCounter == 1 || invisSliderCounter == 2))
        {
            turntable.pushRecordForward = true;
            player->setPositionRelative((posSlider.getValue() + 0.02));
            posSlider.setValue(posSlider.getValue() + 0.02);
            invisSliderCounter = invisSliderCounter + 1;
        }
        else {
            invisSliderCounter = invisSliderCounter + 1;
        }
        if (invisSliderCounter == 5)
        {
            invisSliderCounter = 1;
        }
        invisibleSlider.setValue(1.5);
    }
}
//drag and drop functions onto main load button implemented
/*teacher's work*/
bool DeckGUI::isInterestedInFileDrag(const StringArray& files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}
/*teacher's work*/
void DeckGUI::filesDropped(const StringArray& files,
                           int x,
                           int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {

        loadFileToDeck(juce::URL{ juce::File{files[0]} });
    }
}

/*teacher's work, calls at every timer increment*/
void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

//creating load file to deck function which is able to recieve url's from in playlist component to send to DJAudioPlayer
/*student addition*/
void DeckGUI::loadFileToDeck(juce::URL audioURL)
{
    DBG("DeckGUI::loadFile, loads files into player");
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
    String trackURLFileName = audioURL.getFileName();
    std::string trackstdStrFileName = trackURLFileName.toStdString();
    trackTitleLabel.setText(trackstdStrFileName, juce::dontSendNotification);
}

void DeckGUI::setSliderStyles()
{
    //set volume slider style
    /*student's work*/
    volSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    volSlider.setTextBoxStyle(Slider::TextBoxBelow,
        false,
        32,
        16);
    volSlider.setNumDecimalPlacesToDisplay(1);
    volSlider.setValue(1.0);
    volLabel.setText("Volume", juce::dontSendNotification);
    volLabel.attachToComponent(&volSlider, false);
    volLabel.setFont(juce::Font(10.0f,
        juce::Font::bold));
    volLabel.setJustificationType(juce::Justification::centred);

    //set speed slider style
    /*student's work*/
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow,
        false,
        32,
        16);
    speedSlider.setNumDecimalPlacesToDisplay(1);
    speedSlider.setValue(1.0);
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.attachToComponent(&speedSlider,
        false);
    speedLabel.setFont(juce::Font(10.0f,
        juce::Font::bold));
    speedLabel.setJustificationType(juce::Justification::centred);

    //set position slider style
    /*student's work*/
    posSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    posSlider.setTextBoxStyle(Slider::TextBoxBelow,
        false,
        32,
        16);
    posSlider.setNumDecimalPlacesToDisplay(1);
    posLabel.setText("Position", juce::dontSendNotification);
    posLabel.attachToComponent(&posSlider,
        false);
    posLabel.setFont(juce::Font(10.0f, juce::Font::bold));
    posLabel.setJustificationType(juce::Justification::centred);

    //set bass slider style
    /*student's work*/
    bassSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    bassSlider.setTextBoxStyle(Slider::TextBoxBelow,
        false,
        32,
        16);
    bassSlider.setNumDecimalPlacesToDisplay(1);
    bassSlider.setColour(0x1001400, Colours::black);
    bassSlider.setValue(1.0);
    bassLabel.setText("Bass", juce::dontSendNotification);
    bassLabel.setColour(juce::Label::textColourId, Colours::black);
    bassLabel.attachToComponent(&bassSlider,
        false);
    bassLabel.setFont(juce::Font(10.0f, juce::Font::bold));
    bassLabel.setJustificationType(juce::Justification::centred);

    //set treble slider style
    /*student's work*/
    trebleSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    trebleSlider.setTextBoxStyle(Slider::TextBoxBelow,
        false,
        32,
        16);
    trebleSlider.setNumDecimalPlacesToDisplay(1);
    trebleSlider.setColour(0x1001400, Colours::black);
    trebleSlider.setValue(1.0);
    trebleLabel.setText("Treble", juce::dontSendNotification);
    trebleLabel.setColour(juce::Label::textColourId, Colours::black);
    trebleLabel.attachToComponent(&trebleSlider,
        false);
    trebleLabel.setFont(juce::Font(10.0f, juce::Font::bold));
    trebleLabel.setJustificationType(juce::Justification::centred);

    //set invisible slider (for turntable) styles
    /*student's work*/
    invisibleSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    invisibleSlider.setTextBoxStyle(Slider::TextBoxBelow,
        true,
        0,
        0);
    invisibleSlider.addListener(this);
    invisibleSlider.setRange(1.0,
        2.0,
        0.5);
    invisibleSlider.setValue(1.5);
    invisibleSlider.setAlpha(0);
    invisibleSlider.setOpaque(false);
}
