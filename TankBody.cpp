#include "TankBody.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//コンストラクタ
TankBody::TankBody(GameObject* parent)
    :GameObject(parent, "TankBody"), hModel_(-1)
{
}

//デストラクタ
TankBody::~TankBody()
{
}

//初期化
void TankBody::Initialize()
{
    hModel_ = Model::Load("TankBody.fbx");
    assert(hModel_ >= 0);
}

//更新
void TankBody::Update()
{

    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= 0.5f;
    }

    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += 0.5f;
    }
   
}

//描画
void TankBody::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void TankBody::Release()
{
}