//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/19
// <file>			Graphics.h
// <�T�v>		�@�@�`�揈���ɕK�v�Ȃ��̂܂Ƃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"DeviceResources.h"
class Graphics final
{
public:
	// �C���X�^���X�擾
	static Graphics* const GetInstance();

	// �X�N���[���T�C�Y�ݒ�
	void GetScreenSize(int& width, int height) const { width = m_screenW; height = m_screenH; }
	void SetScreenSize(const int& width, const int& height) { m_screenW = width; m_screenH = height; }

	// �f�o�C�X���\�[�X�擾
	DX::DeviceResources* GetDeviceResources() const { return m_deviceResources.get(); }
	// �v���~�e�B�u�o�b�`���擾
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* GetPrimitiveBatch() const { return m_primitiveBatch.get(); }
	// �C���v�b�g���C�A�E�g���擾
	ID3D11InputLayout* GetInputLayout() const { return m_inputLayout.Get(); }
	// �x�[�V�b�N�G�t�F�N�g�擾
	DirectX::BasicEffect* GetBasicEffect() { return m_basicEffect.get(); }
	// �R�����X�e�[�g�擾
	DirectX::CommonStates* GetCommonStates() const { return m_commonStates.get(); }
	// �X�v���C�g�o�b�`�擾
	DirectX::SpriteBatch* GetSpriteBatch() { return m_spriteBatch.get(); }
	// �r���[�s��ݒ�
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	// �r���[�s��擾
	const DirectX::SimpleMath::Matrix& GetViewMatrix() { return m_view; }
	// �ˉe�s���ݒ肷��
	void SetProjectionMatix(const DirectX::SimpleMath::Matrix& projection) { m_projection = projection; }
	// �ˉe�s����擾
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() { return m_projection; }

public:
	// �f�X�g���N�^
	~Graphics();
	// ����������
	void Initialize();
	// �v���~�e�B�u�`����J�n
	void DrawPrimitiveBegin(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	// �v���~�e�B�u�`����I��
	void DrawPrimitiveEnd();

private:
	// �R���X�g���N�^
	Graphics();

	// ����͋��e���Ȃ�
	void operator=(const Graphics& object) = delete;
	// �R�s�[�R���X�g���N�^�͋��e���Ȃ�
	Graphics(const Graphics& object) = delete;

private:
	// �|�C���^
	static std::unique_ptr<Graphics> m_graphics;

	// �f�o�C�X���\�[�X
	std::unique_ptr<DX::DeviceResources> m_deviceResources;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// �X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	// �x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	// �G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory> m_effectFactory;
	// ���X�^���C�U�[�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterrizerState;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �X�N���[���T�C�Y
	int m_screenW, m_screenH;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;
	// �f�o�C�X
	ID3D11Device* m_device;
	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_context;
};