//--------------------------------------------------------------------------------
// 
// キャラクター [character.h]
// Author: Taito Jin
// 
//--------------------------------------------------------------------------------
#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"

//****************************************************
// キャラクタークラス
//****************************************************
class CCharacter : public CObject_2D
{
public:
	CCharacter(int nPriority = static_cast<int>(LAYER::NONE));	// コンストラクタ
	~CCharacter() override = default;							// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	void SetMove(const D3DXVECTOR3& inMove);	// 移動量設定
	const D3DXVECTOR3& GetMove() const;			// 移動量取得

	static CCharacter* Create();	// 生成

private:
	CCharacter(const CCharacter&) = delete;
	void operator=(const CCharacter&) = delete;

	D3DXVECTOR3 m_Move;		// 移動量
};
