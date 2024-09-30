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
	CPlayer(int nPriority = static_cast<int>(LAYER::MIDDLE));	// �R���X�g���N�^
	~CPlayer() override = default;								// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	void SetPrevPos(const D3DXVECTOR3& inPos) { m_PrevPos = inPos; }
	const D3DXVECTOR3& GetPrevPos() const { return m_PrevPos; }

	const Collision::Circle& GetCircle() const { return m_Circle; }

	static CPlayer* Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inSize, const D3DXCOLOR& inCol);	// ����

	static constexpr float MARGIN_WIDTH = 300.0f;										// �]�� (��)
	static constexpr float MARGIN_HEIGHT = 200.0f;										// �]�� (����)
	static constexpr float LINE_WIDTH = (SCREEN_WIDTH - MARGIN_WIDTH * 2.0f) * 0.5f;	// ���̕�
	static constexpr float LINE_HEIGHT = 5.0f;											// ���̍���

private:
	enum class PLAYER_FLAG : BYTE
	{
		NONE = 0u,
		CAN_INPUT = 1 << 0,
		CAN_LEFT = 1 << 1,
		CAN_RIGHT = 1 << 2,
		BUZZ_UP = 1 << 3,
		BUZZ_DOWN = 1 << 4,
	};

	enum LINE_TYPE
	{
		LINE_TYPE_TOP = 0,
		LINE_TYPE_UNDER,
		LINE_TYPE_LEFT,
		LINE_TYPE_RIGHT,
		LINE_TYPE_MAX
	};

	CPlayer(const CPlayer&) = delete;
	void operator=(const CPlayer&) = delete;

	D3DXVECTOR3 m_PrevPos;	// �O�t���[���̈ʒu
	BYTE m_PlayerFlag;		// �v���C���[�t���O

	std::vector<CLine**> m_Lines;	// ������

	float m_graceCounter;		// �P�\�J�E���g
	D3DXVECTOR3 m_TargetPos;	// �ړI�̈ʒu

	bool m_bWasPressL;
	bool m_bWasPressR;
	//DWORD m_ReleaseTime;
	bool m_bWasReleaseAll;	// �ǂ���������Ă���

	int m_nCntPressL;
	int m_nCntPressR;

	Collision::Circle m_Circle;

	int m_nBuzzCounter;

	D3DXVECTOR3 m_BuzzPoint;
	D3DXVECTOR3 m_BuzzMove;
};
