#pragma once
//------  SwapChain.h  ------  //…　スワップチェイン作成ヘッダーファイル　…//
//---  参照まとめ  ---
#include"../../Windows/Window.h"
#include"Device.h"
#include"DrawingCommandRelated/DrawingCommandRelated.h"

namespace MyEngineGame::RenderingPipline {
	//@brief	//…　スワップチェイン作成クラス　…//
	class SwapChain final
	{
	public:
		SwapChain() = default;
		~SwapChain() = default;

		//@brief	//…　SwapChain作成関数　…//
		//@return	作成の成否
		[[nodiscard]] bool Create(const CommandQueue& Queue_)noexcept;

		//@brief	//…　SwapChain取得関数　…//
		//@return	SwapChainのポインター
		[[nodiscard]] IDXGISwapChain3* Get()const noexcept;

		//@brief	//…　SwapChain設定取得関数　…//
		//@return	SwapChain設定
		[[nodiscard]] DXGI_SWAP_CHAIN_DESC1 GetDesc()const noexcept;
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain3> SwapChain_{};	//スワップチェインインスタンス
		DXGI_SWAP_CHAIN_DESC1					Desc_{};		//スワップチェイン設定
	};
}