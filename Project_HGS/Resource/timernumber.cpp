//============================================================================
// 
// �^�C�}�[�\�� [timernumber.cpp]
// Author : �v�ێs�ĕ�
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "timernumber.h"//�^�C�}�[�i���o�[�w�b�_�[�t�@�C��
#include "timer.h"//�^�C�}�[�Ǘ��w�b�_�[�t�@�C��
#include <manager.h>//�}�l�[�W���[�w�b�_�[�t�@�C��

//============================================================================
// �R���X�g���N�^
//============================================================================
CTimerNumber::CTimerNumber(int nPriority) : CObject_2D{ nPriority }
{
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CTimerNumber::~CTimerNumber()
{
}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CTimerNumber::Init()
{
	// �e�N�X�`���ݒ�
	BindTex(CTexture_Manager::TYPE::TIMER);

	// �p�����[�^�ݒ�
	SetTexWidth(0.1f);// ���̃e�N�X�`�������� 

	// 2D�I�u�W�F�N�g�����ݒ�
	if (FAILED(CObject_2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CTimerNumber::Uninit()
{
	// 2D�I�u�W�F�N�g�I������
	CObject_2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CTimerNumber::Update()
{
	// ���[�J���ϐ��錾
	int nTimer = CManager::GetTimer()->GetTime();// ���݂̃^�C�}�[
	int nMulti = 1;// �e���̔{��

	// ID�ɍ��킹�Ĕ{�������߂�
	for (int nCntTime = 0; nCntTime < m_nIdx + 1; nCntTime++)
	{
		nMulti *= 10;
	}

	// �Y�����錅�̐��������߂�
	int nPosTex = (nTimer % nMulti) / (nMulti / 10);

	// ���݂̃e�N�X�`�����������ݒ�
	SetNowPatternU(nPosTex);

	//�c�莞�Ԃɍ��킹�ĐԐF�ɂ��Ă���
	if (nTimer <= START_COL_CHANGE)
	{
		// ���݂̃J���[�����擾
		D3DXCOLOR col = GetCol();

		//�΂ƐF�𔖂����Ă���
		col.g = static_cast<float>(nTimer) / static_cast<float>(START_COL_CHANGE);
		col.b = static_cast<float>(nTimer) / static_cast<float>(START_COL_CHANGE);

		// �J���[����ݒ�
		SetCol(col);
	}

	// 2D�I�u�W�F�N�g�X�V����
	CObject_2D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CTimerNumber::Draw()
{
	// 2D�I�u�W�F�N�g�`�揈��
	CObject_2D::Draw();
}

//============================================================================
// ��������
//============================================================================
CTimerNumber* CTimerNumber::Create(int nIdx)
{
	// �������𓮓I�m��
	CTimerNumber* pTimeNumber = new CTimerNumber();

	//�p�����[�^�ݒ�
	pTimeNumber->SetIdx(nIdx);// ID
	pTimeNumber->SetSize(CREATE_SIZE);// �T�C�Y
	pTimeNumber->SetTimerNumberPos(CREATE_POS);// ���W
	pTimeNumber->SetTexWidth(10.0f);// ���̃e�N�X�`��������

	//����������
	pTimeNumber->Init();

	return nullptr;
}

//============================================================================
// ��������Alt
//============================================================================
CTimerNumber* CTimerNumber::Create(int nIdx, int nNum)
{
	nNum = nNum;	// �x�����p���ʏ���

	// �������𓮓I�m��
	CTimerNumber* pTimeNumber = new CTimerNumber();

	//�p�����[�^�ݒ�
	pTimeNumber->SetIdx(nIdx);// ID
	pTimeNumber->SetSize(CREATE_SIZE * 2.5f);// �T�C�Y

	pTimeNumber->SetPos({ (SCREEN_WIDTH * 0.75f) - (nIdx * 250.0f), (SCREEN_HEIGHT * 0.5f), 0.0f });

	pTimeNumber->SetTexWidth(10.0f);// ���̃e�N�X�`��������

	//����������
	pTimeNumber->Init();

	return nullptr;
}

//============================================================================
// ���W�ݒ�
//============================================================================
void CTimerNumber::SetTimerNumberPos(D3DXVECTOR3 pos)
{
	SetPos({ pos.x - m_nIdx * (GetSize().x + 25.0f), pos.y, pos.z });
}
