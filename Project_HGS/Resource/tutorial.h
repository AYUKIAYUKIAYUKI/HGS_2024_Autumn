//============================================================================
// 
// チュートリアル、ヘッダファイル [tutorial.h]
// Author : 久保市篤武
// 
//============================================================================

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "scene.h"
#include "fade.h"

//****************************************************
// チュートリアルクラス
//****************************************************
class CTutorial : public CScene
{
public:

	CTutorial();			// コンストラクタ
	~CTutorial() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理
};

#endif // _TITLE_H_