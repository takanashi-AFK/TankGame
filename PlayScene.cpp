#include "PlayScene.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include"Ground.h"
#include"TankBody.h"
#include"TankHead.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
    :GameObject(parent, "PlayScene"), hModel_(-1)
{
}

//�f�X�g���N�^
PlayScene::~PlayScene()
{
}

//������
void PlayScene::Initialize()
{
    Instantiate<Ground>(this);
    Instantiate<TankBody>(this);
    
}

//�X�V
void PlayScene::Update()
{

}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}