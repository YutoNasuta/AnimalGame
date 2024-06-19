//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/13
// <file>			BehaviorNode.h
// <概要>		　　ステージをパーリンノイズで生成
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include <vector>
#include <memory>

namespace NakashiLib
{
	class CollisionMesh;
}

class StageCase;

class GenerateStage
{
private:
	static const unsigned int LAND_HEIGHT = 22;
	static const unsigned int LAND_WIDTH = 22;
	static const unsigned int STAGE_QUANTITY = 4;

	float m_landScape[LAND_HEIGHT][LAND_WIDTH];

	std::unique_ptr<NakashiLib::CollisionMesh> m_collisionMesh;	
	std::unique_ptr<StageCase> m_stageCase[STAGE_QUANTITY];

	int m_octaves;
	float m_correction;
	int m_correctionNoise;
	float m_normalHeight;
	int m_correctionHeight;
	int m_scale;

public:
	//コンストラクタ
	GenerateStage();
	~GenerateStage();

	void Initialize(
		ID3D11Device* device,
		ID3D11DeviceContext* context);

	void Render(
		DirectX::CommonStates* states,
		const DirectX::SimpleMath::Matrix& view, 
		const DirectX::SimpleMath::Matrix& projection);

public:		// プロパティ
	float GetLandScape(int height, int width) { return m_landScape[height][width]; }

	NakashiLib::CollisionMesh* GetCollisionMesh() { return m_collisionMesh.get(); }
	StageCase* GetStageCase(int number) { return m_stageCase[number].get(); }

private:
	// パーリンノイズ作成
	void CreatePerlinNoise();
	// 頂点作成
	void CreateVertex(
		ID3D11Device* device,
		ID3D11DeviceContext* context);
	// ステージの外側作成
	void CreateStageCase();
};