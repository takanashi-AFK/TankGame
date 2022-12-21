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

//�R���X�g���N�^
TankBody::TankBody(GameObject* parent)
    :GameObject(parent, "TankBody"), hModel_(-1),camType_(0)
{
}

//�f�X�g���N�^
TankBody::~TankBody()
{
}

//������
void TankBody::Initialize()
{
    hModel_ = Model::Load("TankBody.fbx");
    assert(hModel_ >= 0);
}

//�X�V
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


    //��Ԃ̌��݈ʒu���x�N�g���^�ɕϊ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //����0.1����
    XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };

    //Y����transform_.rotate_.y����]������s��
    XMMATRIX MrotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//transform_.position_.�ɂ��Ă���

    //�ړ��x�N�g�����Ԃ̌����Ă��������
    vMove = XMVector3TransformCoord(vMove, MrotY);	//�x�N�g�������s�񂍂ŕό`   
   
    //���݈ʒu���x�N�g���^����transform_.position_.�֕ϊ�

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
        //camera�؂�ւ��L�[��z�u
    }

    Ground* pStage = (Ground*)FindObject("Ground");    //�X�e�[�W�I�u�W�F�N�g��T��
    int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾

    RayCastData data;
    data.start = transform_.position_;   //���C�̔��ˈʒu
    data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &data); //���C�𔭎�

  

    if (data.hit == true)
    {
        transform_.position_.y -= data.dist;
    }
}

//�`��
void TankBody::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void TankBody::Release()
{
}