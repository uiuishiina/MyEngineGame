//------  ApplicationMain.cpp  ------  //…　アプリケーションメインファイル　…//
//---  参照まとめ  ---
//…　Windows　…//
#include"../Windows/Window.h"
//…　RenderingPipline　…//
#include"../RenderingPipeline/RenderingPipline.h"


#include<cassert>

using namespace MyEngineGame;//今回使用する名前

//@brief	//…　アプリケーションメインクラス　…//
class Application final
{
public:
	Application() = default;
	~Application() = default;

	//@brief	//…　アプリケーション作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool APPInitialization(HINSTANCE hInstance) noexcept {
		
		//ウィンドウ作成
		if (!Window::Instance().Create(hInstance)) {
			return false;
		}

		//MEGRP作成
		if (!MyEngineGame::RenderingPipline::MEGRP::Instance().Initialization()) {
			return false;
		}

		return true;
	}

	//@brief	//…　アプリケーションループ関数　…//
	void APPLoop()const noexcept {
		while (Window::Instance().MessageLoop())
		{
			MyEngineGame::RenderingPipline::MEGRP::Instance().BeforeUpdate();
			//UpData処理
			MyEngineGame::RenderingPipline::MEGRP::Instance().LateUpdate();
		}
	}
private:
};

//@brief	//…　メイン関数　…//
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	Application App;

	if (!App.APPInitialization(hInstance)) {
		assert(false && "Application initialization failed.");
		return 1;
	}

	App.APPLoop();

    return 0;
}