//============================================================================
// 
// �`���[�g���A���A�w�b�_�t�@�C�� [tutorial.h]
// Author : �v�ێs�ĕ�
// 
//============================================================================

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "scene.h"
#include "fade.h"

//****************************************************
// �`���[�g���A���N���X
//****************************************************
class CTutorial : public CScene
{
public:

	CTutorial();			// �R���X�g���N�^
	~CTutorial() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��
};

#endif // _TITLE_H_