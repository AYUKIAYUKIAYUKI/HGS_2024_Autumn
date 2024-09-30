//============================================================================
// 
// �c�C�X�g�ז����A�w�b�_�t�@�C�� [obstacle_twist.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBSTACLE_TWIST_H_
#define _OBSTACLE_TWIST_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle.h"

//****************************************************
// �c�C�X�g�ז����N���X
//****************************************************
class CObstacle_Twist : public CObstacle
{
public:

	CObstacle_Twist(int nRouteStyle, int nPriority = static_cast<int>(LAYER::NONE));	// �R���X�g���N�^
	~CObstacle_Twist() override;														// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3 GetVelocity();				// �ړ��ʂ��擾
	void SetVelocity(D3DXVECTOR3 Velocity);	// �ړ��ʂ�ݒ�

	static CObstacle_Twist* Create(int nRouteStyle);	// ����

private:

	void Move();	// �ړ�

	int m_nRouteStyle;			// �ړ��X�^�C��
	D3DXVECTOR3 m_Velocity;		// �ړ���
	int m_nCast;				// �L���X�g����
	D3DXVECTOR3 m_TwistTarget;	// �c�C�X�g�ڕW
};

#endif	// _OBSTACLE_TWIST_H_