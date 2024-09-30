//============================================================================
// 
// �ז����A�w�b�_�t�@�C�� [obstacle.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"

//****************************************************
// �ז����N���X
//****************************************************
class CObstacle : public CObject_2D
{
public:

	//****************************************************
	// �ז����X�^�C��
	//****************************************************
	enum class STYLE
	{
		NONE = 0,	// �o�O
		NORMAL,		// �m�[�}��
		SPEEDY,		// �X�s�[�f�B
		TURN,		// �^�[��
		WAVE,		// �E�F�[�u
		TWIST,		// �c�C�X�g
		LONG,		// �����O
		MAX,
	};

	CObstacle(int nPriority = static_cast<int>(LAYER::NONE));	// �R���X�g���N�^
	~CObstacle() override;										// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	void SetStyle(STYLE style);	// �ז����X�^�C����ݒ�
	STYLE GetStyle();			// �ז����X�^�C�����擾

	D3DXVECTOR3 GetPosTarget();					// �ڕW���W���擾
	void SetPosTarget(D3DXVECTOR3 PosTarget);	// �ڕW���W��ݒ�

	D3DXVECTOR3 GetRotTarget();					// �ڕW�������擾
	void SetRotTarget(D3DXVECTOR3 RotTarget);	// �ڕW������ݒ�

	D3DXVECTOR3 GetSizeTarget();				// �ڕW�T�C�Y���擾
	void SetSizeTarget(D3DXVECTOR3 SizeTarget);	// �ڕW�T�C�Y��ݒ�

	D3DXCOLOR GetColTarget();				// �ڕW�F���擾
	void SetColTarget(D3DXCOLOR ColTarget);	// �ڕW�F��ݒ�

protected:

	static const float INITSPAN;
	static const float SPAN_X;
	static const float SPAN_Y;

private:

	void DeleteCheck();		// ���Ŕ���

	STYLE m_Style;				// �ז����X�^�C��
	D3DXVECTOR3 m_PosTarget;	// �ڕW���W
	D3DXVECTOR3 m_RotTarget;	// �ڕW����
	D3DXVECTOR3 m_SizeTarget;	// �ڕW�T�C�Y
	D3DXCOLOR m_ColTarget;		// �ڕW�F
};

#endif // _OBSTACLE_H_