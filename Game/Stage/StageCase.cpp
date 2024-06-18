//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/18
// <file>			StageCase.cpp
// <概要>		　　ステージの枠
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"StageCase.h"
#include"Game/CommonResources.h"
#include"Framework/DeviceResources.h"
#include "Libraries/Microsoft/DebugDraw.h"

StageCase::StageCase()
	:
	m_stageCaseBoundingBox{}
{
	m_commonResources = CommonResources::GetInstance();
}

StageCase::~StageCase()
{

}

void StageCase::Initialize()
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);

		DX::ThrowIfFailed(
			DirectX::CreateInputLayoutFromEffect<DirectX::VertexPositionColor>(
				device,
				m_basicEffect.get(),
				m_inputLayout.ReleaseAndGetAddressOf()
			)
		);
}


void StageCase::Update()
{

}

void StageCase::Render()
{
	m_primitiveBatch->Begin();
	DX::Draw(m_primitiveBatch.get(), m_stageCaseBoundingBox);
	m_primitiveBatch->End();
}

/// <summary>
/// バウンディングボックスを作る
/// </summary>
/// <param name="position">ポジション</param>
/// <param name="boxsize">ボックスのサイズを決める</param>
void StageCase::SetBoundingPosition(
	DirectX::SimpleMath::Vector3& position,
	DirectX::SimpleMath::Vector3& boxSize)
{
	m_stageCaseBoundingBox
		= DirectX::BoundingBox(
			DirectX::SimpleMath::Vector3(position),
			DirectX::SimpleMath::Vector3(boxSize / 2)
		);
}