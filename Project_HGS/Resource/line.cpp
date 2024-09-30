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
	, m_LineSegment2D{}
	, m_bIsUnderPlayer{ false }
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
CLine* CLine::Create(
		const D3DXVECTOR3& inPos,		// 位置
		const D3DXVECTOR3& inSize,		// サイズ
		const D3DXVECTOR2& inStartPos, 	// 始点
		const D3DXVECTOR2& inEndPos,	// 終点
		const D3DXCOLOR& inCol)			// 色
{
	CLine* pLine = DBG_NEW CLine{};

	// 生成出来ていたら初期設定
	if (pLine != nullptr)
	{
		pLine->Init();
	}

	pLine->SetPos(inPos);
	pLine->SetSize(inSize);
	pLine->SetLineSegment2D({ inStartPos, inEndPos });
	pLine->SetCol(inCol);

	return pLine;
}
