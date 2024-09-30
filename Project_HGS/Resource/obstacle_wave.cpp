//============================================================================
// 
// �E�F�[�u�ז��� [obstacle_wave.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle_wave.h"

//============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//============================================================================
CObstacle_Wave::~CObstacle_Wave()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CObstacle_Wave::Init()
{
	float fAdder{ 2.0f };

	// �T�C�Y�ݒ�
	SetSize({ 15.0f, 15.0f, 0.0f });

	switch (m_nRouteStyle)
	{
		// �E
	case 0:
		SetPos({ SCREEN_WIDTH + INITSPAN, SPAN_Y, 0.0f });
		m_Velocity = { -fAdder, 0.0f, 0.0f, };
		break;
	case 1:
		SetPos({ SCREEN_WIDTH + INITSPAN, SCREEN_HEIGHT - SPAN_Y, 0.0f });
		m_Velocity = { -fAdder, 0.0f, 0.0f, };
		break;

		// ��
	case 2:
		SetPos({ -INITSPAN, SPAN_Y, 0.0f });
		m_Velocity = { fAdder, 0.0f, 0.0f, };
		break;
	case 3:
		SetPos({ -INITSPAN, SCREEN_HEIGHT - SPAN_Y, 0.0f });
		m_Velocity = { fAdder, 0.0f, 0.0f, };
		break;

	default:
		assert(false && "�ړ��X�^�C���w��G���[");
		break;
	}

	// ���N���X�̏����ݒ�
	HRESULT hr{ CObstacle::Init() };

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CObstacle_Wave::Uninit()
{
	// ���N���X�̏I������
	CObstacle::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CObstacle_Wave::Update()
{
	// �ړ�
	Move();

	// ���N���X�̍X�V����
	CObstacle::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CObstacle_Wave::Draw()
{
	// ���N���X�̕`�揈��
	CObstacle::Draw();
}

//============================================================================
// �ړ��ʂ��擾
//============================================================================
D3DXVECTOR3 CObstacle_Wave::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// �ړ��ʂ�ݒ�
//============================================================================
void CObstacle_Wave::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// ����
//============================================================================
CObstacle_Wave* CObstacle_Wave::Create(int nRouteStyle)
{
	// �C���X�^���X����
	CObstacle_Wave* pInstance{ DBG_NEW CObstacle_Wave(nRouteStyle, static_cast<int>(CObject::LAYER::MIDDLE)) };

	// ����̓I�u�W�F�N�g�ň�����^�C�v�̐ݒ�
	pInstance->SetType(CObject::TYPE::NONE);

	// ����͎ז����X�^�C���̐ݒ�
	pInstance->SetStyle(STYLE::TURN);

	// CObject2D -> CObstacle �����ݒ�
	pInstance->Init();

	return pInstance;
}

//============================================================================
// �ړ�
//============================================================================
void CObstacle_Wave::Move()
{
	m_fCoeffWave += 0.05f;

	if (m_fCoeffWave > D3DX_PI)
	{
		m_fCoeffWave += D3DX_PI * -2.0f;
	}

	// �g�ł��ړ��ʐݒ�
	m_WaveVelocity.x = cosf(m_fCoeffWave) * fabsf(cosf(atan2f(m_Velocity.x, m_Velocity.y)));
	m_WaveVelocity.y = cosf(m_fCoeffWave) * fabsf(sinf(atan2f(m_Velocity.x, m_Velocity.y)));

	// �ړ�
	D3DXVECTOR3 NewPos{ GetPos() };
	NewPos += m_Velocity + m_WaveVelocity * 5.0f;
	SetPos(NewPos);
}