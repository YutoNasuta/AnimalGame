//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			PlayerTreeBuilder.h
// <�T�v>			�r�w�C�r�A�c���[�����N���X
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
	// �c���[�m�[�h�̔ԍ���m��
	int m_nodeNumber;
};