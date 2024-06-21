//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/21
// <file>			PlayerStateExecutor.h
// <�T�v>		�@�@�v���C���[�̃X�e�[�g�����s����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include "Interface/IState.h"


class Player;
class PlayerStateBuilder;

class PlayerStateExecutor {
public:
    PlayerStateExecutor(Player* player, IState* initialState);
    void ChangeState(IState* newState);
    void Initialize();
    void Update();

    IState* GetCurrentState() const;

    PlayerStateBuilder* GetStateBuilder() { return m_stateBuilder.get(); }

private:
    IState* m_currentState;
    std::unique_ptr<PlayerStateBuilder> m_stateBuilder;
    Player* m_player;
};
