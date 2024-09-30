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
	, m_PlayerFlag{ 0x00 }
	, m_TargetPos{ 0.0f, 0.0f, 0.0f }
	, m_bWasPressL{ false }
	, m_bWasPressR{ false }
	, m_bWasReleaseAll{ false }
	, m_nCntPressL{ 0 }
	, m_nCntPressR{ 0 }
	, m_Circle{}
	, m_nBuzzCounter{ 0 }
	, m_BuzzPoint{ 0.0f, 0.0f, 0.0f }
{
#if 1
	m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);
	m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_LEFT);
	m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_RIGHT);
#endif
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

	m_Circle.r = 15.0f;

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
	{
		D3DXVECTOR3 pos = GetPos();
		m_PrevPos = pos;
		m_Circle.c = { pos.x, pos.y };
	}

	bool bRevivalLeft = false;
	bool bRevivalRight = false;

	// �ړ��ʂ̐ݒ�
	if (m_PlayerFlag & static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT))
	{ // �ړ��\
		CInputKeyboard* keyboard = CManager::GetKeyboard();
		CInputPad* pad = CManager::GetPad();

		static int GRACE_FRAME = 2;

		bool bPressLeft = keyboard->GetPress(DIK_LEFT) || pad->GetPress(CInputPad::JOYKEY::L);
		bool bTriggerLeft = keyboard->GetTrigger(DIK_LEFT) || pad->GetTrigger(CInputPad::JOYKEY::L);
		bool bPressRight = keyboard->GetPress(DIK_RIGHT) || pad->GetPress(CInputPad::JOYKEY::R);
		bool bTriggerRight = keyboard->GetTrigger(DIK_RIGHT) || pad->GetTrigger(CInputPad::JOYKEY::R);
		bool bReleaseL = keyboard->GetRelease(DIK_LEFT) || pad->GetRelease(CInputPad::JOYKEY::L);
		bool bReleaseR = keyboard->GetRelease(DIK_RIGHT) || pad->GetRelease(CInputPad::JOYKEY::R);

		if (bPressLeft)
		{
			m_nCntPressL++;
		}
		
		if (bReleaseL)
		{
			m_nCntPressL = 0;
		}

		if (bPressRight)
		{
			m_nCntPressR++;
		}

		if (bReleaseR)
		{
			m_nCntPressR = 0;
		}

		//if (m_nCntPressL >= GRACE_FRAME || m_nCntPressR >= GRACE_FRAME)
		//{
		//	//m_bWasReleaseAll = false;
		//}

		D3DXVECTOR3 move = GetMove();
		move.x = 0.0f;

		if (((bPressLeft && bTriggerRight) || (bPressRight && bTriggerLeft)) && m_bWasReleaseAll &&
			(m_nCntPressL <= 5 && m_nCntPressR <= 5))
		{ // ��������
			D3DXVECTOR3 pos = GetPos();
			if (pos.y <= SCREEN_HEIGHT * 0.5f)
			{ // ��ʏ㕔
				m_TargetPos = { pos.x, SCREEN_HEIGHT - MARGIN_HEIGHT - 1.0f, pos.z };
				//move = { 0.0f, MOVE_SPEED, 0.0f };
			}
			else
			{ // ��ʉ���
				m_TargetPos = { pos.x, MARGIN_HEIGHT, pos.z };
				//move = { 0.0f, -MOVE_SPEED, 0.0f };
			}

			m_bWasReleaseAll = false;

			m_PlayerFlag &= ~static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);
			//m_bWasReleaseAll = false;
		}
		else if (bPressLeft && !bPressRight/* && m_nCntPressL >= GRACE_FRAME*/ && !m_bWasPressR)
		{ // ��
			if (m_PlayerFlag & static_cast<BYTE>(PLAYER_FLAG::CAN_LEFT))
			{
				move = { -MOVE_SPEED, 0.0f, 0.0f };
				m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_RIGHT);
				bRevivalRight = true;
				//m_bWasReleaseAll = false;
			}
		}
		else if (bPressRight && !bPressLeft/* && m_nCntPressR >= GRACE_FRAME*/ && !m_bWasPressL)
		{ // �E
			if (m_PlayerFlag & static_cast<BYTE>(PLAYER_FLAG::CAN_RIGHT))
			{
				move = { MOVE_SPEED, 0.0f, 0.0f };
				m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_LEFT);
				bRevivalLeft = true;
				//m_bWasReleaseAll = false;
			}
		}
		else if (!bPressLeft && !bPressRight)
		{
			m_bWasReleaseAll = true;
		}

		SetMove(move);

		m_bWasPressL = bPressLeft;
		m_bWasPressR = bPressRight;
	}
	else
	{
		D3DXVECTOR3 distance = (m_TargetPos - GetPos());
		D3DXVECTOR2 distanceVec2 = { distance.x, distance.y };
		float fLength = fabsf(D3DXVec2Length(&distanceVec2));
		bool bDone = fLength <= 1.0f;
		if (bDone)
		{
			//SetPos(m_TargetPos);
		}

		if (!bRevivalRight && !bRevivalLeft && !bDone)
		{
			// �ړ��ʂ̍X�V (����)
			D3DXVECTOR3 move = distance * 0.1f;
			static float MIN_MOVE = 5.0f;
			if (move.y <= 0.0f && move.y >= -MIN_MOVE)
			{
				move.y = -MIN_MOVE;
			}
			else if (move.y >= 0.0f && move.y <= MIN_MOVE)
			{
				move.y = MIN_MOVE;
			}

			SetMove(move);
		}
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

					m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::BUZZ_UP);

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

					m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::BUZZ_DOWN);
				}
			}
		}
	}
	
	// ���E�̓����蔻��
	for (uint32_t i = LINE_TYPE_LEFT; i < LINE_TYPE_MAX; i++)
	{
		if (!m_Lines[i])
		{
			continue;
		}

		CLine* pLine = *m_Lines[i];
		if (!pLine)
		{
			continue;
		}

		if (pLine->GetIsUnderPlayer())
		{
			continue;
		}

		D3DXVECTOR3 currPos = GetPos();
		Collision::LineSegment2D segmentPlayer{ { m_PrevPos.x, m_PrevPos.y }, { currPos.x, currPos.y } };
		Collision::LineSegment2D segmentLine = pLine->GetLineSegment2D();
		bool isCollision = Collision::IsSegmentsCollide(segmentPlayer, segmentLine);
		if (!isCollision)
		{ // ���Փ�
			continue;
		}

		// �Փ˂���
		m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);

		D3DXVECTOR2 pos = Collision::GetCrossPoint(segmentPlayer, segmentLine);

		D3DXVECTOR3 move = GetMove();
		move.x = 0.0f;
		SetMove(move);
		SetPos({ pos.x, pos.y, 0.0f });

		pLine->SetIsUnderPlayer(true);

		if (i == LINE_TYPE_LEFT)
		{
			if (m_Lines[LINE_TYPE_RIGHT])
			{
				if (CLine* pUnder = *m_Lines[LINE_TYPE_RIGHT])
				{
					pUnder->SetIsUnderPlayer(false);
				}
			}
			m_PlayerFlag &= ~static_cast<BYTE>(PLAYER_FLAG::CAN_LEFT);
			m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_RIGHT);
		}
		else if (i == LINE_TYPE_RIGHT)
		{
			if (m_Lines[LINE_TYPE_LEFT])
			{
				if (CLine* pUnder = *m_Lines[LINE_TYPE_LEFT])
				{
					pUnder->SetIsUnderPlayer(false);
				}
			}
			m_PlayerFlag &= ~static_cast<BYTE>(PLAYER_FLAG::CAN_RIGHT);
			m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_LEFT);
		}

		break;
	}

	if (bRevivalLeft)
	{
		if (m_Lines[LINE_TYPE_LEFT])
		{
			if (CLine* pUnder = *m_Lines[LINE_TYPE_LEFT])
			{
				pUnder->SetIsUnderPlayer(false);
			}
		}
	}

	if (bRevivalRight)
	{
		if (m_Lines[LINE_TYPE_RIGHT])
		{
			if (CLine* pUnder = *m_Lines[LINE_TYPE_RIGHT])
			{
				pUnder->SetIsUnderPlayer(false);
			}
		}
	}

	if (m_PlayerFlag & static_cast<BYTE>(PLAYER_FLAG::BUZZ_DOWN))
	{

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