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
    Debug::Log(transform_.rotate_.y, true);


    //��Ԃ̌��݈ʒu���x�N�g���^�ɕϊ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //����0.1����
    XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };

    //Y����transform_.rotate_.y����]������s��
    XMMATRIX MrotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//��]�s��

    //�ړ��x�N�g�����Ԃ̌����Ă��������
    vMove = XMVector3TransformCoord(vMove, MrotY);	//�x�N�g�������s�񂍂ŕό`   

    //���݈ʒu���x�N�g���^����transform_.position_.�֕ϊ�

    if (Input::IsKey(DIK_W))
    {
        vPos += vMove;

        XMStoreFloat3(&transform_.position_, vPos);
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



    if (Input::IsKeyDown(DIK_F))
    {
        if (camType_ < CAM_TYPE_FPS)CamType += 1;
        else camType_ = CAM_TYPE_FIXED;
    }

    //�œ_�̈ʒu
    XMFLOAT3 CamTarget = { 0,0,0 };
    //��l�̃J�����̈ʒu
    XMFLOAT3 CamPosition = { 0,0,0 };
    //�R�l�̃J�����̈ʒu
    XMVECTOR CamVector = { 0,5,-10,0 };
    CamVector = XMVector3TransformCoord(CamVector, MrotY);

    //���_���
    switch (camType_)
    {
    case CAM_TYPE_FIXED://��_�J����(�X�e�[�W�S�̂��f��)
        CamTarget = XMFLOAT3(0, 0, -7);
        CamPosition = XMFLOAT3(0, 45, -30);
        break;
    case CAM_TPS_NO_ROT://3�l�̎��_(��]�Ȃ�)
        CamTarget = transform.position;
        CamPosition = transform.position_;
        CamPosition.y += 5;//tank��荂�����T�����ʒu
        CamPosition.z -= 10;//tank��肚���P�O�����ʒu
        break;
    case CAM_TYPE_TPS://3�l�̎��_(��]����)
        CamTarget = transform.position_;
        XMStoreFloat3(&CamPosition, vPos + CamVector);
        break;
    case CAM_TYPE_FPS://��l�̎��_

        XMStoreFloat3(&CamTarget, vPos + vMove);
        XMStoreFloat3(&CamPosition, vPos);
        break;
    }
    Camera::SetTarget(CamTarget);
    Camera::SetPosition(CamPosition);
    



    Ground* pStage = (Ground*)FindObject("Ground");    //�X�e�[�W�I�u�W�F�N�g��T��
    int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾

    RayCastData data;
    data.start = transform_.position_;//���C�̔��ˈʒu
    data.start.y = 0;
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