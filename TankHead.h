#pragma once
#include "Engine/GameObject.h"
class TankHead : public GameObject
{
    int hModel_;
public:
    //�R���X�g���N�^
    TankHead(GameObject* parent);

    //�f�X�g���N�^
    ~TankHead();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};