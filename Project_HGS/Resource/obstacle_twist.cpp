//============================================================================
// 
// ツイスト邪魔物 [obstacle_twist.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "obstacle_twist.h"

//============================================================================
// コンストラクタ
//============================================================================
CObstacle_Twist::CObstacle_Twist(int nRouteStyle, int nPriority) :
	CObstacle{ nPriority },
	m_nRouteStyle{ nRouteStyle },
	m_Velocity{ 0.0f, 0.0f, 0.0f },
	m_nCast{ 0 },
	m_TwistTarget{ 0.0f, 0.0f, 0.0f }
{
	SetCol({ 1.0f, 0.0f, 0.0f, 1.0f });
}

//============================================================================
// デストラクタ
//============================================================================
CObstacle_Twist::~CObstacle_Twist()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CObstacle_Twist::Init()
{
	BindTex(CTexture_Manager::TYPE::SQUARE);

	float fAdder{ 3.0f };

	// サイズ設定
	SetSize({ 15.0f, 15.0f, 0.0f });

	switch (m_nRouteStyle)
	{
		// 右
	case 0:
		SetPos({ SCREEN_WIDTH + INITSPAN, SPAN_Y, 0.0f });
		m_Velocity = { -fAdder, 0.0f, 0.0f, };
		m_TwistTarget = { 0.0f, SCREEN_HEIGHT - SPAN_Y, 0.0f };
		break;
	case 1:
		SetPos({ SCREEN_WIDTH + INITSPAN, SCREEN_HEIGHT - SPAN_Y, 0.0f });
		m_Velocity = { -fAdder, 0.0f, 0.0f, };
		m_TwistTarget = { 0.0f, SPAN_Y, 0.0f };
		break;

		// 左
	case 2:
		SetPos({ -INITSPAN, SPAN_Y, 0.0f });
		m_Velocity = { fAdder, 0.0f, 0.0f, };
		m_TwistTarget = { 0.0f, SCREEN_HEIGHT - SPAN_Y, 0.0f };
		break;
	case 3:
		SetPos({ -INITSPAN, SCREEN_HEIGHT - SPAN_Y, 0.0f });
		m_Velocity = { fAdder, 0.0f, 0.0f, };
		m_TwistTarget = { 0.0f, SPAN_Y, 0.0f };
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
void CObstacle_Twist::Uninit()
{
	// 基底クラスの終了処理
	CObstacle::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CObstacle_Twist::Update()
{
	// 移動
	Move();

	// 基底クラスの更新処理
	CObstacle::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CObstacle_Twist::Draw()
{
	// 基底クラスの描画処理
	CObstacle::Draw();
}

//============================================================================
// 移動量を取得
//============================================================================
D3DXVECTOR3 CObstacle_Twist::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// 移動量を設定
//============================================================================
void CObstacle_Twist::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// 生成
//============================================================================
CObstacle_Twist* CObstacle_Twist::Create(int nRouteStyle)
{
	// インスタンス生成
	CObstacle_Twist* pInstance{ DBG_NEW CObstacle_Twist(nRouteStyle, static_cast<int>(CObject::LAYER::MIDDLE)) };

	// これはオブジェクトで扱われるタイプの設定
	pInstance->SetType(CObject::TYPE::NONE);

	// これは邪魔物スタイルの設定
	pInstance->SetStyle(STYLE::TURN);

	// CObject2D -> CObstacle 初期設定
	pInstance->Init();

	return pInstance;
}

//============================================================================
// 移動
//============================================================================
void CObstacle_Twist::Move()
{
	// キャスト
	m_nCast++;

	// 移動量反転
	if (m_nCast > 180)
	{
		// ツイスト座標を追う
		D3DXVECTOR3 NewPos{ GetPos() };
		NewPos.y += (m_TwistTarget.y - GetPos().y) * 0.05f;
		SetPos(NewPos);
	}

	// 移動
	D3DXVECTOR3 NewPos{ GetPos() };
	NewPos += m_Velocity;
	SetPos(NewPos);
}