#pragma once
#include "Component.h"
#include "../Commons/Vector2.h"

// コライダコンポーネントクラス
// *現時点では円コライダのみ
class ColliderComponent : public Component
{
public:
    ColliderComponent(class Actor* actor);
    const Vector2& GetCenter() const;
private:
    float mRadius; // 半径
public:
    void SetRadius(float radius) { mRadius = radius; }
    float GetRadius() const;
};

// 衝突判定処理
bool Intersect(const ColliderComponent& a, const ColliderComponent& b);
