#pragma once

// コンポーネントクラス
// *各コンポーネントはこのクラスを継承する
class Component
{
public:
    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();
    virtual void Update(float deltaTime); // コンポーネント更新処理

protected:
    class Actor* mActor; // コンポーネントを追加するアクタ
    int mUpdateOrder;    // コンポーネント更新の順番

public:
    // Getter, Setter
    int GetUpdateOrder() const { return mUpdateOrder; }
};
