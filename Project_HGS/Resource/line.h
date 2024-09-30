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

	void SetMove(const D3DXVECTOR3& inMove);	// 移動量設定
	const D3DXVECTOR3& GetMove() const;			// 移動量取得

	static CLine* Create();	// 生成

private:
	CLine(const CLine&) = delete;
	void operator=(const CLine&) = delete;

	D3DXVECTOR3 m_StartPos;	// 始点
	D3DXVECTOR3 m_EndPos;	// 終点
};
