//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			PlayerTreeBuilder.cpp
// <概要>			ビヘイビアツリーを作るクラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"BehaviorTreeBuilder.h"
#include"State/EnemyStanding.h"

std::unique_ptr<NakashiLib::IBehaviorNode> BehaviorTreeBuilder::BuildTree(Enemy* enemy)
{
	using namespace NakashiLib;		//NakashiLibを省略する

	// 最初の条件を作る
	auto root = std::make_unique<SequenceNode>();

	root->AddChild(std::make_unique<EnemyStanding>(enemy));

	return root;

}