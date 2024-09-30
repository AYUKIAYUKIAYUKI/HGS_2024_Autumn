//============================================================================
// 
// 背景、ヘッダファイル [bg.h]
// Author : 久保市篤武
// 
//============================================================================

#ifndef _BG_H_
#define _BG_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"// 2Dオブジェクト管理ヘッダーファイル

//****************************************************
// タイマークラス
//****************************************************
class CBg : public CObject_2D
{
public:

	CBg(int nPriority = static_cast<int>(LAYER::BG));// コンストラクタ
	~CBg() override;// デストラクタ

	HRESULT Init() override;// 初期設定
	void Uninit() override;// 終了処理
	void Update() override;// 更新処理
	void Draw() override;// 描画処理
	static CBg* Create();// 生成処理

private:
	static inline const D3DXVECTOR3 CREATE_SIZE = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5, 0.0f };// 生成サイズ
	static inline const D3DXVECTOR3 CREATE_POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f };// 生成位置
};

#endif // _BG_H_

