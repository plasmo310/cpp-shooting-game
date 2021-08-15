#pragma once
#include "Actor.h"

// 爆発エフェクト
class BombEffect : public Actor {
public:
    BombEffect(class Game* game);
    void UpdateActor(float deltaTime) override;

private:
    float mTimeCount; // 経過時間
    const float DisplayTime = 1.0f; // 表示時間
};
