#include "Game.h"
#include "SDL_image.h"
#include "Actors/Actor.h"
#include "Actors/Ship.h"
#include "Actors/Enemy.h"
#include "Components/SpriteComponent.h"
#include "Components/ScrollSpriteComponent.h"

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

    mWindow = SDL_CreateWindow("ShootingGame", 100, 100, ScreenWidth, ScreenHeight, 0);
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
    // 背景の描画
    // ２枚のスクロール速度を変えて視差スクロールにする
    Actor* bgBack = new Actor(this);
    bgBack->SetPosition(Vector2(ScreenWidth / 2, ScreenHeight / 2));
    ScrollSpriteComponent* bgBackSprite = new ScrollSpriteComponent(bgBack, 10);
    bgBackSprite->SetTexture(LoadTexture("../Assets/bg_back.png"));
    bgBackSprite->SetScrollSpeedY(100.0f); // 速度：100

    Actor* bgFront = new Actor(this);
    bgFront->SetPosition(Vector2(ScreenWidth / 2, ScreenHeight / 2));
    ScrollSpriteComponent* bgFrontSprite = new ScrollSpriteComponent(bgFront, 20);
    bgFrontSprite->SetTexture(LoadTexture("../Assets/bg_front.png"));
    bgFrontSprite->SetScrollSpeedY(200.0f); // 速度：200

    // 宇宙船の作成
    mShip = new Ship(this);
    mShip->SetPosition(Vector2(ScreenWidth / 2, 824.0f));

    // TODO ジェネレータの作成
    // エネミーの作成
    Enemy* enemy = new Enemy(this);
    enemy->SetPosition(Vector2(ScreenWidth / 2, 0.0f));
    enemy->SetScale(1.2f);
    enemy->SetEnemyMoveType(Enemy::SHAKE);

    Enemy* enemy2 = new Enemy(this);
    enemy2->SetPosition(Vector2(100, -100.0f));
    enemy2->SetEnemySpeed(350a.0f);

    Enemy* enemy3 = new Enemy(this);
    enemy3->SetPosition(Vector2(550, -200.0f));
    enemy3->SetScale(0.7f);
    enemy3->SetEnemyMoveType(Enemy::SHAKE);
    enemy3->SetEnemySpeed(500.0f);
    enemy3->SetEnemyShakeWidth(10.0f);
}

// データのアンロード処理
void Game::UnloadData()
{
    // アクタ破棄
    while (!mActors.empty())
    {
        delete mActors.back();
    }
    // テクスチャ破棄
    for (auto i : mCachedTextures)
    {
        SDL_DestroyTexture(i.second);
    }
    mCachedTextures.clear();
}

// ファイル名からテクスチャをロードする
SDL_Texture* Game::LoadTexture(const std::string& fileName)
{
    SDL_Texture* tex = nullptr;
    auto iter = mCachedTextures.find(fileName);
    if (iter != mCachedTextures.end())
    {
        // キャッシュ済なら変数から取得
        tex = iter->second;
    }
    else
    {
        // テクスチャをロードする
        SDL_Surface* surf = IMG_Load(fileName.c_str());
        if (!surf)
        {
            SDL_Log("Error load texture file %s", fileName.c_str());
            return nullptr;
        }
        tex = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_FreeSurface(surf);
        if (!tex)
        {
            SDL_Log("Error convert surface to texture %s", fileName.c_str());
            return nullptr;
        }
        // 変数にキャッシュする
        mCachedTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
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
    // キーの入力イベントを受け取る
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
    // 宇宙船のキーイベント
    mShip->ProcessKeyboard(state);
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
    SDL_SetRenderDrawColor(mRenderer,19,56,111,255); // 紺色
    SDL_RenderClear(mRenderer);

    // スプライトを描画
    for (auto sprite : mSprites)
    {
        sprite->Draw(mRenderer);
    }

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

// 描画中のスプライト追加処理
void Game::AddSprite(SpriteComponent* sprite)
{
    // 描画順にソートして追加
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }
    mSprites.insert(iter, sprite);
}

// 描画中のスプライト削除処理
void Game::RemoveSprite(SpriteComponent* sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

// エネミー追加
void Game::AddEnemy(Enemy* enemy)
{
    mEnemies.emplace_back(enemy);
}

// エネミー削除
void Game::RemoveEnemy(Enemy* enemy)
{
    auto iter = std::find(mEnemies.begin(),mEnemies.end(), enemy);
    if (iter != mEnemies.end())
    {
        mEnemies.erase(iter);
    }
}
