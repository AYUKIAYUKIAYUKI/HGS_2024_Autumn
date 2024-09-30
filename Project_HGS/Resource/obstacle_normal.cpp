//============================================================================
// 
// ノーマル邪魔物 [obstacle_normal.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "obstacle_normal.h"

//============================================================================
// コンストラクタ
//============================================================================
CObstacle_Normal::CObstacle_Normal(int nRouteStyle, int nPriority) :
	CObstacle{ nPriority },
	m_nRouteStyle{ nRouteStyle },
	m_Velocity{ 0.0f, 0.0f, 0.0f }
{
	SetCol({ 0.0f, 0.0f, 1.0f, 1.0f });
}

//============================================================================
// デストラクタ
//============================================================================
CObstacle_Normal::~CObstacle_Normal()
{
	
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CObstacle_Normal::Init()
{
	float fAdder{ 1.0f };

	// サイズ設定
	SetSize({ 15.0f, 15.0f, 0.0f });

	switch (m_nRouteStyle)
	{
	//	// 上
	//case 0:
	//	SetPos({ SPAN_X, -INITSPAN, 0.0f });
	//	m_Velocity = { 0.0f, 1.0f, 0.0f, };
	//	break;
	//case 1:
	//	SetPos({ SCREEN_WIDTH - SPAN_X, -INITSPAN, 0.0f });
	//	m_Velocity = { 0.0f, 1.0f, 0.0f, };
	//	break;

	//	// 下
	//case 4:
	//	SetPos({ SCREEN_WIDTH - SPAN_X, SCREEN_HEIGHT + INITSPAN, 0.0f });
	//	m_Velocity = { 0.0f, -1.0f, 0.0f, };
	//	break;
	//case 5:
	//	SetPos({ SPAN_X, SCREEN_HEIGHT + INITSPAN, 0.0f });
	//	m_Velocity = { 0.0f, -1.0f, 0.0f, };
	//	break;

		// 右
	case 0:
		SetPos({ SCREEN_WIDTH + INITSPAN, SPAN_Y, 0.0f });
		m_Velocity = { -fAdder, 0.0f, 0.0f, };
		break;
	case 1:
		SetPos({ SCREEN_WIDTH + INITSPAN, SCREEN_HEIGHT - SPAN_Y, 0.0f });
		m_Velocity = { -fAdder, 0.0f, 0.0f, };
		break;

		// 左
	case 2:
		SetPos({ -INITSPAN, SPAN_Y, 0.0f  });
		m_Velocity = { fAdder, 0.0f, 0.0f, };
		break;
	case 3:
		SetPos({ -INITSPAN, SCREEN_HEIGHT - SPAN_Y, 0.0f });
		m_Velocity = { fAdder, 0.0f, 0.0f, };
		break;

	default:
		assert(false && "移動スタイル指定エラー");
		break;
	}

	// 基底クラスの初期設定
	HRESULT hr{ CObstacle::Init() };

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CObstacle_Normal::Uninit()
{
	// 基底クラスの終了処理
	CObstacle::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CObstacle_Normal::Update()
{
	// 移動
	Move();

	// 基底クラスの更新処理
	CObstacle::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CObstacle_Normal::Draw()
{
	// 基底クラスの描画処理
	CObstacle::Draw();
}

//============================================================================
// 移動量を取得
//============================================================================
D3DXVECTOR3 CObstacle_Normal::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// 移動量を設定
//============================================================================
void CObstacle_Normal::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// 生成
//============================================================================
CObstacle_Normal* CObstacle_Normal::Create(int nRouteStyle)
{
	// インスタンス生成
	CObstacle_Normal* pInstance{ DBG_NEW CObstacle_Normal(nRouteStyle, static_cast<int>(CObject::LAYER::MIDDLE)) };

	// これはオブジェクトで扱われるタイプの設定
	pInstance->SetType(CObject::TYPE::NONE);

	// これは邪魔物スタイルの設定
	pInstance->SetStyle(STYLE::NORMAL);

	// CObject2D -> CObstacle 初期設定
	pInstance->Init();

	return pInstance;
}

//============================================================================
// 移動
//============================================================================
void CObstacle_Normal::Move()
{
	// 移動
	D3DXVECTOR3 NewPos{ GetPos() };
	NewPos += m_Velocity;
	SetPos(NewPos);
}