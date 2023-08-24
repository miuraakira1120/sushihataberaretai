#pragma once
#include "Engine/GameObject.h"
#include <directxmath.h>
#include <vector>

//Pause�V�[�����Ǘ�����N���X
class Pause
{
private:
    std::vector<GameObject*> UIList;

public:
    //�R���X�g���N�^
    Pause();

    //�f�X�g���N�^
    ~Pause();

    //������
    void Initialize();

    //�X�V
    void Update();

    //�`��
    void Draw();

    //�J��
    void Release();

    //UI�̍쐬
    void CreateUI();

    //UI�̍폜
    void DeleteUI();

    //UI���X�g�̒��g�̍X�V��S���Ă�
    void AllPauseUIUpdate();

    //UI���X�g�̒��g�̕`���S���Ă�
    void AllPauseUIDraw();

    //UIList�ɓ����
    void AddUIList(GameObject* ui);
};