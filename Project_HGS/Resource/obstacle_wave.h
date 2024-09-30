//============================================================================
// 
// ウェーブ邪魔物、ヘッダファイル [obstacle_wave.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBSTACLE_WAVE_H_
#define _OBSTACLE_WAVE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "obstacle.h"

//****************************************************
// ターン邪魔物クラス
//****************************************************
class CObstacle_Wave : public CObstacle
{
public:

	CObstacle_Wave(int nRouteStyle, int nPriority = static_cast<int>(LAYER::NONE));	// コンストラクタ
	~CObstacle_Wave() override;														// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3 GetVelocity();				// 移動量を取得
	void SetVelocity(D3DXVECTOR3 Velocity);	// 移動量を設定

	static CObstacle_Wave* Create(int nRouteStyle);	// 生成

private:

	void Move();	// 移動

	int m_nRouteStyle;			// 移動スタイル
	D3DXVECTOR3 m_Velocity;		// 移動量
	float m_fCoeffWave;			// 波打ち係数
	D3DXVECTOR3 m_WaveVelocity;	// 波打ち移動量
};

#endif	// _OBSTACLE_WAVE_H_