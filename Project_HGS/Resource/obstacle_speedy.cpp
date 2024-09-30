//============================================================================
// 
// スピーディ邪魔物 [obstacle_speedy.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "obstacle_speedy.h"

//============================================================================
// コンストラクタ
//============================================================================
CObstacle_Speedy::CObstacle_Speedy(int nRouteStyle, int nPriority) :
	CObstacle{ nPriority },
	m_nRouteStyle{ nRouteStyle },
	m_Velocity{ 0.0f, 0.0f, 0.0f, }
{
	SetCol({ 1.0f, 0.0f, 1.0f, 1.0f });
}

//============================================================================
// デストラクタ
//============================================================================
CObstacle_Speedy::~CObstacle_Speedy()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CObstacle_Speedy::Init()
{
	float fAdder{ 5.0f };

	// サイズ設定
	SetSize({ 15.0f, 15.0f, 0.0f });

	switch (m_nRouteStyle)
	{
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
		SetPos({ -INITSPAN, SPAN_Y, 0.0f });
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
void CObstacle_Speedy::Uninit()
{
	// 基底クラスの終了処理
	CObstacle::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CObstacle_Speedy::Update()
{
	// 移動
	Move();

	// 基底クラスの更新処理
	CObstacle::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CObstacle_Speedy::Draw()
{
	// 基底クラスの描画処理
	CObstacle::Draw();
}

//============================================================================
// 移動量を取得
//============================================================================
D3DXVECTOR3 CObstacle_Speedy::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// 移動量を設定
//============================================================================
void CObstacle_Speedy::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// 生成
//============================================================================
CObstacle_Speedy* CObstacle_Speedy::Create(int nRouteStyle)
{
	// インスタンス生成
	CObstacle_Speedy* pInstance{ DBG_NEW CObstacle_Speedy(nRouteStyle, static_cast<int>(CObject::LAYER::MIDDLE)) };

	// これはオブジェクトで扱われるタイプの設定
	pInstance->SetType(CObject::TYPE::NONE);

	// これは邪魔物スタイルの設定
	pInstance->SetStyle(STYLE::SPEEDY);

	// CObject2D -> CObstacle 初期設定
	pInstance->Init();

	return pInstance;
}

//============================================================================
// 移動
//============================================================================
void CObstacle_Speedy::Move()
{
	// 移動
	D3DXVECTOR3 NewPos{ GetPos() };
	NewPos += m_Velocity;
	SetPos(NewPos);
}