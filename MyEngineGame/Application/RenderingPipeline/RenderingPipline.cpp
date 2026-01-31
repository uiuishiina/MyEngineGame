//------  RenderingPipline.cpp  ------  //…　レンダリングパイプライン作成ソースファイル　…//
//---  参照まとめ  ---
#include"RenderingPipline.h"
#include<cassert>

namespace MyEngineGame::RenderingPipline {

	//@brief	//…　レンダリングパイプライン作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool MEGRP :: Initialization()noexcept {

		//Device作成
		if (!Device::Instance().Create()) {
			assert(false && "MEGRP::Device.Create() failed.");
		}


		return true;
	}
}
