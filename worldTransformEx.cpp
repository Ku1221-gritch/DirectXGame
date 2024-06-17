#include "WorldTransform.h"

void WorldTransform::UpdateMatrix() {
	//スケール、回転、平行移動を合成して行列を計算する
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	//定数バッファに転送する
	TransferMatrix();
}

Matrix4x4 WorldTransform::MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 Answer;
	Answer.m[0][0] = 1.0f;
	Answer.m[0][1] = 0.0f;
	Answer.m[0][2] = 0.0f;
	Answer.m[0][3] = 0.0f;
	Answer.m[1][0] = 0.0f;
	Answer.m[1][1] = 1.0f;
	Answer.m[1][2] = 0.0f;
	Answer.m[1][3] = 0.0f;
	Answer.m[2][0] = 0.0f;
	Answer.m[2][1] = 0.0f;
	Answer.m[2][2] = 1.0f;
	Answer.m[2][3] = 0.0f;
	Answer.m[3][0] = translate.x;
	Answer.m[3][1] = translate.y;
	Answer.m[3][2] = translate.z;
	Answer.m[3][3] = 1.0f;
	return Answer;
}

Matrix4x4 WorldTransform::MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 Answer;
	Answer.m[0][0] = scale.x;
	Answer.m[0][1] = 0.0f;
	Answer.m[0][2] = 0.0f;
	Answer.m[0][3] = 0.0f;
	Answer.m[1][0] = 0.0f;
	Answer.m[1][1] = scale.y;
	Answer.m[1][2] = 0.0f;
	Answer.m[1][3] = 0.0f;
	Answer.m[2][0] = 0.0f;
	Answer.m[2][1] = 0.0f;
	Answer.m[2][2] = scale.z;
	Answer.m[2][3] = 0.0f;
	Answer.m[3][0] = 0.0f;
	Answer.m[3][1] = 0.0f;
	Answer.m[3][2] = 0.0f;
	Answer.m[3][3] = 1.0f;
	return Answer;
}

Matrix4x4 WorldTransform::MakeRotateXMatrix(float radian) {
	Matrix4x4 Answer;
	Answer.m[0][0] = 1.0f;
	Answer.m[0][1] = 0.0f;
	Answer.m[0][2] = 0.0f;
	Answer.m[0][3] = 0.0f;
	Answer.m[1][0] = 0.0f;
	Answer.m[1][1] = std::cos(radian);
	Answer.m[1][2] = std::sin(radian);
	Answer.m[1][3] = 0.0f;
	Answer.m[2][0] = 0.0f;
	Answer.m[2][1] = -std::sin(radian);
	Answer.m[2][2] = std::cos(radian);
	Answer.m[2][3] = 0.0f;
	Answer.m[3][0] = 0.0f;
	Answer.m[3][1] = 0.0f;
	Answer.m[3][2] = 0.0f;
	Answer.m[3][3] = 1.0f;
	return Answer;
}

Matrix4x4 WorldTransform::MakeRotateYMatrix(float radian) {
	Matrix4x4 Answer;
	Answer.m[0][0] = std::cos(radian);
	Answer.m[0][1] = 0.0f;
	Answer.m[0][2] = -std::sin(radian);
	Answer.m[0][3] = 0.0f;
	Answer.m[1][0] = 0.0f;
	Answer.m[1][1] = 1.0f;
	Answer.m[1][2] = 0.0f;
	Answer.m[1][3] = 0.0f;
	Answer.m[2][0] = std::sin(radian);
	Answer.m[2][1] = 0.0f;
	Answer.m[2][2] = std::cos(radian);
	Answer.m[2][3] = 0.0f;
	Answer.m[3][0] = 0.0f;
	Answer.m[3][1] = 0.0f;
	Answer.m[3][2] = 0.0f;
	Answer.m[3][3] = 1.0f;
	return Answer;
}

Matrix4x4 WorldTransform::MakeRotateZMatrix(float radian) {
	Matrix4x4 Answer;
	Answer.m[0][0] = std::cos(radian);
	Answer.m[0][1] = std::sin(radian);
	Answer.m[0][2] = 0.0f;
	Answer.m[0][3] = 0.0f;
	Answer.m[1][0] = -std::sin(radian);
	Answer.m[1][1] = std::cos(radian);
	Answer.m[1][2] = 0.0f;
	Answer.m[1][3] = 0.0f;
	Answer.m[2][0] = 0.0f;
	Answer.m[2][1] = 0.0f;
	Answer.m[2][2] = 1.0f;
	Answer.m[2][3] = 0.0f;
	Answer.m[3][0] = 0.0f;
	Answer.m[3][1] = 0.0f;
	Answer.m[3][2] = 0.0f;
	Answer.m[3][3] = 1.0f;
	return Answer;
}

Matrix4x4 WorldTransform::Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	{
		Matrix4x4 Answer;
		Answer.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
		Answer.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
		Answer.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
		Answer.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
		Answer.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
		Answer.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
		Answer.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
		Answer.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
		Answer.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
		Answer.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
		Answer.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
		Answer.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
		Answer.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
		Answer.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
		Answer.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
		Answer.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
		return Answer;
	}
}

Matrix4x4 WorldTransform::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result = Multiply(Multiply(MakeRotateXMatrix(rotate.x), MakeRotateYMatrix(rotate.y)), MakeRotateZMatrix(rotate.z));
	result.m[0][0] *= scale.x;
	result.m[0][1] *= scale.x;
	result.m[0][2] *= scale.x;
	result.m[1][0] *= scale.y;
	result.m[1][1] *= scale.y;
	result.m[1][2] *= scale.y;
	result.m[2][0] *= scale.z;
	result.m[2][1] *= scale.z;
	result.m[2][2] *= scale.z;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	return result;
}
