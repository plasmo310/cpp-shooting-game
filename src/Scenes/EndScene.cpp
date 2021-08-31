#include "EndScene.h"
#include "ReadyScene.h"
#include "../Game.h"
#include "../Actors/Actor.h"
#include "../Actors/Enemy.h"
#include "../Actors/Ship.h"
#include "../Components/SpriteComponent.h"

EndScene::EndScene(class Game *game)
:Scene(game)
{
}

EndScene::~EndScene()
{
}

void EndScene::Start()
{
    // 終了メッセージの作成
    mEndMsg = new Actor(mGame);
    mEndMsg->SetPosition(Vector2(mGame->ScreenWidth / 2, mGame->ScreenHeight / 2));
    auto* endMsgSprite = new SpriteComponent(mEndMsg, 200);
    endMsgSprite->SetTexture(
            mGame->LoadTexture(mGame->GetAssetsPath() + (mGame->GetGameClear() ? "msg_clear.png" : "msg_over.png")));
}

void EndScene::Update(float deltaTime)
{
}

void EndScene::ProcessInput(const Uint8 *state)
{
    // スペースかエンター押下で開始シーンに遷移
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN])
    {
        mGame->SetNextScene(new ReadyScene(mGame));
        mEndMsg->SetState(Actor::EDead);
        // 宇宙船とエネミーを破棄
        std::vector<class Actor*> actors = mGame->GetActors();
        Actor* ship = mGame->GetShip();
        auto iter = std::find(actors.begin(), actors.end(), ship);
        if (iter != actors.end())
        {
            ship->SetState(Actor::EDead);
        }
        for (auto enemy : mGame->GetEnemies())
        {
            enemy->SetState(Actor::EDead);
        }
    }
}

std::string const EndScene::GetSceneName()
{
    return "END";
}
