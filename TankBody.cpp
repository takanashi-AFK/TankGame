#include "TankBody.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

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