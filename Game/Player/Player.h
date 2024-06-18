//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			Player.h
// <�T�v>		�@�@�v���C���[�̒��S�j
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IComponent.h"
#include"Interface/IState.h"
#include"Game/Player/PlayerBase.h"
#include"Game/Player/State/PlayerStanding.h"
#include"State/PlayerJumping.h"
#include"State/PlayerRunning.h"
#include"State/PlayerTake.h"
#include"State/PlayerThrow.h"

// �O���錾
class CommonResources;
class PlayerStanding;
class PlayerJumping;
class PlayerRunning;
class PlayerTake;
class PlayerThrow;

class PlayerBody;

class Player : public PlayerBase
{
public:
	// �C���^�t�F�[�X�p++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// �ʒu�ݒ�
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }						
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override{ m_position = position; }		

	// ��]�ݒ�
	DirectX::SimpleMath::Quaternion GetQuaternion() const override { return m_quaternion; }						
	void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion)override { m_quaternion = quaternion; }		

	// ���ʐݒ�
	float GetMass() const override { return m_mass; }				
	void SetMass(const float& mass) override { m_mass = mass; }		

	// �X�e�[�g�p++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ��Ԏ擾
	PlayerStanding* GetStanding() { return m_standing.get(); }		// ������Ԏ擾
	PlayerJumping* GetJumping() { return m_jumping.get(); }			// �W�����v��Ԏ擾
	PlayerRunning* GetRunning() { return m_runnning.get(); }		// �����Ԏ擾
	PlayerTake* GetTake() { return m_taking.get(); }				// ����Ԏ擾
	PlayerThrow* GetThrow() { return m_throw.get(); }				// ������Ԏ擾

	// ��Ԃ�J�ڂ���
	void ChangeState(IState* currentState);	

	// ���݂̃X�e�[�g�����擾
	IState* GetNowState() const { return m_currentState; }			

	// �v���p�e�B�i�擾�Ɛݒ�j++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ���x�ݒ�
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }						
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }	

	// �����x�ݒ�
	DirectX::SimpleMath::Vector3 GetAcceleration() const { return m_acceleration; }								
	void SetAcceleration(const DirectX::SimpleMath::Vector3& acceleration) { m_acceleration = acceleration; }	
	
	// �d�͐ݒ�
	DirectX::SimpleMath::Vector3 GetGravity() const { return m_gravity; }		

	// ���C�ݒ�
	DirectX::SimpleMath::Vector3 GetFriction() const { return m_friction; }		

	// ���[���h�s��ݒ�
	DirectX::SimpleMath::Matrix GetWorld() const { return m_worldMatrix; }		
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_worldMatrix = world; }

	// �J�����ݒ�
	DirectX::SimpleMath::Matrix GetCameraView() const { return m_cameraView; }					
	DirectX::SimpleMath::Matrix GetProjection() const { return m_cameraProjection; }			
	DirectX::SimpleMath::Quaternion GetCameraQuaternion() const { return m_cameraQuaternion; }	
	void SetCameraQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { m_cameraQuaternion = quaternion; }

	// �{�[���t���O�ݒ�
	bool GetBallTakeFlag() const { return m_ballTaking; }			
	void SetBallTakeFlag(const bool& flag) { m_ballTaking = flag; }	

	// �{�[���͐ݒ�
	float GetForceCharge() const { return m_forceCharge; }				
	void SetForceCharge(const float& force) { m_forceCharge = force; }	

	// �v���C���[�̃{�f�B�擾
	PlayerBody* GetBody() const { return m_body; }

	// �n�ʐݒ�
	DirectX::SimpleMath::Vector3 GetGround() const { return m_ground; }
	void SetGround(const DirectX::SimpleMath::Vector3& ground) { m_ground = ground; }
	
	// �m�[�h�ԍ��擾
	int GetNodeNumber() const { return m_nodeNumber; }
	
public:
	// �R���X�g���N�^
	Player(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion);
	// �f�X�g���N�^
	~Player();
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& quaternion) override;
	// �`�悷��
	void Render(
		const DirectX::SimpleMath::Matrix& view , 
		const DirectX::SimpleMath::Matrix& projection) override;


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �n�ʈʒu
	DirectX::SimpleMath::Vector3 m_ground;
	// �m�[�h�ԍ�
	int m_nodeNumber;
	
	//�@�X�e�[�g�p+++++++++++++++++++++++++++++++++++++++++++++++
	IState* m_currentState;						// ���݂̏��
	std::unique_ptr<PlayerStanding> m_standing;	// �������
	std::unique_ptr<PlayerJumping> m_jumping;	// �W�����v���
	std::unique_ptr<PlayerRunning> m_runnning;	// ������
	std::unique_ptr<PlayerTake> m_taking;		// �����
	std::unique_ptr<PlayerThrow> m_throw;		// �������

	//  �v���C���[�̏��+++++++++++++++++++++++++++++++++++++++++++
	int m_partID;								 // ID
	DirectX::SimpleMath::Vector3 m_position;	 // ���݂̈ʒu
	DirectX::SimpleMath::Vector3 m_velocity;	 // ���݂̑��x
	DirectX::SimpleMath::Quaternion m_quaternion;// ���݂̉�]�p
	DirectX::SimpleMath::Matrix m_worldMatrix;   // ���[���h�s�� 
	DirectX::SimpleMath::Vector3 m_friction;	 // ���C
	float m_mass;								 // ����
	DirectX::SimpleMath::Vector3 m_acceleration; // �����x
	DirectX::SimpleMath::Vector3 m_gravity;      // �d��
	bool m_ballTaking;							 // �{�[���������Ă����Ԃ������Ă��Ȃ���Ԃ�
	float m_forceCharge;						 // �{�[���̃`���[�W��

	//  �J�����̏��++++++++++++++++++++++++++++++++++++++++++++++++++
	DirectX::SimpleMath::Matrix m_cameraView;			 // �J�����̃r���[�s��
	DirectX::SimpleMath::Matrix m_cameraProjection;		 // �J�����v���W�F�N�V����
	DirectX::SimpleMath::Quaternion m_cameraQuaternion;	 // �J�����̉�]�p


	PlayerBody* m_body;
};