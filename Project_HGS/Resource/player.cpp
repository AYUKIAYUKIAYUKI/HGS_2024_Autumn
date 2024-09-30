//--------------------------------------------------------------------------------
// 
// �v���C���[ [player.cpp]
// Author: Taito Jin
// 
//--------------------------------------------------------------------------------

//---------------------------------------------------
// �C���N���[�h
//---------------------------------------------------
#include "player.h"
#include "manager.h"

//===================================================
// �������O���
//===================================================
namespace /* anonymous */
{
	//---------------------------------------------------
	// using �錾
	//---------------------------------------------------
	using namespace HGSAutumn240930;

	//---------------------------------------------------
	// �萔
	//---------------------------------------------------
	constexpr float MOVE_SPEED = 50.0f;									// �v���C���[�̈ړ����x
	constexpr float MARGIN_WIDTH = 300.0f;								// �]�� (��)
	constexpr float MARGIN_HEIGHT = 250.0f;								// �]�� (����)
	constexpr float LINE_WIDTH = SCREEN_WIDTH - MARGIN_WIDTH * 2.0f;	// ���̕�
	constexpr float LINE_HEIGHT = 5.0f;									// ���̍���

} // namespace /* anonymous */

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer(int nPriority)
	: CCharacter{ nPriority }
	, m_PrevPos{ 0.0f, 0.0f, 0.0f }
	, m_PlayerFlag{ 0u }
{
	// DO_NOTHING
}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CPlayer::Init()
{
	// �e�N���X�̏���
	HRESULT hr = CCharacter::Init();
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// ���̐���
	{ // ��̐�
		float fHeight = SCREEN_HEIGHT - MARGIN_HEIGHT;
		CLine* pLine = CLine::Create(
			{ SCREEN_WIDTH * 0.5f, MARGIN_HEIGHT, 0.0f }, 
			{ LINE_WIDTH, LINE_HEIGHT, 0.0f },
			{ MARGIN_WIDTH, fHeight },
			{ SCREEN_WIDTH - MARGIN_WIDTH, fHeight });
		CLine** ppLine = DBG_NEW CLine*{ pLine };
		m_Lines.push_back(ppLine);
	}
	{ // ���̐�
		float fHeight = SCREEN_HEIGHT - MARGIN_HEIGHT;
		CLine* pLine = CLine::Create(
			{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - MARGIN_HEIGHT, 0.0f },
			{ LINE_WIDTH, LINE_HEIGHT, 0.0f },
			{ MARGIN_WIDTH, fHeight },
			{ SCREEN_WIDTH - MARGIN_WIDTH, fHeight });
		CLine** ppLine = DBG_NEW CLine* { pLine };
		m_Lines.push_back(ppLine);
	}

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CPlayer::Uninit()
{
	for (auto& line : m_Lines)
	{
		delete line;
		line = nullptr;
	}
	m_Lines.clear();

	// �e�N���X�̏���
	CCharacter::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CPlayer::Update()
{
	// �ړ��ʂ̐ݒ�
	if (m_PlayerFlag & static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT))
	{ // �ړ��\
		bool bPressLeft = CManager::GetKeyboard()->GetPress(DIK_LEFT);
		bool bTriggerLeft = CManager::GetKeyboard()->GetTrigger(DIK_LEFT);
		bool bPressRight = CManager::GetKeyboard()->GetPress(DIK_RIGHT);
		bool bTriggerRight = CManager::GetKeyboard()->GetTrigger(DIK_RIGHT);

		D3DXVECTOR3 move = GetMove();

		if ((bPressLeft && bTriggerRight) || (bPressRight && bTriggerLeft))
		{ // ��������
			D3DXVECTOR3 pos = GetPos();
			if (pos.y <= SCREEN_HEIGHT * 0.5f)
			{ // ��ʏ㕔
				move = { 0.0f, MOVE_SPEED, 0.0f };
			}
			else
			{ // ��ʉ���
				move = { 0.0f, -MOVE_SPEED, 0.0f };
			}
		}
		else if (bTriggerLeft)
		{ // ��
			move = { -MOVE_SPEED, 0.0f, 0.0f };
		}
		else if (bTriggerRight)
		{ // �E
			move = { MOVE_SPEED, 0.0f, 0.0f };
		}

		SetMove(move);
	}

	// �e�N���X�̏���
	CCharacter::Update();

	// �����蔻��
	for (auto& line : m_Lines)
	{
		if (line == nullptr)
		{
			continue;
		}

		CLine* pLine = *line;
		if (pLine == nullptr)
		{
			continue;
		}

		D3DXVECTOR3 currPos = GetPos();
		Collision::LineSegment2D segment{ { m_PrevPos.x, m_PrevPos.y }, { currPos.x, currPos.y } };
		bool isCollision = Collision::IsSegmentsCollide(segment, pLine->GetLineSegment2D());
		if (isCollision)
		{ // �Փ�
			m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);

			SetMove({ 0.0f, 0.0f, 0.0f });
			break;
		}
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CPlayer::Draw()
{
	// �e�N���X�̏���
	CCharacter::Draw();
}

//============================================================================
// ����
//============================================================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inSize)
{
	CPlayer* pPlayer = DBG_NEW CPlayer{};

	// �����o���Ă����珉���ݒ�
	if (pPlayer != nullptr)
	{
		pPlayer->Init();
	}

	pPlayer->SetPos(inPos);
	pPlayer->SetSize(inSize);

	return pPlayer;
}