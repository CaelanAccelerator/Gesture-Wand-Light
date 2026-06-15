#pragma once

enum class Gesture {
    None,
    SwingUp,      // 上挥 → 变亮
    SwingDown,    // 下挥 → 变暗
    SwingSide,    // 横挥 → 切颜色(不分左右)
    Circle,       // 画圈 → 开关(IMU 阶段)
    // W, S, Roll —— 暂不做
};
