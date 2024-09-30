//============================================================================
// 
// �E�F�[�u�ז����A�w�b�_�t�@�C�� [obstacle_wave.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBSTACLE_WAVE_H_
#define _OBSTACLE_WAVE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle.h"

//****************************************************
// �^�[���ז����N���X
//****************************************************
class CObstacle_Wave : public CObstacle
{
public:

	CObstacle_Wave(int nRouteStyle, int nPriority = static_cast<int>(LAYER::NONE));	// �R���X�g���N�^
	~CObstacle_Wave() override;														// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3 GetVelocity();				// �ړ��ʂ��擾
	void SetVelocity(D3DXVECTOR3 Velocity);	// �ړ��ʂ�ݒ�

	static CObstacle_Wave* Create(int nRouteStyle);	// ����

private:

	void Move();	// �ړ�

	int m_nRouteStyle;			// �ړ��X�^�C��
	D3DXVECTOR3 m_Velocity;		// �ړ���
	float m_fCoeffWave;			// �g�ł��W��
	D3DXVECTOR3 m_WaveVelocity;	// �g�ł��ړ���
};

#endif	// _OBSTACLE_WAVE_H_