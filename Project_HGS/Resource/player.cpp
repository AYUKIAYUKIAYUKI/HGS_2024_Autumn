//--------------------------------------------------------------------------------
// 
// プレイヤー [player.cpp]
// Author: Taito Jin
// 
//--------------------------------------------------------------------------------

//---------------------------------------------------
// インクルード
//---------------------------------------------------
#include "player.h"
#include "manager.h"

//===================================================
// 無名名前空間
//===================================================
namespace /* anonymous */
{
	//---------------------------------------------------
	// using 宣言
	//---------------------------------------------------
	using namespace HGSAutumn240930;

	//---------------------------------------------------
	// 定数
	//---------------------------------------------------
	constexpr float MOVE_SPEED = 10.0f;	// プレイヤーの移動速度

} // namespace /* anonymous */

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer(int nPriority)
	: CCharacter{ nPriority }
	, m_PrevPos{ 0.0f, 0.0f, 0.0f }
	, m_PlayerFlag{ 0x00 }
{
#if 1
	m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);
	m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_LEFT);
	m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_RIGHT);
#endif
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CPlayer::Init()
{
	// 親クラスの処理
	HRESULT hr = CCharacter::Init();
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// 線の生成
	{ // 上の線
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
	{ // 下の線
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
	{ // 当たり判定用左の線
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
	{ // 当たり判定用右の線
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
// 終了処理
//============================================================================
void CPlayer::Uninit()
{
	for (auto& line : m_Lines)
	{
		delete line;
		line = nullptr;
	}
	m_Lines.clear();

	// 親クラスの処理
	CCharacter::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CPlayer::Update()
{
	m_PrevPos = GetPos();

	bool bRevivalLeft = false;
	bool bRevivalRight = false;

	// 移動量の設定
	if (m_PlayerFlag & static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT))
	{ // 移動可能
		bool bPressLeft = CManager::GetKeyboard()->GetPress(DIK_LEFT);
		bool bTriggerLeft = CManager::GetKeyboard()->GetTrigger(DIK_LEFT);
		bool bPressRight = CManager::GetKeyboard()->GetPress(DIK_RIGHT);
		bool bTriggerRight = CManager::GetKeyboard()->GetTrigger(DIK_RIGHT);

		D3DXVECTOR3 move = GetMove();
		move.x = 0.0f;

		if ((bPressLeft && bTriggerRight) || (bPressRight && bTriggerLeft))
		{ // 同時押し
			D3DXVECTOR3 pos = GetPos();
			if (pos.y <= SCREEN_HEIGHT * 0.5f)
			{ // 画面上部
				move = { 0.0f, MOVE_SPEED, 0.0f };
			}
			else
			{ // 画面下部
				move = { 0.0f, -MOVE_SPEED, 0.0f };
			}

			m_PlayerFlag &= ~static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);
		}
		else if (bPressLeft && !bPressRight)
		{ // 左
			if (m_PlayerFlag & static_cast<BYTE>(PLAYER_FLAG::CAN_LEFT))
			{
				move = { -MOVE_SPEED, 0.0f, 0.0f };
				m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_RIGHT);
				bRevivalRight = true;
			}
		}
		else if (bPressRight && !bPressLeft)
		{ // 右
			if (m_PlayerFlag & static_cast<BYTE>(PLAYER_FLAG::CAN_RIGHT))
			{
				move = { MOVE_SPEED, 0.0f, 0.0f };
				m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_LEFT);
				bRevivalLeft = true;
			}
		}

		SetMove(move);
	}

	// 親クラスの処理
	CCharacter::Update();

	// 当たり判定
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
				{ // 衝突
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
				{ // 衝突
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
	
	// 左右の当たり判定
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
		{ // 未衝突
			continue;
		}

		// 衝突した
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
}

//============================================================================
// 描画処理
//============================================================================
void CPlayer::Draw()
{
	// 親クラスの処理
	CCharacter::Draw();
}

//============================================================================
// 生成
//============================================================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inSize, const D3DXCOLOR& inCol)
{
	CPlayer* pPlayer = DBG_NEW CPlayer{};

	// 生成出来ていたら初期設定
	if (pPlayer != nullptr)
	{
		pPlayer->Init();
	}

	pPlayer->SetPos(inPos);
	pPlayer->SetSize(inSize);
	pPlayer->SetCol(inCol);

	return pPlayer;
}