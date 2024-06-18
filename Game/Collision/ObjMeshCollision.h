#pragma once
#include"pch.h"
#include"Game/Collision/Collision.h"
#include"Game/Collision/DisplayCollision.h"

class ObjMeshCollision
{
private:

	// 位置
	DirectX::SimpleMath::Vector3 m_position;

	// 回転
	DirectX::SimpleMath::Quaternion m_rotation;

private:

	// 頂点情報
	std::vector<DirectX::VertexPosition> m_vertexes;

	// インデックス情報
	std::vector<uint16_t> m_indexes;

	// コリジョン用三角形データ
	std::vector<Collision::Triangle> m_triangles;

	// コリジョン用三角形データの追加関数
	void AddTriangle(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c);

public:

	// コンストラクタ
	ObjMeshCollision(const wchar_t* filename);

	// コリジョン情報の更新
	void UpdateBoundingInfo(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate);

	// 線分との交差判定関数
	bool IntersectLineSegment(
		DirectX::SimpleMath::Vector3 a,
		DirectX::SimpleMath::Vector3 b,
		DirectX::SimpleMath::Vector3* hitPosition,
		DirectX::SimpleMath::Vector3* normal = nullptr
	);

	// 衝突判定の表示に登録する関数
	void AddDisplayCollision(DisplayCollision* displayCollision, DirectX::FXMVECTOR lineColor = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f, 0.0f }) const;
};