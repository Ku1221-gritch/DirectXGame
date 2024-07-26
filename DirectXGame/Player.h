#pragma once

#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"

class MapChipField;

// マップとの当たり判定情報
struct CollisionMapInfo 
{
	// 天井衝突フラグ
	bool onCeiling_ = false;
	// 着地フラグ
	bool onLanding_ = true;
	// 壁接触フラグ
	bool onWallcontact = false;
	Vector3 movement_;
};

// 角
enum Corner
{
	kRightBottom, // 右下
	kLeftBottom,  // 左下
	kRightTop,    // 右上
	kLeftTop,     // 左上

	kNumCorner // 要素数
};

class Player
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model,ViewProjection* viewProjection,const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	///<summary>
	/// 描画
	/// </summary>
	void Draw();

	void MovementInput();

	WorldTransform& GetWorldTransform() { return worldTransform_; };

	const Vector3& GetVelocity() const { return velocity_; };

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	//void MapCollisionDetection(CollisionMapInfo& info);

	void MapCollisionDetectionUp(CollisionMapInfo& info);

	//void MapCollisionDetectionDown(CollisionMapInfo& info);

	//void MapCollisionDetectionRight(CollisionMapInfo& info);

	//void MapCollisionDetectionLeft(CollisionMapInfo& info);

	//判定結果を反映して移動させる
	void MoveJudgmentResults(const CollisionMapInfo& info);

	private:
		//マップチップによるフィールド
	    MapChipField* mapChipField_ = nullptr;
		//カメラ
	    ViewProjection* viewProjection_ = nullptr;
		//ワールド変換データ
	    WorldTransform worldTransform_;

		//モデル
	    Model* model_ = nullptr;

		Vector3 velocity_ = {};

		static inline const float kBlank = 0.9f;

		static inline const float kAcceleration = 0.1f;

		static inline const float kLimitRunSpeed = 0.3f;

		//キャラクターの当たり判定サイズ 
	    static inline const float kWidth = 1.8f;
	    static inline const float kHeight = 1.8f;

		//旋回開始時の角度
	    float turnFirstRotationY_= 0.0f;
		//旋回タイマー
	    float turnTimer_ = 0.0f;
		//旋回時間<秒>
	    static inline const float kTimeTurn = 0.3f;

		//接地状態フラグ
	    bool onGround_ = true;

		//重力加速度（下方向）
	    static inline const float kGravityAcceleration = 0.1f;

		//最大落下速度（下方向
	    static inline const float kLimitFallSpeed = 0.7f;

		//ジャンプ初速（上方向）
	    static inline const float kJumpAcceleration = 1.1f;

		static inline const float kAttenuation = 0.3f;

		//左右
		enum class LRDirection 
		{
			kRight,
			kLeft,
		};

		LRDirection lrDirection_ = LRDirection::kRight;
};