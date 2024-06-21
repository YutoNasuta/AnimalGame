//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/01
// <file>			PlayerStanding.h
// <�T�v>		�@�@�v���C���[�̓����Ă��Ȃ��X�e�[�g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Interface/IState.h"

// �O���錾
class Player;
class CommonResources;
class PlayerStateExecutor;
class PlayerStateBuilder;

class PlayerStanding : public IState
{
public:
	// �R���X�g���N�^
	PlayerStanding(Player* player , PlayerStateExecutor* executor, PlayerStateBuilder* builder);
	// �f�X�g���N�^
	~PlayerStanding();
	// ������
	void Initialize() override;
	// �������
	void Update() override;
	// �����̕`��
	void Render() override;
	// ��������
	void OnEnter() override;
	// �o���Ƃ�
	void OnExit() override;
	// ��n��
	void Finalize() override;
	// �L�[��State�ύX
	void ChangeStateKey(const DirectX::Keyboard::State& keyboardStateTracker);
	// �q�̓���
	void MoveChild();
	// �r�̓���
	void MoveHand();
	// �����ۂ̓���
	void MoveTail();

private:
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// ���s�N���X
	PlayerStateExecutor* m_stateExecutor;
	// ���X�e�[�g�̃r���_�[
	PlayerStateBuilder* m_stateBuilder;
};
