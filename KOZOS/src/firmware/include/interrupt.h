/*****************************************************************************
	オーダー	: 割り込み ヘッダファイル
	CPU			: H8 3069F
	コンパイラ	: h8300-elf-gcc version 3.4.6
	ファイル名	: interrpt.h
	接頭辞		: sv
	作成日時	: 2013-11-14
*****************************************************************************/
/*
	改訂履歴
*/

#ifndef _INTERRPT_H_
#define _INTERRPT_H_

/*****************************************************************************
	インクルード
*****************************************************************************/

/*****************************************************************************
	定義
*****************************************************************************/
/* "SV"は"Software Vector"の略 */
/* 割り込み領域の先頭アドレス */
#define	SV_ADDR			(&softvec)

/* 割り込み領域の先頭アドレス */
#define	SOFTVECS		((SV_HANDLER_T**)SV_ADDR)

/* 割り込み有効化 */
#define	INTR_ENABLE(...)	asm	volatile	("andc.b #0x3F,ccr")

/* 割り込み無効化(禁止) */
#define	INTR_DISABLE(...)	asm	volatile	("orc.b #0xc0,ccr")

/*****************************************************************************
	型定義、構造体定義
*****************************************************************************/
/*
  割り込みハンドラ用の型定義
  ・ハードウェア割り込み
  ・ソフトウェア割り込み(システムコールなど)
  ・例外処理 
 */
/*
   ※型を再定義する意図
   本プロジェクトのように小規模なものであれば、プリミティブな型を使用しても
   問題ないが、プロジェクトが巨大化してきた場合に、
   「この関数の第一引数は何を表すのか?」と意味が不明瞭にならないようにし、
   内容を明確にすることができる
 */
typedef	short	SV_T;

/* 割り込みハンドラの型 */
typedef	void	(SV_HANDLER_T)(SV_T type, uint32 ulSP);	

/*****************************************************************************
	プロトタイプ宣言
*****************************************************************************/
/* 割り込み初期化 */
int16	svInit(void);

/* 割り込みハンドラ設定関数 */
int16	svSetHandler(SV_T type, SV_HANDLER_T* pHandler);

/* 共通割り込みハンドラ */
void	svInterrupt(SV_T type, uint32 ulSP);

/*****************************************************************************
	外部変数 
*****************************************************************************/
/* ソフトウェア割り込みベクタ */
/* リンカスクリプトで定義してある */
extern	char	softvec;

#endif /* _INTERRPT_H_ */

/***** End Of File *****/

