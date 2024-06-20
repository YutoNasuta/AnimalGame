//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/16
// <file>			Resources.cpp
// <�T�v>			�Q�[���Ŏg���摜�⃂�f���B
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Resources.h"
#include"CommonResources.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
NakashiLib::Resources::Resources()
{
	m_commonResources = CommonResources::GetInstance();
	CreateModels();
	CreateSrvs();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NakashiLib::Resources::~Resources()
{

}

/// <summary>
///	���f���̐ݒ�
/// </summary>
void NakashiLib::Resources::CreateModels()
{
	auto ResourcesManager = m_commonResources->GetResourcesManager();

	// �v���C���[�̃p�[�c����
	ResourcesManager->CreateModel(L"PlayerBody",		 L"Player/PlayerBody.cmo");
	ResourcesManager->CreateModel(L"PlayerLeftHand",	 L"Player/PlayerLeftHand.cmo");
	ResourcesManager->CreateModel(L"PlayerHead",		 L"Player/PlayerHead.cmo");
	ResourcesManager->CreateModel(L"PlayerLeg",			 L"Player/PlayerLeg.cmo");
	ResourcesManager->CreateModel(L"PlayerRightHand",	 L"Player/PlayerRightHand.cmo");
	ResourcesManager->CreateModel(L"PlayerTail",		 L"Player/PlayerTail.cmo");

	// �G�l�~�[�̃p�[�c����
	ResourcesManager->CreateModel(L"EnemyBody",		     L"Enemy/EnemyBody.cmo");
	ResourcesManager->CreateModel(L"EnemyLeftHand",		 L"Enemy/EnemyLeftHand.cmo");
	ResourcesManager->CreateModel(L"EnemyRightHand",	 L"Enemy/EnemyRightHand.cmo");
	ResourcesManager->CreateModel(L"EnemyHead",			 L"Enemy/EnemyHead.cmo");
	ResourcesManager->CreateModel(L"EnemyLeg",			 L"Enemy/EnemyLeg.cmo");
	ResourcesManager->CreateModel(L"EnemyTail",			 L"Enemy/EnemyTail.cmo");
}

/// <summary>
/// �摜�̐ݒ�
/// </summary>
void NakashiLib::Resources::CreateSrvs()
{

}