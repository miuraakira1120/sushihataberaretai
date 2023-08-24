#include "Global.h"
#include "Image.h"
#include "Input.h"

//3D�摜���Ǘ�����
namespace Image
{
	//���[�h�ς݂̉摜�f�[�^�ꗗ
	std::vector<ImageData*>	_datas;

	//������
	void Initialize()
	{
		AllRelease();
	}

	//�摜�����[�h
	int Load(std::string fileName)
	{
		ImageData* pData = new ImageData;

		//�J�����t�@�C���ꗗ���瓯���t�@�C�����̂��̂��������T��
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
			{
				pData->pSprite = _datas[i]->pSprite;
				isExist = true;
				break;
			}
		}

		//�V���Ƀt�@�C�����J��
		if (isExist == false)
		{
			pData->pSprite = new Sprite;
			if (FAILED(pData->pSprite->Load(fileName)))
			{
				//�J���Ȃ�����
				SAFE_DELETE(pData->pSprite);
				SAFE_DELETE(pData);
				return -1;
			}

			//�����J����
			pData->fileName = fileName;
		}


		//�g���ĂȂ��ԍ����������T��
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] == nullptr)
			{
				_datas[i] = pData;
				return i;
			}
		}

		//�V���ɒǉ�
		_datas.push_back(pData);

		//�摜�ԍ�����U��
		int handle = (int)_datas.size() - 1;

		//�؂蔲���͈͂����Z�b�g
		ResetRect(handle);

		return handle;
	}

	//�`��
	void Draw(int handle, Direct3D::SHADER_TYPE type)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}
		_datas[handle]->transform.Calclation();
		_datas[handle]->pSprite->Draw(_datas[handle]->transform, _datas[handle]->rect, _datas[handle]->alpha, type);
	}

	//�C�ӂ̉摜���J��
	void Release(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		//�������f���𑼂ł��g���Ă��Ȃ���
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas[i] != nullptr && i != handle && _datas[i]->pSprite == _datas[handle]->pSprite)
			{
				isExist = true;
				break;
			}
		}

		//�g���ĂȂ���΃��f�����
		if (isExist == false)
		{
			SAFE_DELETE(_datas[handle]->pSprite);
		}

		SAFE_DELETE(_datas[handle]);
	}



	//�S�Ẳ摜�����
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			Release(i);
		}
		_datas.clear();
	}


	//�؂蔲���͈͂̐ݒ�
	void SetRect(int handle, int x, int y, int width, int height)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		_datas[handle]->rect.left = x;
		_datas[handle]->rect.top = y;
		_datas[handle]->rect.right = width;
		_datas[handle]->rect.bottom = height;
	}


	//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
	void ResetRect(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		XMFLOAT3 size = _datas[handle]->pSprite->GetTextureSize();

		_datas[handle]->rect.left = 0;
		_datas[handle]->rect.top = 0;
		_datas[handle]->rect.right = (long)size.x;
		_datas[handle]->rect.bottom = (long)size.y;

	}

	//�A���t�@�l�ݒ�
	void SetAlpha(int handle, int alpha)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}
		_datas[handle]->alpha = (float)alpha / 255.0f;
	}


	//���[���h�s���ݒ�
	void SetTransform(int handle, Transform& transform)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		_datas[handle]->transform = transform;
	}


	//���[���h�s��̎擾
	XMMATRIX GetMatrix(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return XMMatrixIdentity();
		}
		return _datas[handle]->transform.GetWorldMatrix();
	}

	void SetTransformFullSize(int handle)
	{
		if (handle < 0 || handle >= _datas.size()) {
			return;
		}
		auto textureSize = _datas[handle]->pSprite->GetTextureSize();
		const auto winW = Direct3D::screenWidth_;
		const auto winH = Direct3D::screenWidth_;

		Transform transform;
		transform.scale_.x *= winW / textureSize.x;
		transform.scale_.y *= winH / textureSize.y;

		_datas[handle]->transform = transform;
		_datas[handle]->transform = transform;
		_datas[handle]->transform = transform;
	}

	//�摜�T�C�Y�̎擾
	XMFLOAT3 GetTextureSize(const int handle)
	{
		return _datas[handle]->pSprite->GetTextureSize();
	}

	bool OnMouseOver(int handle)
	{
		UINT wid = (UINT)(_datas[handle]->pSprite->GetTextureSize().x * _datas[handle]->transform.scale_.x / 2);
		UINT hgt = (UINT)(_datas[handle]->pSprite->GetTextureSize().y * _datas[handle]->transform.scale_.y / 2);
		float Left = (_datas[handle]->transform.position_.x + 1) * (Direct3D::screenWidth_ / 2.0f) - wid;
		float Right = (_datas[handle]->transform.position_.x + 1) * (Direct3D::screenWidth_ / 2.0f) + wid;
		float Top = (-_datas[handle]->transform.position_.y + 1) * (Direct3D::screenHeight_ / 2.0f) - hgt;
		float Bottom = (-_datas[handle]->transform.position_.y + 1) * (Direct3D::screenHeight_ / 2.0f) + hgt;
		if (Left <= Input::GetMousePosition().x && Input::GetMousePosition().x <= Right &&
			Top <= Input::GetMousePosition().y && Input::GetMousePosition().y <= Bottom)
		{
			return true;
		}
		return false;
	}
}
