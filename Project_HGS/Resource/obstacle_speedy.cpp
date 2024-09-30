//============================================================================
// 
// �X�s�[�f�B�ז��� [obstacle_speedy.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle_speedy.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CObstacle_Speedy::CObstacle_Speedy(int nRouteStyle, int nPriority) :
	CObstacle{ nPriority },
	m_nRouteStyle{ nRouteStyle },
	m_Velocity{ 0.0f, 0.0f, 0.0f, }
{
	SetCol({ 1.0f, 0.0f, 1.0f, 1.0f });
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CObstacle_Speedy::~CObstacle_Speedy()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CObstacle_Speedy::Init()
{
	float fAdder{ 5.0f };

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
void CObstacle_Speedy::Uninit()
{
	// ���N���X�̏I������
	CObstacle::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CObstacle_Speedy::Update()
{
	// �ړ�
	Move();

	// ���N���X�̍X�V����
	CObstacle::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CObstacle_Speedy::Draw()
{
	// ���N���X�̕`�揈��
	CObstacle::Draw();
}

//============================================================================
// �ړ��ʂ��擾
//============================================================================
D3DXVECTOR3 CObstacle_Speedy::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// �ړ��ʂ�ݒ�
//============================================================================
void CObstacle_Speedy::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// ����
//============================================================================
CObstacle_Speedy* CObstacle_Speedy::Create(int nRouteStyle)
{
	// �C���X�^���X����
	CObstacle_Speedy* pInstance{ DBG_NEW CObstacle_Speedy(nRouteStyle, static_cast<int>(CObject::LAYER::MIDDLE)) };

	// ����̓I�u�W�F�N�g�ň�����^�C�v�̐ݒ�
	pInstance->SetType(CObject::TYPE::NONE);

	// ����͎ז����X�^�C���̐ݒ�
	pInstance->SetStyle(STYLE::SPEEDY);

	// CObject2D -> CObstacle �����ݒ�
	pInstance->Init();

	return pInstance;
}

//============================================================================
// �ړ�
//============================================================================
void CObstacle_Speedy::Move()
{
	// �ړ�
	D3DXVECTOR3 NewPos{ GetPos() };
	NewPos += m_Velocity;
	SetPos(NewPos);
}