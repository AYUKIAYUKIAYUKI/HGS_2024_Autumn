//============================================================================
// 
// ツイスト邪魔物、ヘッダファイル [obstacle_twist.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBSTACLE_TWIST_H_
#define _OBSTACLE_TWIST_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "obstacle.h"

//****************************************************
// ツイスト邪魔物クラス
//****************************************************
class CObstacle_Twist : public CObstacle
{
public:

	CObstacle_Twist(int nRouteStyle, int nPriority = static_cast<int>(LAYER::NONE));	// コンストラクタ
	~CObstacle_Twist() override;														// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3 GetVelocity();				// 移動量を取得
	void SetVelocity(D3DXVECTOR3 Velocity);	// 移動量を設定

	static CObstacle_Twist* Create(int nRouteStyle);	// 生成

private:

	void Move();	// 移動

	int m_nRouteStyle;			// 移動スタイル
	D3DXVECTOR3 m_Velocity;		// 移動量
	int m_nCast;				// キャスト時間
	D3DXVECTOR3 m_TwistTarget;	// ツイスト目標
};

#endif	// _OBSTACLE_TWIST_H_