#include "Actor.h"
#include <vector>
#include "../Game.h"
#include "../Components/Component.h"
#include "../Components/SpriteComponent.h"

Actor::Actor(Game* game)
:mState(EActive)
,mPosition(Vector2::Zero)
,mScale(1.0f)
,mRotation(0.0f)
,mGame(game)
{
    // ゲームクラスにアクタを追加
    mGame->AddActor(this);
}

Actor::~Actor()
{
    // ゲームクラスからアクタを削除
    mGame->RemoveActor(this);
    // コンポーネントも合わせて削除
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
}

// 更新処理
void Actor::Update(float deltaTime)
{
    if (mState == EActive)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

// コンポーネント更新処理
void Actor::UpdateComponents(float deltaTime)
{
    for (auto comp : mComponents)
    {
        comp->Update(deltaTime);
    }
}

// アクタ更新処理
void Actor::UpdateActor(float deltaTime)
{
}

// コンポーネント追加
void Actor::AddComponent(Component* component)
{
    // 設定された更新順となるようソートする
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); ++iter)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }
    mComponents.insert(iter, component);
}

// コンポーネント削除
void Actor::RemoveComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}
