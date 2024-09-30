//============================================================================
// 
// シーン管理、ヘッダファイル [scene.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _SCENE_H_
#define _SCENE_H_	// 二重インクルード防止

//****************************************************
// シーン管理クラス
//****************************************************
class CScene
{
public:

	//****************************************************
	// シーンの種類
	//****************************************************
	enum class MODE
	{
		NONE = 0,	// 無し
		TITLE,		// タイトル
		TUTORIAL,	// チュートリアル
		GAME,		// ゲーム
		RESULT_GAMECLEAR,		// リザルト
		RESULT_GAMEOVER,		// リザルト
		MAX,
	};

	CScene();			// コンストラクタ
	virtual ~CScene();	// デストラクタ

	virtual HRESULT Init();	// 初期設定
	virtual void Uninit();	// 終了処理
	virtual void Update();	// 更新処理
	virtual void Draw();	// 描画処理

	MODE GetMode();	// 現在のモードを取得する

	static CScene* Create(MODE mode);	// 生成

private:

	MODE m_mode;	// 現在のモード
};

#endif // _SCENE_H_