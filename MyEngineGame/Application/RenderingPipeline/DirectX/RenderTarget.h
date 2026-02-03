#pragma once
//------  RenderTarget.h  ------  //…　レンダーターゲット作成ヘッダーファイル　…//
//---  参照  ---
#include"Device.h"
#include"SwapChain.h"
#include"DescriptorHeap/DescriptorHeap_Administrator.h"

namespace MyEngineGame::RenderingPipline {

	//@brief	//…　レンダーターゲット作成クラス　…//
	class RenderTarget final
	{
	public:
		RenderTarget() = default;
		~RenderTarget() = default;

		//@brief	//…　レンダーターゲット作成関数　…//
		//@return	作成の成否
		[[nodiscard]] bool Create(const SwapChain& swapChain_)noexcept;

		//@brief	//…　レンダーターゲット取得関数　…//
		//@return	レンダーターゲットのポインター
		[[nodiscard]] ID3D12Resource* GetTarget(UINT index)const noexcept;

		//@brief	//…　レンダーターゲットハンドル作成関数　…//
		//@return	レンダーターゲットハンドル
		[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE GetHandle(UINT index)noexcept;
 	private:
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> RenderTarget_{};	//レンダーターゲット
		D3D12_CPU_DESCRIPTOR_HANDLE	Handle_{};
	};
}