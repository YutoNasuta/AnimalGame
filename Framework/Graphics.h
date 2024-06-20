//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/19
// <file>			Graphics.h
// <概要>		　　描画処理に必要なものまとめ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"DeviceResources.h"
class Graphics final
{
public:
	// インスタンス取得
	static Graphics* const GetInstance();

	// スクリーンサイズ設定
	void GetScreenSize(int& width, int height) const { width = m_screenW; height = m_screenH; }
	void SetScreenSize(const int& width, const int& height) { m_screenW = width; m_screenH = height; }

	// デバイスリソース取得
	DX::DeviceResources* GetDeviceResources() const { return m_deviceResources.get(); }
	// プリミティブバッチを取得
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* GetPrimitiveBatch() const { return m_primitiveBatch.get(); }
	// インプットレイアウトを取得
	ID3D11InputLayout* GetInputLayout() const { return m_inputLayout.Get(); }
	// ベーシックエフェクト取得
	DirectX::BasicEffect* GetBasicEffect() { return m_basicEffect.get(); }
	// コモンステート取得
	DirectX::CommonStates* GetCommonStates() const { return m_commonStates.get(); }
	// スプライトバッチ取得
	DirectX::SpriteBatch* GetSpriteBatch() { return m_spriteBatch.get(); }
	// ビュー行列設定
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	// ビュー行列取得
	const DirectX::SimpleMath::Matrix& GetViewMatrix() { return m_view; }
	// 射影行列を設定する
	void SetProjectionMatix(const DirectX::SimpleMath::Matrix& projection) { m_projection = projection; }
	// 射影行列を取得
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() { return m_projection; }

public:
	// デストラクタ
	~Graphics();
	// 初期化する
	void Initialize();
	// プリミティブ描画を開始
	void DrawPrimitiveBegin(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	// プリミティブ描画を終了
	void DrawPrimitiveEnd();

private:
	// コンストラクタ
	Graphics();

	// 代入は許容しない
	void operator=(const Graphics& object) = delete;
	// コピーコンストラクタは許容しない
	Graphics(const Graphics& object) = delete;

private:
	// ポインタ
	static std::unique_ptr<Graphics> m_graphics;

	// デバイスリソース
	std::unique_ptr<DX::DeviceResources> m_deviceResources;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	// ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	// エフェクトファクトリー
	std::unique_ptr<DirectX::EffectFactory> m_effectFactory;
	// ラスタライザーステート
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterrizerState;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// スクリーンサイズ
	int m_screenW, m_screenH;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;
	// デバイス
	ID3D11Device* m_device;
	// デバイスコンテキスト
	ID3D11DeviceContext* m_context;
};