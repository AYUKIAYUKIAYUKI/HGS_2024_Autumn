//============================================================================
// 
// 軌跡、ヘッダファイル [trajectory.h]
// Author : 久保市篤武
// 
//============================================================================

#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"// 2Dオブジェクト管理ヘッダーファイル

//****************************************************
// タイマークラス
//****************************************************
class CTrajectory : public CObject_2D
{
public:

	CTrajectory(int nPriority = static_cast<int>(LAYER::UI));// コンストラクタ
	~CTrajectory() override;// デストラクタ

	HRESULT Init() override;// 初期設定
	void Uninit() override;// 終了処理
	void Update() override;// 更新処理
	void Draw() override;// 描画処理
	static CTrajectory* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);// 生成処理
};

#endif // _TIMERNUMBER_H_
