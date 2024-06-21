//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			EnemyStanding.h
// <概要>			エネミーの立ち状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"EnemyStanding.h"
#include"Game/Enemy/Enemy.h"
#include"Framework/StepTimer.h"
#include"Game/Enemy/Parts/EnemyBody.h"
#include"Game/Enemy/Parts/EnemyLeftHand.h"
#include"Game/Enemy/Parts/EnemyRightHand.h"
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemy">敵</param>
EnemyStanding::EnemyStanding(Enemy* enemy)
{
	m_enemy = enemy;
	m_commonResources = CommonResources::GetInstance();
	m_timeExit = 0;
}

/// <summary>
/// 実行
/// </summary>
bool EnemyStanding::Execute()
{
	

	// 時間を計る
	m_timeExit += static_cast<float>(m_commonResources->GetStepTimer()->GetElapsedSeconds());
	if (m_timeExit <= EXITTIME)		//タイムより下なら
	{
		MoveParts();
		return false;
	}
	else
	{
		return true;
	}
	
}


/// <summary>
/// エネミーパーツを動かす
/// </summary>
void EnemyStanding::MoveParts()
{
	// 手を動かす
	MoveHand();
}

/// <summary>
/// 手の動き
/// </summary>
void EnemyStanding::MoveHand()
{
	auto Timer = m_commonResources->GetStepTimer();
	auto rightHand = m_enemy->GetBody()->GetRightHand();
	auto leftHand = m_enemy->GetBody()->GetLeftHand();
	auto m_normalQuaternion = DirectX::SimpleMath::Quaternion::Identity;
	// 右手の振りモーションのパラメーター
	float swingSpeed = 1.0f;
	float swingAmount = 0.1f;

	// 振りモーションを追加
	float swing = sin(Timer->GetTotalSeconds() * swingSpeed) * swingAmount;


	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), m_normalQuaternion, 0.2f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), m_normalQuaternion, 0.2f);// 線形補完する

	rightHand->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, swing, 0.0f));
	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, swing, 0.0f));
	leftHand->SetAddQuaternion(slerpRotationLeft);
}