#pragma once
#include "SDL_image.h"
#include "string"

// シーン基底クラス
// *各シーンはこのクラスを継承する
class Scene
{
public:
    Scene(class Game* game);
    virtual ~Scene();
    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void ProcessInput(const Uint8* state);
    virtual std::string const GetSceneName();

protected:
    class Game* mGame;

};
