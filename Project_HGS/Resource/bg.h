//============================================================================
// 
// �w�i�A�w�b�_�t�@�C�� [bg.h]
// Author : �v�ێs�ĕ�
// 
//============================================================================

#ifndef _BG_H_
#define _BG_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"// 2D�I�u�W�F�N�g�Ǘ��w�b�_�[�t�@�C��

//****************************************************
// �^�C�}�[�N���X
//****************************************************
class CBg : public CObject_2D
{
public:

	CBg(int nPriority = static_cast<int>(LAYER::BG));// �R���X�g���N�^
	~CBg() override;// �f�X�g���N�^

	HRESULT Init() override;// �����ݒ�
	void Uninit() override;// �I������
	void Update() override;// �X�V����
	void Draw() override;// �`�揈��
	static CBg* Create();// ��������

private:
	static inline const D3DXVECTOR3 CREATE_SIZE = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5, 0.0f };// �����T�C�Y
	static inline const D3DXVECTOR3 CREATE_POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f };// �����ʒu
};

#endif // _BG_H_

