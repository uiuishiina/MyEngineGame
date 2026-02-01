//------  Window.cpp  ------  //…　Windowsウィンドウ作成ソースファイル　…//
//---  参照  ---
#include"Window.h"
#include<cassert>

//namespace
namespace {
	//@brief	//…　Windowsプロシージャ関数　…//
	LRESULT CALLBACK Procedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

        switch (uMsg)
        {
        case WM_DESTROY:    //Windows終了処理
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

namespace MyEngineGame {

    //@brief	//…　Windowsウィンドウ作成関数　…//
    //@param	instance インスタンスハンドル
    //@param	width	横幅(任意)
    //@param	height	縦幅(任意)
    //@param	name	ウィンドウ名(任意)
    //@return	作成の成否
    [[nodiscard]] bool Window::Create(HINSTANCE instance, int width, int height, std::string_view name)noexcept {

        //ウィンドウクラス定義
        WNDCLASS wc{};
        wc.lpfnWndProc = Procedure;
        wc.hInstance = instance;
        wc.lpszClassName = name.data();
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

        // ウィンドウクラスの登録
        RegisterClass(&wc);

        // ウィンドウの作成
        MyHandle_ = CreateWindow(wc.lpszClassName, wc.lpszClassName,
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            nullptr, nullptr, instance, nullptr);
        if (!MyHandle_) {
            assert(false && "Window Creation Failed.");
            return false;
        }

        //ウィンドウの表示
        ShowWindow(MyHandle_, SW_SHOW);

        // ウィンドウを更新
        UpdateWindow(MyHandle_);

        // ウィンドウのサイズを保存
        Width_ = width;
        Height_ = height;

        // 成功を返す
        return true;
    }

    //@brief	//…　ウィンドウループ関数　…//
    //@return	ループの可否
    [[nodiscard]] bool Window::MessageLoop() const noexcept {

        //
        MSG msg{};  // メッセージを格納する構造体
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))  //メッセージを処理するためループ
        {
            if (msg.message == WM_QUIT) {
                return false;  // WM_QUITメッセージが来たら終了
            }
            TranslateMessage(&msg);  // キーボードメッセージを使いやすい形に変換
            DispatchMessage(&msg);   // 適切なウィンドウプロシージャに送信
        }

        return true;
    }

    //@brief	//…　ウィンドウハンドル取得関数　…//
    //@return	ウィンドウハンドル
    [[nodiscard]] HWND Window::GetHandle()const noexcept {
        if (!MyHandle_) {
            assert(false && "Not Found WHND. Possibly it has not been created or has been deleted.");
        }
        return MyHandle_;
    }

    //@brief	//…　ウィンドウサイズ取得関数　…//
    //@return	ウィンドウサイズ
    [[nodiscard]] std::pair<int, int> Window::GetSize()const noexcept {
        return { Width_ ,Height_ };
    }
}