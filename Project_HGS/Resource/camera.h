﻿//============================================================================
//
// カメラ、ヘッダファイル [camera.h]
// Author : 福田歩希
//
//============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_	// 二重インクルード防止

//****************************************************
// カメラクラス
//****************************************************
class CCamera
{
public:

	CCamera();	// デフォルトコンストラクタ
	~CCamera();	// デストラクタ

	HRESULT Init();		// 初期設定
	void Update();		// 更新処理
	void SetCamera();	// カメラをセット
	
	D3DXVECTOR3 GetPos();			// 位置を取得
	void SetPos(D3DXVECTOR3 pos);	// 位置を設定

	D3DXVECTOR3 GetPosTarget();					// 目標位置を取得
	void SetPosTarget(D3DXVECTOR3 posTarget);	// 目標位置を設定

	D3DXVECTOR3 GetRot();	// 向きを取得

	float GetDistance();				// 間距離を取得
	void SetDistance(float fDistance);	// 間距離を設定

private:

	void Control();				// カメラ操作
	void Rotation();			// 回転
	void Translation();			// 移動
	void RestrictYaw();			// ヨー角の範囲を制限
	void RestrictPitch();		// ピッチ角の範囲を制限
	void CalcPosV();			// 視点位置を算出
	void CalcPosR();			// 注視点位置を算出
	void CalcMtxProjection();	// プロジェクション行列計算
	void CalcMtxView();			// ビュー行列計算

	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_posTarget;					// 目標位置
	D3DXVECTOR3 m_posV;							// 視点位置
	D3DXVECTOR3 m_posTargetV;					// 目標視点位置
	D3DXVECTOR3 m_posR;							// 注視点位置
	D3DXVECTOR3 m_posTargetR;					// 目標注視点位置
	D3DXVECTOR3 m_rot;							// 向き
	D3DXVECTOR3 m_rotTarget;					// 目標向き
	float m_fDistance;							// 視点 -> 注視点間の距離
	D3DXVECTOR3 m_vecU;							// 上方向ベクトル
	D3DXMATRIX m_mtxProjection;					// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;						// ビューマトリックス
	float m_fAdjust;							// 俯瞰度合
};

#endif // _CAMERA_H_