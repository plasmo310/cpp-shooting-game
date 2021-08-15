#include "Game.h"

// メインクラス
// *ここから処理が呼ばれる
int main(int argc, char* argv[]) {
    // 初期化->ループ->終了
    Game game;
    bool success = game.Initialize();
    if (success)
    {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
