//--------------------------------------------------------------------------------
// 
// �L�����N�^�[ [character.h]
// Author: Taito Jin
// 
//--------------------------------------------------------------------------------
#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"

//****************************************************
// �L�����N�^�[�N���X
//****************************************************
class CCharacter : public CObject_2D
{
public:
	CCharacter(int nPriority = static_cast<int>(LAYER::NONE));	// �R���X�g���N�^
	~CCharacter() override = default;							// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	void SetMove(const D3DXVECTOR3& inMove);	// �ړ��ʐݒ�
	const D3DXVECTOR3& GetMove() const;			// �ړ��ʎ擾

	static CCharacter* Create();	// ����

private:
	CCharacter(const CCharacter&) = delete;
	void operator=(const CCharacter&) = delete;

	D3DXVECTOR3 m_Move;		// �ړ���
};
