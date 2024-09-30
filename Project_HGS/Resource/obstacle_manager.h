//============================================================================
// 
// �ז����}�l�[�W���[�A�w�b�_�t�@�C�� [obstacle_manager.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBSTACLE_MANAGER_H_
#define _OBSTACLE_MANAGER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle.h"

//****************************************************
// �ז����}�l�[�W���[
//****************************************************
class CObstacle_Manager final
{
public:

	HRESULT Init();	// �����ݒ�
	void Release();	// ���
	void Update();	// �X�V����

	static CObstacle_Manager* GetInstance();	// �ז����}�l�[�W���[���擾

private:

	CObstacle_Manager();	// �R���X�g���N�^
	~CObstacle_Manager();	// �f�X�g���N�^

	void ImportObstacle();	// �ז������C���|�[�g
	void Create();			// ����
	void Uninit();			// �I������

	bool m_bEndUpdate;						// �X�V����
	std::ifstream m_Import;					// �t�@�C���ǂݎ��p
	int m_nCast;							// �L���X�g�^�C��
	static CObstacle_Manager* m_pInstance;	// ���C���X�^���X
};

#endif	// _OBSTACLE_H_