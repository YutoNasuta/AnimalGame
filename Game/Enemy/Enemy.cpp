//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			Enemy.cpp
// <概要>			エネミーの中心核
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include "Enemy.h"
#include"Game/Enemy/Parts/EnemyBody.h"
#include "Game/CommonResources.h"
#include "Libraries/NakashiLib/InputManager.h"
#include"Game/Enemy/BehaviorTree/BehaviorTreeBuilder.h"
#include"Libraries/NakashiLib/BehaviorNode.h"

Enemy::Enemy(IComponent* parent,
    const DirectX::SimpleMath::Vector3& position,
    const DirectX::SimpleMath::Quaternion& quaternion
)
    :
    EnemyBase(parent , position , quaternion),
    m_commonResources{},
    m_partID{EnemyBase::PartID::ROOT} ,
    m_position{position},
    m_velocity{},
    Number{ 1 }, 
    Debug{ 1 },
    m_ballTaking{},
    m_body{},
    m_mass{}
{
    m_commonResources = CommonResources::GetInstance();
}

Enemy::~Enemy()
{

}

void Enemy::Initialize() 
{


    EnemyBase::Initialize();				// ベースの初期化を呼ぶ

    auto body = std::make_unique<EnemyBody>(				// プレイヤーボディを作成
        this,
        DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
        DirectX::SimpleMath::Quaternion::Identity
    );
    m_body = body.get();									// 呼び出し用bodyに格納
    SetChild(std::move(body));					// プレイヤーの子にbodyを設定

    m_behaviorTreeBuilder = std::make_unique<BehaviorTreeBuilder>();
    auto tree =  m_behaviorTreeBuilder->BuildTree(this);
    m_behaviorExecutor = std::make_unique<NakashiLib::BehaviorTreeExecutor>(std::move(tree));
}

void Enemy::Update(
 
    const DirectX::SimpleMath::Vector3& position,
    const DirectX::SimpleMath::Quaternion& quaternion
)
{
    EnemyBase::Update(
      
        m_position + GetInitialPosition(),
        m_quaternion
    );

    m_behaviorExecutor->Update();
}


void Enemy::Render(
    const DirectX::SimpleMath::Matrix& view,
    const DirectX::SimpleMath::Matrix& projection
)
{
    EnemyBase::Render(view, projection);
}