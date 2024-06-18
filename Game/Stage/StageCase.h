//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/18
// <file>			StageCase.h
// <�T�v>		�@�@�X�e�[�W�̘g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"

class CommonResources;

class StageCase
{
private:
	// ���ʃX�e�[�g
	CommonResources* m_commonResources;
	// �o�E���f�B���O�{�b�N�X
	DirectX::BoundingBox m_stageCaseBoundingBox;

	// �`��p
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	StageCase();
	~StageCase();

	void Initialize();
	void Update();
	void Render();

	void SetBoundingPosition(
		DirectX::SimpleMath::Vector3& position, 
		DirectX::SimpleMath::Vector3& boxSize);

	 DirectX::BoundingBox GetBoundingBox() const { return m_stageCaseBoundingBox; }
};