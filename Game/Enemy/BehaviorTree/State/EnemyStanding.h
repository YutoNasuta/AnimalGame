//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			EnemyStanding.h
// <�T�v>			�G�l�~�[�̗������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"
#include"Game/CommonResources.h"
class Enemy;

class EnemyStanding : public NakashiLib::ActionNode
{


public:
	// �R���X�g���N�^
	EnemyStanding(Enemy* enemy);
	// ���s����
	bool Execute() override;

private:
	// �G�l�~�[�擾
	Enemy* m_enemy;
	CommonResources* m_commonResources;

	float m_timeExit;
	const float EXITTIME = 10;

	void MoveParts();
	void MoveHand();
};