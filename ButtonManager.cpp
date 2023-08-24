#include "ButtonManager.h"
#include "ChangeSceneButton.h"
#include "PlayerControlButton.h"
#include "Slider.h"
#include "MoveByMouthButton.h"

namespace ButtonManager
{
    //�{�^���I�u�W�F�N�g�̐����Ə����ݒ�
    void InstantiateButton(GameObject* pParent, GameObject* pChild, XMFLOAT3& position, const XMFLOAT3& interval)
    {
        if (pParent != nullptr)
        {
            pParent->PushBackChild(pChild);
        }

        //����������
        pChild->Initialize();
        //�����ʒu����
        pChild->SetPosition(position);

        //�Ԋu���󂯂�
        Math::Float3Sub(position, interval);
    }


    //��ʑJ�ڃ{�^���̍쐬
    GameObject* CreateSceneChangeButton(GameObject* pParent, XMFLOAT3 position, SCENE_ID name, std::string imageName)
    {
        auto* pNewObject = new ChangeSceneButton(pParent, name, imageName);
        InstantiateButton(pParent, pNewObject, position, XMFLOAT3(0.0f, 0.0f, 0.0f));
        return pNewObject;
    }

    //�v���C���[�̃{�^���ݒ��ʂ̍쐬
    GameObject* CreatePlayerControlButton(GameObject* pParent, XMFLOAT3 position, std::string imageName)
    {
        auto* pNewObject = new PlayerControlButton(pParent, imageName);
        InstantiateButton(pParent, pNewObject, position, XMFLOAT3(0.0f, 0.0f, 0.0f));
        return pNewObject;
    }

    //�X���C�_�[�̍쐬
    GameObject* CreateSliderButton(GameObject* pParent, XMFLOAT3 position, std::string imageName, std::string childImageName)
    {
        auto* pNewObject = new Slider(pParent, imageName, childImageName);
        InstantiateButton(pParent, pNewObject, position, XMFLOAT3(0.0f, 0.0f, 0.0f));
        return pNewObject;
    }

    // �}�E�X�ɂ���ē����{�^���̍쐬
    GameObject* CreateMoveByMouthButton(GameObject* pParent, XMFLOAT3 position, std::string imageName)
    {
        auto* pNewObject = new MoveByMouthButton(pParent, imageName);
        InstantiateButton(pParent, pNewObject, position, XMFLOAT3(0.0f, 0.0f, 0.0f));
        return pNewObject;
    }
}