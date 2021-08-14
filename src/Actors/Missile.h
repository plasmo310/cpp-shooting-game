#pragma once
#include "Actor.h"

// ミサイルクラス
class Missile : public Actor {
public:
    Missile(class Game* game);
    void UpdateActor(float deltaTime) override; // アクタ更新

private:
    const float mMissileSpeed = 1000.0f; // ミサイル移動速度
    class ColliderComponent* mCollider;  // コライダ
};
