//============================================================================
// 
// 邪魔物マネージャー、ヘッダファイル [obstacle_manager.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBSTACLE_MANAGER_H_
#define _OBSTACLE_MANAGER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "obstacle.h"

//****************************************************
// 邪魔物マネージャー
//****************************************************
class CObstacle_Manager final
{
public:

	HRESULT Init();	// 初期設定
	void Release();	// 解放
	void Update();	// 更新処理

	static CObstacle_Manager* GetInstance();	// 邪魔物マネージャーを取得

private:

	CObstacle_Manager();	// コンストラクタ
	~CObstacle_Manager();	// デストラクタ

	void ImportObstacle();	// 邪魔物をインポート
	void Create();			// 生成
	void Uninit();			// 終了処理

	bool m_bEndUpdate;						// 更新判定
	std::ifstream m_Import;					// ファイル読み取り用
	int m_nCast;							// キャストタイム
	static CObstacle_Manager* m_pInstance;	// 自インスタンス
};

#endif	// _OBSTACLE_H_