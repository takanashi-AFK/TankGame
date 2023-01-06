#include "PlayScene.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include"Ground.h"
#include"TankBody.h"
#include"TankHead.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
    :GameObject(parent, "PlayScene"), hModel_(-1)
{
}

//デストラクタ
PlayScene::~PlayScene()
{
}

//初期化
void PlayScene::Initialize()
{
    Instantiate<Ground>(this);
    Instantiate<TankBody>(this);
    
}

//更新
void PlayScene::Update()
{

}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}