//============================================================================
// 
// �^�[���ז����A�w�b�_�t�@�C�� [obstacle_turn.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBSTACLE_TURN_H_
#define _OBSTACLE_TURN_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle.h"

//****************************************************
// �^�[���ז����N���X
//****************************************************
class CObstacle_Turn : public CObstacle
{
public:

	CObstacle_Turn(int nRouteStyle, int nPriority = static_cast<int>(LAYER::NONE));	// �R���X�g���N�^
	~CObstacle_Turn() override;														// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3 GetVelocity();				// �ړ��ʂ��擾
	void SetVelocity(D3DXVECTOR3 Velocity);	// �ړ��ʂ�ݒ�

	static CObstacle_Turn* Create(int nRouteStyle);	// ����

private:

	void Move();	// �ړ�

	int m_nRouteStyle;		// �ړ��X�^�C��
	D3DXVECTOR3 m_Velocity;	// �ړ���
	int m_nCast;			// �L���X�g����
	D3DXVECTOR3 m_Reverse;	// ���]��
};

#endif	// _OBSTACLE_H_