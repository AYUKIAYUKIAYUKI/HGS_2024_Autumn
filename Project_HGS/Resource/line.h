//--------------------------------------------------------------------------------
// 
// �v���C���[���ړ��ł���� [line.h]
// Author: Taito Jin
// 
//--------------------------------------------------------------------------------
#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"

//---------------------------------------------------
// using �錾
//---------------------------------------------------
using namespace HGSAutumn240930;

//****************************************************
// �v���C���[���ړ��ł�����̃N���X
//****************************************************
class CLine : public CObject_2D
{
public:
	CLine(int nPriority = static_cast<int>(LAYER::BACK));	// �R���X�g���N�^
	~CLine() override = default;							// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	void SetLineSegment2D(const Collision::LineSegment2D& inSegment) { m_LineSegment2D = inSegment; }	// ���̐ݒ�
	const Collision::LineSegment2D& GetLineSegment2D() const { return m_LineSegment2D; };				// ���̎擾

	// ����
	static CLine* Create(
		const D3DXVECTOR3& inPos,		// �ʒu
		const D3DXVECTOR3& inSize,		// �T�C�Y
		const D3DXVECTOR2& inStartPos, 	// �n�_
		const D3DXVECTOR2& inEndPos);	// �I�_

private:
	CLine(const CLine&) = delete;
	void operator=(const CLine&) = delete;

	Collision::LineSegment2D m_LineSegment2D;	// ��
};
