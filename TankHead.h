#pragma once
#include "Engine/GameObject.h"
class TankHead : public GameObject
{
    int hModel_;
public:
    //コンストラクタ
    TankHead(GameObject* parent);

    //デストラクタ
    ~TankHead();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};
