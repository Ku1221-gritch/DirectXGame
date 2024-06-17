#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"
#include <d3d12.h>
#include <type_traits>
#include <wrl.h>
#define _USE_MATH_DEFINES
#include<cmath>

// 定数バッファ用データ構造体
struct ConstBufferDataWorldTransform {
	Matrix4x4 matWorld; // ローカル → ワールド変換行列
};

/// <summary>
/// ワールド変換データ
/// </summary>
class WorldTransform {
public:
	// ローカルスケール
	Vector3 scale_ = {1.0f, 1.0f, 1.0f};
	Matrix4x4 scaleMatrix; // = MakeScaleMatrix(scale_);
	// X,Y,Z軸回りのローカル回転角
	Vector3 rotation_ = {0.0f, 0.0f, 0.0f};
	Matrix4x4 rotateXMatrix;// = MakeRotateXMatrix(rotation_.x);
	Matrix4x4 rotateYMatrix;// = MakeRotateYMatrix(rotation_.y);
	Matrix4x4 rotateZMatrix;// = MakeRotateZMatrix(rotation_.z);
	Matrix4x4 rotateXYZMatrix;// = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));
	// ローカル座標
	Vector3 translation_ = {0.0f, 0.0f, 0.0f};
	Matrix4x4 translateMatrix;//	= MakeTranslateMatrix(translation_);
	// ローカル → ワールド変換行列
	Matrix4x4 matWorld_;//	= MakeAffineMatrix(scale_, rotation_, translation_);

	// 親となるワールド変換へのポインタ
	const WorldTransform* parent_ = nullptr;

	WorldTransform() = default;
	~WorldTransform() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 定数バッファ生成
	/// </summary>
	void CreateConstBuffer();
	/// <summary>
	/// マッピングする
	/// </summary>
	void Map();
	/// <summary>
	/// 行列を転送する
	/// </summary>
	void TransferMatrix();
	/// <summary>
	/// 行列を計算・転送する
	/// </summary>
	void UpdateMatrix();
	/// <summary>
	/// 定数バッファの取得
	/// </summary>
	/// <returns>定数バッファ</returns>
	const Microsoft::WRL::ComPtr<ID3D12Resource>& GetConstBuffer() const { return constBuffer_; }

	// 1.平行移動行列
	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	// 2.拡大縮小行列
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	// 1.X軸回転行列
	Matrix4x4 MakeRotateXMatrix(float radian);

	// 2.Y軸回転行列
	Matrix4x4 MakeRotateYMatrix(float radian);

	// 3.Z軸回転行列
	Matrix4x4 MakeRotateZMatrix(float radian);

	// 3.行列の積 
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

private:
	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer_;
	// マッピング済みアドレス
	ConstBufferDataWorldTransform* constMap = nullptr;
	// コピー禁止
	WorldTransform(const WorldTransform&) = delete;
	WorldTransform& operator=(const WorldTransform&) = delete;
};

static_assert(!std::is_copy_assignable_v<WorldTransform>);