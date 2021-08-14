#pragma once
#include "SpriteComponent.h"
#include "../Commons/Vector2.h"

// スプライトスクロールコンポーネント
// *設定した速度でスプライトをスクロールする
class ScrollSpriteComponent : public SpriteComponent {
public:
    ScrollSpriteComponent(class Actor* actor, int drawOrder = 100);
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

private:
    float mScreenHeight; // Y方向のスクリーンサイズ
    float mScrollSpeedY; // Y方向のスクロール速度
    float mOffsetY;      // Y方向のオフセット値

public:
    // Setter, Getter
    void SetScreenHeight(const float size) { mScreenHeight = size; }
    void SetScrollSpeedY(float speed) { mScrollSpeedY = speed; }

};
