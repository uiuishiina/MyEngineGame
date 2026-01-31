#pragma once
//------  RenderingPipline.h  ------  //…　レンダリングパイプライン作成ヘッダーファイル　…//
//---  参照まとめ  ---
#include <unordered_map>
//…　Windows　…//
#include "../Windows/Window.h"
//…　DirectX　…//
#include"DirectX/Device.h"
#include"DirectX/DrawingCommandRelated/DrawingCommandRelated.h"


namespace MyEngineGame::RenderingPipline {

	//@brief	//…　レンダリングパイプラインインスタンス作成クラス　…//
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
		[[nodiscard]] bool Initialization()noexcept;
		
	private:

	};
}