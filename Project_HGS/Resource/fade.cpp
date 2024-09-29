//============================================================================
// 
// 旧フェード遷移処理 [fade.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "fade.h"

// デバイス取得用
#include "renderer.h"

// シーン取得用
#include "manager.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CFade* CFade::m_pInstnce = nullptr;

//============================================================================
// 初期設定
//============================================================================
HRESULT CFade::Init()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// 頂点バッファの生成
	pDev->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	if (m_pVtxBuff == nullptr)
	{ // 生成失敗
		return E_FAIL;
	}

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx{};

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	// 位置の設定
	pVtx[0].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[1].pos = { SCREEN_WIDTH, 0.0f, 0.0f };
	pVtx[2].pos = { 0.0f, SCREEN_HEIGHT, 0.0f };
	pVtx[3].pos = { SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f };

	// 除算数の設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 色の設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	// テクスチャの設定
	pVtx[0].tex = { 0.0f, 0.0f };
	pVtx[1].tex = { 1.0f, 0.0f };
	pVtx[2].tex = { 0.0f, 1.0f };
	pVtx[3].tex = { 1.0f, 1.0f };

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 解放
//=============================================================================
void CFade::Release()
{
	if (m_pInstnce != nullptr)
	{
		// フェードの終了処理
		m_pInstnce->Uninit();

		// メモリを解放
		delete m_pInstnce;

		// ポインタを初期化
		m_pInstnce = nullptr;
	}
}

//============================================================================
// 更新処理
//============================================================================
void CFade::Update()
{
	// フェード関連の判定が何も出てなければ処理を行わない
	if (!m_bFadeIn && !m_bFadeOut)
	{
		return;
	}

	// フェードイン処理
	FadeIn();

	// フェードアウト処理
	FadeOut();

	// 頂点情報の設定処理
	SetVtx();
}

//============================================================================
// 描画処理
//============================================================================
void CFade::Draw()
{
	// フェード関連の判定が何も出てなければ処理を行わない
	if (!m_bFadeIn && !m_bFadeOut)
	{
		return;
	}

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// 頂点バッファをデータストリームに設定
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDev->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDev->SetTexture(0, nullptr);

	// ポリゴンの描画
	pDev->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,										// 頂点情報の先頭アドレス
		2);										// プリミティブ数
}

//============================================================================
// フェード設定
//============================================================================
void CFade::SetFade(CScene::MODE Mode)
{
	CFade* pFade{ GetInstance() };

	// フェード関連の判定が何も出てなければ
	if (!pFade->m_bFadeIn && !pFade->m_bFadeOut)
	{
		// フェードイン判定を出す
		pFade->m_bFadeIn = true;

		// 次のモードの情報を保持しておく
		pFade->m_NextMode = Mode;
	}
}

//============================================================================
// フェードを取得
//============================================================================
CFade* CFade::GetInstance()
{
	if (m_pInstnce == nullptr)
	{
		// 生成
		m_pInstnce->Create();
	}

	return m_pInstnce;
}

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CFade::CFade()
{
	m_pVtxBuff = nullptr;				// 頂点バッファのポインタ
	m_NextMode = CScene::MODE::NONE;	// 次のモード
	m_bFadeIn = false;					// フェードイン
	m_bFadeOut = false;					// フェードアウト
	m_fBrightness = 0.0f;				// 明度
}

//============================================================================
// デストラクタ
//============================================================================
CFade::~CFade()
{

}

//============================================================================
// 生成
//============================================================================
void CFade::Create()
{
	if (m_pInstnce != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// インスタンスを生成
	m_pInstnce = DBG_NEW CFade{};
}

//============================================================================
// 終了処理
//============================================================================
void CFade::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================================================================
// フェードイン
//============================================================================
void CFade::FadeIn()
{
	if (m_bFadeIn)
	{
		// 明度が上がっていく
		m_fBrightness += 0.05f;

		// 最大明度到達で
		if (m_fBrightness > 1.0f)
		{
			// 明度を最高に固定
			m_fBrightness = 1.0f;

			// フェードインを終了
			m_bFadeIn = false;

			// 次のシーンへ変更
			CManager::SetScene(m_NextMode);

			// フェードアウトを開始
			m_bFadeOut = true;
		}
	}
}

//============================================================================
// フェードアウト
//============================================================================
void CFade::FadeOut()
{
	if (m_bFadeOut)
	{
		// 明度が下がっていく
		m_fBrightness += -0.05f;

		// 最低明度到達で
		if (m_fBrightness < 0.0f)
		{
			// 明度を最低に固定
			m_fBrightness = 0.0f;

			// フェードアウトを終了
			m_bFadeOut = false;
		}
	}
}

//============================================================================
// 頂点情報の設定
//============================================================================
void CFade::SetVtx()
{
	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	// 色の設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fBrightness);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fBrightness);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fBrightness);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fBrightness);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}