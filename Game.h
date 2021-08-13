#pragma once
#include <SDL.h>

class Game {
public:
    Game();
    bool Initialize(); // ゲーム初期化
    void RunLoop();    // ゲームループ処理
    void Shutdown();   // シャットダウン処理
private:
    bool InitializeSDL();  // SDL関連初期化
    void ProcessInput();   // ゲームループ 入力検知
    void UpdateGame();     // ゲームループ 更新処理
    void GenerateOutput(); // ゲームループ 出力処理

    SDL_Window* mWindow;     // SDLウィンドウ
    SDL_Renderer* mRenderer; // SDLレンダラー
    Uint32 mTicksCount;  // ゲーム時間
    bool mIsRunning;     // 実行中か否か？
};
