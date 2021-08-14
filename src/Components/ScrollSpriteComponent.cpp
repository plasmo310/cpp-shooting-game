#include "ScrollSpriteComponent.h"
#include "../Actors/Actor.h"
#include "../Game.h"

ScrollSpriteComponent::ScrollSpriteComponent(class Actor *actor, int drawOrder)
: SpriteComponent(actor, drawOrder)
, mScrollSpeedY(0.0f)
, mOffsetY(0.0f)
{
}

void ScrollSpriteComponent::Update(float deltaTime)
{
    // 親のメソッド呼び出し
    SpriteComponent::Update(deltaTime);
    // オフセット値を更新
    mOffsetY += mScrollSpeedY * deltaTime;
    if (mOffsetY > Game::ScreenHeight)
    {
        mOffsetY -= Game::ScreenHeight;
    }
}

void ScrollSpriteComponent::Draw(SDL_Renderer* renderer)
{
    // スクロールを考慮して２枚描画する
    // 通常のテクスチャ描画
    SDL_Rect r_bottom;
    r_bottom.w = static_cast<int>(mTexWidth * mActor->GetScale());
    r_bottom.h = static_cast<int>(mTexHeight * mActor->GetScale());
    r_bottom.x = static_cast<int>(mActor->GetPosition().x - r_bottom.w / 2);
    r_bottom.y = static_cast<int>(mActor->GetPosition().y - r_bottom.h / 2 + mOffsetY); // オフセットを加える
    SDL_RenderCopy(renderer,
           mTexture,
           nullptr,
           &r_bottom);

    // 通常テクスチャの上部にもう一枚描画
    SDL_Rect r_top;
    r_top.w = static_cast<int>(mTexWidth * mActor->GetScale());
    r_top.h = static_cast<int>(mTexHeight * mActor->GetScale());
    r_top.x = static_cast<int>(mActor->GetPosition().x - r_top.w / 2);
    r_top.y = static_cast<int>(mActor->GetPosition().y - r_top.h / 2  - Game::ScreenHeight + mOffsetY); // スクリーンサイズ分引く
    SDL_RenderCopy(renderer,
           mTexture,
           nullptr,
           &r_top);
}
