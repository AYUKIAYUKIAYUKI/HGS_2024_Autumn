//============================================================================
// 
// �X�s�[�f�B�ז����A�w�b�_�t�@�C�� [obstacle_speedy.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBSTACLE_SPEEDY_H_
#define _OBSTACLE_SPEEDY_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle.h"

//****************************************************
// �X�s�[�f�B�ז����N���X
//****************************************************
class CObstacle_Speedy : public CObstacle
{
public:

	CObstacle_Speedy(int nRouteStyle, int nPriority = static_cast<int>(LAYER::NONE));	// �R���X�g���N�^
	~CObstacle_Speedy() override;														// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3 GetVelocity();				// �ړ��ʂ��擾
	void SetVelocity(D3DXVECTOR3 Velocity);	// �ړ��ʂ�ݒ�

	static CObstacle_Speedy* Create(int nRouteStyle);	// ����

private:

	void Move();	// �ړ�

	int m_nRouteStyle;		// �ړ��X�^�C��
	D3DXVECTOR3 m_Velocity;	// �ړ���
};

#endif	// _SPEEDY_H_