﻿//============================================================================
// 
// ゲーム [game.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "game.h"
#include "fade.h"

// インプット取得用
#include "manager.h"

// 邪魔物生成用
#include "obstacle_manager.h"

/* test */
#include "object_X.h"
#include "texture_manager.h"

#include <timernumber.h>
#include "player.h"
#include <bg.h>
#include "sound.h"
//============================================================================
// デフォルトコンストラクタ
//============================================================================
CGame::CGame()
{

}

//============================================================================
// デストラクタ
//============================================================================
CGame::~CGame()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CGame::Init()
{
	// 基底クラスの初期設定
	HRESULT hr{ CScene::Init() };

	// 邪魔物マネージャーの生成
	CObstacle_Manager::GetInstance()->Init();

	//背景生成
	CBg::Create();

	// プレイヤーの生成
	CPlayer* pPlayer{ CPlayer::Create({ SCREEN_WIDTH * 0.5f, CPlayer::MARGIN_HEIGHT, 0.0f }, { 15.0f, 15.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }) };

	// タイマー表示生成
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		CTimerNumber::Create(nCnt);
	}
	
	

	// BGMをかける
	CSound::GetInstance()->Play(CSound::LABEL::BGM_02);

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CGame::Uninit()
{
	// 全てのサウンドを停止
	CSound::GetInstance()->Stop();

	// 邪魔物マネージャーの破棄
	CObstacle_Manager::GetInstance()->Release();

	// 基底クラスの終了処理
	CScene::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CGame::Update()
{
	// 基底クラスの更新処理
	CScene::Update();

	if (CFade::GetInstance()->GetNextMode() == CScene::MODE::RESULT_GAMEOVER)
	{
		return;
	}

	// 邪魔物マネージャーの更新
	CObstacle_Manager::GetInstance()->Update();

#ifdef _DEBUG
	// リザルト画面へ
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CFade::SetFade(CScene::MODE::RESULT_GAMEOVER);
	}
#endif // _DEBUG

	// タイマーが0になったら
	if (CManager::GetTimer()->GetTime() <= 0)
	{
		//リザルト画面へ
		CFade::SetFade(CScene::MODE::RESULT_GAMECLEAR);
	}
}

//============================================================================
// 描画処理
//============================================================================
void CGame::Draw()
{
	// 基底クラスの描画処理
	CScene::Draw();
}