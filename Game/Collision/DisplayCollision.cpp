#include"pch.h"
#include"DisplayCollision.h"
#include"Libraries/Microsoft/DebugDraw.h"

// コンストラクタ
DisplayCollision::DisplayCollision(
	ID3D11Device* device,
	ID3D11DeviceContext* context,
	bool modelActive,
	bool lineActive,
	uint32_t collisionMax)
	:
	m_lineActive(lineActive),
	m_collisionMax(collisionMax),
	m_modelActive(modelActive)
{
	// モデルの作成（球）
	m_modelSphere = DirectX::GeometricPrimitive::CreateSphere(context, 2.0f, 8);

	// モデルの作成（ボックス）
	m_modelBox = DirectX::GeometricPrimitive::CreateCube(context);

	// エフェクト++++++++++

	// エフェクトの作成（ライン用）
	m_lineEffect = std::make_unique<DirectX::BasicEffect>(device);
	m_lineEffect->SetVertexColorEnabled(true);
	m_lineEffect->SetTextureEnabled(false);
	m_lineEffect->SetLightingEnabled(false);
	m_lineEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);

	

	// エフェクトの作成（メッシュ用）
	m_meshEffect = std::make_unique<DirectX::BasicEffect>(device);
	m_meshEffect->SetVertexColorEnabled(false);
	m_meshEffect->SetTextureEnabled(false);
	m_meshEffect->SetLightingEnabled(false);



	// エフェクトの作成（モデル用）
	m_modelEffect = std::make_unique<DirectX::NormalMapEffect>(device);
	m_modelEffect->SetVertexColorEnabled(false);
	m_modelEffect->SetBiasedVertexNormals(false);
	m_modelEffect->SetInstancingEnabled(true);
	m_modelEffect->SetFogEnabled(false);
	m_modelEffect->SetTexture(nullptr);
	m_modelEffect->DisableSpecular();
	m_modelEffect->EnableDefaultLighting();
	m_modelEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);

	// 入力レイアウトの作成（モデル用）
	const D3D11_INPUT_ELEMENT_DESC c_InputElements[] =
	{
		{ "SV_Position", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
		{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
		{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
		{ "InstMatrix",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "InstMatrix",  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "InstMatrix",  2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	};
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect(device, m_modelEffect.get(),
			c_InputElements, std::size(c_InputElements),
			m_modelInputLayout.ReleaseAndGetAddressOf())
	);
	// ----- 定数バッファ ----- //

// インスタンシング用のワールド行列格納用定数バッファを作成
	auto desc = CD3D11_BUFFER_DESC(
		static_cast<UINT>(DISPLAY_COLLISION_MAX * sizeof(DirectX::XMFLOAT3X4)),
		D3D11_BIND_VERTEX_BUFFER,
		D3D11_USAGE_DYNAMIC,
		D3D11_CPU_ACCESS_WRITE);
	DX::ThrowIfFailed(
		device->CreateBuffer(&desc, nullptr,
			m_instancedVB.ReleaseAndGetAddressOf())
	);
	// プリミティブバッチの作成（メッシュ用）
	m_meshBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPosition>>(context);

	// 入力レイアウトの作成（メッシュ用）
	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPosition>(device, m_meshEffect.get(),
			m_meshInputLayout.ReleaseAndGetAddressOf())
	);

	// プリミティブバッチの作成（ライン用）
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);


	// 入力レイアウトの作成
	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPositionColor>(device, m_lineEffect.get(),
			m_lineInputLayout.ReleaseAndGetAddressOf())
	);
	
}

// 登録されたコリジョンの描画関数
void DisplayCollision::DrawCollision(
	ID3D11DeviceContext* context,
	DirectX::CommonStates* states,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& proj,
	DirectX::FXMVECTOR baseColor,
	DirectX::FXMVECTOR lineColor,
	float alpha
)
{
	// 色＋α値
	DirectX::SimpleMath::Color color = baseColor;
	color.w = alpha;

	// コリジョンモデルの描画
	if (m_modelActive) DrawCollisionModel(context, states, view, proj, color);

	// ラインの色を指定している場合
	DirectX::SimpleMath::Color c = lineColor;
	if (c.w != 0.0f)
	{
		color = lineColor;
		color.w = alpha;
	}

	// コリジョンラインの描画
	if (m_lineActive) DrawCollisionLine(context, states, view, proj, color);

	// 登録された表示情報をクリアする
	m_lineSegments.clear();
	m_meshes.clear();
	m_spheres.clear();
	m_boxes.clear();
}


void DisplayCollision::DrawCollisionModel(ID3D11DeviceContext* context, DirectX::CommonStates* states, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, DirectX::FXMVECTOR color)
{
	// 登録数が最大表示数を超えていないか？
	assert(static_cast<uint32_t>(m_spheres.size()) < m_collisionMax);
	assert(static_cast<uint32_t>(m_boxes.size()) < m_collisionMax);

	// ----- 球のモデルを描画 ----- //

	// エフェクトを適応する
	m_modelEffect->SetColorAndAlpha(color);
	m_modelEffect->SetView(view);
	m_modelEffect->SetProjection(proj);
	m_modelEffect->Apply(context);

	{
		// ワールド行列を設定
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		context->Map(m_instancedVB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		DirectX::XMFLOAT3X4* p = static_cast<DirectX::XMFLOAT3X4*>(mappedResource.pData);
		std::memset(p, 0 ,sizeof(DirectX::XMFLOAT3X4) * m_spheres.size());
		for (int i = 0; i < m_spheres.size(); i++)
		{
			// 拡大縮小
			p[i]._11 = p[i]._22 = p[i]._33 = m_spheres[i].radius;
			// 位置
			p[i]._14 = m_spheres[i].center.x;
			p[i]._24 = m_spheres[i].center.y;
			p[i]._34 = m_spheres[i].center.z;
		}
		context->Unmap(m_instancedVB.Get(), 0);
	}

	// 球をインスタンスし描画している（高速化のため）
	m_modelSphere->DrawInstanced(m_modelEffect.get(), m_modelInputLayout.Get(), static_cast<uint32_t>(m_spheres.size()), true, false, 0, [=]()
		{
			UINT stride = sizeof(DirectX::XMFLOAT3X4);
			UINT offset = 0;
			context->OMSetDepthStencilState(states->DepthRead(), 0);
			context->IASetVertexBuffers(1, 1, m_instancedVB.GetAddressOf(), &stride, &offset);
		}
	);

	// ----- ボックスのモデルを描画 ----- //

	{
		// ワールド行列を設定
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		context->Map(m_instancedVB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		DirectX::XMFLOAT3X4* p = static_cast<DirectX::XMFLOAT3X4*>(mappedResource.pData);
		std::memset(p,0 , sizeof(DirectX::XMFLOAT3X4) * m_boxes.size());
		for (int i = 0; i < m_boxes.size(); i++)
		{
			DirectX::SimpleMath::Matrix s = DirectX::SimpleMath::Matrix::CreateScale(m_boxes[i].extents * 2.0f);
			DirectX::SimpleMath::Matrix r = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_boxes[i].rotate);
			DirectX::SimpleMath::Matrix c = DirectX::SimpleMath::Matrix::CreateTranslation(m_boxes[i].center);
			DirectX::SimpleMath::Matrix m = s * r * c;
			p[i]._11 = m._11;  p[i]._12 = m._21; p[i]._13 = m._31; p[i]._14 = m._41;
			p[i]._21 = m._12;  p[i]._22 = m._22; p[i]._23 = m._32; p[i]._24 = m._42;
			p[i]._31 = m._13;  p[i]._32 = m._23; p[i]._33 = m._33; p[i]._34 = m._43;
		}
		context->Unmap(m_instancedVB.Get(), 0);
	}

	// ボックスをインスタンスし描画している（高速化のため）
	m_modelBox->DrawInstanced(m_modelEffect.get(), m_modelInputLayout.Get(), static_cast<uint32_t>(m_boxes.size()), true, false, 0, [=]()
		{
			UINT stride = sizeof(DirectX::XMFLOAT3X4);
			UINT offset = 0;
			context->OMSetDepthStencilState(states->DepthRead(), 0);
			context->IASetVertexBuffers(1, 1, m_instancedVB.GetAddressOf(), &stride, &offset);
		}
	);

}


void DisplayCollision::DrawCollisionLine(ID3D11DeviceContext* context, DirectX::CommonStates* states, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, DirectX::FXMVECTOR color)
{
	// ラインを描画

	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFF);
	context->OMSetDepthStencilState(states->DepthRead(), 0);
	context->RSSetState(states->CullNone());

	// エフェクトを適応する
	m_lineEffect->SetView(view);
	m_lineEffect->SetProjection(proj);
	m_lineEffect->Apply(context);

	// 入力レイアウトを設定する
	context->IASetInputLayout(m_lineInputLayout.Get());

	m_primitiveBatch->Begin();

	// 線分を描画
	for (int i = 0; i < m_lineSegments.size(); i++)
	{
		DirectX::SimpleMath::Color lineColor = color;
		if (m_lineSegments[i].lineColor.w != 0.0f) { lineColor = m_lineSegments[i].lineColor; }

		// 線分の描画
		DirectX::VertexPositionColor verts[2] = {};
		DirectX::XMStoreFloat3(&verts[0].position, m_lineSegments[i].a);
		DirectX::XMStoreFloat3(&verts[1].position, m_lineSegments[i].b);
		DirectX::XMStoreFloat4(&verts[0].color, lineColor);
		DirectX::XMStoreFloat4(&verts[1].color, lineColor);
		m_primitiveBatch->Draw(D3D_PRIMITIVE_TOPOLOGY_LINELIST, verts, 2);
	}

	m_primitiveBatch->End();

	// ------------------------------------------------------------------------ //
	// メッシュコリジョンのラインの描画
	// ------------------------------------------------------------------------ //
	context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(states->DepthRead(), 0);
	context->RSSetState(states->Wireframe());

	// 入力レイアウトを設定する
	context->IASetInputLayout(m_meshInputLayout.Get());

	m_meshEffect->SetView(view);
	m_meshEffect->SetProjection(proj);

	m_meshBatch->Begin();
	// ----- メッシュの描画 ----- //
	for (int i = 0; i < m_meshes.size(); i++)
	{
		DirectX::SimpleMath::Color lineColor = color;
		if (m_meshes[i].lineColor.w != 0.0f) lineColor = m_meshes[i].lineColor;

		m_meshEffect->SetColorAndAlpha(lineColor);

		DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_meshes[i].rotate);
		DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_meshes[i].position);
		DirectX::SimpleMath::Matrix world = rotate * trans;

		// エフェクトを適応する
		m_meshEffect->SetWorld(world);
		m_meshEffect->Apply(context);

		m_meshBatch->DrawIndexed(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			&m_meshes[i].indexes[0], m_meshes[i].indexes.size(),
			&m_meshes[i].vertexes[0], m_meshes[i].vertexes.size()
		);
	}
	m_meshBatch->End();
}