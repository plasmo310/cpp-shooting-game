#pragma once
#include "SDL.h"
#include "Component.h"

// スプライトコンポーネントクラス
// *描画を行うコンポーネントはこのクラスを継承する
class SpriteComponent : public Component
{
public:
    SpriteComponent(class Actor* actor, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(SDL_Renderer* renderer);     // 描画処理
    virtual void SetTexture(SDL_Texture* texture); // テクスチャ設定処理

protected:
    SDL_Texture* mTexture;
    int mDrawOrder; // 描画順
    int mTexWidth;  // テクスチャ横幅
    int mTexHeight; // テクスチャ縦幅

public:
    // Getter, Setter
    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexWidth() const { return mTexWidth; }
    int GetTexHeight() const { return mTexHeight; }
};
