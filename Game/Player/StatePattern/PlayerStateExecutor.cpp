//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/21
// <file>			PlayerStateExecutor.cpp
// <�T�v>		�@�@�v���C���[�̃X�e�[�g�����s����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include "PlayerStateExecutor.h"
#include "Game/Player/Player.h"
#include"PlayerStateBuilder.h"

PlayerStateExecutor::PlayerStateExecutor(Player* player, IState* initialState)
    : 
    m_player(player),
    m_currentState(initialState) 
{
    
    
}

void PlayerStateExecutor::Initialize()
{
    m_stateBuilder->Initialize();
    m_currentState->OnEnter();
}

void PlayerStateExecutor::ChangeState(IState* newState) {
    m_currentState->OnExit();
    m_currentState = newState;
    m_currentState->OnEnter();
}

void PlayerStateExecutor::Update() {
    m_currentState->Update();
}

IState* PlayerStateExecutor::GetCurrentState() const {
    return m_currentState;
}