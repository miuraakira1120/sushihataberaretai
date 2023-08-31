#pragma once
#include "Engine/GameObject.h"

class ModelBase;

//�l�^�̑f�N���X
class NetaMaterial : public GameObject
{
protected:
    const float     MODEL_ALPHA = 0.2f;                             //���f���̃A���t�@�l
    const float     INTERNAL_MODEL_SCALE = 0.5f;                    //�����ɓ���郂�f���̑傫��
    const float     SPHERE_SIZE = 1.0f;                             //���̃��f���̃T�C�Y
    const XMFLOAT3  INTERNAL_MODEL_ROTATE = { 0.0f, 0.3f, 0.0f };   //�����ɓ���郂�f���̉�]���x 

    int hModel_;                    //���f���ԍ�
    ModelBase* pInternalModel;      //�����ɓ���郂�f���̃|�C���^
    std::string internalModelPath;  //�����ɓ���郂�f���̃p�X
    std::string internalModelType;  //���Ɖ��̃l�^���悹��̂�
    

public:
    //�R���X�g���N�^
    NetaMaterial(GameObject* parent);
    NetaMaterial(GameObject* parent, std::string fileName);

    //�f�X�g���N�^
    ~NetaMaterial();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����ɓ�������
   //�����FpTarget ������������
    virtual void OnCollision(GameObject* pTarget);
};