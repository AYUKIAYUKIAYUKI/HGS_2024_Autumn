//============================================================================
// 
// �^�C�}�[�\���A�w�b�_�t�@�C�� [timernumber.h]
// Author : �v�ێs�ĕ�
// 
//============================================================================

#ifndef _TIMERNUMBER_H_
#define _TIMERNUMBER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"// 2D�I�u�W�F�N�g�Ǘ��w�b�_�[�t�@�C��

//****************************************************
// �^�C�}�[�N���X
//****************************************************
class CTimerNumber : public CObject_2D
{
public:

	CTimerNumber(int nPriority = static_cast<int>(LAYER::UI));// �R���X�g���N�^
	~CTimerNumber() override;// �f�X�g���N�^

	HRESULT Init() override;// �����ݒ�
	void Uninit() override;// �I������
	void Update() override;// �X�V����
	void Draw() override;// �`�揈��
	static CTimerNumber* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nIdx);// ��������

private:

	void SetTimerNumberPos(D3DXVECTOR3 pos);// ���W�ݒ�
	void SetIdx(int nIdx) { m_nIdx = nIdx; }// ID�ݒ�

	int m_nIdx;// ID
};

#endif // _TIMERNUMBER_H_
