//============================================================================
// 
// ウェーブ邪魔物 [obstacle_wave.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "obstacle_wave.h"

//============================================================================
// コンストラクタ
//============================================================================
CObstacle_Wave::CObstacle_Wave(int nRouteStyle, int nPriority) :
	CObstacle{ nPriority },
	m_nRouteStyle{ nRouteStyle },
	m_Velocity{ 0.0f, 0.0f, 0.0f },
	m_fCoeffWave{ 0.0f },
	m_WaveVelocity{ 0.0f, 0.0f, 0.0f }
{
	SetCol({ 0.0f, 1.0f, 0.0f, 1.0f });
}

//============================================================================
// デストラクタ
//============================================================================
CObstacle_Wave::~CObstacle_Wave()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CObstacle_Wave::Init()
{
	float fAdder{ 2.0f };

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
void CObstacle_Wave::Uninit()
{
	// 基底クラスの終了処理
	CObstacle::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CObstacle_Wave::Update()
{
	// 移動
	Move();

	// 基底クラスの更新処理
	CObstacle::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CObstacle_Wave::Draw()
{
	// 基底クラスの描画処理
	CObstacle::Draw();
}

//============================================================================
// 移動量を取得
//============================================================================
D3DXVECTOR3 CObstacle_Wave::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// 移動量を設定
//============================================================================
void CObstacle_Wave::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// 生成
//============================================================================
CObstacle_Wave* CObstacle_Wave::Create(int nRouteStyle)
{
	// インスタンス生成
	CObstacle_Wave* pInstance{ DBG_NEW CObstacle_Wave(nRouteStyle, static_cast<int>(CObject::LAYER::MIDDLE)) };

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
void CObstacle_Wave::Move()
{
	m_fCoeffWave += 0.05f;

	if (m_fCoeffWave > D3DX_PI)
	{
		m_fCoeffWave += D3DX_PI * -2.0f;
	}

	// 波打ち移動量設定
	m_WaveVelocity.x = cosf(m_fCoeffWave) * fabsf(cosf(atan2f(m_Velocity.x, m_Velocity.y)));
	m_WaveVelocity.y = cosf(m_fCoeffWave) * fabsf(sinf(atan2f(m_Velocity.x, m_Velocity.y)));

	// 移動
	D3DXVECTOR3 NewPos{ GetPos() };
	NewPos += m_Velocity + m_WaveVelocity * 5.0f;
	SetPos(NewPos);
}