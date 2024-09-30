//============================================================================
// 
// 邪魔物マネージャー [obstacle_manager.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "obstacle_manager.h"
#include "obstacle.h"
#include "obstacle_normal.h"
#include "obstacle_speedy.h"
#include "obstacle_turn.h"
#include "obstacle_wave.h"
#include "obstacle_twist.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CObstacle_Manager* CObstacle_Manager::m_pInstance = nullptr;	// 自インスタンス

//============================================================================
// 初期設定
//============================================================================
HRESULT CObstacle_Manager::Init()
{
	return S_OK;
}

//=============================================================================
// 解放
//=============================================================================
void CObstacle_Manager::Release()
{
	if (m_pInstance != nullptr)
	{
		// フェードの終了処理
		m_pInstance->Uninit();

		// メモリを解放
		delete m_pInstance;

		// ポインタを初期化
		m_pInstance = nullptr;
	}
}

//============================================================================
// 更新処理
//============================================================================
void CObstacle_Manager::Update()
{
	if (!m_bEndUpdate)
	{
		// 邪魔物を読み込む
		ImportObstacle();
	}
}

//============================================================================
// 邪魔物マネージャーを取得
//============================================================================
CObstacle_Manager* CObstacle_Manager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// 生成
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// コンストラクタ
//============================================================================
CObstacle_Manager::CObstacle_Manager() :
	m_bEndUpdate{ false },
	m_Import{ "Data\\TXT\\obstacle_list.txt" },
	m_nCast{ 0 }
{

}

//============================================================================
// デストラクタ
//============================================================================
CObstacle_Manager::~CObstacle_Manager()
{

}

//============================================================================
// 邪魔物をインポート
//============================================================================
void CObstacle_Manager::ImportObstacle()
{
	if (m_nCast > 0)
	{
		m_nCast--;

		return;
	}

	// 文章格納先
	std::string List;

	// テキストを読み取る
	std::getline(m_Import, List);

	if (List == "END_SCRIPT")
	{
		m_bEndUpdate = true;

		return;
	}

#if 0
	// 情報格納先
	D3DXVECTOR3 Pos{ 0.0f, 0.0f, 0.0f }, Velocity{ 0.0f, 0.0f, 0.0f };

	// 座標変換
	std::string ConvertPos[3];

	for (int i = 0; i < 3; i++)
	{
		// 数値部分のみ抽出する
		ConvertPos[i] = List.substr(List.find(":") + 1, List.find(",") - (List.find(":") + 1));

		// 不必要になった部分を削除する
		List.erase(0, List.find(",") + 1);
	}

	// 抽出した数値を座標に変換
	Pos.x = std::stof(ConvertPos[0]);
	Pos.y = std::stof(ConvertPos[1]);
	Pos.z = std::stof(ConvertPos[2]);

	/*------------------------------------------------------*/

	// 移動量変換
	std::string ConvertVelocity[3];

	for (int i = 0; i < 3; i++)
	{
		// 数値部分のみ抽出する
		ConvertVelocity[i] = List.substr(List.find(":") + 1, List.find(",") - (List.find(":") + 1));

		// 不必要になった部分を削除する
		List.erase(0, List.find(",") + 1);
	}

	// 抽出した数値を座標に変換
	Velocity.x = std::stof(ConvertVelocity[0]);
	Velocity.y = std::stof(ConvertVelocity[1]);
	Velocity.z = std::stof(ConvertVelocity[2]);
#else
	// 移動スタイル設定
	std::string ConvertMoveStyle;

	// 数値部分のみ抽出する
	ConvertMoveStyle = List.substr(List.find(":") + 1, List.find(",") - (List.find(":") + 1));

	// 不必要になった部分を削除する
	List.erase(0, List.find(",") + 1);
#endif

	/*------------------------------------------------------*/

	// 種類を識別する文字格納先
	std::string ConvertType;

	// 種類を抽出する
	ConvertType = List.substr(List.find(":") + 1, List.find(",") - (List.find(":") + 1));

	// 不必要になった部分を削除する
	List.erase(0, List.find(",") + 1);

	// 種類に応じて生成する
	if (ConvertType == "normal")
	{ // ノーマル邪魔物
		CObstacle_Normal::Create(std::stoi(ConvertMoveStyle));
		//CObstacle_Normal* pNormal{ CObstacle_Normal::Create(std::stoi(ConvertMoveStyle)) };
		//pNormal->SetPos(Pos);
		//pNormal->SetVelocity(Velocity);
	}
	else if (ConvertType == "speedy")
	{ // スピーディ邪魔物
		CObstacle_Speedy::Create(std::stoi(ConvertMoveStyle));
	}
	else if (ConvertType == "turn")
	{ // ターン邪魔物
		CObstacle_Turn::Create(std::stoi(ConvertMoveStyle));
	}
	else if (ConvertType == "wave")
	{ // ウェーブ邪魔物
		CObstacle_Wave::Create(std::stoi(ConvertMoveStyle));
	}
	else if (ConvertType == "twist")
	{ // ツイスト邪魔物
		CObstacle_Twist::Create(std::stoi(ConvertMoveStyle));
	}

	/*------------------------------------------------------*/

	// キャスト時間の格納先
	std::string ConvertCast;

	// 種類を抽出する
	ConvertCast = List.substr(List.find(":") + 1, List.find(",") - (List.find(":") + 1));

	// 不必要になった部分を削除する
	List.erase(0, List.find(",") + 1);

	// キャスト時間を設定
	m_nCast = std::stoi(ConvertCast);
}

//============================================================================
// 生成
//============================================================================
void CObstacle_Manager::Create()
{
	if (m_pInstance != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// インスタンスを生成
	m_pInstance = DBG_NEW CObstacle_Manager{};
}

//============================================================================
// 終了処理
//============================================================================
void CObstacle_Manager::Uninit()
{

}