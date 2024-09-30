//============================================================================
// 
// タイマー表示、ヘッダファイル [timernumber.h]
// Author : 久保市篤武
// 
//============================================================================

#ifndef _TIMERNUMBER_H_
#define _TIMERNUMBER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"// 2Dオブジェクト管理ヘッダーファイル

//****************************************************
// タイマークラス
//****************************************************
class CTimerNumber : public CObject_2D
{
public:

	CTimerNumber(int nPriority = static_cast<int>(LAYER::UI));// コンストラクタ
	~CTimerNumber() override;// デストラクタ

	HRESULT Init() override;// 初期設定
	void Uninit() override;// 終了処理
	void Update() override;// 更新処理
	void Draw() override;// 描画処理
	static CTimerNumber* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nIdx);// 生成処理

private:

	void SetTimerNumberPos(D3DXVECTOR3 pos);// 座標設定
	void SetIdx(int nIdx) { m_nIdx = nIdx; }// ID設定

	int m_nIdx;// ID
};

#endif // _TIMERNUMBER_H_
