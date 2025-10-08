/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   loadButton_png;
    const int            loadButton_pngSize = 33705;

    extern const char*   deleteButton_png;
    const int            deleteButton_pngSize = 28692;

    extern const char*   leftButton_png;
    const int            leftButton_pngSize = 31685;

    extern const char*   rightButton_png;
    const int            rightButton_pngSize = 33242;

    extern const char*   pauseButton_png;
    const int            pauseButton_pngSize = 13605;

    extern const char*   playButton_png;
    const int            playButton_pngSize = 22517;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
