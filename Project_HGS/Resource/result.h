//============================================================================
// 
// リザルト、ヘッダファイル [result.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _RESULT_H_
#define _RESULT_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "scene.h"

//****************************************************
// リザルトクラス
//****************************************************
class CResult : public CScene
{
public:

	CResult();				// コンストラクタ
	~CResult() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理
};

#endif // _RESULT_H_