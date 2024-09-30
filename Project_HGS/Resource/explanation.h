//============================================================================
// 
// ��������A�w�b�_�t�@�C�� [explanation.h]
// Author : �v�ێs�ĕ�
// 
//============================================================================

#ifndef _EXPLANATION_H_
#define _EXPLANATION_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"// 2D�I�u�W�F�N�g�Ǘ��w�b�_�[�t�@�C��

//****************************************************
// �^�C�}�[�N���X
//****************************************************
class CExplanation : public CObject_2D
{
public:

	CExplanation(int nPriority = static_cast<int>(LAYER::UI));// �R���X�g���N�^
	~CExplanation() override;// �f�X�g���N�^

	HRESULT Init() override;// �����ݒ�
	void Uninit() override;// �I������
	void Update() override;// �X�V����
	void Draw() override;// �`�揈��
	static CExplanation* Create();// ��������

private:
	static inline const D3DXVECTOR3 CREATE_SIZE = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f };// �����T�C�Y
	static inline const D3DXVECTOR3 CREATE_POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f };// �����ʒu
};

#endif // _TIMERNUMBER_H_
