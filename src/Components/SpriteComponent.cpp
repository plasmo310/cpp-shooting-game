#include "SpriteComponent.h"
#include "../Game.h"
#include "../Actors/Actor.h"
#include "../Commons/Math.h"

SpriteComponent::SpriteComponent(class Actor *actor, int drawOrder)
:Component(actor)
,mTexture(nullptr)
,mDrawOrder(drawOrder)
,mTexWidth(0)
,mTexHeight(0)
{
    // 描画中のスプライトとして追加
    mActor->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    // 描画中のスプライトから削除
    mActor->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
    if (mTexture)
    {
        SDL_Rect r;
        // 大きさ、位置（左上座標）を設定
        r.w = static_cast<int>(mTexWidth * mActor->GetScale());
        r.h = static_cast<int>(mTexHeight * mActor->GetScale());
        r.x = static_cast<int>(mActor->GetPosition().x - r.w / 2);
        r.y = static_cast<int>(mActor->GetPosition().y - r.h / 2);
        // 描画
        SDL_RenderCopyEx(renderer,
                mTexture,
                nullptr,
                &r,
                -Math::ToDegrees(mActor->GetRotation()),
                nullptr,
                SDL_FLIP_NONE);
    }
}

// テクスチャ設定処理
void SpriteComponent::SetTexture(SDL_Texture *texture)
{
    mTexture = texture;
    // テクスチャから幅を設定
    SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
