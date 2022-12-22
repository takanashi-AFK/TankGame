#include "TankHead.h"
#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//コンストラクタ
TankHead::TankHead(GameObject* parent)
    :GameObject(parent, "TankHead"), hModel_(-1)
{
}

//デストラクタ
TankHead::~TankHead()
{
}

//初期化
void TankHead::Initialize()
{
    hModel_ = Model::Load("TankHead.fbx");
    assert(hModel_ >= 0);
}

//更新
void TankHead::Update()
{
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 2;
    }
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 2;
    }

    if (Input::IsKeyDown(DIK_SPACE))
    {

        XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");
        XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");

        XMVECTOR vTop = XMLoadFloat3(&cannonTop);
        XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);

        XMVECTOR vMove = vTop - vRoot;
        vMove = XMVector3Normalize(vMove);
        vMove *= 0.5;
        XMFLOAT3 Move;
        XMStoreFloat3(&Move, vMove);

     Bullet* pBullet = Instantiate <Bullet>(GetParent()->GetParent());
     pBullet->SetPosition(cannonTop);
    }
}

//描画
void TankHead::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void TankHead::Release()
{
}