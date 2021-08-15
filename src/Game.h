#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>

// ゲーム管理クラス
// *ゲーム全体の流れ、アクタ生成、テクスチャ読込を行う
class Game
{
public:
    Game();
    bool Initialize(); // ゲーム初期化
    void RunLoop();    // ゲームループ処理
    void Shutdown();   // シャットダウン処理

    void AddActor(class Actor* actor);    // アクタ追加
    void RemoveActor(class Actor* actor); // アクタ削除

    void AddSprite(class SpriteComponent* sprite);    // 描画中のスプライトを追加
    void RemoveSprite(class SpriteComponent* sprite); // 描画中のスプライトを削除

    void AddEnemy(class Enemy* enemy);    // エネミー追加
    void RemoveEnemy(class Enemy* enemy); // エネミー削除

    SDL_Texture* LoadTexture(const std::string& fileName); // テクスチャロード処理

    // シーン
    enum Scene
    {
        READY_SCENE, // 開始シーン
        GAME_SCENE,  // ゲームシーン
        END_SCENE    // 終了シーン
    };

    constexpr static const float ScreenWidth  = 768.0f;  // スクリーン横幅
    constexpr static const float ScreenHeight = 1024.0f; // スクリーン縦幅

private:
    bool InitSDL();        // SDL関連初期化
    void InitScene();      // シーン初期化処理
    void StartScene();     // シーン開始処理
    void UpdateScene();    // シーン更新処理
    void ProcessInput();   // 入力検知
    void GenerateOutput(); // 出力処理

    std::vector<class Actor*> mActors;            // アクタリスト
    std::vector<class Actor*> mPendingActors;     // 待機中のアクタリスト
    std::vector<class SpriteComponent*> mSprites; // 描画中のスプライトリスト
    std::unordered_map<std::string, SDL_Texture*> mCachedTextures; // キャッシュしたテクスチャリスト

    SDL_Window* mWindow;     // SDLウィンドウ
    SDL_Renderer* mRenderer; // SDLレンダラー
    Uint32 mTicksCount;      // ゲーム時間
    bool mIsRunning;         // 実行中か否か？
    bool mUpdatingActors;    // アクタ更新中か否か？
    bool mGameClear;         // ゲームをクリアしたか否か？

    Scene mScene;     // 現在のシーン
    Scene mNextScene; // 遷移するシーン

    class Actor* mStartMsg; // 開始メッセージ
    class Actor* mEndMsg;   // 終了メッセージ
    class Ship* mShip;      // 宇宙船
    std::vector<class Enemy*> mEnemies; // エネミー群
    
    // 画像パス
    const std::string AssetsPath = "../Assets/"; // Mac + CLion
    //const std::string AssetsPath = "Assets\\"; // Win + VisualStudio

public:
    // getter, setter
    Scene GetNextScene() const { return mNextScene; }
    void SetNextScene(const Scene scene) { mNextScene = scene; }
    Scene GetScene() const { return mScene; }
    void SetScene(const Scene scene) { mScene = scene; }
    std::vector<class Enemy*> GetEnemies() { return mEnemies; }
    std::string GetAssetsPath() const { return AssetsPath; }
};
