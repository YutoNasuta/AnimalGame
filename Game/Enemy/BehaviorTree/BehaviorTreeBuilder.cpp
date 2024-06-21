//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			PlayerTreeBuilder.cpp
// <�T�v>			�r�w�C�r�A�c���[�����N���X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"BehaviorTreeBuilder.h"
#include"State/EnemyStanding.h"

std::unique_ptr<NakashiLib::IBehaviorNode> BehaviorTreeBuilder::BuildTree(Enemy* enemy)
{
	using namespace NakashiLib;		//NakashiLib���ȗ�����

	// �ŏ��̏��������
	auto root = std::make_unique<SequenceNode>();

	root->AddChild(std::make_unique<EnemyStanding>(enemy));

	return root;

}