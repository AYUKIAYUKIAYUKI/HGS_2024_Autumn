//--------------------------------------------------------------------------------
// 
// �v���C���[���ړ��ł���� [line.h]
// Author: Taito Jin
// 
//--------------------------------------------------------------------------------
#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"

//****************************************************
// �v���C���[���ړ��ł�����̃N���X
//****************************************************
class CLine : public CObject_2D
{
public:
	CLine(int nPriority = static_cast<int>(LAYER::BACK));	// �R���X�g���N�^
	~CLine() override = default;							// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	void SetMove(const D3DXVECTOR3& inMove);	// �ړ��ʐݒ�
	const D3DXVECTOR3& GetMove() const;			// �ړ��ʎ擾

	static CLine* Create();	// ����

private:
	CLine(const CLine&) = delete;
	void operator=(const CLine&) = delete;

	D3DXVECTOR3 m_StartPos;	// �n�_
	D3DXVECTOR3 m_EndPos;	// �I�_
};
