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
	constexpr float MOVE_SPEED = 10.0f;	// �v���C���[�̈ړ����x

} // namespace /* anonymous */

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer(int nPriority)
	: CCharacter{ nPriority }
	, m_PrevPos{ 0.0f, 0.0f, 0.0f }
	, m_PlayerFlag{ 0x01 }
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
		float fHeight = MARGIN_HEIGHT;
		CLine* pLine = CLine::Create(
			{ SCREEN_WIDTH * 0.5f, MARGIN_HEIGHT, 0.0f }, 
			{ LINE_WIDTH, LINE_HEIGHT, 0.0f },
			{ MARGIN_WIDTH, fHeight },
			{ SCREEN_WIDTH - MARGIN_WIDTH, fHeight },
			{ 0.0f, 0.0f, 0.0f, 1.0f });
		pLine->SetIsUnderPlayer(true);
		CLine** ppLine = DBG_NEW CLine*{ pLine };
		m_Lines.push_back(ppLine);
	}
	{ // ���̐�
		float fHeight = SCREEN_HEIGHT - MARGIN_HEIGHT;
		CLine* pLine = CLine::Create(
			{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - MARGIN_HEIGHT, 0.0f },
			{ LINE_WIDTH, LINE_HEIGHT, 0.0f },
			{ MARGIN_WIDTH, fHeight },
			{ SCREEN_WIDTH - MARGIN_WIDTH, fHeight },
			{ 0.0f, 0.0f, 0.0f, 1.0f });
		CLine** ppLine = DBG_NEW CLine* { pLine };
		m_Lines.push_back(ppLine);
	}
	{ // �����蔻��p���̐�
		float fWidth = MARGIN_WIDTH;
		CLine* pLine = CLine::Create(
			{ SCREEN_WIDTH * 0.5f, MARGIN_HEIGHT, 0.0f },
			{ LINE_WIDTH, LINE_HEIGHT, 0.0f },
			{ fWidth, MARGIN_HEIGHT },
			{ fWidth, SCREEN_HEIGHT - MARGIN_HEIGHT },
			{ 0.0f, 0.0f, 0.0f, 1.0f });
		CLine** ppLine = DBG_NEW CLine* { pLine };
		m_Lines.push_back(ppLine);
	}
	{ // �����蔻��p�E�̐�
		float fWidth = SCREEN_WIDTH - MARGIN_WIDTH;
		CLine* pLine = CLine::Create(
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ fWidth, MARGIN_HEIGHT },
			{ fWidth, SCREEN_HEIGHT - MARGIN_HEIGHT },
			{ 0.0f, 0.0f, 0.0f, 1.0f });
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
	m_PrevPos = GetPos();

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

			m_PlayerFlag &= ~static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);
		}
		else if (bTriggerLeft)
		{ // ��
			move = { -MOVE_SPEED, 0.0f, 0.0f };
			m_PlayerFlag &= ~static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);
		}
		else if (bTriggerRight)
		{ // �E
			move = { MOVE_SPEED, 0.0f, 0.0f };
			m_PlayerFlag &= ~static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);
		}

		SetMove(move);
	}

	// �e�N���X�̏���
	CCharacter::Update();

	// �����蔻��
	bool bTopAndUnder = false;
	if (m_Lines[LINE_TYPE_TOP] != nullptr)
	{
		CLine* pLine = *m_Lines[LINE_TYPE_TOP];
		if (pLine != nullptr)
		{
			if (!pLine->GetIsUnderPlayer())
			{
				D3DXVECTOR3 currPos = GetPos();
				Collision::LineSegment2D segmentPlayer{ { m_PrevPos.x, m_PrevPos.y }, { currPos.x, currPos.y } };
				Collision::LineSegment2D segmentLine = pLine->GetLineSegment2D();
				bool isCollision = Collision::IsSegmentsCollide(segmentPlayer, segmentLine);
				if (isCollision)
				{ // �Փ�
					// �Փ˂���
					m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);

					//if (m_PrevPos != currPos)
					D3DXVECTOR2 pos = Collision::GetCrossPoint(segmentPlayer, segmentLine);

					D3DXVECTOR3 move = GetMove();
					move.y = 0.0f;
					SetMove(move);
					SetPos({ pos.x, pos.y, 0.0f });

					pLine->SetIsUnderPlayer(true);

					if (CLine* pUnder = *m_Lines[LINE_TYPE_UNDER])
					{
						pUnder->SetIsUnderPlayer(false);
					}

					bTopAndUnder = true;
				}
			}
		}
	}
	
	if (m_Lines[LINE_TYPE_UNDER] != nullptr && !bTopAndUnder)
	{
		CLine* pLine = *m_Lines[LINE_TYPE_UNDER];
		if (pLine != nullptr)
		{
			if (!pLine->GetIsUnderPlayer())
			{
				D3DXVECTOR3 currPos = GetPos();
				Collision::LineSegment2D segmentPlayer{ { m_PrevPos.x, m_PrevPos.y }, { currPos.x, currPos.y } };
				Collision::LineSegment2D segmentLine = pLine->GetLineSegment2D();
				bool isCollision = Collision::IsSegmentsCollide(segmentPlayer, segmentLine);
				if (isCollision)
				{ // �Փ�
					// �Փ˂���
					m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);

					//if (m_PrevPos != currPos)
					D3DXVECTOR2 pos = Collision::GetCrossPoint(segmentPlayer, segmentLine);

					D3DXVECTOR3 move = GetMove();
					move.y = 0.0f;
					SetMove(move);
					SetPos({ pos.x, pos.y, 0.0f });

					pLine->SetIsUnderPlayer(true);

					if (CLine* pUnder = *m_Lines[LINE_TYPE_TOP])
					{
						pUnder->SetIsUnderPlayer(false);
					}
				}
			}
		}
	}
	
	bool bLeftAndRight = false;
	if (m_Lines[LINE_TYPE_LEFT] != nullptr)
	{
		CLine* pLine = *m_Lines[LINE_TYPE_LEFT];
		if (pLine != nullptr)
		{
			if (!pLine->GetIsUnderPlayer())
			{
				D3DXVECTOR3 currPos = GetPos();
				Collision::LineSegment2D segmentPlayer{ { m_PrevPos.x, m_PrevPos.y }, { currPos.x, currPos.y } };
				Collision::LineSegment2D segmentLine = pLine->GetLineSegment2D();
				bool isCollision = Collision::IsSegmentsCollide(segmentPlayer, segmentLine);
				if (isCollision)
				{ // �Փ�
					// �Փ˂���
					m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);

					//if (m_PrevPos != currPos)
					D3DXVECTOR2 pos = Collision::GetCrossPoint(segmentPlayer, segmentLine);

					D3DXVECTOR3 move = GetMove();
					move.x = 0.0f;
					SetMove(move);
					SetPos({ pos.x, pos.y, 0.0f });

					pLine->SetIsUnderPlayer(true);

					if (CLine* pUnder = *m_Lines[LINE_TYPE_RIGHT])
					{
						pUnder->SetIsUnderPlayer(false);
					}

					bLeftAndRight = true;
				}
			}
		}
	}

	if (m_Lines[LINE_TYPE_RIGHT] != nullptr && !bLeftAndRight)
	{
		CLine* pLine = *m_Lines[LINE_TYPE_RIGHT];
		if (pLine != nullptr)
		{
			if (!pLine->GetIsUnderPlayer())
			{
				D3DXVECTOR3 currPos = GetPos();
				Collision::LineSegment2D segmentPlayer{ { m_PrevPos.x, m_PrevPos.y }, { currPos.x, currPos.y } };
				Collision::LineSegment2D segmentLine = pLine->GetLineSegment2D();
				bool isCollision = Collision::IsSegmentsCollide(segmentPlayer, segmentLine);
				if (isCollision)
				{ // �Փ�
					// �Փ˂���
					m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);

					//if (m_PrevPos != currPos)
					D3DXVECTOR2 pos = Collision::GetCrossPoint(segmentPlayer, segmentLine);

					D3DXVECTOR3 move = GetMove();
					move.x = 0.0f;
					SetMove(move);
					SetPos({ pos.x, pos.y, 0.0f });

					pLine->SetIsUnderPlayer(true);

					if (CLine* pUnder = *m_Lines[LINE_TYPE_LEFT])
					{
						pUnder->SetIsUnderPlayer(false);
					}
				}
			}
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
CPlayer* CPlayer::Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inSize, const D3DXCOLOR& inCol)
{
	CPlayer* pPlayer = DBG_NEW CPlayer{};

	// �����o���Ă����珉���ݒ�
	if (pPlayer != nullptr)
	{
		pPlayer->Init();
	}

	pPlayer->SetPos(inPos);
	pPlayer->SetSize(inSize);
	pPlayer->SetCol(inCol);

	return pPlayer;
}