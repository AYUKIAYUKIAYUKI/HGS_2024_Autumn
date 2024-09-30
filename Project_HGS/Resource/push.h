//============================================================================
// 
// PUSHUI、ヘッダファイル [logo.h]
// Author : 久保市篤武
// 
//============================================================================

#ifndef _PUSH_H_
#define _PUSH_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"// 2Dオブジェクト管理ヘッダーファイル

//****************************************************
// タイマークラス
//****************************************************
class CPush : public CObject_2D
{
public:

	CPush(int nPriority = static_cast<int>(LAYER::UI));// コンストラクタ
	~CPush() override;// デストラクタ

	HRESULT Init() override;// 初期設定
	void Uninit() override;// 終了処理
	void Update() override;// 更新処理
	void Draw() override;// 描画処理
	static CPush* Create();// 生成処理

private:
	static inline const D3DXVECTOR3 CREATE_SIZE = { 300.0f, 60.0f, 0.0f };// 生成サイズ
	static inline const D3DXVECTOR3 CREATE_POS = { SCREEN_WIDTH * 0.5f, 600.0f, 0.0f };// 生成位置

	const float STAND_SPEED = 0.02f;//待機中の点滅速度
	bool m_bLightUp;//ライトアップフラグ
};

#endif // _PUSH_H_

