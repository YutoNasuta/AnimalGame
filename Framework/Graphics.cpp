//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/19
// <file>			Graphics.h
// <概要>		　　描画処理に必要なものまとめ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Graphics.h"
#include"Game/CommonResources.h"

std::unique_ptr<Graphics> Graphics::m_graphics = nullptr;

/// <summary>
/// グラフィックスのインスタンスを返す
/// </summary>
Graphics* const Graphics::GetInstance()
{
	if (m_graphics == nullptr)
	{
		// グラフィックスのインスタンスを生成する
		m_graphics.reset(new Graphics());
	}
	// インスタンスを返す
	return m_graphics.get();
}

/// <summary>
/// コンストラクタ
/// </summary>
Graphics::Graphics()
	:
	m_deviceResources{},
	m_commonStates{},
	m_spriteBatch{},
	m_spriteFont{},
	m_basicEffect{},
	m_primitiveBatch{},
	m_rasterrizerState{},
	m_effectFactory{},
	m_inputLayout{},
	m_screenW(0),
	m_screenH(0),
	m_view{},
	m_projection{},
	m_device{},
	m_context{}
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
}

/// <summary>
/// デストラクタ
/// </summary>
Graphics::~Graphics()
{
}

void Graphics::Initialize()
{
	// デバイス取得
	m_device = m_deviceResources->GetD3DDevice();
	// デバイスコンテキストを取得する
	m_context = m_deviceResources->GetD3DDeviceContext();

	// コモンステートを生成する
	m_commonStates = std::make_unique<DirectX::CommonStates>(m_device);
	// スプライトバッチを生成する
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context);
	// ベーシックエフェクトを生成する
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(m_device);
	// スプライトフォントを生成する
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_device, L"resources\\font\\SegoeUI_18.spritefont");
	// プリミティブバッチを生成する
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(m_context);
	// 頂点カラーを有効にする
	m_basicEffect->SetVertexColorEnabled(true);
	// テクスチャを無効にする
	m_basicEffect->SetTextureEnabled(false);
	void const* shaderByteCode;
	size_t byteCodeLength;
	// 頂点シェーダーを取得する
	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	// 入力レイアウトを生成する
	m_device->CreateInputLayout(
		DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.ReleaseAndGetAddressOf()
	);
	// ラスタライザーディスクリプション
	CD3D11_RASTERIZER_DESC rasterizerStateDesc(
		D3D11_FILL_SOLID, D3D11_CULL_NONE, FALSE,
		D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
		D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE, FALSE, FALSE, TRUE
	);
	// ラスタライズステートを生成する
	m_device->CreateRasterizerState(&rasterizerStateDesc, m_rasterrizerState.ReleaseAndGetAddressOf());
	// エフェクトファクトリを生成する
	m_effectFactory = std::make_unique<DirectX::EffectFactory>(m_device);
}

void Graphics::DrawPrimitiveBegin(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	// ブレンディング状態を設定する
	m_context->OMSetBlendState(m_commonStates->Opaque(), nullptr, 0xFFFFFFFF);
	// 深度ステンシル状態を設定する
	m_context->OMSetDepthStencilState(m_commonStates->DepthNone(), 0);
	// カリングを行わない
	m_context->RSSetState(m_commonStates->CullNone());
	// ラスタライザー状態を設定する
	m_context->RSSetState(m_rasterrizerState.Get());

	// ビュー行列を設定する
	m_basicEffect->SetView(view);
	// プロジェクション行列を設定する
	m_basicEffect->SetProjection(projection);
	// ワールド行列を設定する
	m_basicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	// コンテキストを設定する
	m_basicEffect->Apply(m_context);
	// 入力レイアウトを設定する
	m_context->IASetInputLayout(m_inputLayout.Get());
	// プリミティブバッチを開始する
	m_primitiveBatch->Begin();
}

// 描画プリミティブを終了する
void Graphics::DrawPrimitiveEnd()
{
	// プリミティブバッチを終了する
	m_primitiveBatch->End();
}