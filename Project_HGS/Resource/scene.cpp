﻿//============================================================================
// 
// シーン管理 [scene.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "scene.h"
#include "fade.h"

// デバッグ表示用
#include "renderer.h"

// カメラ取得用
#include "manager.h"

// 各シーン用
#include "game.h"
#include "result.h"
#include "title.h"
#include "tutorial.h"

// オブジェクト管理用
#include "object.h"

//============================================================================
// コンストラクタ
//============================================================================
CScene::CScene() : m_mode(MODE::NONE)
{

}

//============================================================================
// デストラクタ
//============================================================================
CScene::~CScene()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CScene::Init()
{
	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CScene::Uninit()
{
	// ウェーブの強制終了
	//CFakeScreen::GetInstance()->StopWave();

	// 全オブジェクトの解放処理
	CObject::ReleaseAll();
}

//============================================================================
// 更新処理
//============================================================================
void CScene::Update()
{
	//ゲーム中のみ
	if (GetMode() == MODE::GAME)
	{
		//タイマーの更新処理
		CManager::GetTimer()->Update();
	}

	// フェードの更新
	CFade::GetInstance()->Update();

#ifdef _DEBUG
	// 現在のシーンのクラスを表示
	/* typeid(*this)だとバグっちゃう */
	std::string Name{ typeid(*CManager::GetScene()).name() };
	CRenderer::GetInstance()->SetDebugString("現在のシーンのクラス -> " + Name);
#endif	// _DEBUG
}

//============================================================================
// 描画処理
//============================================================================
void CScene::Draw()
{
	// フェードの描画
	CFade::GetInstance()->Draw();
}

//============================================================================
// モードを取得
//============================================================================
CScene::MODE CScene::GetMode()
{
	return m_mode;
}

//============================================================================
// 生成
//============================================================================
CScene* CScene::Create(MODE mode)
{
	// 基底クラスのポインタを用意
	CScene* pScene = nullptr;

	switch (mode)
	{
	case CScene::MODE::TITLE:
		pScene = DBG_NEW CTitle;
		pScene->m_mode = MODE::TITLE;
		break;

	case CScene::MODE::TUTORIAL:
		pScene = DBG_NEW CTutorial;
		pScene->m_mode = MODE::TUTORIAL;
		break;

	case CScene::MODE::GAME:
		pScene = DBG_NEW CGame;
		pScene->m_mode = MODE::GAME;
		break;

	case CScene::MODE::RESULT_GAMECLEAR:
		pScene = DBG_NEW CResult;
		pScene->m_mode = MODE::RESULT_GAMECLEAR;
		break;

	case CScene::MODE::RESULT_GAMEOVER:
		pScene = DBG_NEW CResult;
		pScene->m_mode = MODE::RESULT_GAMEOVER;
		break;

	default:
		assert(false);
		break;
	}

	if (pScene == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// 初期設定
	/* ここで初期化をする -> シーンのInitでモードに応じた生成のために、ダングリングポインタにアクセスする -> エラー */
	//pScene->Init();

	// シーン切り替えのたびにカメラリセット
	CManager::GetCamera()->Init();

	return pScene;
}