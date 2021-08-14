#include "Enemy.h"
#include <cmath>
#include "../Game.h"
#include "../Components/SpriteComponent.h"
#include "../Components/ColliderComponent.h"

Enemy::Enemy(Game* game)
:Actor(game)
,mEnemyMoveType(STRAIGHT)
,mEnemySpeed(150.0f)
,mUpdateCount(0.0f)
,mEnemyShakeWidth(5.0f)
{
    // スプライト設定
    SpriteComponent* sprite = new SpriteComponent(this);
    sprite->SetTexture(GetGame()->LoadTexture("../Assets/enemy.png"));
    // コライダ追加
    mCollider = new ColliderComponent(this);
    mCollider->SetRadius(50.0f * GetScale());
    // エネミー追加
    game->AddEnemy(this);
}

Enemy::~Enemy()
{
    // エネミー削除
    GetGame()->RemoveEnemy(this);
}

void Enemy::UpdateActor(float deltaTime)
{
    // 親のメソッド呼び出し
    Actor::UpdateActor(deltaTime);
    // 移動処理
    Vector2 pos = GetPosition();
    switch (mEnemyMoveType)
    {
        case STRAIGHT:
            pos.y += mEnemySpeed * deltaTime;
            break;
        case SHAKE:
            pos.x = mInitPosition->x + (sinf(mUpdateCount / 10.0f) * mEnemyShakeWidth);
            pos.y += mEnemySpeed * deltaTime;
            break;
        default:
            break;
    }
    // 画面外に出たら破棄
    if (pos.y >= GetGame()->ScreenHeight)
    {
        SetState(EDead);
    }
    SetPosition(pos);

    // 時間をカウント
    mUpdateCount++;
}

void Enemy::SetPosition(const Vector2& pos)
{
    // 位置を保持する
    mInitPosition = new Vector2(pos.x, pos.y);
    Actor::SetPosition(pos);
}
