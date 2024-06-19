//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/05/28
// <file>			IPlayerFactory.h
// <�T�v>			�v���C���[�t�@�N�g���C���^�[�t�F�[�X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Interface/IComponent.h"

class IPlayerFactory
{
public:
	// �v���C���[����
	virtual std::unique_ptr<IComponent> CreatePlayer(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// ������
	virtual std::unique_ptr<IComponent> CreatePlayerHead(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// ������
	virtual std::unique_ptr<IComponent> CreatePlayerBody(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// �E�r����
	virtual std::unique_ptr<IComponent> CreatePlayerRightHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// ���r����
	virtual std::unique_ptr<IComponent> CreatePlayerLeftHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// ������
	virtual std::unique_ptr<IComponent> CreatePlayerLeg(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// �����ې���
	virtual std::unique_ptr<IComponent> CreatePlayerTail(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
};