#include "Missile.h"

Missile::Missile(class Game *game)
: Actor(game)
{
}

// アクタ更新
void Missile::UpdateActor(float deltaTime)
{
    // 親のメソッド呼び出し
    Actor::UpdateActor(deltaTime);
    // ミサイルを移動させる
    Vector2 pos = GetPosition();
    pos.y -= mMissileSpeed * deltaTime;
    // 画面外に出たら破棄
    if (pos.y <= 50.0f)
    {
        SetState(EDead);
    }
    SetPosition(pos);
}
