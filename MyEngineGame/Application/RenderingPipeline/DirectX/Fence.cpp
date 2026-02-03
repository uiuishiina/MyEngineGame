//------  Fence.cpp  ------  //…　フェンス作成ソースファイル　…//
//---  参照  ---
#include"Fence.h"
#include<cassert>

namespace MyEngineGame::RenderingPipline {

	//@brief	//…　Fence作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool Fence :: Create()noexcept {

		// フェンス作成
		const auto hr = Device::Instance().GetDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence_));
		if (FAILED(hr)) {
			assert(false && "Fence Creation Failed.");
			return false;
		}

		// GPU 同期用イベントハンドル作成
		WaitEvent_ = CreateEvent(nullptr, false, false, "WAIT_GPU");
		if (!WaitEvent_) {
			assert(false && "Event for GPU Synchronization Handle Creation Failed.");
			return false;
		}

		return true;
	}

	//@brief	//…　Fence取得関数　…//
	//@return	Fenceのポインター
	[[nodiscard]] ID3D12Fence* Fence :: Get()const noexcept {
		assert(Fence_ && "Not Found Fence_.");
		return Fence_.Get();
	}

	//@brief	//…　Fence待機関数　…//
	void Fence :: WaitFunction(UINT value)const noexcept {


		if (value == 0) { return; }

		// フェンスの値が指定された値に達するまで待機
		if (Fence_->GetCompletedValue() < value) {
			// GPU がフェンス値に到達するまで待つ
			Fence_->SetEventOnCompletion(value, WaitEvent_);
			WaitForSingleObject(WaitEvent_, INFINITE);
		}
	}
}