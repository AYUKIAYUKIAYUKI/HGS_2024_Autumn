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
	constexpr float MOVE_SPEED = 50.0f;									// プレイヤーの移動速度
	constexpr float MARGIN_WIDTH = 300.0f;								// 余幅 (幅)
	constexpr float MARGIN_HEIGHT = 250.0f;								// 余幅 (高さ)
	constexpr float LINE_WIDTH = SCREEN_WIDTH - MARGIN_WIDTH * 2.0f;	// 線の幅
	constexpr float LINE_HEIGHT = 5.0f;									// 線の高さ

} // namespace /* anonymous */

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer(int nPriority)
	: CCharacter{ nPriority }
	, m_PrevPos{ 0.0f, 0.0f, 0.0f }
	, m_PlayerFlag{ 0u }
{
	// DO_NOTHING
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
		float fHeight = SCREEN_HEIGHT - MARGIN_HEIGHT;
		CLine* pLine = CLine::Create(
			{ SCREEN_WIDTH * 0.5f, MARGIN_HEIGHT, 0.0f }, 
			{ LINE_WIDTH, LINE_HEIGHT, 0.0f },
			{ MARGIN_WIDTH, fHeight },
			{ SCREEN_WIDTH - MARGIN_WIDTH, fHeight });
		CLine** ppLine = DBG_NEW CLine*{ pLine };
		m_Lines.push_back(ppLine);
	}
	{ // 下の線
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
	// 移動量の設定
	if (m_PlayerFlag & static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT))
	{ // 移動可能
		bool bPressLeft = CManager::GetKeyboard()->GetPress(DIK_LEFT);
		bool bTriggerLeft = CManager::GetKeyboard()->GetTrigger(DIK_LEFT);
		bool bPressRight = CManager::GetKeyboard()->GetPress(DIK_RIGHT);
		bool bTriggerRight = CManager::GetKeyboard()->GetTrigger(DIK_RIGHT);

		D3DXVECTOR3 move = GetMove();

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
		}
		else if (bTriggerLeft)
		{ // 左
			move = { -MOVE_SPEED, 0.0f, 0.0f };
		}
		else if (bTriggerRight)
		{ // 右
			move = { MOVE_SPEED, 0.0f, 0.0f };
		}

		SetMove(move);
	}

	// 親クラスの処理
	CCharacter::Update();

	// 当たり判定
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
		{ // 衝突
			m_PlayerFlag |= static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT);

			SetMove({ 0.0f, 0.0f, 0.0f });
			break;
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
CPlayer* CPlayer::Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inSize)
{
	CPlayer* pPlayer = DBG_NEW CPlayer{};

	// 生成出来ていたら初期設定
	if (pPlayer != nullptr)
	{
		pPlayer->Init();
	}

	pPlayer->SetPos(inPos);
	pPlayer->SetSize(inSize);

	return pPlayer;
}