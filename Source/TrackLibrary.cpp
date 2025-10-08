/*student's work, vector<class> which is used as a data structure for the tracks being loaded in from the playlist component*/

#include "TrackLibrary.h"
#include <string>
TrackLibrary::TrackLibrary(std::string _urlString,
                           std::string _trackName,
                           bool _isTrackLoaded) :
                           urlString(_urlString),
                           trackName(_trackName),
                           isTrackLoaded(_isTrackLoaded)
{

}