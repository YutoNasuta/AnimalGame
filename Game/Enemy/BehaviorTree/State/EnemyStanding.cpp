//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			EnemyStanding.h
// <�T�v>			�G�l�~�[�̗������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"EnemyStanding.h"
#include"Game/Enemy/Enemy.h"
#include"Framework/StepTimer.h"
#include"Game/Enemy/Parts/EnemyBody.h"
#include"Game/Enemy/Parts/EnemyLeftHand.h"
#include"Game/Enemy/Parts/EnemyRightHand.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="enemy">�G</param>
EnemyStanding::EnemyStanding(Enemy* enemy)
{
	m_enemy = enemy;
	m_commonResources = CommonResources::GetInstance();
	m_timeExit = 0;
}

/// <summary>
/// ���s
/// </summary>
bool EnemyStanding::Execute()
{
	

	// ���Ԃ��v��
	m_timeExit += static_cast<float>(m_commonResources->GetStepTimer()->GetElapsedSeconds());
	if (m_timeExit <= EXITTIME)		//�^�C����艺�Ȃ�
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
/// �G�l�~�[�p�[�c�𓮂���
/// </summary>
void EnemyStanding::MoveParts()
{
	// ��𓮂���
	MoveHand();
}

/// <summary>
/// ��̓���
/// </summary>
void EnemyStanding::MoveHand()
{
	auto Timer = m_commonResources->GetStepTimer();
	auto rightHand = m_enemy->GetBody()->GetRightHand();
	auto leftHand = m_enemy->GetBody()->GetLeftHand();
	auto m_normalQuaternion = DirectX::SimpleMath::Quaternion::Identity;
	// �E��̐U�胂�[�V�����̃p�����[�^�[
	float swingSpeed = 1.0f;
	float swingAmount = 0.1f;

	// �U�胂�[�V������ǉ�
	float swing = sin(Timer->GetTotalSeconds() * swingSpeed) * swingAmount;


	DirectX::SimpleMath::Quaternion slerpRotationRight =
		DirectX::SimpleMath::Quaternion::Slerp(rightHand->GetAddQUaternion(), m_normalQuaternion, 0.2f);
	DirectX::SimpleMath::Quaternion slerpRotationLeft =
		DirectX::SimpleMath::Quaternion::Slerp(leftHand->GetAddQUaternion(), m_normalQuaternion, 0.2f);// ���`�⊮����

	rightHand->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, swing, 0.0f));
	rightHand->SetAddQuaternion(slerpRotationRight);
	leftHand->SetVelocity(DirectX::SimpleMath::Vector3(0.0f, swing, 0.0f));
	leftHand->SetAddQuaternion(slerpRotationLeft);
}