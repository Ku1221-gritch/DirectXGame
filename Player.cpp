#include "TextureManager.h"
#include "GameScene.h"
#include "Player.h"
#include <cassert>

Player::Player() {}

Player::~Player() {

}

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {
	//引数の内容をメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
	//NULLポインタチェック
	assert(model);

	model_ = Model::Create();
	worldTransform_.Initialize();
}

void Player::Update() { 
	worldTransform_.TransferMatrix();
}

void Player::Draw() {
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_); 
}
