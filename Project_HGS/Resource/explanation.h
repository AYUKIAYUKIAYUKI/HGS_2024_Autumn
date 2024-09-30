//============================================================================
// 
// 操作説明、ヘッダファイル [explanation.h]
// Author : 久保市篤武
// 
//============================================================================

#ifndef _EXPLANATION_H_
#define _EXPLANATION_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"// 2Dオブジェクト管理ヘッダーファイル

//****************************************************
// タイマークラス
//****************************************************
class CExplanation : public CObject_2D
{
public:

	CExplanation(int nPriority = static_cast<int>(LAYER::UI));// コンストラクタ
	~CExplanation() override;// デストラクタ

	HRESULT Init() override;// 初期設定
	void Uninit() override;// 終了処理
	void Update() override;// 更新処理
	void Draw() override;// 描画処理
	static CExplanation* Create();// 生成処理

private:
	static inline const D3DXVECTOR3 CREATE_SIZE = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f };// 生成サイズ
	static inline const D3DXVECTOR3 CREATE_POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f };// 生成位置
};

#endif // _TIMERNUMBER_H_
