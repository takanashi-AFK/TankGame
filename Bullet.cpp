#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//コンストラクタ
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet"), hModel_(-1)
{
}

//デストラクタ
Bullet::~Bullet()
{
}

//初期化
void Bullet::Initialize()
{
    hModel_ = Model::Load("Bullet.fbx");
    assert(hModel_ >= 0);

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.25f);
    AddCollider(collision);

  
}

//更新
void Bullet::Update()
{
    transform_.position_.x += move_.x;
    transform_.position_.y += move_.y;
    transform_.position_.z += move_.z;
    if (transform_.position_.z > 75.0f)
    {
        KillMe();
    }
}

//描画
void Bullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Bullet::Release()
{
}