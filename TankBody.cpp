#include "TankBody.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

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
    Debug::Log(transform_.rotate_.y,true);


    //戦車の現在位置をベクトル型に変換
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //奥に0.1動く
    XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };

    //Y軸でtransform_.rotate_.y°回転させる行列
    XMMATRIX MrotY = XMMatrixRotationY(XMConvertToRadians(transform_.position_.y));

    //移動ベクトルを戦車の向いている方向に
    vMove = XMVector3TransformCoord(vMove, MrotY);	//ベクトルｖを行列ｍで変形   
   
    //現在位置をベクトル型からtransform_.position_.へ変換

    if (Input::IsKey(DIK_W))
    {
        vPos += vMove;
       
        XMStoreFloat3(&transform_.position_,vMove );
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