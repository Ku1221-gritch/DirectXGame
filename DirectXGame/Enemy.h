#pragma once

#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"

class MapChipField;

class Enemy 
{
public:
/// <summary>
/// コンストラクタ
/// </summary>
Enemy();

/// <summary>
/// デストラクタ
/// </summary>
~Enemy();

/// <summary>
/// 初期化
/// </summary>
/// <param name="model">モデル</param>
/// <param name="textureHandle">テクスチャハンドル</param>
void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

/// <summary>
/// 更新
/// </summary>
void Update();

///< summary>
/// 描画
/// </summary>
void Draw();

void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

//敵の動く速度
static inline const float kWalkSpeed = 0.1f;

//最初の角度[度]
static inline const float kWalkMotionAngleStart = 0.05f;
//最後の角度[度]
static inline const float kWalkMotionAngleEnd = 0.3f;
//アニメーションの周期となる時間[秒]
static inline const float kWalkMotionTime = 0.3f;
//経過時間
float walkTimer_ = 0.0f;
//速度
Vector3 velocity_ = {};

private:
	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;
	// カメラ
	ViewProjection* viewProjection_ = nullptr;
	// モデル
	Model* model_ = nullptr;
	// ワールド変換データ
	WorldTransform worldTransform_;

};