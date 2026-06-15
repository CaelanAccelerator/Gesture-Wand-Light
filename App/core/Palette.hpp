#pragma once
#include "LedColor.hpp"

struct Palette {
    LedColor c1;
    LedColor c2;
    LedColor c3;
};


namespace Palettes {

    constexpr Palette Sunset = {
        {255, 140, 0},
        {255, 100, 150},
        {128, 0, 255}
    };

    constexpr Palette Lighting = {
        {255, 220, 160},
        {255, 230, 180},
        {255, 240, 200}
    };

    constexpr Palette PinkBlue = {
        {255, 150, 200},
        {200, 150, 230},
        {120, 180, 255}
    };

    constexpr Palette Aurora = {
        {0, 220, 180},
        {40, 120, 230},
        {130, 60, 220}
    };
}
