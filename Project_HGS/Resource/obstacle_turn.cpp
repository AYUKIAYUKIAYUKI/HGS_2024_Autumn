//============================================================================
// 
// �^�[���ז��� [obstacle_turn.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle_turn.h"

//============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//============================================================================
CObstacle_Turn::~CObstacle_Turn()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CObstacle_Turn::Init()
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

		// ��
	case 4:
		SetPos({ SCREEN_WIDTH * 0.35f, -INITSPAN * 3.0f, 0.0f });
		m_Velocity = { 0.0f, fAdder, 0.0f, };
		break;
	case 5:
		SetPos({ SCREEN_WIDTH * 0.65f, -INITSPAN * 3.0f, 0.0f });
		m_Velocity = { 0.0f, fAdder, 0.0f, };
		break;

		// ��
	case 6:
		SetPos({ SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT + INITSPAN * 3.0f, 0.0f });
		m_Velocity = { 0.0f, -fAdder, 0.0f, };
		break;
	case 7:
		SetPos({ SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT + INITSPAN * 3.0f, 0.0f });
		m_Velocity = { 0.0f, -fAdder, 0.0f, };
		break;

	default:
		assert(false && "�ړ��X�^�C���w��G���[");
		break;
	}

	// ���]�����ړ��ʂ�ۑ�
	m_Reverse = m_Velocity * -1.0f;

	// ���N���X�̏����ݒ�
	HRESULT hr{ CObstacle::Init() };

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CObstacle_Turn::Uninit()
{
	// ���N���X�̏I������
	CObstacle::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CObstacle_Turn::Update()
{
	// �ړ�
	Move();

	// ���N���X�̍X�V����
	CObstacle::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CObstacle_Turn::Draw()
{
	// ���N���X�̕`�揈��
	CObstacle::Draw();
}

//============================================================================
// �ړ��ʂ��擾
//============================================================================
D3DXVECTOR3 CObstacle_Turn::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// �ړ��ʂ�ݒ�
//============================================================================
void CObstacle_Turn::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// ����
//============================================================================
CObstacle_Turn* CObstacle_Turn::Create(int nRouteStyle)
{
	// �C���X�^���X����
	CObstacle_Turn* pInstance{ DBG_NEW CObstacle_Turn(nRouteStyle, static_cast<int>(CObject::LAYER::MIDDLE)) };

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
void CObstacle_Turn::Move()
{
	// �L���X�g
	m_nCast++;

	// �ړ��ʔ��]
	if(m_nCast > 150)
	{
		m_Velocity += (m_Reverse - m_Velocity) * 0.01f;
	}

	// �ړ�
	D3DXVECTOR3 NewPos{ GetPos() };
	NewPos += m_Velocity;
	SetPos(NewPos);
}