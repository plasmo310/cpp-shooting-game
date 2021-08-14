#pragma once
#include "Actor.h"
#include "../Commons/Vector2.h"

// エネミークラス
class Enemy : public Actor {
public:
    Enemy(class Game* game);
    ~Enemy();
    void UpdateActor(float deltaTime) override;
    void SetPosition(const Vector2& pos);

    // 移動タイプ
    enum MoveType
    {
        STRAIGHT, // 直線移動
        SHAKE,    // 揺れながら移動
    };

private:
    MoveType mEnemyMoveType; // 移動タイプ
    float mEnemySpeed;       // 移動速度
    float mEnemyShakeWidth;  // 揺れる幅
    Vector2* mInitPosition;  // 最初の位置
    float mUpdateCount; // 経過時間(sin更新用)
    class ColliderComponent* mCollider;  // コライダ

public:
    // Getter, Setter
    MoveType GetEnemyMoveType() const { return mEnemyMoveType; }
    void SetEnemyMoveType(const MoveType moveType) { mEnemyMoveType = moveType; }
    float GetEnemySpeed() const { return mEnemySpeed; }
    void SetEnemySpeed(const float speed) { mEnemySpeed = speed; }
    float GetEnemyShakeWidth() const { return mEnemyShakeWidth; }
    void SetEnemyShakeWidth(const float width) { mEnemyShakeWidth = width; }
    class ColliderComponent* GetCollider() const { return mCollider; }
};
