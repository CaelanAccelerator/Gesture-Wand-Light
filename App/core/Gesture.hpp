#pragma once

enum class Gesture {
    None,
    SwingUp,      // increase brightness
    SwingDown,    // decrease brightness
    SwingSide,    // change color (right left doesn't matter)
    Circle,       // turn on or off
    // W, S, Roll —— pending
};
