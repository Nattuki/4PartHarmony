/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   flat_svg;
    const int            flat_svgSize = 2318;

    extern const char*   nature_svg;
    const int            nature_svgSize = 2241;

    extern const char*   sharp_svg;
    const int            sharp_svgSize = 2613;

    extern const char*   Grand_staff_png;
    const int            Grand_staff_pngSize = 11306;

    extern const char*   Grand_staff_svg;
    const int            Grand_staff_svgSize = 21933;

    extern const char*   note_svg;
    const int            note_svgSize = 2589;

    extern const char*   note_png;
    const int            note_pngSize = 1759;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 7;

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
