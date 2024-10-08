//============================================================================
// 
// タイマー [timer.cpp]
// Author : 久保市篤武
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "timer.h"

//============================================================================
// コンストラクタ
//============================================================================
CTimer::CTimer()
{
	//メンバ変数初期化
	m_nCntFrame = 0;	// フレームカウンタ
	m_nTimer = 60;		// タイマー

	// ローカル変数宣言
	int nNum = m_nTimer;	// 現在のスコアを保存
	int nDigit = 0;			// 桁数

	// 桁数を求める
	while (nNum != 0)
	{
		nNum /= 10;	// 値を10で割る
		nDigit++;	// 桁数を加算
	}

	// 桁数が0の場合
	if (nDigit == 0)
	{
		// 桁数を1に調整
		nDigit = 1;
	}

	// 桁数を反映
	m_nDigit = nDigit;
}

//============================================================================
// デストラクタ
//============================================================================
CTimer::~CTimer()
{
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CTimer::Init()
{
	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CTimer::Uninit()
{
}

//============================================================================
// 更新処理
//============================================================================
void CTimer::Update()
{
	// フレームカウンタ加算
	m_nCntFrame++;

	// フレームカウントが60に達した場合
	if (m_nCntFrame == 60)
	{
		// タイマーを1秒減らす
		m_nTimer--;

		// フレームカウンタをリセット
		m_nCntFrame = 0;

		// ローカル変数宣言
		int nNum = m_nTimer;//現在のスコアを保存
		int nDigit = 0;//桁数

		// 桁数を求める
		while (nNum != 0)
		{
			nNum /= 10;//スコアを10で割る
			nDigit++;//桁数を加算
		}

		// 桁数が0の場合
		if (nDigit == 0)
		{
			//桁数を1に調整
			nDigit = 1;
		}

		// 桁数を反映
		m_nDigit = nDigit;
	}
}

//============================================================================
// リセット
//============================================================================
void CTimer::Reset()
{

	//メンバ変数初期化
	m_nCntFrame = 0;	// フレームカウンタ
	m_nTimer = 60;		// タイマー

	// ローカル変数宣言
	int nNum = m_nTimer;	// 現在のスコアを保存
	int nDigit = 0;			// 桁数

	// 桁数を求める
	while (nNum != 0)
	{
		nNum /= 10;	// 値を10で割る
		nDigit++;	// 桁数を加算
	}

	// 桁数が0の場合
	if (nDigit == 0)
	{
		// 桁数を1に調整
		nDigit = 1;
	}

	// 桁数を反映
	m_nDigit = nDigit;
}
