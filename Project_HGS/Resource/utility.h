//============================================================================
// 
// 便利関数、ヘッダファイル [utility.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _UTILITY_H_
#define _UTILITY_H_	// 二重インクルード防止

//****************************************************
// 便利関数クラス
//****************************************************
class CUtility final
{
public:

	HRESULT Init();	// 初期設定
	void Release();	// 破棄

	static CUtility* GetInstance();	// 便利関数を取得

	// 乱数生成
	template <typename T> T GetRandomValue();

	// ダウンキャスト
	template <typename T1, typename T2> T1* DownCast(T2* pBase);

private:

	CUtility();		// コンストラクタ
	~CUtility();	// デストラクタ

	void Create();	// 生成
	void Uninit();	// 終了処理

	static CUtility* m_pInstance;	// 便利関数
};

//============================================================================
// 乱数生成
//============================================================================
template <typename T> T CUtility::GetRandomValue()
{
	// 数値の取る範囲を設定
	const int nRange = 180;

	// 倍の範囲からランダムな整数を生成
	int random{ rand() % (nRange * 2) };

	// もとの範囲を超えていた場合正負を反転
	if (random > nRange)
	{
		random %= nRange;
		random *= -1;
	}

	// 整数を指定された型にキャスト
	return static_cast<T>(random);
}

//============================================================================
// ダウンキャスト
//============================================================================
template <typename T1, typename T2> T1* CUtility::DownCast(T2* pBase)
{
	// 引数のオブジェクトを指定されたクラスにダウンキャスト
	T1* pObj{ dynamic_cast<T1*>(pBase) };

	// ダウンキャスト失敗
	if (!pObj)
	{
		assert(false);
	}

	return pObj;
}

#endif // _UTILITY_H_