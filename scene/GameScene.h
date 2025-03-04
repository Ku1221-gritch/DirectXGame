#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "Player.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include<vector>
#include "Function.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Sprite* sprite_ = nullptr;
	Model* modelBlock_ = nullptr;
	Player* player_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;
	uint32_t textureHandle_ = 0;
	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	//ImGuiで値を入力する変数
	float inputFloat3[3] = {0.0f, 0.0f, 0.0f};
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
