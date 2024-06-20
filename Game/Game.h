//
// Game.h
//

#pragma once

#include "Framework/DeviceResources.h"
#include "Framework/StepTimer.h"

// ★includeの追記★
#include "Game/CommonResources.h"
#include "Interface/IScene.h"
#include "Game/Scene/SceneManager.h"
#include "Libraries/NakashiLib/DebugString.h"
#include "Libraries/NakashiLib/InputManager.h"
#include "Libraries/NakashiLib/ResourcesManager.h"
#include "Framework/Graphics.h"
// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    //フルスクリーンにする
    void SetFullscreenState(BOOL value)
    {
        m_fullscreen = value;
        m_deviceResources->GetSwapChain()->SetFullscreenState(m_fullscreen, nullptr);
        if (value)m_deviceResources->CreateWindowSizeDependentResources();
    }

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

   

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;


    // ★追記ココから↓↓↓★

    BOOL m_fullscreen;      // フルスクリーンにするかどうか

    // コモンステート
    std::unique_ptr<DirectX::CommonStates>  m_commonStates;

    // コモンリソース
    CommonResources*                        m_commonResources;

    // デバッグストリング
    std::unique_ptr<NakashiLib::DebugString>     m_debugString;

    // 入力マネージャ
    std::unique_ptr<NakashiLib::InputManager>    m_inputManager;

    // シーンマネージャ
    std::unique_ptr<SceneManager>           m_sceneManager;

    // リソースマネージャー
    std::unique_ptr<NakashiLib::ResourcesManager> m_resourceManager;

    // グラフィックス
    Graphics* m_graphics;

   

    // ★追記ココまで↑↑↑★
};
