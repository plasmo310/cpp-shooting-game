#include "ReadyScene.h"
#include "Scene.h"
#include "GameScene.h"
#include "../Game.h"
#include "../Actors/Actor.h"
#include "../Actors/Ship.h"
#include "../Components/SpriteComponent.h"

ReadyScene::ReadyScene(class Game* game)
:Scene(game)
{
}

ReadyScene::~ReadyScene()
{
}

void ReadyScene::Start()
{
    // クリアフラグを初期化
    mGame->SetGameClear(false);
    // 開始メッセージの作成
    mStartMsg = new Actor(mGame);
    mStartMsg->SetPosition(Vector2(mGame->ScreenWidth / 2, mGame->ScreenHeight / 2));
    auto* startMsgSprite = new SpriteComponent(mStartMsg, 200);
    startMsgSprite->SetTexture(mGame->LoadTexture(mGame->GetAssetsPath() + "msg_start.png"));
    // 宇宙船の作成
    Ship* ship = new Ship(mGame);
    ship->SetPosition(Vector2(mGame->ScreenWidth / 2, mGame->ScreenHeight - 200.0f));
    mGame->SetShip(ship);
}

void ReadyScene::Update(float deltaTime)
{
}

void ReadyScene::ProcessInput(const Uint8 *state)
{
    // スペースかエンター押下でゲームシーンに遷移
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN])
    {
        mGame->SetNextScene(new GameScene(mGame));
        mStartMsg->SetState(Actor::EDead);
    }
}

std::string const ReadyScene::GetSceneName()
{
    return "READY";
}
