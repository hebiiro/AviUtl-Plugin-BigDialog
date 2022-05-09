# AviUtl プラグイン - ダイアログ巨大化

* 3.0.0 by 蛇色 - 2022/05/09 「新規プロジェクトの作成」を修正
* 2.0.0 by 蛇色 - 2022/02/24 リソースがおかしかった問題を修正
* 1.0.0 by 蛇色 - 2022/02/06 初版

AviUtl のダイアログを巨大化してテキストが途切れないようにします。

|  巨大化あり  |  巨大化なし  |
| ---- | ---- |
|  ![ダイアログ巨大化](https://user-images.githubusercontent.com/96464759/152672354-5333ce1b-f276-47d9-94fb-eaa0e1f50407.png)  |  ![ダイアログ巨大化なし](https://user-images.githubusercontent.com/96464759/152672353-57443323-9022-4241-b73c-a67890e989e1.png)  |  

## 導入方法

1. 以下のファイルを AviUtl の Plugins フォルダに配置します。
	* BigDialog.aul

## 動作確認

* (必須) AviUtl 1.10 & 拡張編集 0.92 http://spring-fragrance.mints.ne.jp/aviutl/
* (共存確認) patch.aul r21 https://scrapbox.io/ePi5131/patch.aul

## クレジット

* Microsoft Research Detours Package https://github.com/microsoft/Detours
* aviutl_exedit_sdk https://github.com/ePi5131/aviutl_exedit_sdk
* Common Library https://github.com/hebiiro/Common-Library
