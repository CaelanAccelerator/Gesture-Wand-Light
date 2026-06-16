#pragma once
#include "MotionData.hpp"
#include "Gesture.hpp"
#include <cstdlib>   // abs

class GestureDetector {
public:
    Gesture detect(const MotionData& d) {
        // Subtract gravity baseline (Z axis reads ~1g at rest)
        int ax = d.ax;
        int ay = d.ay;
        int az = d.az - GRAVITY_BASELINE;

        // Find the dominant axis: the one with the largest magnitude above threshold
        int absX = abs(ax);
        int absY = abs(ay);

        // Vertical swing (Y axis dominant)
        if (absY > THRESHOLD && absY >= absX) {
            return (ay > 0) ? Gesture::SwingUp : Gesture::SwingDown;
        }

        // Horizontal swing (X axis dominant)
        if (absX > THRESHOLD && absX > absY) {
            return Gesture::SwingSide;
        }

        // TODO: Circle — requires gyroscope angular-velocity (gx/gy/gz)
        //       integration + temporal analysis. Implement once IMU is available.

        return Gesture::None;
    }

private:
    static constexpr int THRESHOLD = 10000;         // TODO: calibrate with real IMU
    static constexpr int GRAVITY_BASELINE = 16000;  // TODO: adjust for actual range / mounting orientation
};
