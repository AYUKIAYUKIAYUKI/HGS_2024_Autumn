//============================================================================
// 
// �ז����}�l�[�W���[ [obstacle_manager.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "obstacle_manager.h"
#include "obstacle.h"
#include "obstacle_normal.h"
#include "obstacle_speedy.h"
#include "obstacle_turn.h"
#include "obstacle_wave.h"
#include "obstacle_twist.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
CObstacle_Manager* CObstacle_Manager::m_pInstance = nullptr;	// ���C���X�^���X

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CObstacle_Manager::Init()
{
	return S_OK;
}

//=============================================================================
// ���
//=============================================================================
void CObstacle_Manager::Release()
{
	if (m_pInstance != nullptr)
	{
		// �t�F�[�h�̏I������
		m_pInstance->Uninit();

		// �����������
		delete m_pInstance;

		// �|�C���^��������
		m_pInstance = nullptr;
	}
}

//============================================================================
// �X�V����
//============================================================================
void CObstacle_Manager::Update()
{
	if (!m_bEndUpdate)
	{
		// �ז�����ǂݍ���
		ImportObstacle();
	}
}

//============================================================================
// �ז����}�l�[�W���[���擾
//============================================================================
CObstacle_Manager* CObstacle_Manager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// ����
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// �R���X�g���N�^
//============================================================================
CObstacle_Manager::CObstacle_Manager() :
	m_bEndUpdate{ false },
	m_Import{ "Data\\TXT\\obstacle_list.txt" },
	m_nCast{ 0 }
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CObstacle_Manager::~CObstacle_Manager()
{

}

//============================================================================
// �ז������C���|�[�g
//============================================================================
void CObstacle_Manager::ImportObstacle()
{
	if (m_nCast > 0)
	{
		m_nCast--;

		return;
	}

	// ���͊i�[��
	std::string List;

	// �e�L�X�g��ǂݎ��
	std::getline(m_Import, List);

	if (List == "END_SCRIPT")
	{
		m_bEndUpdate = true;

		return;
	}

#if 0
	// ���i�[��
	D3DXVECTOR3 Pos{ 0.0f, 0.0f, 0.0f }, Velocity{ 0.0f, 0.0f, 0.0f };

	// ���W�ϊ�
	std::string ConvertPos[3];

	for (int i = 0; i < 3; i++)
	{
		// ���l�����̂ݒ��o����
		ConvertPos[i] = List.substr(List.find(":") + 1, List.find(",") - (List.find(":") + 1));

		// �s�K�v�ɂȂ����������폜����
		List.erase(0, List.find(",") + 1);
	}

	// ���o�������l�����W�ɕϊ�
	Pos.x = std::stof(ConvertPos[0]);
	Pos.y = std::stof(ConvertPos[1]);
	Pos.z = std::stof(ConvertPos[2]);

	/*------------------------------------------------------*/

	// �ړ��ʕϊ�
	std::string ConvertVelocity[3];

	for (int i = 0; i < 3; i++)
	{
		// ���l�����̂ݒ��o����
		ConvertVelocity[i] = List.substr(List.find(":") + 1, List.find(",") - (List.find(":") + 1));

		// �s�K�v�ɂȂ����������폜����
		List.erase(0, List.find(",") + 1);
	}

	// ���o�������l�����W�ɕϊ�
	Velocity.x = std::stof(ConvertVelocity[0]);
	Velocity.y = std::stof(ConvertVelocity[1]);
	Velocity.z = std::stof(ConvertVelocity[2]);
#else
	// �ړ��X�^�C���ݒ�
	std::string ConvertMoveStyle;

	// ���l�����̂ݒ��o����
	ConvertMoveStyle = List.substr(List.find(":") + 1, List.find(",") - (List.find(":") + 1));

	// �s�K�v�ɂȂ����������폜����
	List.erase(0, List.find(",") + 1);
#endif

	/*------------------------------------------------------*/

	// ��ނ����ʂ��镶���i�[��
	std::string ConvertType;

	// ��ނ𒊏o����
	ConvertType = List.substr(List.find(":") + 1, List.find(",") - (List.find(":") + 1));

	// �s�K�v�ɂȂ����������폜����
	List.erase(0, List.find(",") + 1);

	// ��ނɉ����Đ�������
	if (ConvertType == "normal")
	{ // �m�[�}���ז���
		CObstacle_Normal::Create(std::stoi(ConvertMoveStyle));
		//CObstacle_Normal* pNormal{ CObstacle_Normal::Create(std::stoi(ConvertMoveStyle)) };
		//pNormal->SetPos(Pos);
		//pNormal->SetVelocity(Velocity);
	}
	else if (ConvertType == "speedy")
	{ // �X�s�[�f�B�ז���
		CObstacle_Speedy::Create(std::stoi(ConvertMoveStyle));
	}
	else if (ConvertType == "turn")
	{ // �^�[���ז���
		CObstacle_Turn::Create(std::stoi(ConvertMoveStyle));
	}
	else if (ConvertType == "wave")
	{ // �E�F�[�u�ז���
		CObstacle_Wave::Create(std::stoi(ConvertMoveStyle));
	}
	else if (ConvertType == "twist")
	{ // �c�C�X�g�ז���
		CObstacle_Twist::Create(std::stoi(ConvertMoveStyle));
	}

	/*------------------------------------------------------*/

	// �L���X�g���Ԃ̊i�[��
	std::string ConvertCast;

	// ��ނ𒊏o����
	ConvertCast = List.substr(List.find(":") + 1, List.find(",") - (List.find(":") + 1));

	// �s�K�v�ɂȂ����������폜����
	List.erase(0, List.find(",") + 1);

	// �L���X�g���Ԃ�ݒ�
	m_nCast = std::stoi(ConvertCast);
}

//============================================================================
// ����
//============================================================================
void CObstacle_Manager::Create()
{
	if (m_pInstance != nullptr)
	{ // ��d�����֎~
		assert(false);
	}

	// �C���X�^���X�𐶐�
	m_pInstance = DBG_NEW CObstacle_Manager{};
}

//============================================================================
// �I������
//============================================================================
void CObstacle_Manager::Uninit()
{

}