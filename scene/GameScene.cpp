#include "GameScene.h"
#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	delete modelBlock_;
	delete debugCamera_;
	delete player_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {

	// 要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	// ブロック1個分の横幅
	const float kBlockHeight = 2.0f;
	const float kBlockWidth = 2.0f;
	// 要素数を変更する
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}
	// ブロックの生成
	for (uint32_t y = 0; y < kNumBlockVirtical; ++y) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {

			worldTransformBlocks_[y][j] = new WorldTransform();
			worldTransformBlocks_[y][j]->Initialize();
			worldTransformBlocks_[y][j]->translation_.x = kBlockWidth * j;
			worldTransformBlocks_[y][j]->translation_.y = kBlockHeight * y;
		}
	}
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// textureHandle_ = TextureManager::Load("sample.png");
	// soundDataHandle_ = audio_->LoadWave("mokugyo.wav");
	// audio_->PlayWave(soundDataHandle_);
	// voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
	// sprite_ = Sprite::Create(textureHandle_, {100, 50});
	modelBlock_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	////自キャラの生成
	// player_ = new Player();
	////自キャラの初期化
	// player_->Initialize(modelBlock_,textureHandle_,&viewProjection_);
	// ライン描画が参照するビュープロジェクションを指定する（アドレス渡し）
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {
	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_); // アフィン変換行列

			// 定数バッファに転送する
			worldTransformBlock->TransferMatrix();
		}
	}

	// 自キャラの更新
	// player_->Update();
	////スプライトの今の座標を取得
	// Vector2 position = sprite_->GetPosition();
	////座標を｛2，1｝移動
	// position.x += 2.0f;
	// position.y += 1.0f;
	////移動した座標をスプライトに反映
	// sprite_->SetPosition(position);
	// スペースキーを押した瞬間
	// if (input_->TriggerKey(DIK_SPACE)) {
	//	//音声停止
	//	audio_->StopWave(voiceHandle_);
	// }
	// デバッグカメラの更新
	debugCamera_->Update();

#ifdef DEBUG
	// デバッグテキストの表示
	ImGui::Begin("Debug1");
	// float3入力ボックス
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	// float3スライダー
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	// デモウィンドウの表示を有効化
	ImGui::ShowDemoWindow();
	ImGui::End();
#endif // DEBUG
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	// ラインを描画する
	// PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			modelBlock_->Draw(*worldTransformBlock, viewProjection_);
		}
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	// sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
