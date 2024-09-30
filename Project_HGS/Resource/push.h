//============================================================================
// 
// PUSHUI�A�w�b�_�t�@�C�� [logo.h]
// Author : �v�ێs�ĕ�
// 
//============================================================================

#ifndef _PUSH_H_
#define _PUSH_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"// 2D�I�u�W�F�N�g�Ǘ��w�b�_�[�t�@�C��

//****************************************************
// �^�C�}�[�N���X
//****************************************************
class CPush : public CObject_2D
{
public:

	CPush(int nPriority = static_cast<int>(LAYER::UI));// �R���X�g���N�^
	~CPush() override;// �f�X�g���N�^

	HRESULT Init() override;// �����ݒ�
	void Uninit() override;// �I������
	void Update() override;// �X�V����
	void Draw() override;// �`�揈��
	static CPush* Create();// ��������

private:
	static inline const D3DXVECTOR3 CREATE_SIZE = { 300.0f, 60.0f, 0.0f };// �����T�C�Y
	static inline const D3DXVECTOR3 CREATE_POS = { SCREEN_WIDTH * 0.5f, 600.0f, 0.0f };// �����ʒu

	const float STAND_SPEED = 0.02f;//�ҋ@���̓_�ő��x
	bool m_bLightUp;//���C�g�A�b�v�t���O
};

#endif // _PUSH_H_

