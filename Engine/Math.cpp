#include "Math.h"
#include "Direct3D.h"

namespace Math
{
	/// <summary>
	/// XMFloat3�̑����Z
	/// </summary>
	/// <param name="����1 : ������鐔"></param>
	/// <param name="����2 : ������"></param>
	/// <param name="�ߒl  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	/// <summary>
	/// XMFloat3�̈����Z
	/// </summary>
	/// <param name="����1 : ������鐔"></param>
	/// <param name="����2 : ������"></param>
	/// <param name="�ߒl  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Sub(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/// <summary>
	///  XMFloat3��xyz�ɓ�����������
	/// </summary>
	/// <param name="a">XMFloat3�̂������鐔</param>
	/// <param name="b">XMFloat3��x�ɂ����鐔</param>
	/// <param name="c">XMFloat3��y�ɂ����鐔</param>
	/// <param name="d">XMFloat3��z�ɂ����鐔</param>
	/// <returns></returns>
	XMFLOAT3 Float3Mul(XMFLOAT3 a, float b, float c, float d)
	{
		return XMFLOAT3(a.x * b, a.y * c, a.z * d);
	}

	XMFLOAT3 Float3Mul(XMFLOAT3 a, float b)
	{
		return XMFLOAT3(a.x * b, a.y * b, a.z * b);
	}

	/// <summary>
	/// XMFloat3�̕����̔��]
	/// </summary>
	/// <param name="����1 : ���]���鐔"></param>
	/// <param name="�ߒl  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Reverse(XMFLOAT3 a)
	{
		return XMFLOAT3(-(a.x), -(a.y), -(a.z));
	}
	//����2���r���ē��������ׂ�
	bool Float3Comparison(XMFLOAT3 a, XMFLOAT3 b)
	{
		//��r
		if (a.x == b.x && a.y == b.y && a.z == b.z)
		{
			return true;
		}
		return false;
	}

	/// <summary>
	/// Transform���s�N�Z���ɕϊ�
	/// </summary>
	/// <param name="transform"></param>
	/// <returns></returns>
	XMFLOAT3 TransformToPixel(const XMFLOAT3& transform)
	{
		//position_��0~1�ɕύX
		XMFLOAT3 pos = { (transform.x + 1) / 2, (-transform.y + 1) / 2, transform.z };
		pos = { pos.x * Direct3D::screenWidth_, pos.y * Direct3D::screenHeight_, pos.z };

		return pos;
	}

	/// <summary>
	/// �s�N�Z����Transform�ɕϊ�
	/// </summary>
	/// <param name="pixel"></param>
	/// <returns></returns>
	XMFLOAT3 PixelToTransform(const XMFLOAT3& pixel)
	{
		XMFLOAT3 pos = { pixel.x / Direct3D::screenWidth_, pixel.y / Direct3D::screenHeight_, pixel.z };
		pos = { pos.x * 2 - 1, -pos.y * 2 + 1, pos.z };

		return pos;
	}

	//// �p�[�����m�C�Y�̐����֐�
	//// �����_���Ȓl�𐶐�����֐�
	//float Random()
	//{
	//	return static_cast<float>(std::rand()) / RAND_MAX;
	//}

	//// �O���f�B�G���g�x�N�g���𐶐�����֐�
	//void GenerateGradientVectors(float* gradientVectors, int count)
	//{
	//	for (int i = 0; i < count; ++i)
	//	{
	//		float angle = Random() * 2.0f * 3.14159265359f;
	//		gradientVectors[i * 2] = std::cos(angle);
	//		gradientVectors[i * 2 + 1] = std::sin(angle);
	//	}
	//}

	//// �p�[�����m�C�Y�̐����֐�
	//float PerlinNoise(float x, float y)
	//{
	//	// ���������Ə��������̌v�Z
	//	int xi = static_cast<int>(x) & 255;
	//	int yi = static_cast<int>(y) & 255;
	//	float xf = x - static_cast<int>(x);
	//	float yf = y - static_cast<int>(y);

	//	// �O���f�B�G���g�x�N�g���̐���
	//	const int gradientCount = 256;
	//	float gradientVectors[gradientCount * 2];
	//	GenerateGradientVectors(gradientVectors, gradientCount);

	//	// 4�̒��_����̋����x�N�g���̌v�Z
	//	float v00[2] = { xf, yf };
	//	float v01[2] = { xf, yf - 1.0f };
	//	float v10[2] = { xf - 1.0f, yf };
	//	float v11[2] = { xf - 1.0f, yf - 1.0f };

	//	// �e���_����̋����x�N�g���ƃO���f�B�G���g�x�N�g���̓��ς��v�Z
	//	float dot00 = v00[0] * gradientVectors[(xi + yi * gradientCount) * 2] + v00[1] * gradientVectors[(xi + yi * gradientCount) * 2 + 1];
	//	float dot01 = v01[0] * gradientVectors[(xi + (yi + 1) * gradientCount) * 2] + v01[1] * gradientVectors[(xi + (yi + 1) * gradientCount) * 2 + 1];
	//	float dot10 = v10[0] * gradientVectors[((xi + 1) + yi * gradientCount) * 2] + v10[1] * gradientVectors[((xi + 1) + yi * gradientCount) * 2 + 1];
	//	float dot11 = v11[0] * gradientVectors[((xi + 1) + (yi + 1) * gradientCount) * 2] + v11[1] * gradientVectors[((xi + 1) + (yi + 1) * gradientCount) * 2 + 1];

	//	// �o�C���e�������
	//	float u = xf * xf * (3.0f - 2.0f * xf);
	//	float v = yf * yf * (3.0f - 2.0f * yf);
	//	float lerp1 = dot00 + u * (dot10 - dot00);
	//	float lerp2 = dot01 + u * (dot11 - dot01);
	//	return lerp1 + v * (lerp2 - lerp1);
	//}

	//// ���C���֐�
	//int main()
	//{
	//	// �p�[�����m�C�Y�̃T���v�����O
	//	float x = 0.5f;
	//	float y = 0.5f;
	//	float perlinValue = PerlinNoise(x, y);

	//	return 0;
	//}
}