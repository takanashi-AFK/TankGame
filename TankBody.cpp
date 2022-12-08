#include "TankBody.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

//�R���X�g���N�^
TankBody::TankBody(GameObject* parent)
    :GameObject(parent, "TankBody"), hModel_(-1)
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
    XMMATRIX MrotY = XMMatrixRotationY(XMConvertToRadians(transform_.position_.y));

    //�ړ��x�N�g�����Ԃ̌����Ă��������
    vMove = XMVector3TransformCoord(vMove, MrotY);	//�x�N�g�������s�񂍂ŕό`   
   
    //���݈ʒu���x�N�g���^����transform_.position_.�֕ϊ�

    if (Input::IsKey(DIK_W))
    {
        vPos += vMove;
       
        XMStoreFloat3(&transform_.position_,vMove );
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