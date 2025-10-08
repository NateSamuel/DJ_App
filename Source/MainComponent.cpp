
#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    //initial main component size
    setSize(800, 900);

    /*Teacher's work*/
    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio)
        && !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request(RuntimePermissions::recordAudio,
            [&](bool granted) { if (granted)  setAudioChannels(2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(0, 2);
    }



    /*Student's work*/
    addAndMakeVisible(backgroundGraphics);
    addAndMakeVisible(frequencyVisualiser);
    /*Teacher's work*/
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(playlistComponent);

    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    /*Teacher's work*/
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected,
                                  double sampleRate)
{
    
    /*Teacher's work, mixing the two player's audio together*/
    player1.prepareToPlay(samplesPerBlockExpected,
                          sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected,
                          sampleRate);

    mixerSource.prepareToPlay(samplesPerBlockExpected,
                              sampleRate);

    mixerSource.addInputSource(&player1,
                               false);
    mixerSource.addInputSource(&player2,
                               false);


}
void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    /*Teacher's work, getting the next audioblock*/

    mixerSource.getNextAudioBlock(bufferToFill);

    /*Student's work, pushing bufferToFill data into the frequency visualiser class to use*/
    if (bufferToFill.buffer->getNumChannels() > 0)
    {
        auto* channelData = bufferToFill.buffer->getReadPointer(0,
                                                                bufferToFill.startSample);

        for (auto i = 0; i < bufferToFill.numSamples; ++i)
            frequencyVisualiser.pushNextSampleIntoFifo(channelData[i]);
    }
}

void MainComponent::releaseResources()
{
    /*Teacher's work*/
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

void MainComponent::paint(Graphics& g)
{

}

void MainComponent::resized()
{
    
    /*Student's work, adding local variables and setting resized on components below*/
    double rowH = getHeight() / 14;
    double marginW = getWidth() / 24;
    double marginH = getHeight() / 36;
    double centreW = getWidth() / 2;
    deckGUI1.isMirrored = 1;
    deckGUI2.isMirrored = -1;
    backgroundGraphics.setBounds(0,0, getWidth(), getHeight() * 5 / 7);
    deckGUI1.setBounds(0,
                       0,
                       getWidth() / 2,
                       getHeight()  * 5/7);
    deckGUI2.setBounds(getWidth() / 2,
                       0,
                       getWidth() / 2,
                       getHeight() * 5 / 7);
    playlistComponent.setBounds(0,
                                getHeight() * 5 / 7,
                                getWidth(),
                                getHeight() * 2/7);
    frequencyVisualiser.setBounds(getWidth() / 4,
                                  (getHeight() * 3 / 14) + (marginH / 2),
                                  centreW,
                                  (getHeight() * 1 / 7) - marginH);

}

