//============================================================================
// 
// �m�[�}���ז����A�w�b�_�t�@�C�� [obstacle_normal.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBSTACLE_NORMAL_H_
#define _OBSTACLE_NORMAL_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle.h"

//****************************************************
// �m�[�}���ז����N���X
//****************************************************
class CObstacle_Normal : public CObstacle
{
public:

	CObstacle_Normal(int nRouteStyle, int nPriority = static_cast<int>(LAYER::NONE));	// �R���X�g���N�^
	~CObstacle_Normal() override;														// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3 GetVelocity();				// �ړ��ʂ��擾
	void SetVelocity(D3DXVECTOR3 Velocity);	// �ړ��ʂ�ݒ�

	static CObstacle_Normal* Create(int nRouteStyle);	// ����

private:

	void Move();	// �ړ�

	int m_nRouteStyle;		// �ړ��X�^�C��
	D3DXVECTOR3 m_Velocity;	// �ړ���
};

#endif	// _OBSTACLE_H_