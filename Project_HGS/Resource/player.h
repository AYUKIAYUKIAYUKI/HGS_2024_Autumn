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
	CPlayer(int nPriority = static_cast<int>(LAYER::MIDDLE));	// コンストラクタ
	~CPlayer() override = default;								// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	void SetPrevPos(const D3DXVECTOR3& inPos) { m_PrevPos = inPos; }
	const D3DXVECTOR3& GetPrevPos() const { return m_PrevPos; }

	const Collision::Circle& GetCircle() const { return m_Circle; }

	static CPlayer* Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inSize, const D3DXCOLOR& inCol);	// 生成

	static constexpr float MARGIN_WIDTH = 300.0f;										// 余幅 (幅)
	static constexpr float MARGIN_HEIGHT = 200.0f;										// 余幅 (高さ)
	static constexpr float LINE_WIDTH = (SCREEN_WIDTH - MARGIN_WIDTH * 2.0f) * 0.5f;	// 線の幅
	static constexpr float LINE_HEIGHT = 5.0f;											// 線の高さ

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

	D3DXVECTOR3 m_PrevPos;	// 前フレームの位置
	BYTE m_PlayerFlag;		// プレイヤーフラグ

	std::vector<CLine**> m_Lines;	// 線たち

	float m_graceCounter;		// 猶予カウント
	D3DXVECTOR3 m_TargetPos;	// 目的の位置

	bool m_bWasPressL;
	bool m_bWasPressR;
	//DWORD m_ReleaseTime;
	bool m_bWasReleaseAll;	// どちらも離している

	int m_nCntPressL;
	int m_nCntPressR;

	Collision::Circle m_Circle;

	int m_nBuzzCounter;

	D3DXVECTOR3 m_BuzzPoint;
	D3DXVECTOR3 m_BuzzMove;
};
