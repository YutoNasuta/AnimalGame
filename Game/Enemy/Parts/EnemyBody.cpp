//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			EnemyBody.cpp
// <概要>			プレイヤーの胴体パーツ
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
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
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
/// デストラクタ
/// </summary>
EnemyBody::~EnemyBody()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void EnemyBody::Initialize()
{



	ModelInitialize();
	ChildInitialize();

	// 基底クラスのInitialize呼び出し
	EnemyBase::Initialize(m_nodeNumber , m_model);
}

/// <summary>
/// 子供の初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void EnemyBody::ChildInitialize()
{
	// 腕を子オブジェクトに
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

	// 足を子オブジェクトに
	auto leg = std::make_unique<EnemyLeg>(
		this,
		DirectX::SimpleMath::Vector3(0.0f, -0.6f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity);
	m_leg = leg.get();
	SetChild(std::move(leg));

	// 頭を子オブジェクトに
	auto Head = std::make_unique<EnemyHead>(
		this,
		DirectX::SimpleMath::Vector3(0.0f, 0.9f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity);

	m_head = Head.get();
	SetChild(std::move(Head));

	// しっぽを子オブジェクトに
	auto Tail = std::make_unique<EnemyTail>(
		this,
		DirectX::SimpleMath::Vector3(0.0f, -0.5f, -0.8f),
		DirectX::SimpleMath::Quaternion::Identity);
	m_tail = Tail.get();
	SetChild(std::move(Tail));
}

/// <summary>
/// モデルの初期化
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
/// 更新処理
/// </summary>
/// <param name="timer">時間</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
void EnemyBody::Update(
	const DirectX::SimpleMath::Vector3& position , 
	const DirectX::SimpleMath::Quaternion& quaternion)
{

	DirectX::SimpleMath::Vector3 localPosition = position;
	DirectX::SimpleMath::Quaternion localQuaternion = m_quaternion;

	localPosition += m_velocity;
	m_position = localPosition;

	m_quaternion = quaternion;			// 現在の回転角を更新する

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
/// 描画処理
/// </summary>
/// <param name="view">カメラのビュー</param>
/// <param name="projection">カメラの投影</param>
void EnemyBody::Render(
const DirectX::SimpleMath::Matrix& view ,
const DirectX::SimpleMath::Matrix& projection
)
{
	EnemyBase::Render(m_worldMatrix, view, projection);
}

/// <summary>
/// 後処理
/// </summary>
void EnemyBody::Finalize()
{
}

