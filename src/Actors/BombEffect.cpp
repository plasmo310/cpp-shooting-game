#include "BombEffect.h"
#include "../Game.h"
#include "../Components/SpriteComponent.h"

BombEffect::BombEffect(class Game *game)
:Actor(game)
,mTimeCount(0.0f)
{
    // スプライト設定
    auto* sprite = new SpriteComponent(this);
    sprite->SetTexture(GetGame()->LoadTexture(GetGame()->GetAssetsPath() + "bomb.png"));
    // 最初は大きさ0にする
    SetScale(0.0f);
}

void BombEffect::UpdateActor(float deltaTime)
{
    // 親のメソッド呼び出し
    Actor::UpdateActor(deltaTime);
    // 徐々に大きくする
    float changeScale = mTimeCount / DisplayTime * 3.0f;
    if (changeScale > 1.0f)
    {
        changeScale = 1.0f;
    }
    SetScale(changeScale);
    // 表示時間を過ぎたら破棄
    mTimeCount += deltaTime;
    if (mTimeCount >= DisplayTime)
    {
        SetState(EDead);
    }
}
