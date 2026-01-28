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

		return true;
	}

	//@brief	//…　アプリケーションループ関数　…//
	void APPLoop()const noexcept {
		while (Window::Instance().MessageLoop())
		{
			//UpData処理
		}
	}
private:
};

//@brief	//…　メイン関数クラス　…//
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	Application App;

	if (!App.APPInitialization(hInstance)) {
		assert(false && "Application initialization failed.");
		return 1;
	}
    return 0;
}