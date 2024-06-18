//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/01
// <file>			EnemyBase.cpp
// <概要>		　　プレイヤーのベース
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"EnemyBase.h"
#include"Game/CommonResources.h"
#include"Framework/DeviceResources.h"
#include "Libraries/Microsoft/DebugDraw.h"

/// <summary>
///  コンストラクタ
/// </summary>
/// <param name="parent">親</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
EnemyBase::EnemyBase(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& position, 
	const DirectX::SimpleMath::Quaternion& quaternion
)
	:
	m_commonResources{},
	m_model{},
	m_parent{parent},
	m_initialPosition{position},
	m_initialQuaternion{quaternion},
	m_mass{},
	m_enemyParts{},
	m_worldMatrix{},
	m_collision{}
{
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyBase::~EnemyBase()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void EnemyBase::Initialize() 
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="model">モデルの取得</param>
void EnemyBase::Initialize(
	DirectX::Model* model
)
{
	// モデルを設定
	m_model = model;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">時間</param>
/// <param name="position">位置</param>
/// <param name="quaternion">回転</param>
void EnemyBase::Update(
	const DirectX::SimpleMath::Vector3& position, 
	const DirectX::SimpleMath::Quaternion& quaternion
)
{
	// パーツの更新
	for (auto& Part : m_enemyParts)
	{
		Part->Update(position, quaternion);
	
	}

	
}

/// <summary>
/// 子を設定する
/// </summary>
/// <param name="playerPart">プレイヤーのパーツ</param>
/// <param name="resources">共通リソース</param>
void EnemyBase::SetChild(
	std::unique_ptr<IComponent> playerPart
)
{
	// 初期化
	playerPart->Initialize();
	// パーツの追加
	m_enemyParts.emplace_back(std::move(playerPart));
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">カメラのビュー</param>
/// <param name="projection">カメラの投影</param>
void EnemyBase::Render(
	const DirectX::SimpleMath::Matrix& view ,
	const DirectX::SimpleMath::Matrix& projection
)
{
	// パーツの描画
	for (auto& playerPart : m_enemyParts)
	{
		// パーツを描画
		playerPart->Render(view , projection);
	}
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="matrix">行列</param>
/// <param name="view">カメラのビュー</param>
/// <param name="projection">カメラの投影</param>
void EnemyBase::Render(
	const DirectX::SimpleMath::Matrix& matrix ,
	const DirectX::SimpleMath::Matrix& view ,
	const DirectX::SimpleMath::Matrix& projection
)
{

	// モデルの描画
	DrawModel( matrix , view , projection);
#ifdef _DEBUG
	DrawBoundingBox(matrix, view, projection);
#endif

	// パーツを描画する
	for (auto& playerPart : m_enemyParts)
	{
		playerPart->Render(view , projection);
	}

}

/// <summary>
/// モデルの描画
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="matrix">行列</param>
/// <param name="view">カメラのビュー</param>
/// <param name="projection">カメラの投影</param>
void EnemyBase::DrawModel(
	const DirectX::SimpleMath::Matrix& matrix,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// モデルの描画
	m_model->Draw(context, *states, matrix, view, projection);
}

void EnemyBase::DrawBoundingBox
(
	const DirectX::SimpleMath::Matrix& matrix,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	auto m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);
	auto m_effect = std::make_unique<DirectX::BasicEffect>(device);
	m_effect->SetVertexColorEnabled(true);
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout;

	// 入力レイアウトを作成する
	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPositionColor>(
			device,
			m_effect.get(),
			m_layout.ReleaseAndGetAddressOf()
		)
	);

	// デバッグドロー用の設定
	m_effect->SetView(view);
	m_effect->SetProjection(projection);
	m_effect->Apply(context);

	//バウンディングボックスの設定
	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);	// 透過しない
	context->OMSetDepthStencilState(states->DepthDefault(), 0);			// Ｚバッファを使用する
	context->RSSetState(states->CullNone());							// ポリゴンの両面を描画する
	context->IASetInputLayout(m_layout.Get());

	DirectX::BoundingBox boundingBox;
	// 境界ボックスのトランスフォーム
	m_boundingBox.Transform(boundingBox, matrix);
	// プリミティブ描画の開始
	m_batch->Begin();

	DX::Draw(m_batch.get(), boundingBox, DirectX::Colors::White);

	m_batch->End();
}