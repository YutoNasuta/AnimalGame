//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/21
// <file>			PlayerStateBuilder.h
// <概要>		　　プレイヤーのステートを管理するクラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

class Player;
class PlayerStanding;
class PlayerJumping;
class PlayerRunning;
class PlayerTake;
class PlayerThrow;

class PlayerStateBuilder {
public:
    PlayerStateBuilder(Player* player);
    ~PlayerStateBuilder();
    void Initialize();
    PlayerStanding* GetStanding() const;
    PlayerJumping* GetJumping() const;
    PlayerRunning* GetRunning() const;
    PlayerTake* GetTake() const;
    PlayerThrow* GetThrow() const;

private:
    Player* m_player;
    std::unique_ptr<PlayerStanding> m_standing;
    std::unique_ptr<PlayerJumping> m_jumping;
    std::unique_ptr<PlayerRunning> m_running;
    std::unique_ptr<PlayerTake> m_take;
    std::unique_ptr<PlayerThrow> m_throw;
};
