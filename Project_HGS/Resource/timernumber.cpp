//============================================================================
// 
// タイマー表示 [timernumber.cpp]
// Author : 久保市篤武
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "timernumber.h"//タイマーナンバーヘッダーファイル
#include "timer.h"//タイマー管理ヘッダーファイル
#include <manager.h>//マネージャーヘッダーファイル

//============================================================================
// コンストラクタ
//============================================================================
CTimerNumber::CTimerNumber(int nPriority) : CObject_2D{ nPriority }
{
}

//============================================================================
// デストラクタ
//============================================================================
CTimerNumber::~CTimerNumber()
{
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CTimerNumber::Init()
{
	// テクスチャ設定
	BindTex(CTexture_Manager::TYPE::TIMER);

	// パラメータ設定
	SetTexWidth(0.1f);// 横のテクスチャ分割数 

	// 2Dオブジェクト初期設定
	if (FAILED(CObject_2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CTimerNumber::Uninit()
{
	// 2Dオブジェクト終了処理
	CObject_2D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CTimerNumber::Update()
{
	// ローカル変数宣言
	int nTimer = CManager::GetTimer()->GetTime();// 現在のタイマー
	int nMulti = 1;// 各桁の倍数

	// IDに合わせて倍数を求める
	for (int nCntTime = 0; nCntTime < m_nIdx + 1; nCntTime++)
	{
		nMulti *= 10;
	}

	// 該当する桁の数字を求める
	int nPosTex = (nTimer % nMulti) / (nMulti / 10);

	// 現在のテクスチャ横分割幅設定
	SetNowPatternU(nPosTex);

	//残り時間に合わせて赤色にしていく
	if (nTimer <= START_COL_CHANGE)
	{
		// 現在のカラー情報を取得
		D3DXCOLOR col = GetCol();

		//緑と青色を薄くしていく
		col.g = static_cast<float>(nTimer) / static_cast<float>(START_COL_CHANGE);
		col.b = static_cast<float>(nTimer) / static_cast<float>(START_COL_CHANGE);

		// カラー情報を設定
		SetCol(col);
	}

	// 2Dオブジェクト更新処理
	CObject_2D::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CTimerNumber::Draw()
{
	// 2Dオブジェクト描画処理
	CObject_2D::Draw();
}

//============================================================================
// 生成処理
//============================================================================
CTimerNumber* CTimerNumber::Create(int nIdx)
{
	// メモリを動的確保
	CTimerNumber* pTimeNumber = new CTimerNumber();

	//パラメータ設定
	pTimeNumber->SetIdx(nIdx);// ID
	pTimeNumber->SetSize(CREATE_SIZE);// サイズ
	pTimeNumber->SetTimerNumberPos(CREATE_POS);// 座標
	pTimeNumber->SetTexWidth(10.0f);// 横のテクスチャ分割数

	//初期化処理
	pTimeNumber->Init();

	return nullptr;
}

//============================================================================
// 生成処理Alt
//============================================================================
CTimerNumber* CTimerNumber::Create(int nIdx, int nNum)
{
	nNum = nNum;	// 警告回避用無駄処理

	// メモリを動的確保
	CTimerNumber* pTimeNumber = new CTimerNumber();

	//パラメータ設定
	pTimeNumber->SetIdx(nIdx);// ID
	pTimeNumber->SetSize(CREATE_SIZE * 2.5f);// サイズ

	pTimeNumber->SetPos({ (SCREEN_WIDTH * 0.75f) - (nIdx * 250.0f), (SCREEN_HEIGHT * 0.5f), 0.0f });

	pTimeNumber->SetTexWidth(10.0f);// 横のテクスチャ分割数

	//初期化処理
	pTimeNumber->Init();

	return nullptr;
}

//============================================================================
// 座標設定
//============================================================================
void CTimerNumber::SetTimerNumberPos(D3DXVECTOR3 pos)
{
	SetPos({ pos.x - m_nIdx * (GetSize().x + 25.0f), pos.y, pos.z });
}
