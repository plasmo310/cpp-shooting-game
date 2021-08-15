#include "ColliderComponent.h"
#include "../Actors/Actor.h"

ColliderComponent::ColliderComponent(class Actor *actor)
:Component(actor)
,mRadius(0.0f)
{
}

// 中心座標を取得
const Vector2& ColliderComponent::GetCenter() const
{
    return mActor->GetPosition();
}

// スケールを考慮した半径を返却
float ColliderComponent::GetRadius() const
{
    return mActor->GetScale() * mRadius;
}

// 衝突処理
bool Intersect(const ColliderComponent& a, const ColliderComponent& b)
{
    // 計算負荷軽減のためsqrtせずに比較
    // 衝突した物体との距離
    Vector2 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();
    // 衝突円の半径の合計以下なら衝突
    float radDiff = a.GetRadius() + b.GetRadius();
    return distSq <= radDiff * radDiff;
}
