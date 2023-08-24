#pragma once
#include "Engine/SceneManager.h"
#include "ButtonManager.h"
#include "InstanceManager.h"

//imgui���Ǘ�����N���X
namespace Imgui_Obj
{
    //�Đݒ�̎��ɕK�v�ȏ��
    struct SettingInfo
    {
        SettingInfo(GameObject* obj, std::string loadFileName, std::string sectionName, std::string writeFileName, XMFLOAT3 position, XMFLOAT3 rotate, XMFLOAT3 scale, int alpha = 255) :
            pObject_{ obj }, loadFileName_{ loadFileName }, sectionName_{ sectionName }, writeFile_{ writeFileName }, iniPosition_
            { position }, iniRotate_{ rotate }, iniScale_{ scale }, alpha_{ alpha } {}

        GameObject* pObject_;
        std::string loadFileName_;      //�ǂݍ��ރt�@�C����
        std::string sectionName_;       //�Z�N�V�����̖��O 
        std::string writeFile_;         //�ۑ�������ۂɏ�������JSON�̃t�@�C����
        XMFLOAT3    iniPosition_;       //�ʒu
        XMFLOAT3    iniRotate_;         //����
        XMFLOAT3    iniScale_;          //�g�嗦
        int         alpha_;             //�A���t�@�l 

    };

    //������
    void Initialize(SceneManager* pSceneManager_);

    //�X�V
    void Update();

    //�J��
    void Release();

    /// <summary>
    /// Imgui�̐���
    /// </summary>
    void InstantiateImgui();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

    /// <summary>
    /// �I�u�W�F�N�g�𐶐�����Imgui���o���֐�
    /// </summary>
    void ImguiIniObj();
    
    /// <summary>
    /// �V�[���`�F���W����Imgui�𐶐�����֐�
    /// </summary>
    /// <param name="isPause">�|�[�Y��ʂ��ǂ���</param>
    void SceneChangeImgui();

    /// <summary>
    /// imgui�Ń{�^���𐶐�������ɂ�邱��
    /// </summary>
    void RearButtonInstantiate();

    /// <summary>
    /// imgui�ŉ摜�𐶐�������ɂ�邱��
    /// </summary>
    void RearImageInstantiate();
    
    //������{�^���̍Ĉړ������o����悤�ɂ���
    void ReSettingButton();

    /// <summary>
    /// �{�^���쐬���[�h�̎��ɏo��imgui
    /// </summary>
    void CreateButtonImgui();

    /// <summary>
    /// �摜�쐬���[�h�̎��ɏo��Imgui(Begin�̒��Ŏg��)
    /// </summary>
    void CreateImageImgui();

    /// <summary>
    /// 3D�I�u�W�F�N�g�쐬���[�h�̎��ɏo��Imgui(Begin�̒��Ŏg��)
    /// </summary>
    void CreateObjectImgui();

    /// <summary>
    /// �I�u�W�F�N�g�𐶐����鎞�Ɋ�{�I��Imgui���o��(Begin�̒��Ŏg��)
    /// </summary>
    void SettingBasicImgui();

    /// <summary>
    /// �f�o�b�O���O��\������Imgui���o��
    /// </summary>
    void CreateDebugLog();
    
    /// <summary>
    /// �f�o�b�O���O��\�����郊�X�g�ɒǉ�����
    /// </summary>
    /// <param name="obj">�ǉ�����I�u�W�F�N�g</param>
    void AddDebugLogList(GameObject* obj);


    /// <summary>
    /// �g���q��ǉ�����֐�(�ϐ�extension���Q��)
    /// </summary>
    /// <returns>�Ԃ��g���q</returns>
    std::string AddExtension();

    /// <summary>
    /// ������{�^���̃��X�g�ɓ����
    /// </summary>
    /// <param name="filename">�t�@�C����</param>
    /// <param name="section">�Z�N�V������</param>
    /// <param name="info">�������鎞�ɕK�v�ȏ��</param>
    /// <param name="button">�����|�C���^</param>
    void AddButtonList(std::string filename, std::string section, InstanceManager::CreateInfoJSON info, Button* button);

    /// <summary>
    /// ������摜�̃��X�g�ɓ����
    /// </summary>
    /// <param name="filename">�t�@�C����</param>
    /// <param name="section">�Z�N�V������</param>
    /// <param name="info">�������鎞�ɕK�v�ȏ��</param>
    /// <param name="button">�����|�C���^</param>
    void AddImageList(std::string filename, std::string section, InstanceManager::CreateImageInfoJSON info, GameObject* image);

    /// <summary>
    /// �����郊�X�g���N���A����
    /// </summary>
    void ClearList();

    /// <summary>
    /// UI���[�h��I������Imgui���쐬����
    /// </summary>
    void UISelectModeImgui();

    //modeUI�̃Q�b�^�[

    /// <summary>
    /// modeUI�̃Q�b�^�[
    /// </summary>
    /// <returns>modeUI</returns>
    int GetUIType();
    
    /// <summary>
    /// �t�@�C�������邩�m�F
    /// </summary>
    /// <param name="filename">���ׂ�t�@�C����</param>
    /// <returns><returns>���݂��邩�ǂ���</returns></returns>
    bool existFile(std::string filename);

    
};

//�ǉ�����{�^���𑝂₷�菇
//1 CreateButtonImgui�̒��̂ǂ�Ȏ�ނ̃{�^���𐶐����邩�ɒǉ�
//2 �����{�^���ɒǉ�
//3 JsonOperator::ButtonToString�ɒǉ�(buttonStrList)
