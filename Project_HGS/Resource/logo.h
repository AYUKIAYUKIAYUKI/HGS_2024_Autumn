//============================================================================
// 
// �^�C�g�����S�A�w�b�_�t�@�C�� [logo.h]
// Author : �v�ێs�ĕ�
// 
//============================================================================

#ifndef _LOGO_H_
#define _LOGO_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"// 2D�I�u�W�F�N�g�Ǘ��w�b�_�[�t�@�C��

//****************************************************
// �^�C�}�[�N���X
//****************************************************
class CLogo : public CObject_2D
{
public:

	CLogo(int nPriority = static_cast<int>(LAYER::UI));// �R���X�g���N�^
	~CLogo() override;// �f�X�g���N�^

	HRESULT Init() override;// �����ݒ�
	void Uninit() override;// �I������
	void Update() override;// �X�V����
	void Draw() override;// �`�揈��
	static CLogo* Create();// ��������

private:
	static inline const D3DXVECTOR3 CREATE_SIZE = { 500.0f, 250.0f, 0.0f };// �����T�C�Y
	static inline const D3DXVECTOR3 CREATE_POS = { SCREEN_WIDTH * 0.5f, 250.0f, 0.0f };// �����ʒu
};

#endif // _LOGO_H_

