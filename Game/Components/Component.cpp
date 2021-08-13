#include "Component.h"
#include "../Actors/Actor.h"

Component::Component(Actor* actor, int updateOrder)
:mActor(actor)
,mUpdateOrder(updateOrder)
{
    // アクタにコンポーネントを追加
    mActor->AddComponent(this);
}

Component::~Component()
{
    // アクタからコンポーネントを削除
    mActor->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}
