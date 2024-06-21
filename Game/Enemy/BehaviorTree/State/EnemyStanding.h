//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			EnemyStanding.h
// <概要>			エネミーの立ち状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Libraries/NakashiLib/BehaviorNode.h"
#include"Game/CommonResources.h"
class Enemy;

class EnemyStanding : public NakashiLib::ActionNode
{


public:
	// コンストラクタ
	EnemyStanding(Enemy* enemy);
	// 実行する
	bool Execute() override;

private:
	// エネミー取得
	Enemy* m_enemy;
	CommonResources* m_commonResources;

	float m_timeExit;
	const float EXITTIME = 10;

	void MoveParts();
	void MoveHand();
};