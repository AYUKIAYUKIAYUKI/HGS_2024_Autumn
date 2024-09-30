//--------------------------------------------------------------------------------
// 
// プレイヤーが移動できる線 [line.cpp]
// Author: Taito Jin
// 
//--------------------------------------------------------------------------------

//---------------------------------------------------
// インクルード
//---------------------------------------------------
#include "line.h"

//============================================================================
// コンストラクタ
//============================================================================
CLine::CLine(int nPriority)
	: CObject_2D{ nPriority }
{
	// DO_NOTHING
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CLine::Init()
{
	// 親クラスの処理
	HRESULT hr = CObject_2D::Init();
	if (FAILED(hr))
	{
		return E_FAIL;
	}


	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CLine::Uninit()
{
	// 親クラスの処理
	CObject_2D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CLine::Update()
{
	// 親クラスの処理
	CObject_2D::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CLine::Draw()
{
	// 親クラスの処理
	CObject_2D::Draw();
}

//============================================================================
// 生成
//============================================================================
CLine* CLine::Create()
{
	CLine* pLine = DBG_NEW CLine{};

	// 生成出来ていたら初期設定
	if (pLine != nullptr)
	{
		pLine->Init();
	}

	return pLine;
}