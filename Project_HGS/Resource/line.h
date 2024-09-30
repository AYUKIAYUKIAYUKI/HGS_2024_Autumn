//--------------------------------------------------------------------------------
// 
// プレイヤーが移動できる線 [line.h]
// Author: Taito Jin
// 
//--------------------------------------------------------------------------------
#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"

//---------------------------------------------------
// using 宣言
//---------------------------------------------------
using namespace HGSAutumn240930;

//****************************************************
// プレイヤーが移動できる線のクラス
//****************************************************
class CLine : public CObject_2D
{
public:
	CLine(int nPriority = static_cast<int>(LAYER::BACK));	// コンストラクタ
	~CLine() override = default;							// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	void SetLineSegment2D(const Collision::LineSegment2D& inSegment) { m_LineSegment2D = inSegment; }	// 線の設定
	const Collision::LineSegment2D& GetLineSegment2D() const { return m_LineSegment2D; };				// 線の取得

	// 生成
	static CLine* Create(
		const D3DXVECTOR3& inPos,		// 位置
		const D3DXVECTOR3& inSize,		// サイズ
		const D3DXVECTOR2& inStartPos, 	// 始点
		const D3DXVECTOR2& inEndPos);	// 終点

private:
	CLine(const CLine&) = delete;
	void operator=(const CLine&) = delete;

	Collision::LineSegment2D m_LineSegment2D;	// 線
};
