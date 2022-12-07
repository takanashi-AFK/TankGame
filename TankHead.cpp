#include "TankHead.h"
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