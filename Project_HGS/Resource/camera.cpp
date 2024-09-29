//============================================================================
// 
// カメラ [camera.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "camera.h"
#include "utility.h"

// インプット取得用
#include "manager.h"

// デバイス取得用
#include "renderer.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CCamera::CCamera() :
	m_pos{ 0.0f, 0.0f, 0.0f },
	m_posTarget{ 0.0f, 0.0f, 0.0f },
	m_posV{ 0.0f, 0.0f, 0.0f },
	m_posTargetV{ 0.0f, 0.0f, 0.0f },
	m_posR{ 0.0f, 0.0f, 0.0f },
	m_posTargetR{ 0.0f, 0.0f, 0.0f },
	m_rot{ 0.0f, 0.0f, 0.0f },
	m_rotTarget{ 0.0f, 0.0f, 0.0f },
	m_fDistance{ 0.0f },
	m_vecU{ 0.0f, 1.0f, 0.0f },
	m_fAdjust{ 0.0f }
{
	D3DXMatrixIdentity(&m_mtxProjection);	// プロジェクションマトリックス
	D3DXMatrixIdentity(&m_mtxView);			// ビューマトリックス
}

//============================================================================
// デストラクタ
//============================================================================
CCamera::~CCamera()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CCamera::Init()
{
	m_fDistance = 300.0f;

	return S_OK;
}

//============================================================================
// 更新処理
//============================================================================
void CCamera::Update()
{
	// カメラ操作
	Control();

	// 回転
	Rotation();

	// 移動
	Translation();

	// 視点位置を算出
	CalcPosV();

	// 注視点位置を算出
	CalcPosR();
}

//============================================================================
// カメラをセット
//============================================================================
void CCamera::SetCamera()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// 画面バッファクリア
	pDev->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	// プロジェクション行列を計算
	CalcMtxProjection();
	
	// ビュー行列を計算
	CalcMtxView();
}

//============================================================================
// 位置を取得
//============================================================================
D3DXVECTOR3 CCamera::GetPos()
{
	return m_pos;
}

//============================================================================
// 位置を設定
//============================================================================
void CCamera::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================================================
// 目標位置を取得
//============================================================================
D3DXVECTOR3 CCamera::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// 目標位置を設定
//============================================================================
void CCamera::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// 向きを取得
//============================================================================
D3DXVECTOR3 CCamera::GetRot()
{
	return m_rot;
}

//============================================================================
// 間距離を取得
//============================================================================
float CCamera::GetDistance()
{
	return m_fDistance;
}

//============================================================================
// 間距離を設定
//============================================================================
void CCamera::SetDistance(float fDistance)
{
	m_fDistance = fDistance;
}

//============================================================================
// カメラ操作
//============================================================================
void CCamera::Control()
{
	// ズームイン / アウト
	if (CManager::GetKeyboard()->GetPress(DIK_AT) && m_fDistance > 10.0f)
	{
		m_fDistance -= 10.0f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_COLON))
	{
		m_fDistance += 10.0f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_BACKSLASH))
	{
		// 距離間リセット
		m_fDistance = 200.0f;
	}

	// 左右
	if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))
	{
		m_rotTarget.y += 0.02f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_LEFT))
	{
		m_rotTarget.y -= 0.02f;
	}

	// 上下
	if (CManager::GetKeyboard()->GetPress(DIK_UP))
	{
		m_rotTarget.x += 0.02f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_DOWN))
	{
		m_rotTarget.x -= 0.02f;
	}
}

//============================================================================
// 回転
//============================================================================
void CCamera::Rotation()
{
	// 回転量減衰
	m_rotTarget *= 0.8f;

	// 回転量反映
	m_rot += m_rotTarget * 0.5f;

	// ヨー角の範囲を制限
	RestrictYaw();

	// ピッチ角の範囲を制限
	RestrictPitch();
}

//============================================================================
// 移動
//============================================================================
void CCamera::Translation()
{
	// 追従度合
	float fTracking = 0.25f;

	// 移動量反映
	// posTargetに値を設定していない場合は数値がおかしくなります
	m_pos += (m_posTarget - m_pos) * fTracking;
}

//============================================================================
// ヨー角の範囲を制限
//============================================================================
void CCamera::RestrictYaw()
{
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}
}

//============================================================================
// ピッチ角の範囲を制限
//============================================================================
void CCamera::RestrictPitch()
{
	// 0 ～ 0.5
	float fCoeff{ 0.48f };

	if (m_rot.x + m_rotTarget.x > D3DX_PI * fCoeff)
	{
		m_rot.x = D3DX_PI * fCoeff;
	}
	else if (m_rot.x + m_rotTarget.x < -D3DX_PI * fCoeff)
	{
		m_rot.x = -D3DX_PI * fCoeff;
	}
}

//============================================================================
// 視点位置を算出
//============================================================================
void CCamera::CalcPosV()
{
	// 視点は対象物の後方に
	m_posV =
	{
		m_pos.x - (sinf(m_rot.y) * cosf(m_rot.x) * (m_fDistance)),
		m_pos.y - (sinf(m_rot.x) * (m_fDistance)),
		m_pos.z - (cosf(m_rot.y) * cosf(m_rot.x) * (m_fDistance))
	};
}

//============================================================================
// 注視点位置を算出
//============================================================================
void CCamera::CalcPosR()
{
	// 注視点を対象物の前方に
	m_posR =
	{
		m_pos.x + (sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance),
		m_pos.y + (sinf(m_rot.x) * m_fDistance),
		m_pos.z + (cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance)
	};
}

//============================================================================
// プロジェクション行列計算
//============================================================================
void CCamera::CalcMtxProjection()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// プロジェクション行列の初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクション行列を生成
#if 1
	// 透視投影
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		5000.0f);	
#else
	// 平行投影
	D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_WIDTH * 0.25f,
		(float)SCREEN_HEIGHT * 0.25f,
		10.0f,
		5000.0f);
#endif

	// プロジェクション行列の設定
	pDev->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}

//============================================================================
// ビュー行列計算
//============================================================================
void CCamera::CalcMtxView()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// 視点位置の調整用
	D3DXVECTOR3 posV = m_posV;
	D3DXVECTOR3 posR = m_posR;

	// カメラを俯瞰気味に
	posV.y += m_fAdjust;

	// ビューマトリックスの生成
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,
		&posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDev->SetTransform(D3DTS_VIEW,
		&m_mtxView);
}