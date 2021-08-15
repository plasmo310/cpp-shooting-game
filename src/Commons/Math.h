#pragma once
#include <random>

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

    // random
    static std::random_device seed_gen;
    static std::default_random_engine randomEngine(seed_gen());
    inline float GetRand(float min, float max)
    {
        std::uniform_real_distribution<> dist(min, max);
        return dist(Math::randomEngine);
    }
}
