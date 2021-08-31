#pragma once
#include "Scene.h"

// 終了シーンクラス
class EndScene : public Scene {
public:
    EndScene(class Game* game);
    ~EndScene();
    void Start() override;
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* state) override;
    std::string const GetSceneName() override;

private:
    class Actor* mEndMsg;   // 終了メッセージ

};
