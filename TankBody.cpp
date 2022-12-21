#include "TankBody.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "Ground.h"


enum
{
    CAM_TYPE_FIXED,
    CAM_TYPE_TPS_NO_ROT,
    CAM_TYPE_TPS,
    CAM_TYPE_FPS,
    CAM_TYPE_MAX
};

//コンストラクタ
TankBody::TankBody(GameObject* parent)
    :GameObject(parent, "TankBody"), hModel_(-1),camType_(0)
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
    XMMATRIX MrotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//transform_.position_.にしてたわ

    //移動ベクトルを戦車の向いている方向に
    vMove = XMVector3TransformCoord(vMove, MrotY);	//ベクトルｖを行列ｍで変形   
   
    //現在位置をベクトル型からtransform_.position_.へ変換

    if (Input::IsKey(DIK_W))
    {
        vPos += vMove;
       
        XMStoreFloat3(&transform_.position_,vPos );
    }

    if (Input::IsKey(DIK_S))
    {
        vPos -= vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    Camera::SetTarget(transform_.position_);
    XMVECTOR vCam = { 0,5,-10,0 };
    vCam = XMVector3TransformCoord(vCam, MrotY);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(camPos);

    /*XMFLOAT3 camPos = transform_.position_;
    camPos.y += 5;
    camPos.z -= 10;
    Camera::SetPosition(camPos);*/


    if (Input::IsKeyDown(DIK_Z))
    {
        //camera切り替えキーを配置
    }

    Ground* pStage = (Ground*)FindObject("Ground");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

    RayCastData data;
    data.start = transform_.position_;   //レイの発射位置
    data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &data); //レイを発射

  

    if (data.hit == true)
    {
        transform_.position_.y -= data.dist;
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