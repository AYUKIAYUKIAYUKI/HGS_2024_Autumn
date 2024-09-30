//============================================================================
// 
// �O�ՁA�w�b�_�t�@�C�� [trajectory.h]
// Author : �v�ێs�ĕ�
// 
//============================================================================

#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"// 2D�I�u�W�F�N�g�Ǘ��w�b�_�[�t�@�C��

//****************************************************
// �^�C�}�[�N���X
//****************************************************
class CTrajectory : public CObject_2D
{
public:

	CTrajectory(int nPriority = static_cast<int>(LAYER::UI));// �R���X�g���N�^
	~CTrajectory() override;// �f�X�g���N�^

	HRESULT Init() override;// �����ݒ�
	void Uninit() override;// �I������
	void Update() override;// �X�V����
	void Draw() override;// �`�揈��
	static CTrajectory* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);// ��������
};

#endif // _TIMERNUMBER_H_
