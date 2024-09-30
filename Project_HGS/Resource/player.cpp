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
	constexpr float MOVE_SPEED = 50.0f;	// プレイヤーの移動速度

} // namespace /* anonymous */

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer(int nPriority)
	: CCharacter{ nPriority }
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


	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CPlayer::Uninit()
{
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
	{
		

		Collision::Circle a;
		Collision::Circle b;
		Collision::IsCollisionCircleVsCircle(a, b);

		D3DXVECTOR3 pos = GetPos();
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
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = DBG_NEW CPlayer{};

	// 生成出来ていたら初期設定
	if (pPlayer != nullptr)
	{
		pPlayer->Init();
	}

	return pPlayer;
}