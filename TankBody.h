#pragma once
#include "Engine/GameObject.h"
class TankBody : public GameObject
{
    int hModel_;
public:
    //�R���X�g���N�^
    TankBody(GameObject* parent);

    //�f�X�g���N�^
    ~TankBody();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};
