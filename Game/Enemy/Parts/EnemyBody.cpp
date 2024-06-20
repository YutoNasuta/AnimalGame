//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			EnemyBody.cpp
// <�T�v>			�v���C���[�̓��̃p�[�c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"EnemyBody.h"
#include"Interface/IComponent.h"
#include"Libraries/NakashiLib/ResourcesManager.h"
#include"Game/CommonResources.h"
#include"Game/Enemy/Parts/EnemyHead.h"
#include"Game/Enemy/Parts/EnemyLeftHand.h"
#include"Game/Enemy/Parts/EnemyRightHand.h"
#include"Game/Enemy/Parts/EnemyLeg.h"
#include"Libraries/NakashiLib/InputManager.h"
#include"Game/Enemy/Parts/EnemyTail.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
EnemyBody::EnemyBody(
	IComponent* parent, 
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& quaternion
)
	: EnemyBase(parent , position ,quaternion),
	m_commonResources{},
	m_partID{EnemyBase::PartID::BODY},
	m_model{},
	m_position{},
	m_velocity{},
	m_quaternion{},
	m_mass{},
	m_worldMatrix{},
	m_rightHand{},
	m_leftHand{},
	m_leg{},
	m_head{},
	m_tail{},
	m_addQuaternion{},
	m_nodeNumber{1}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBody::~EnemyBody()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void EnemyBody::Initialize()
{



	ModelInitialize();
	ChildInitialize();

	// ���N���X��Initialize�Ăяo��
	EnemyBase::Initialize(m_nodeNumber , m_model);
}

/// <summary>
/// �q���̏�����
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void EnemyBody::ChildInitialize()
{
	// �r���q�I�u�W�F�N�g��
	auto rightHand =
		std::make_unique<EnemyRightHand>(
			this,
			DirectX::SimpleMath::Vector3(-1.0f, 0.5f, 0.0f),
			DirectX::SimpleMath::Quaternion::Identity);
	m_rightHand = rightHand.get();
	SetChild(std::move(rightHand));

	auto leftHand =
		std::make_unique<EnemyLeftHand>(
			this,
			DirectX::SimpleMath::Vector3(1.0f, 0.5f, 0.0f),
			DirectX::SimpleMath::Quaternion::Identity);
	m_leftHand = leftHand.get();
	SetChild(std::move(leftHand));

	// �����q�I�u�W�F�N�g��
	auto leg = std::make_unique<EnemyLeg>(
		this,
		DirectX::SimpleMath::Vector3(0.0f, -0.6f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity);
	m_leg = leg.get();
	SetChild(std::move(leg));

	// �����q�I�u�W�F�N�g��
	auto Head = std::make_unique<EnemyHead>(
		this,
		DirectX::SimpleMath::Vector3(0.0f, 0.9f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity);

	m_head = Head.get();
	SetChild(std::move(Head));

	// �����ۂ��q�I�u�W�F�N�g��
	auto Tail = std::make_unique<EnemyTail>(
		this,
		DirectX::SimpleMath::Vector3(0.0f, -0.5f, -0.8f),
		DirectX::SimpleMath::Quaternion::Identity);
	m_tail = Tail.get();
	SetChild(std::move(Tail));
}

/// <summary>
/// ���f���̏�����
/// </summary>
void EnemyBody::ModelInitialize()
{
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyBody", L"EnemyBody.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyLeftHand", L"EnemyLeftHand.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyHead", L"EnemyHead.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyLeg", L"EnemyLeg.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyRightHand", L"EnemyRightHand.cmo");
	//m_commonResources->GetResourcesManager()->CreateModel(L"EnemyTail", L"EnemyTail.cmo");
	m_model = m_commonResources->GetResourcesManager()->GetModel(L"EnemyBody");
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">����</param>
/// <param name="position">�ʒu</param>
/// <param name="quaternion">��]</param>
void EnemyBody::Update(
	const DirectX::SimpleMath::Vector3& position , 
	const DirectX::SimpleMath::Quaternion& quaternion)
{

	DirectX::SimpleMath::Vector3 localPosition = position;
	DirectX::SimpleMath::Quaternion localQuaternion = m_quaternion;

	localPosition += m_velocity;
	m_position = localPosition;

	m_quaternion = quaternion;			// ���݂̉�]�p���X�V����

	EnemyBase::Update(
		m_position,
		m_quaternion);

	m_worldMatrix =
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_addQuaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(GetInitialPosition())
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_quaternion)
		* DirectX::SimpleMath::Matrix::CreateTranslation(m_position)
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetInitialQuaternion());
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�J�����̃r���[</param>
/// <param name="projection">�J�����̓��e</param>
void EnemyBody::Render(
const DirectX::SimpleMath::Matrix& view ,
const DirectX::SimpleMath::Matrix& projection
)
{
	EnemyBase::Render(m_worldMatrix, view, projection);
}

/// <summary>
/// �㏈��
/// </summary>
void EnemyBody::Finalize()
{
}

