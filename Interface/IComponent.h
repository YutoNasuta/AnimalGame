//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/28
// <file>			IComponent.h
// <�T�v>			�R���|�[�l���g�̃C���^�[�t�F�[�X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Framework/StepTimer.h"

// �O���錾
class IComponent;
 
class IComponent
{
public:
	// ���݂̈ʒu���擾����
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// ���݂̈ʒu���擾����
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	// ���݂̉�]�p���擾����
	virtual DirectX::SimpleMath::Quaternion GetQuaternion() const = 0;
	// ���݂̉�]�p��ݒ肷��
	virtual void SetAngle(const DirectX::SimpleMath::Quaternion& quaternion) = 0;
	// ���ʂ��擾����
	virtual float GetMass() const = 0;
	// ���ʂ�ݒ肷��
	virtual void SetMass(const float& mass) = 0;
	// ���f���̎擾
	virtual DirectX::Model* GetModel() = 0;

public:

	// �f�X�g���N�^
	virtual ~IComponent() = default;
	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update(
		const DirectX::SimpleMath::Vector3& position , 
		const DirectX::SimpleMath::Quaternion& quaternion) = 0;
	// �q�ɂ���
	virtual void SetChild(std::unique_ptr<IComponent> part) = 0;

	// �`��
	virtual void Render(
		const DirectX::SimpleMath::Matrix& view , 
		const DirectX::SimpleMath::Matrix& projection) = 0;

};