//------  RenderTarget.h  ------  //…　レンダーターゲット作成ソースファイル　…//
//---  参照  ---
#include"RenderTarget.h"
#include<cassert>

namespace MyEngineGame::RenderingPipline {

	//@brief	//…　レンダーターゲット作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool RenderTarget :: Create(const SwapChain& swapChain_)noexcept {

		// スワップチェインの設定を取得
		const auto& desc = swapChain_.GetDesc();

		// レンダーターゲットリソースのサイズを設定
		RenderTarget_.resize(desc.BufferCount);

		// ディスクリプターヒープのハンドルを取得
		Handle_ = DescriptorHeap_Administrator::Instance().GetDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)->GetCPUDescriptorHandleForHeapStart();

		auto h = Handle_;
		// バックバッファの生成
		for (uint8_t i = 0; i < desc.BufferCount; ++i) {
			const auto hr = swapChain_.Get()->GetBuffer(i, IID_PPV_ARGS(&RenderTarget_[i]));
			if (FAILED(hr)) {
				assert(false && "Failed to Get BackBuffer.");
				return false;
			}

			// レンダーターゲットビューを作成してディスクリプタヒープのハンドルと関連付ける
			Device::Instance().GetDevice()->CreateRenderTargetView(RenderTarget_[i].Get(), nullptr, h);

			// 次のハンドルへ移動
			h.ptr += Device::Instance().GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}

		return true;
	}

	//@brief	//…　レンダーターゲット取得関数　…//
	//@return	レンダーターゲットのポインター
	[[nodiscard]] ID3D12Resource* RenderTarget :: GetTarget(UINT index)const noexcept {

		assert(RenderTarget_[index] && "Not Found RenderTarget_.");
		assert(index < RenderTarget_.size() && "index is more than RenderTarget_.size().");

		//取得
		return RenderTarget_[index].Get();
	}

	//@brief	//…　レンダーターゲットハンドル作成関数　…//
	//@return	レンダーターゲットハンドル
	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget :: GetHandle(UINT index)noexcept {

		assert(RenderTarget_[index] && "Not Found RenderTarget_.");
		assert(index < RenderTarget_.size() && "index is more than RenderTarget_.size().");

		//取得
		auto h = Handle_;
		h.ptr += (index * Device::Instance().GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
		return h;
	}
}