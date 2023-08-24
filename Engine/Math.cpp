#include "Math.h"
#include "Direct3D.h"

namespace Math
{
	/// <summary>
	/// XMFloat3の足し算
	/// </summary>
	/// <param name="引数1 : 足される数"></param>
	/// <param name="引数2 : 足す数"></param>
	/// <param name="戻値  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	/// <summary>
	/// XMFloat3の引き算
	/// </summary>
	/// <param name="引数1 : 引かれる数"></param>
	/// <param name="引数2 : 引く数"></param>
	/// <param name="戻値  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Sub(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/// <summary>
	///  XMFloat3のxyzに同じ数かける
	/// </summary>
	/// <param name="a">XMFloat3のかけられる数</param>
	/// <param name="b">XMFloat3のxにかける数</param>
	/// <param name="c">XMFloat3のyにかける数</param>
	/// <param name="d">XMFloat3のzにかける数</param>
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
	/// XMFloat3の符号の反転
	/// </summary>
	/// <param name="引数1 : 反転する数"></param>
	/// <param name="戻値  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Reverse(XMFLOAT3 a)
	{
		return XMFLOAT3(-(a.x), -(a.y), -(a.z));
	}
	//引数2つを比較して同じか調べる
	bool Float3Comparison(XMFLOAT3 a, XMFLOAT3 b)
	{
		//比較
		if (a.x == b.x && a.y == b.y && a.z == b.z)
		{
			return true;
		}
		return false;
	}

	/// <summary>
	/// Transformをピクセルに変換
	/// </summary>
	/// <param name="transform"></param>
	/// <returns></returns>
	XMFLOAT3 TransformToPixel(const XMFLOAT3& transform)
	{
		//position_を0~1に変更
		XMFLOAT3 pos = { (transform.x + 1) / 2, (-transform.y + 1) / 2, transform.z };
		pos = { pos.x * Direct3D::screenWidth_, pos.y * Direct3D::screenHeight_, pos.z };

		return pos;
	}

	/// <summary>
	/// ピクセルをTransformに変換
	/// </summary>
	/// <param name="pixel"></param>
	/// <returns></returns>
	XMFLOAT3 PixelToTransform(const XMFLOAT3& pixel)
	{
		XMFLOAT3 pos = { pixel.x / Direct3D::screenWidth_, pixel.y / Direct3D::screenHeight_, pixel.z };
		pos = { pos.x * 2 - 1, -pos.y * 2 + 1, pos.z };

		return pos;
	}

	//// パーリンノイズの生成関数
	//// ランダムな値を生成する関数
	//float Random()
	//{
	//	return static_cast<float>(std::rand()) / RAND_MAX;
	//}

	//// グラディエントベクトルを生成する関数
	//void GenerateGradientVectors(float* gradientVectors, int count)
	//{
	//	for (int i = 0; i < count; ++i)
	//	{
	//		float angle = Random() * 2.0f * 3.14159265359f;
	//		gradientVectors[i * 2] = std::cos(angle);
	//		gradientVectors[i * 2 + 1] = std::sin(angle);
	//	}
	//}

	//// パーリンノイズの生成関数
	//float PerlinNoise(float x, float y)
	//{
	//	// 整数部分と小数部分の計算
	//	int xi = static_cast<int>(x) & 255;
	//	int yi = static_cast<int>(y) & 255;
	//	float xf = x - static_cast<int>(x);
	//	float yf = y - static_cast<int>(y);

	//	// グラディエントベクトルの生成
	//	const int gradientCount = 256;
	//	float gradientVectors[gradientCount * 2];
	//	GenerateGradientVectors(gradientVectors, gradientCount);

	//	// 4つの頂点からの距離ベクトルの計算
	//	float v00[2] = { xf, yf };
	//	float v01[2] = { xf, yf - 1.0f };
	//	float v10[2] = { xf - 1.0f, yf };
	//	float v11[2] = { xf - 1.0f, yf - 1.0f };

	//	// 各頂点からの距離ベクトルとグラディエントベクトルの内積を計算
	//	float dot00 = v00[0] * gradientVectors[(xi + yi * gradientCount) * 2] + v00[1] * gradientVectors[(xi + yi * gradientCount) * 2 + 1];
	//	float dot01 = v01[0] * gradientVectors[(xi + (yi + 1) * gradientCount) * 2] + v01[1] * gradientVectors[(xi + (yi + 1) * gradientCount) * 2 + 1];
	//	float dot10 = v10[0] * gradientVectors[((xi + 1) + yi * gradientCount) * 2] + v10[1] * gradientVectors[((xi + 1) + yi * gradientCount) * 2 + 1];
	//	float dot11 = v11[0] * gradientVectors[((xi + 1) + (yi + 1) * gradientCount) * 2] + v11[1] * gradientVectors[((xi + 1) + (yi + 1) * gradientCount) * 2 + 1];

	//	// バイラテラル補間
	//	float u = xf * xf * (3.0f - 2.0f * xf);
	//	float v = yf * yf * (3.0f - 2.0f * yf);
	//	float lerp1 = dot00 + u * (dot10 - dot00);
	//	float lerp2 = dot01 + u * (dot11 - dot01);
	//	return lerp1 + v * (lerp2 - lerp1);
	//}

	//// メイン関数
	//int main()
	//{
	//	// パーリンノイズのサンプリング
	//	float x = 0.5f;
	//	float y = 0.5f;
	//	float perlinValue = PerlinNoise(x, y);

	//	return 0;
	//}
}