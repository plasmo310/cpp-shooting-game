#pragma once

// 共通の計算処理
// namespaceとして定義
namespace Math
{
    const float Pi = 3.1415926535f;

    // degrees -> radians
    inline float ToRadians(float degrees)
    {
        return degrees * Pi / 180.0f;
    }

    // radians -> degrees
    inline float ToDegrees(float radians)
    {
        return radians * 180.0f / Pi;
    }
}
