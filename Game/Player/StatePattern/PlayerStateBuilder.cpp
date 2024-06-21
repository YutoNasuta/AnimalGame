//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/21
// <file>			PlayerStateBuilder.cpp
// <概要>		　　プレイヤーのステートを管理するクラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"PlayerStateBuilder.h"
#include"State/PlayerStanding.h"
#include"State/PlayerJumping.h"
#include"State/PlayerRunning.h"
#include"State/PlayerTake.h"
#include"State/PlayerThrow.h"

PlayerStateBuilder::PlayerStateBuilder(Player * player)
    : m_player(player),
    m_standing(),
    m_jumping(),
    m_running(),
    m_take(),
    m_throw()
{

}

PlayerStateBuilder::~PlayerStateBuilder()
{

}

void PlayerStateBuilder::Initialize()
{
    m_standing = std::make_unique<PlayerStanding>(m_player);
    m_jumping = std::make_unique<PlayerJumping>(m_player);
    m_running = std::make_unique<PlayerRunning>(m_player);
    m_take = std::make_unique<PlayerTake>(m_player);
    m_throw = std::make_unique<PlayerThrow>(m_player);
}


PlayerStateBuilder::~PlayerStateBuilder() {
}

PlayerStanding* PlayerStateBuilder::GetStanding() const {
    return m_standing.get();
}

PlayerJumping* PlayerStateBuilder::GetJumping() const {
    return m_jumping.get();
}

PlayerRunning* PlayerStateBuilder::GetRunning() const {
    return m_running.get();
}

PlayerTake* PlayerStateBuilder::GetTake() const {
    return m_take.get();
}

PlayerThrow* PlayerStateBuilder::GetThrow() const {
    return m_throw.get();
}


//TODO
// エラーの内容の為に、Executorと、Builderを重複させないようにしましょう。
// やり方としては、Executorだけで簡潔させるようにする。