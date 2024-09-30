//============================================================================
// 
// �c�C�X�g�ז��� [obstacle_twist.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle_twist.h"

//============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//============================================================================
CObstacle_Twist::~CObstacle_Twist()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CObstacle_Twist::Init()
{
	BindTex(CTexture_Manager::TYPE::SQUARE);

	float fAdder{ 3.0f };

	// �T�C�Y�ݒ�
	SetSize({ 15.0f, 15.0f, 0.0f });

	switch (m_nRouteStyle)
	{
		// �E
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

		// ��
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
void CObstacle_Twist::Uninit()
{
	// ���N���X�̏I������
	CObstacle::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CObstacle_Twist::Update()
{
	// �ړ�
	Move();

	// ���N���X�̍X�V����
	CObstacle::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CObstacle_Twist::Draw()
{
	// ���N���X�̕`�揈��
	CObstacle::Draw();
}

//============================================================================
// �ړ��ʂ��擾
//============================================================================
D3DXVECTOR3 CObstacle_Twist::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// �ړ��ʂ�ݒ�
//============================================================================
void CObstacle_Twist::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// ����
//============================================================================
CObstacle_Twist* CObstacle_Twist::Create(int nRouteStyle)
{
	// �C���X�^���X����
	CObstacle_Twist* pInstance{ DBG_NEW CObstacle_Twist(nRouteStyle, static_cast<int>(CObject::LAYER::MIDDLE)) };

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
void CObstacle_Twist::Move()
{
	// �L���X�g
	m_nCast++;

	// �ړ��ʔ��]
	if (m_nCast > 180)
	{
		// �c�C�X�g���W��ǂ�
		D3DXVECTOR3 NewPos{ GetPos() };
		NewPos.y += (m_TwistTarget.y - GetPos().y) * 0.05f;
		SetPos(NewPos);
	}

	// �ړ�
	D3DXVECTOR3 NewPos{ GetPos() };
	NewPos += m_Velocity;
	SetPos(NewPos);
}