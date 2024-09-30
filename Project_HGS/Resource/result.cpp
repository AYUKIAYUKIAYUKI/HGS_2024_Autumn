//============================================================================
// 
// リザルト [result.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "result.h"
#include "fade.h"

// インプット取得用
#include "manager.h"

/* test */
#include "object_3D.h"
#include "texture_manager.h"
#include <bg.h>

//============================================================================
// コンストラクタ
//============================================================================
CResult::CResult()
{

}

//============================================================================
// デストラクタ
//============================================================================
CResult::~CResult()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CResult::Init()
{	
	// 基底クラスの初期設定
	HRESULT hr{ CScene::Init() };

	// 全てのサウンドを停止
	//CSound::GetInstance()->Stop();

	// BGMをかける
	//CSound::GetInstance()->Play(CSound::LABEL::TEST);

	//背景生成
	CBg* pBg{ CBg::Create() };
	if (CScene::GetMode() == MODE::RESULT_GAMECLEAR)
	{
		pBg->BindTex(CTexture_Manager::TYPE::RESULT_GAMECLEAR);
	}
	else if (CScene::GetMode() == MODE::RESULT_GAMEOVER)
	{
		pBg->BindTex(CTexture_Manager::TYPE::RESULT_GAMEOVER);
	}
	

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CResult::Uninit()
{
	// 基底クラスの終了処理
	CScene::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CResult::Update()
{
	// 基底クラスの更新処理
	CScene::Update();

	// タイトル画面へ
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CFade::SetFade(CScene::MODE::TITLE);
	}
}

//============================================================================
// 描画処理
//============================================================================
void CResult::Draw()
{
	// 基底クラスの描画処理
	CScene::Draw();
}