//============================================================================
// 
// �m�[�}���ז��� [obstacle_normal.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle_normal.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CObstacle_Normal::CObstacle_Normal(int nRouteStyle, int nPriority) :
	CObstacle{ nPriority },
	m_nRouteStyle{ nRouteStyle },
	m_Velocity{ 0.0f, 0.0f, 0.0f }
{
	SetCol({ 0.0f, 0.0f, 1.0f, 1.0f });
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CObstacle_Normal::~CObstacle_Normal()
{
	
}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CObstacle_Normal::Init()
{
	float fAdder{ 1.0f };

	// �T�C�Y�ݒ�
	SetSize({ 15.0f, 15.0f, 0.0f });

	switch (m_nRouteStyle)
	{
	//	// ��
	//case 0:
	//	SetPos({ SPAN_X, -INITSPAN, 0.0f });
	//	m_Velocity = { 0.0f, 1.0f, 0.0f, };
	//	break;
	//case 1:
	//	SetPos({ SCREEN_WIDTH - SPAN_X, -INITSPAN, 0.0f });
	//	m_Velocity = { 0.0f, 1.0f, 0.0f, };
	//	break;

	//	// ��
	//case 4:
	//	SetPos({ SCREEN_WIDTH - SPAN_X, SCREEN_HEIGHT + INITSPAN, 0.0f });
	//	m_Velocity = { 0.0f, -1.0f, 0.0f, };
	//	break;
	//case 5:
	//	SetPos({ SPAN_X, SCREEN_HEIGHT + INITSPAN, 0.0f });
	//	m_Velocity = { 0.0f, -1.0f, 0.0f, };
	//	break;

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
		SetPos({ -INITSPAN, SPAN_Y, 0.0f  });
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
void CObstacle_Normal::Uninit()
{
	// ���N���X�̏I������
	CObstacle::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CObstacle_Normal::Update()
{
	// �ړ�
	Move();

	// ���N���X�̍X�V����
	CObstacle::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CObstacle_Normal::Draw()
{
	// ���N���X�̕`�揈��
	CObstacle::Draw();
}

//============================================================================
// �ړ��ʂ��擾
//============================================================================
D3DXVECTOR3 CObstacle_Normal::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// �ړ��ʂ�ݒ�
//============================================================================
void CObstacle_Normal::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// ����
//============================================================================
CObstacle_Normal* CObstacle_Normal::Create(int nRouteStyle)
{
	// �C���X�^���X����
	CObstacle_Normal* pInstance{ DBG_NEW CObstacle_Normal(nRouteStyle, static_cast<int>(CObject::LAYER::MIDDLE)) };

	// ����̓I�u�W�F�N�g�ň�����^�C�v�̐ݒ�
	pInstance->SetType(CObject::TYPE::NONE);

	// ����͎ז����X�^�C���̐ݒ�
	pInstance->SetStyle(STYLE::NORMAL);

	// CObject2D -> CObstacle �����ݒ�
	pInstance->Init();

	return pInstance;
}

//============================================================================
// �ړ�
//============================================================================
void CObstacle_Normal::Move()
{
	// �ړ�
	D3DXVECTOR3 NewPos{ GetPos() };
	NewPos += m_Velocity;
	SetPos(NewPos);
}