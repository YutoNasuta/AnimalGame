//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/05/28
// <file>			IPlayerFactory.h
// <概要>			プレイヤーファクトリインターフェース
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"Interface/IComponent.h"

class IPlayerFactory
{
public:
	// プレイヤー生成
	virtual std::unique_ptr<IComponent> CreatePlayer(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// 頭生成
	virtual std::unique_ptr<IComponent> CreatePlayerHead(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// 胴生成
	virtual std::unique_ptr<IComponent> CreatePlayerBody(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// 右腕生成
	virtual std::unique_ptr<IComponent> CreatePlayerRightHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// 左腕生成
	virtual std::unique_ptr<IComponent> CreatePlayerLeftHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// 足生成
	virtual std::unique_ptr<IComponent> CreatePlayerLeg(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
	// しっぽ生成
	virtual std::unique_ptr<IComponent> CreatePlayerTail(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialQuaternion) = 0;
};