#pragma once
#include "Engine/GameObject.h"
class Bullet : public GameObject
{
    int hModel_;
    XMFLOAT3 move_;
public:
    //コンストラクタ
    Bullet(GameObject* parent);

    //デストラクタ
    ~Bullet();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetMove(XMFLOAT3 move) { move_ = move; }
};
