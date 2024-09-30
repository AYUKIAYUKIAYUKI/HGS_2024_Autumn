//============================================================================
// 
// ���U���g [result.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "result.h"
#include "fade.h"

// �C���v�b�g�擾�p
#include "manager.h"

/* test */
#include "object_3D.h"
#include "texture_manager.h"
#include <bg.h>
#include <timernumber.h>
#include "sound.h"
//============================================================================
// �R���X�g���N�^
//============================================================================
CResult::CResult()
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CResult::~CResult()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CResult::Init()
{	
	// ���N���X�̏����ݒ�
	HRESULT hr{ CScene::Init() };

	// �w�i����
	CBg* pBg{ CBg::Create() };

	// �Q�[���̌��ʂɉ����ď�������
	if (CScene::GetMode() == MODE::RESULT_GAMECLEAR)
	{
		pBg->BindTex(CTexture_Manager::TYPE::RESULT_GAMECLEAR);
	}
	else if (CScene::GetMode() == MODE::RESULT_GAMEOVER)
	{
		pBg->BindTex(CTexture_Manager::TYPE::RESULT_GAMEOVER);

		// �^�C�}�[�\������
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			CTimerNumber::Create(nCnt, 0);
		}
	}

	// BGM��������
	CSound::GetInstance()->Play(CSound::LABEL::BGM_03);
	return hr;
}

//============================================================================
// �I������
//============================================================================
void CResult::Uninit()
{
	// �S�ẴT�E���h���~
	CSound::GetInstance()->Stop();
	// �^�C�}�[���Z�b�g
	CManager::GetTimer()->Reset();

	// ���N���X�̏I������
	CScene::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CResult::Update()
{
	// ���N���X�̍X�V����
	CScene::Update();

	// �^�C�g����ʂ�
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN)
		|| CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::START))
	{
		CSound::GetInstance()->Play(CSound::LABEL::SE_CLICK);
		CFade::SetFade(CScene::MODE::TITLE);
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CResult::Draw()
{
	// ���N���X�̕`�揈��
	CScene::Draw();
}