//============================================================================
// 
// ターン邪魔物 [obstacle_turn.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "obstacle_turn.h"

//============================================================================
// コンストラクタ
//============================================================================
CObstacle_Turn::CObstacle_Turn(int nRouteStyle, int nPriority) :
	CObstacle{ nPriority },
	m_nRouteStyle{ nRouteStyle },
	m_Velocity{ 0.0f, 0.0f, 0.0f },
	m_nCast{ 0 },
	m_Reverse{ 0.0f, 0.0f, 0.0f }
{
	SetCol({ 0.5f, 1.0f, 1.0f, 1.0f });
}

//============================================================================
// デストラクタ
//============================================================================
CObstacle_Turn::~CObstacle_Turn()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CObstacle_Turn::Init()
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

		// 上
	case 4:
		SetPos({ SCREEN_WIDTH * 0.35f, -INITSPAN * 3.0f, 0.0f });
		m_Velocity = { 0.0f, fAdder, 0.0f, };
		break;
	case 5:
		SetPos({ SCREEN_WIDTH * 0.65f, -INITSPAN * 3.0f, 0.0f });
		m_Velocity = { 0.0f, fAdder, 0.0f, };
		break;

		// 下
	case 6:
		SetPos({ SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT + INITSPAN * 3.0f, 0.0f });
		m_Velocity = { 0.0f, -fAdder, 0.0f, };
		break;
	case 7:
		SetPos({ SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT + INITSPAN * 3.0f, 0.0f });
		m_Velocity = { 0.0f, -fAdder, 0.0f, };
		break;

	default:
		assert(false && "移動スタイル指定エラー");
		break;
	}

	// 反転した移動量を保存
	m_Reverse = m_Velocity * -1.0f;

	// 基底クラスの初期設定
	HRESULT hr{ CObstacle::Init() };

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CObstacle_Turn::Uninit()
{
	// 基底クラスの終了処理
	CObstacle::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CObstacle_Turn::Update()
{
	// 移動
	Move();

	// 基底クラスの更新処理
	CObstacle::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CObstacle_Turn::Draw()
{
	// 基底クラスの描画処理
	CObstacle::Draw();
}

//============================================================================
// 移動量を取得
//============================================================================
D3DXVECTOR3 CObstacle_Turn::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// 移動量を設定
//============================================================================
void CObstacle_Turn::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// 生成
//============================================================================
CObstacle_Turn* CObstacle_Turn::Create(int nRouteStyle)
{
	// インスタンス生成
	CObstacle_Turn* pInstance{ DBG_NEW CObstacle_Turn(nRouteStyle, static_cast<int>(CObject::LAYER::MIDDLE)) };

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
void CObstacle_Turn::Move()
{
	// キャスト
	m_nCast++;

	// 移動量反転
	if(m_nCast > 150)
	{
		m_Velocity += (m_Reverse - m_Velocity) * 0.01f;
	}

	// 移動
	D3DXVECTOR3 NewPos{ GetPos() };
	NewPos += m_Velocity;
	SetPos(NewPos);
}