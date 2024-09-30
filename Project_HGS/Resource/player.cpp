//--------------------------------------------------------------------------------
// 
// �v���C���[ [player.cpp]
// Author: Taito Jin
// 
//--------------------------------------------------------------------------------

//---------------------------------------------------
// �C���N���[�h
//---------------------------------------------------
#include "player.h"
#include "manager.h"

//===================================================
// �������O���
//===================================================
namespace /* anonymous */
{
	//---------------------------------------------------
	// using �錾
	//---------------------------------------------------
	using namespace HGSAutumn240930;

	//---------------------------------------------------
	// �萔
	//---------------------------------------------------
	constexpr float MOVE_SPEED = 50.0f;	// �v���C���[�̈ړ����x

} // namespace /* anonymous */

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer(int nPriority)
	: CCharacter{ nPriority }
{
	// DO_NOTHING
}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CPlayer::Init()
{
	// �e�N���X�̏���
	HRESULT hr = CCharacter::Init();
	if (FAILED(hr))
	{
		return E_FAIL;
	}


	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CPlayer::Uninit()
{
	// �e�N���X�̏���
	CCharacter::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CPlayer::Update()
{
	// �ړ��ʂ̐ݒ�
	if (m_PlayerFlag & static_cast<BYTE>(PLAYER_FLAG::CAN_INPUT))
	{ // �ړ��\
		bool bPressLeft = CManager::GetKeyboard()->GetPress(DIK_LEFT);
		bool bTriggerLeft = CManager::GetKeyboard()->GetTrigger(DIK_LEFT);
		bool bPressRight = CManager::GetKeyboard()->GetPress(DIK_RIGHT);
		bool bTriggerRight = CManager::GetKeyboard()->GetTrigger(DIK_RIGHT);

		D3DXVECTOR3 move = GetMove();

		if ((bPressLeft && bTriggerRight) || (bPressRight && bTriggerLeft))
		{ // ��������
			D3DXVECTOR3 pos = GetPos();
			if (pos.y <= SCREEN_HEIGHT * 0.5f)
			{ // ��ʏ㕔
				move = { 0.0f, MOVE_SPEED, 0.0f };
			}
			else
			{ // ��ʉ���
				move = { 0.0f, -MOVE_SPEED, 0.0f };
			}
		}
		else if (bTriggerLeft)
		{ // ��
			move = { -MOVE_SPEED, 0.0f, 0.0f };
		}
		else if (bTriggerRight)
		{ // �E
			move = { MOVE_SPEED, 0.0f, 0.0f };
		}

		SetMove(move);
	}

	// �e�N���X�̏���
	CCharacter::Update();

	// �����蔻��
	{
		

		Collision::Circle a;
		Collision::Circle b;
		Collision::IsCollisionCircleVsCircle(a, b);

		D3DXVECTOR3 pos = GetPos();
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CPlayer::Draw()
{
	// �e�N���X�̏���
	CCharacter::Draw();
}

//============================================================================
// ����
//============================================================================
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = DBG_NEW CPlayer{};

	// �����o���Ă����珉���ݒ�
	if (pPlayer != nullptr)
	{
		pPlayer->Init();
	}

	return pPlayer;
}