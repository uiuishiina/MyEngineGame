//------  SwapChain.cpp  ------  //…　スワップチェイン作成ソースファイル　…//
//---  参照まとめ  ---
#include"SwapChain.h"
#include<cassert>

namespace MyEngineGame::RenderingPipline {

	//@brief	//…　SwapChain作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool SwapChain :: Create(const CommandQueue& Queue_)noexcept {

		//ウィンドウのサイズ取得
		const auto [w, h] = Window::Instance().GetSize();

		//スワップチェインの設定
		Desc_.BufferCount			= 2;
		Desc_.Width					= w;
		Desc_.Height				= h;
		Desc_.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
		Desc_.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		Desc_.SwapEffect			= DXGI_SWAP_EFFECT_FLIP_DISCARD;
		Desc_.SampleDesc.Count		= 1;

		//仮のスワップチェインを作成
		Microsoft::WRL::ComPtr <IDXGISwapChain1> ProvisionalSwapChain_{};
		auto hr = Device::Instance().GetDXGI().GetFactory()->CreateSwapChainForHwnd(Queue_.Get(), Window::Instance().GetHandle(), &Desc_, nullptr, nullptr, &ProvisionalSwapChain_);
		if (FAILED(hr)) {
			assert(false && "ProvisionalSwapChain_ Creation Failed.");
			return false;
		}
		//スワップチェインのアップグレード
		hr = ProvisionalSwapChain_->QueryInterface(IID_PPV_ARGS(&SwapChain_));
		if (FAILED(hr)) {
			assert(false && "SwapChain_ UpGrade Failed.");
			return false;
		}

		return true;
	}

	//@brief	//…　SwapChain取得関数　…//
	//@return	SwapChainのポインター
	[[nodiscard]] IDXGISwapChain3* SwapChain :: Get()const noexcept {
		assert(SwapChain_ && "Not Found SwapChain_.");
		return SwapChain_.Get();
	}

	//@brief	//…　SwapChain設定取得関数　…//
	//@return	SwapChain設定
	[[nodiscard]] DXGI_SWAP_CHAIN_DESC1 SwapChain :: GetDesc()const noexcept {
		assert(SwapChain_ && "Not Found SwapChain_.");
		return Desc_;
	}
}