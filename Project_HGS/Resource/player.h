//--------------------------------------------------------------------------------
// 
// �v���C���[ [player.h]
// Author: Taito Jin
// 
//--------------------------------------------------------------------------------
#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "character.h"
#include "line.h"

//****************************************************
// �v���C���[�N���X
//****************************************************
class CPlayer : public CCharacter
{
public:
	CPlayer(int nPriority = static_cast<int>(LAYER::NONE));	// �R���X�g���N�^
	~CPlayer() override = default;							// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	void SetPrevPos(const D3DXVECTOR3& inPos) { m_PrevPos = inPos; }
	const D3DXVECTOR3& GetPrevPos() const { return m_PrevPos; }

	static CPlayer* Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inSize);	// ����

private:
	enum class PLAYER_FLAG : BYTE
	{
		NONE = 0u,
		CAN_INPUT = 1 << 0,
	};

	CPlayer(const CPlayer&) = delete;
	void operator=(const CPlayer&) = delete;

	D3DXVECTOR3 m_PrevPos;	// �O�t���[���̈ʒu
	BYTE m_PlayerFlag;		// �v���C���[�t���O

	std::vector<CLine**> m_Lines;	// ������
};
