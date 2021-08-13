#include "Game.h"
#include "SDL_image.h"
#include "Actors/Actor.h"

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,mUpdatingActors(false)
{
}

// ゲーム初期化
bool Game::Initialize()
{
    // SDL関連初期化
    if (!InitializeSDL())
    {
        SDL_Log("%s", SDL_GetError());
        return false;
    }
    // データのロード処理
    LoadData();
    // ゲーム時間取得
    mTicksCount = SDL_GetTicks();
    return true;
}

// SDL関連初期化
bool Game::InitializeSDL()
{
    // 初期化に失敗したらfalseを返す
    bool success = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == 0;
    if (!success) return false;

    mWindow = SDL_CreateWindow("ShootingGame", 100, 100, 1024, 768, 0);
    if (!mWindow) return false;

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) return false;

    success = IMG_Init(IMG_INIT_PNG) != 0;
    if (!success) return false;

    return true;
}

// データのロード処理
void Game::LoadData()
{
    // TODO アクタやスプライトの生成
}

// データのアンロード処理
void Game::UnloadData()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }
}

// ゲームループ処理
void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

// ゲームループ 入力検知
void Game::ProcessInput()
{
    // SDLイベントを受け取る
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: // ウィンドウが閉じられた時
                mIsRunning = false;
                break;
        }
    }
    // TODO 入力検知
}

// ゲームループ 更新処理
void Game::UpdateGame()
{
    // 最低16msは待機
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    // フレームの経過時間を取得(最大50ms)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    // ゲーム時間を再取得
    mTicksCount = SDL_GetTicks();

    // アクタ更新処理
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    // 待機中のアクタを追加
    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    // 破棄されたアクタを削除
    std::vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == Actor::EDead)
        {
            deadActors.emplace_back(actor);
        }
    }
    for (auto actor : deadActors)
    {
        delete actor;
    }
}

// ゲームループ 出力処理
void Game::GenerateOutput()
{
    // 背景色をクリア
    SDL_SetRenderDrawColor(mRenderer,10,10,10,255); // グレー
    SDL_RenderClear(mRenderer);

    // TODO ゲームオブジェクト描画

    // バックバッファとスワップ(ダブルバッファ)
    SDL_RenderPresent(mRenderer);
}

// シャットダウン処理
void Game::Shutdown()
{
    // データをアンロード
    UnloadData();
    IMG_Quit();
    // SDL関連の変数を破棄
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

// アクタ追加処理
void Game::AddActor(Actor* actor)
{
    // アクタ更新中ならPendingに格納
    mUpdatingActors
    ? mPendingActors.emplace_back(actor)
    : mActors.emplace_back(actor);
}

// アクタ削除処理
void Game::RemoveActor(Actor* actor)
{
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        mPendingActors.erase(iter);
    }
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        mActors.erase(iter);
    }
}
