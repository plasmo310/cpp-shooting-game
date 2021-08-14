#include "Ship.h"
#include <SDL.h>
#include "Enemy.h"
#include "Missile.h"
#include "../Game.h"
#include "../Components/SpriteComponent.h"
#include "../Components/ColliderComponent.h"

Ship::Ship(Game* game)
:Actor(game)
,mRightSpeed(0.0f)
,mDownSpeed(0.0f)
,mIsCanShot(false)
,mShotDeltaTime(0.0f)
{
    // スプライト設定
    SpriteComponent* sprite = new SpriteComponent(this);
    sprite->SetTexture(GetGame()->LoadTexture("../Assets/ship.png"));
    // コライダ追加
    mCollider = new ColliderComponent(this);
    mCollider->SetRadius(70.0f * GetScale());
}

// アクタ更新
void Ship::UpdateActor(float deltaTime)
{
    // 親のメソッド呼び出し
    Actor::UpdateActor(deltaTime);
    // 宇宙船を移動させる
    Vector2 pos = GetPosition();
    pos.x += mRightSpeed * deltaTime;
    pos.y += mDownSpeed * deltaTime;
    if (pos.x < 25.0f)
    {
        pos.x = 25.0f;
    }
    else if (pos.x > Game::ScreenWidth - 25.0f)
    {
        pos.x = Game::ScreenWidth - 25.0f;
    }
    if (pos.y < 25.0f)
    {
        pos.y = 25.0f;
    }
    else if (pos.y > Game::ScreenHeight - 25.0f)
    {
        pos.y = Game::ScreenHeight - 25.0f;
    }
    SetPosition(pos);

    // エネミーと衝突したら死亡
    for (auto enemy : GetGame()->GetEnemies())
    {
        if (Intersect(*mCollider, *(enemy->GetCollider())))
        {
            // TODO ゲームオーバー処理
            SetState(EDead);
            break;
        }
    }

    // ミサイルを撃つ感覚を空ける
    if (!mIsCanShot)
    {
        mShotDeltaTime += deltaTime;
        if (mShotDeltaTime > CanShotTime)
        {
            mIsCanShot = true;
            mShotDeltaTime = 0.0f;
        }
    }
}

// キーボード入力
void Ship::ProcessKeyboard(const uint8_t* state)
{
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;
    // キー入力で上下左右に移動させる
    if (state[SDL_SCANCODE_D])
    {
        mRightSpeed += ShipSpeed;
    }
    if (state[SDL_SCANCODE_A])
    {
        mRightSpeed -= ShipSpeed;
    }
    if (state[SDL_SCANCODE_S])
    {
        mDownSpeed += ShipSpeed;
    }
    if (state[SDL_SCANCODE_W])
    {
        mDownSpeed -= ShipSpeed;
    }
    // ミサイルを撃つ
    if (state[SDL_SCANCODE_K])
    {
        if (mIsCanShot)
        {
            // 撃つ感覚を空けるためフラグを付ける
            mIsCanShot = false;
            mShotDeltaTime = 0.0f;
            // ミサイル生成
            Missile* missile = new Missile(GetGame());
            Vector2 pos = GetPosition();
            missile->SetPosition(Vector2(pos.x, pos.y - 30.0f));
        }
    }
}
