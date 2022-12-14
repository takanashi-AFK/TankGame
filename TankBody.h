#pragma once
#include "Engine/GameObject.h"
class TankBody : public GameObject
{
    int hModel_;
    int camType_;
public:
    //コンストラクタ
    TankBody(GameObject* parent);

    //デストラクタ
    ~TankBody();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};
