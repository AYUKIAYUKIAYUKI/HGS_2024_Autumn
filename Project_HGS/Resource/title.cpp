//============================================================================
// 
// タイトル [title.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "title.h"

// インプット取得用
#include "manager.h"

#include "renderer.h"

/* test */
#include "object_2D.h"
#include "texture_manager.h"
#include <bg.h>

//============================================================================
// コンストラクタ
//============================================================================
CTitle::CTitle()
{

}

//============================================================================
// デストラクタ
//============================================================================
CTitle::~CTitle()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CTitle::Init()
{
	// 基底クラスの初期設定
	HRESULT hr{ CScene::Init() };

	/* 仮 */
	CObject_2D* pTest{ CObject_2D::Create() };
	pTest->BindTex(CTexture_Manager::TYPE::TEST1);
	pTest->SetPos({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f });
	pTest->SetSize({ 30.0f, 30.0f, 0.0f });

	//背景生成
	CBg::Create();

	// 全てのサウンドを停止
	//CSound::GetInstance()->Stop();

	// BGMをかける
	//CSound::GetInstance()->Play(CSound::LABEL::TEST);

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CTitle::Uninit()
{
	// 基底クラスの終了処理
	CScene::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CTitle::Update()
{
	// 基底クラスの更新処理
	CScene::Update();

	// ゲーム画面へ
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CFade::SetFade(CScene::MODE::GAME);
	}
}

//============================================================================
// 描画処理
//============================================================================
void CTitle::Draw()
{
	// 基底クラスの描画処理
	CScene::Draw();
}