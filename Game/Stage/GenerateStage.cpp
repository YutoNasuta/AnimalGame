//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/13
// <file>			BehaviorNode.cpp
// <概要>		　　ステージをパーリンノイズで生成
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"GenerateStage.h"
#include"Libraries/NakashiLib/PerlinNoise.h"
#include"Libraries/NakashiLib/CollisionMesh.h"
#include"StageCase.h"

/// <summary>
/// コンストラクタ
/// </summary>
GenerateStage::GenerateStage()
	:
	m_correction{15.0f},
	m_correctionHeight{9},
	m_correctionNoise{20},
	m_octaves{ 10},
	m_normalHeight{1.5f},
	m_scale{ 10 },
	m_landScape{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
GenerateStage::~GenerateStage()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="context">デバイスコンテキスト</param>
void GenerateStage::Initialize(
	ID3D11Device* device,
	ID3D11DeviceContext* context)
{
	// パーリンノイズの作成
	CreatePerlinNoise();
	
	// パーリンノイズから頂点情報を作る
	CreateVertex(device , context);

	// 頂点情報からステージの外側を作る
	CreateStageCase();
}


/// <summary>
/// 描画
/// </summary>
/// <param name="states">ステート</param>
/// <param name="view">ビュー</param>
/// <param name="projection">プロジェクション</param>
void GenerateStage::Render( 
	DirectX::CommonStates* states, 
	const DirectX::SimpleMath::Matrix& view, 
	const DirectX::SimpleMath::Matrix& projection
)
{
	m_collisionMesh->DrawMeshTexture(states, view, projection);

#ifdef _DEBUG
	m_collisionMesh->DrawMesh(states, view, projection);
	for (int i = 0; i < 4; i++)
	{
		m_stageCase[i]->Render();
	}
#endif

	
}


/// <summary>
/// パーリンノイズの生成
/// </summary>
void GenerateStage::CreatePerlinNoise()
{
	// パーリンノイズのインスタンス化
	std::random_device rd; //完全ランダム
	auto pPerlinNoise = std::make_unique<NakashiLib::PerlinNoise>(rd());

	for (int y = 0; y < LAND_HEIGHT; y++)
	{
		for (int x = 0; x < LAND_WIDTH; x++)
		{

			int m_NoiseValue = (int)(pPerlinNoise->GetNoise(m_octaves, (float)x / m_correctionNoise, (float)y / m_correctionNoise) * m_correction);

			m_landScape[y][x] = (float)m_NoiseValue * m_normalHeight;
		}
	}
}

/// <summary>
/// 頂点情報の作成
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="contex">コンテキスト</param>
void GenerateStage::CreateVertex(
	ID3D11Device* device,
	ID3D11DeviceContext* context
)
{
	// コリジョンメッシュの作成
	m_collisionMesh = std::make_unique<NakashiLib::CollisionMesh>();

	// 衝突メッシュの初期化
	std::vector<DirectX::VertexPosition> vertices;
	std::vector<DirectX::VertexPositionTexture> verticesTexture;
	std::vector<uint16_t> indices;

	for (int y = 0; y < LAND_HEIGHT - 1; y++)
	{
		for (int x = 0; x < LAND_WIDTH - 1; x++)
		{
			// 頂点座標を作成		scaleで幅を設定
			float scaledX = (float)x * m_scale;
			float scaledY = (float)y * m_scale;
			float scaledX1 = (float)(x + 1) * m_scale;
			float scaledY1 = (float)(y + 1) * m_scale;

			// 頂点情報にポジションを付けて格納
			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y][x] - m_correctionHeight, scaledY } });
			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y][x + 1] - m_correctionHeight, scaledY } });
			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y + 1][x] - m_correctionHeight, scaledY1 } });
			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y + 1][x + 1] - m_correctionHeight, scaledY1 } });

			// 頂点情報にポジションとテクスチャ情報を格納
			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y][x] - m_correctionHeight, scaledY }  , DirectX::SimpleMath::Vector2{0.0f,0.0f} });
			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y][x + 1] - m_correctionHeight, scaledY } , DirectX::SimpleMath::Vector2{1.0f,0.0f} });
			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y + 1][x] - m_correctionHeight, scaledY1 } , DirectX::SimpleMath::Vector2{0.0f,1.0f} });
			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y + 1][x + 1] - m_correctionHeight, scaledY1 }, DirectX::SimpleMath::Vector2{1.0f,1.0f} });


			// インデックスの作成
			uint16_t baseIndex = static_cast<uint16_t>((y * (LAND_WIDTH - 1) + x) * 4);

			// 四角を作るために、インデックスから取り出す
			indices.push_back(baseIndex + 0);
			indices.push_back(baseIndex + 1);
			indices.push_back(baseIndex + 2);
			indices.push_back(baseIndex + 2);
			indices.push_back(baseIndex + 1);
			indices.push_back(baseIndex + 3);
		}
	}

	// コリジョンメッシュに頂点情報などを渡す
	m_collisionMesh->InitializeVertexMesh(device, context, vertices, indices);
	m_collisionMesh->InitializeVertexMeshTexture(device, context, verticesTexture, indices);
}

/// <summary>
/// ステージの外側を作る
/// </summary>
void GenerateStage::CreateStageCase()
{
	// ステージの外側を作る
	for (int i = 0; i < STAGE_QUANTITY; i++)
	{
		m_stageCase[i] = std::make_unique<StageCase>();
		m_stageCase[i]->Initialize();
	}

	// 各StageCaseを各辺の中心に配置
	DirectX::SimpleMath::Vector3 stagePositions[STAGE_QUANTITY] = {
		{static_cast<float>(LAND_WIDTH) * m_scale / 2, 0.0f, 0.0f}, // 上辺の中心
		{static_cast<float>(LAND_WIDTH) * m_scale / 2, 0.0f, (static_cast<float>(LAND_HEIGHT) - 1) * m_scale}, // 下辺の中心
		{0.0f, 0.0f, static_cast<float>(LAND_HEIGHT) * m_scale / 2}, // 左辺の中心
		{(static_cast<float>(LAND_WIDTH) - 1) * m_scale, 0.0f, static_cast<float>(LAND_HEIGHT) * m_scale / 2} // 右辺の中心
	};

	// 各辺に応じたBoxのサイズを作成
	DirectX::SimpleMath::Vector3 boxSize[STAGE_QUANTITY] =
	{
		{static_cast<float>(LAND_HEIGHT) * m_scale, static_cast<float>(m_correctionHeight) * m_scale, 5.0f},
		{static_cast<float>(LAND_HEIGHT) * m_scale, static_cast<float>(m_correctionHeight) * m_scale, 5.0f},
		{5.0f, static_cast<float>(m_correctionHeight) * m_scale, static_cast<float>(LAND_WIDTH) * m_scale},
		{5.0f, static_cast<float>(m_correctionHeight) * m_scale, static_cast<float>(LAND_WIDTH) * m_scale} // 壁のサイズを適宜調整
	};

	// ステージの外側の場所を作る
	for (int i = 0; i < STAGE_QUANTITY; i++)
	{
		m_stageCase[i]->SetBoundingPosition(stagePositions[i], boxSize[i]);
	}
}