//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			Player.h
// <概要>		　　プレイヤーの中心核
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Interface/IState.h"
#include"Game/Player/PlayerBase.h"


// 前方宣言
class CommonResources;

class PlayerBody;
class PlayerStateBuilder;
class PlayerStateExecutor;

class Player : public PlayerBase
{
public:
	// インタフェース用++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// 位置設定
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }						
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override{ m_position = position; }		

	// 回転設定
	DirectX::SimpleMath::Quaternion GetQuaternion() const override { return m_quaternion; }						
	void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion)override { m_quaternion = quaternion; }		

	// 質量設定
	float GetMass() const override { return m_mass; }				
	void SetMass(const float& mass) override { m_mass = mass; }	

	// プレイヤーのステートをゲットする
	PlayerStateExecutor* GetState() { return m_stateExecutor.get(); }
	// プレイヤーのステート一覧の取得
	PlayerStateBuilder* GetStateList() { return m_stateBuilder.get(); }
	

	// プロパティ（取得と設定）++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// 速度設定
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }						
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }	

	// 加速度設定
	DirectX::SimpleMath::Vector3 GetAcceleration() const { return m_acceleration; }								
	void SetAcceleration(const DirectX::SimpleMath::Vector3& acceleration) { m_acceleration = acceleration; }	
	
	// 重力設定
	DirectX::SimpleMath::Vector3 GetGravity() const { return m_gravity; }		

	// 摩擦設定
	DirectX::SimpleMath::Vector3 GetFriction() const { return m_friction; }		

	// ワールド行列設定
	DirectX::SimpleMath::Matrix GetWorld() const { return m_worldMatrix; }		
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_worldMatrix = world; }

	// カメラ設定
	DirectX::SimpleMath::Matrix GetCameraView() const { return m_cameraView; }					
	DirectX::SimpleMath::Matrix GetProjection() const { return m_cameraProjection; }			
	DirectX::SimpleMath::Quaternion GetCameraQuaternion() const { return m_cameraQuaternion; }	
	void SetCameraQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { m_cameraQuaternion = quaternion; }

	// ボールフラグ設定
	bool GetBallTakeFlag() const { return m_ballTaking; }			
	void SetBallTakeFlag(const bool& flag) { m_ballTaking = flag; }	

	// ボール力設定
	float GetForceCharge() const { return m_forceCharge; }				
	void SetForceCharge(const float& force) { m_forceCharge = force; }	

	// プレイヤーのボディ取得
	PlayerBody* GetBody() const { return m_body; }

	// 地面設定
	DirectX::SimpleMath::Vector3 GetGround() const { return m_ground; }
	void SetGround(const DirectX::SimpleMath::Vector3& ground) { m_ground = ground; }
	
	// ノード番号取得
	int GetNodeNumber() const { return m_nodeNumber; }
	
public:
	// コンストラクタ
	Player(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion);
	// デストラクタ
	~Player();
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion) override;
	// 描画する
	void Render(
		const DirectX::SimpleMath::Matrix& view , 
		const DirectX::SimpleMath::Matrix& projection) override;


private:
	// 共通リソース
	CommonResources* m_commonResources;
	// 地面位置
	DirectX::SimpleMath::Vector3 m_ground;
	// ノード番号
	int m_nodeNumber;
	
	//　ステート用+++++++++++++++++++++++++++++++++++++++++++++++
	std::unique_ptr<PlayerStateBuilder> m_stateBuilder;
	std::unique_ptr<PlayerStateExecutor> m_stateExecutor;

	//  プレイヤーの情報+++++++++++++++++++++++++++++++++++++++++++
	int m_partID;								 // ID
	DirectX::SimpleMath::Vector3 m_position;	 // 現在の位置
	DirectX::SimpleMath::Vector3 m_velocity;	 // 現在の速度
	DirectX::SimpleMath::Quaternion m_quaternion;// 現在の回転角
	DirectX::SimpleMath::Matrix m_worldMatrix;   // ワールド行列 
	DirectX::SimpleMath::Vector3 m_friction;	 // 摩擦
	float m_mass;								 // 質量
	DirectX::SimpleMath::Vector3 m_acceleration; // 加速度
	DirectX::SimpleMath::Vector3 m_gravity;      // 重力
	bool m_ballTaking;							 // ボールを持っている状態か持っていない状態か
	float m_forceCharge;						 // ボールのチャージ量

	//  カメラの情報++++++++++++++++++++++++++++++++++++++++++++++++++
	DirectX::SimpleMath::Matrix m_cameraView;			 // カメラのビュー行列
	DirectX::SimpleMath::Matrix m_cameraProjection;		 // カメラプロジェクション
	DirectX::SimpleMath::Quaternion m_cameraQuaternion;	 // カメラの回転角


	PlayerBody* m_body;
};