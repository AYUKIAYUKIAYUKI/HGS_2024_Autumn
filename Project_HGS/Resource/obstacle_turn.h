//============================================================================
// 
// ターン邪魔物、ヘッダファイル [obstacle_turn.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBSTACLE_TURN_H_
#define _OBSTACLE_TURN_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "obstacle.h"

//****************************************************
// ターン邪魔物クラス
//****************************************************
class CObstacle_Turn : public CObstacle
{
public:

	CObstacle_Turn(int nRouteStyle, int nPriority = static_cast<int>(LAYER::NONE));	// コンストラクタ
	~CObstacle_Turn() override;														// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3 GetVelocity();				// 移動量を取得
	void SetVelocity(D3DXVECTOR3 Velocity);	// 移動量を設定

	static CObstacle_Turn* Create(int nRouteStyle);	// 生成

private:

	void Move();	// 移動

	int m_nRouteStyle;		// 移動スタイル
	D3DXVECTOR3 m_Velocity;	// 移動量
	int m_nCast;			// キャスト時間
	D3DXVECTOR3 m_Reverse;	// 反転量
};

#endif	// _OBSTACLE_H_