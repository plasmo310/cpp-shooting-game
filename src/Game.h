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

    SDL_Texture* LoadTexture(const std::string& fileName); // テクスチャロード処理
private:
    bool InitializeSDL();  // SDL関連初期化
    void ProcessInput();   // ゲームループ 入力検知
    void UpdateGame();     // ゲームループ 更新処理
    void GenerateOutput(); // ゲームループ 出力処理
    void LoadData();       // データロード処理
    void UnloadData();     // データアンロード処理

    std::vector<class Actor*> mActors;            // アクタリスト
    std::vector<class Actor*> mPendingActors;     // 待機中のアクタリスト
    std::vector<class SpriteComponent*> mSprites; // 描画中のスプライトリスト
    std::unordered_map<std::string, SDL_Texture*> mCachedTextures; // キャッシュしたテクスチャリスト

    SDL_Window* mWindow;     // SDLウィンドウ
    SDL_Renderer* mRenderer; // SDLレンダラー
    Uint32 mTicksCount;      // ゲーム時間
    bool mIsRunning;         // 実行中か否か？
    bool mUpdatingActors;    // アクタ更新中か否か？
};
