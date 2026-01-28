#pragma once
//------  RenderingPipline.h  ------  //…　レンダリングパイプライン作成ヘッダーファイル　…//
//---  参照まとめ  ---
//…　Windows　…//
#include "../Windows/Window.h"
//…　DirectX　…//


namespace MyEngineGame::RenderingPipline {
	//@brief	
	class MEGRP final
	{
	public:
		//@brief	//…　レンダリングパイプラインインスタンス取得関数　…//
		//@return	レンダリングパイプラインインスタンス
		static MEGRP& Instance() noexcept {
			static MEGRP instance;
			return instance;
		}

		//@brief	//…　レンダリングパイプライン作成関数　…//
		//@return	作成の成否
		[[nodsincard]] bool Initialization()noexcept;
	private:

	};
}