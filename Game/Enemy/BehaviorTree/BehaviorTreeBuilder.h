//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			PlayerTreeBuilder.h
// <概要>			ビヘイビアツリーを作るクラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include<memory>
#include"Libraries/NakashiLib/BehaviorNode.h"

namespace NakashiLib
{
	class IBehaviorNode;
}

class Enemy;

class BehaviorTreeBuilder
{
public:
	std::unique_ptr<NakashiLib::IBehaviorNode> BuildTree(Enemy* enemy);

	int GetNodeNumber() { return m_nodeNumber; }

private:
	// ツリーノードの番号を知る
	int m_nodeNumber;
};