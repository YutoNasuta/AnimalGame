//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/13
// <file>			BehaviorNode.cpp
// <�T�v>		�@�@�X�e�[�W���p�[�����m�C�Y�Ő���
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"GenerateStage.h"
#include"Libraries/NakashiLib/PerlinNoise.h"
#include"Libraries/NakashiLib/CollisionMesh.h"
#include"StageCase.h"

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
GenerateStage::~GenerateStage()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="device">�f�o�C�X</param>
/// <param name="context">�f�o�C�X�R���e�L�X�g</param>
void GenerateStage::Initialize(
	ID3D11Device* device,
	ID3D11DeviceContext* context)
{
	// �p�[�����m�C�Y�̍쐬
	CreatePerlinNoise();
	
	// �p�[�����m�C�Y���璸�_�������
	CreateVertex(device , context);

	// ���_��񂩂�X�e�[�W�̊O�������
	CreateStageCase();
}


/// <summary>
/// �`��
/// </summary>
/// <param name="states">�X�e�[�g</param>
/// <param name="view">�r���[</param>
/// <param name="projection">�v���W�F�N�V����</param>
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
/// �p�[�����m�C�Y�̐���
/// </summary>
void GenerateStage::CreatePerlinNoise()
{
	// �p�[�����m�C�Y�̃C���X�^���X��
	std::random_device rd; //���S�����_��
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
/// ���_���̍쐬
/// </summary>
/// <param name="device">�f�o�C�X</param>
/// <param name="contex">�R���e�L�X�g</param>
void GenerateStage::CreateVertex(
	ID3D11Device* device,
	ID3D11DeviceContext* context
)
{
	// �R���W�������b�V���̍쐬
	m_collisionMesh = std::make_unique<NakashiLib::CollisionMesh>();

	// �Փ˃��b�V���̏�����
	std::vector<DirectX::VertexPosition> vertices;
	std::vector<DirectX::VertexPositionTexture> verticesTexture;
	std::vector<uint16_t> indices;

	for (int y = 0; y < LAND_HEIGHT - 1; y++)
	{
		for (int x = 0; x < LAND_WIDTH - 1; x++)
		{
			// ���_���W���쐬		scale�ŕ���ݒ�
			float scaledX = (float)x * m_scale;
			float scaledY = (float)y * m_scale;
			float scaledX1 = (float)(x + 1) * m_scale;
			float scaledY1 = (float)(y + 1) * m_scale;

			// ���_���Ƀ|�W�V������t���Ċi�[
			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y][x] - m_correctionHeight, scaledY } });
			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y][x + 1] - m_correctionHeight, scaledY } });
			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y + 1][x] - m_correctionHeight, scaledY1 } });
			vertices.emplace_back(DirectX::VertexPosition{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y + 1][x + 1] - m_correctionHeight, scaledY1 } });

			// ���_���Ƀ|�W�V�����ƃe�N�X�`�������i�[
			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y][x] - m_correctionHeight, scaledY }  , DirectX::SimpleMath::Vector2{0.0f,0.0f} });
			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y][x + 1] - m_correctionHeight, scaledY } , DirectX::SimpleMath::Vector2{1.0f,0.0f} });
			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX, m_landScape[y + 1][x] - m_correctionHeight, scaledY1 } , DirectX::SimpleMath::Vector2{0.0f,1.0f} });
			verticesTexture.emplace_back(DirectX::VertexPositionTexture{ DirectX::SimpleMath::Vector3{ scaledX1, m_landScape[y + 1][x + 1] - m_correctionHeight, scaledY1 }, DirectX::SimpleMath::Vector2{1.0f,1.0f} });


			// �C���f�b�N�X�̍쐬
			uint16_t baseIndex = static_cast<uint16_t>((y * (LAND_WIDTH - 1) + x) * 4);

			// �l�p����邽�߂ɁA�C���f�b�N�X������o��
			indices.push_back(baseIndex + 0);
			indices.push_back(baseIndex + 1);
			indices.push_back(baseIndex + 2);
			indices.push_back(baseIndex + 2);
			indices.push_back(baseIndex + 1);
			indices.push_back(baseIndex + 3);
		}
	}

	// �R���W�������b�V���ɒ��_���Ȃǂ�n��
	m_collisionMesh->InitializeVertexMesh(device, context, vertices, indices);
	m_collisionMesh->InitializeVertexMeshTexture(device, context, verticesTexture, indices);
}

/// <summary>
/// �X�e�[�W�̊O�������
/// </summary>
void GenerateStage::CreateStageCase()
{
	// �X�e�[�W�̊O�������
	for (int i = 0; i < STAGE_QUANTITY; i++)
	{
		m_stageCase[i] = std::make_unique<StageCase>();
		m_stageCase[i]->Initialize();
	}

	// �eStageCase���e�ӂ̒��S�ɔz�u
	DirectX::SimpleMath::Vector3 stagePositions[STAGE_QUANTITY] = {
		{static_cast<float>(LAND_WIDTH) * m_scale / 2, 0.0f, 0.0f}, // ��ӂ̒��S
		{static_cast<float>(LAND_WIDTH) * m_scale / 2, 0.0f, (static_cast<float>(LAND_HEIGHT) - 1) * m_scale}, // ���ӂ̒��S
		{0.0f, 0.0f, static_cast<float>(LAND_HEIGHT) * m_scale / 2}, // ���ӂ̒��S
		{(static_cast<float>(LAND_WIDTH) - 1) * m_scale, 0.0f, static_cast<float>(LAND_HEIGHT) * m_scale / 2} // �E�ӂ̒��S
	};

	// �e�ӂɉ�����Box�̃T�C�Y���쐬
	DirectX::SimpleMath::Vector3 boxSize[STAGE_QUANTITY] =
	{
		{static_cast<float>(LAND_HEIGHT) * m_scale, static_cast<float>(m_correctionHeight) * m_scale, 5.0f},
		{static_cast<float>(LAND_HEIGHT) * m_scale, static_cast<float>(m_correctionHeight) * m_scale, 5.0f},
		{5.0f, static_cast<float>(m_correctionHeight) * m_scale, static_cast<float>(LAND_WIDTH) * m_scale},
		{5.0f, static_cast<float>(m_correctionHeight) * m_scale, static_cast<float>(LAND_WIDTH) * m_scale} // �ǂ̃T�C�Y��K�X����
	};

	// �X�e�[�W�̊O���̏ꏊ�����
	for (int i = 0; i < STAGE_QUANTITY; i++)
	{
		m_stageCase[i]->SetBoundingPosition(stagePositions[i], boxSize[i]);
	}
}