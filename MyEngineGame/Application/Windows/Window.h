#pragma once
//------  Window.h  ------  //…　Windowsウィンドウ作成ヘッダーファイル　…//
//---  参照  ---
#include <Windows.h>
#include <string>

namespace MyEngineGame {
	//@brief	//…　Windowsウィンドウ作成クラス　…//
	class Window final
	{
	public:
		//@brief	//…　Windowsインスタンス取得関数　…//
		//@return	Windowsインスタンス
		static Window& Instance() noexcept {
			static Window Instance;
			return Instance;
		}

		//@brief	//…　Windowsウィンドウ作成関数　…//
		//@param	instance	インスタンスハンドル
		//@param	width		横幅		初期::1280
		//@param	height		縦幅		初期::720
		//@param	name		ウィンドウ名	初期::MyEngineGame
		//@return	作成の成否
		[[nodiscard]] bool Create(HINSTANCE instance, int width = 1280, int height = 720, std::string_view name = "MyEngineGame")noexcept;

		//@brief	//…　ウィンドウループ関数　…//
		//@return	ループの可否
		[[nodiscard]] bool MessageLoop() const noexcept;

		//@brief	//…　ウィンドウハンドル取得関数　…//
		//@return	ウィンドウハンドル
		[[nodiscard]] HWND GetHandle()const noexcept;

		//@brief	//…　ウィンドウサイズ取得関数　…//
		//@return	ウィンドウサイズ
		[[nodiscard]] std::pair<int, int> GetSize()const noexcept;
	private:
		Window() = default;
		~Window() = default;

		//…　クラス変数　…//
		int Width_{};		//横幅
		int Height_{};		//縦幅
		HWND MyHandle_{};	//ウィンドウハンドル
	};
}