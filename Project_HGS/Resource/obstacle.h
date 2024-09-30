//============================================================================
// 
// 邪魔物、ヘッダファイル [obstacle.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"

//****************************************************
// 邪魔物クラス
//****************************************************
class CObstacle : public CObject_2D
{
public:

	//****************************************************
	// 邪魔物スタイル
	//****************************************************
	enum class STYLE
	{
		NONE = 0,	// バグ
		NORMAL,		// ノーマル
		SPEEDY,		// スピーディ
		TURN,		// ターン
		WAVE,		// ウェーブ
		TWIST,		// ツイスト
		LONG,		// ロング
		MAX,
	};

	CObstacle(int nPriority = static_cast<int>(LAYER::NONE));	// コンストラクタ
	~CObstacle() override;										// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	void SetStyle(STYLE style);	// 邪魔物スタイルを設定
	STYLE GetStyle();			// 邪魔物スタイルを取得

	D3DXVECTOR3 GetPosTarget();					// 目標座標を取得
	void SetPosTarget(D3DXVECTOR3 PosTarget);	// 目標座標を設定

	D3DXVECTOR3 GetRotTarget();					// 目標向きを取得
	void SetRotTarget(D3DXVECTOR3 RotTarget);	// 目標向きを設定

	D3DXVECTOR3 GetSizeTarget();				// 目標サイズを取得
	void SetSizeTarget(D3DXVECTOR3 SizeTarget);	// 目標サイズを設定

	D3DXCOLOR GetColTarget();				// 目標色を取得
	void SetColTarget(D3DXCOLOR ColTarget);	// 目標色を設定

protected:

	static const float INITSPAN;
	static const float SPAN_X;
	static const float SPAN_Y;

private:

	void DeleteCheck();		// 消滅判定

	STYLE m_Style;				// 邪魔物スタイル
	D3DXVECTOR3 m_PosTarget;	// 目標座標
	D3DXVECTOR3 m_RotTarget;	// 目標向き
	D3DXVECTOR3 m_SizeTarget;	// 目標サイズ
	D3DXCOLOR m_ColTarget;		// 目標色
};

#endif // _OBSTACLE_H_