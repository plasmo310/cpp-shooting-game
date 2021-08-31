#include "GameScene.h"
#include "EndScene.h"
#include "../Game.h"
#include "../Actors/Enemy.h"
#include "../Actors/Ship.h"
#include "../Commons/Math.h"

GameScene::GameScene(class Game *game)
:Scene(game)
{
}

GameScene::~GameScene()
{
}

void GameScene::Start()
{
    // エネミーをランダム作成
    for (int i = 0; i < 30; i++)
    {
        auto* enemy = new Enemy(mGame);
        enemy->SetPosition(Vector2(Math::GetRand(100.0f, mGame->ScreenWidth - 100.0f), -100.0f));
        enemy->SetEnemySpeed(Math::GetRand(300.0f, 550.0f));
        enemy->SetScale(Math::GetRand(0.5f, 1.5f));
        // 数匹ごとに揺らす
        if (i % 2 == 0)
        {
            enemy->SetEnemyMoveType(Enemy::SHAKE);
            enemy->SetEnemyShakeWidth(Math::GetRand(5.0f, 15.0f));
        }
        // 数匹ずつ動かす
        enemy->SetWaitTime(i / 3 * Math::GetRand(80.0f, 100.0f));
    }
}

void GameScene::Update(float deltaTime)
{
    // エネミーを全部撃破したらゲームクリア
    if (mGame->GetEnemies().empty())
    {
        mGame->SetGameClear(true);
        mGame->SetNextScene(new EndScene(mGame));
    }
}

void GameScene::ProcessInput(const Uint8 *state)
{
    // 宇宙船のキー入力操作
    mGame->GetShip()->ProcessKeyboard(state);
}

std::string const GameScene::GetSceneName()
{
    return "GAME";
}
