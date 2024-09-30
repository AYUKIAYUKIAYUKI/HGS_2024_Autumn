//--------------------------------------------------------------------------------
// 
// プレイヤー [player.h]
// Author: Taito Jin
// 
//--------------------------------------------------------------------------------
#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "character.h"
#include "line.h"

//****************************************************
// プレイヤークラス
//****************************************************
class CPlayer : public CCharacter
{
public:
	CPlayer(int nPriority = static_cast<int>(LAYER::NONE));	// コンストラクタ
	~CPlayer() override = default;							// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	void SetPrevPos(const D3DXVECTOR3& inPos) { m_PrevPos = inPos; }
	const D3DXVECTOR3& GetPrevPos() const { return m_PrevPos; }

	static CPlayer* Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inSize);	// 生成

private:
	enum class PLAYER_FLAG : BYTE
	{
		NONE = 0u,
		CAN_INPUT = 1 << 0,
	};

	CPlayer(const CPlayer&) = delete;
	void operator=(const CPlayer&) = delete;

	D3DXVECTOR3 m_PrevPos;	// 前フレームの位置
	BYTE m_PlayerFlag;		// プレイヤーフラグ

	std::vector<CLine**> m_Lines;	// 線たち
};
