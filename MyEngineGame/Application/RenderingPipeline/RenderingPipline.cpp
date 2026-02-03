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

		//描画コマンドまとめ作成
		if (!CommandRelate_.Create(D3D12_COMMAND_LIST_TYPE_DIRECT)) {
			assert(false && "MEGRP::DrawingCommandRelated.Create() failed.");
		}
		
		//スワップチェイン作成
		if (!Swap_.Create(CommandRelate_.GetCommandQueue())) {
			assert(false && "MEGRP::Swap_.Create() failed.");
		}

		//レンダーターゲット用ディスクリプタ作成
		if (!DescriptorHeap_Administrator::Instance().CreateOrder(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 2)) {
			assert(false && "MEGRP::DescriptorHeap_Administrator::Instance().CreateOrder() failed.");
		}

		//レンダーターゲット作成
		if (!RenderTarget_.Create(Swap_)) {
			assert(false && "MEGRP::RenderTarget_.Create() failed.");
		}

		//フェンス作成
		if (!Fence_.Create()) {
			assert(false && "MEGRP::Fence_.Create() failed.");
		}

		return true;
	}

	//@brief	//…　Update前関数　…//
	void MEGRP ::BeforeUpdate()noexcept {

		//終了しているバックバッファのインデックスを取得
		BackIndex_ = Swap_.Get()->GetCurrentBackBufferIndex();

		//処理が終わっていないなら待機
		Fence_.WaitFunction(FenceValue_[BackIndex_]);

		//リセット
		CommandRelate_.Reset(BackIndex_);

		//リソースバリア変更
		ResourceBarrier(CommandRelate_.GetCommandList(), RenderTarget_.GetTarget(BackIndex_), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		
		//レンダーターゲット設定
		D3D12_CPU_DESCRIPTOR_HANDLE Handles[] = {RenderTarget_.GetHandle(BackIndex_)};
		CommandRelate_.GetCommandList().Get()->OMSetRenderTargets(1, Handles, false, nullptr);

		//背景色設定
		const float clearColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };  // 赤色でクリア
		CommandRelate_.GetCommandList().Get()->ClearRenderTargetView(Handles[0], clearColor, 0, nullptr);
	}

	//@brief	//…　Update後関数　…//
	void MEGRP :: LateUpdate()noexcept {

		//リソースバリア変更
		ResourceBarrier(CommandRelate_.GetCommandList(), RenderTarget_.GetTarget(BackIndex_), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

		//描画命令書き込み終了
		CommandRelate_.GetCommandList().Get()->Close();

		//キューに渡す
		ID3D12CommandList* ppCommandLists[] = { CommandRelate_.GetCommandList().Get() };
		CommandRelate_.GetCommandQueue().Get()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

		//スワップチェーン切り替え
		Swap_.Get()->Present(1, 0);

		//フレーム移行処理
		CommandRelate_.GetCommandQueue().Get()->Signal(Fence_.Get(), NextFenceValue_);
		FenceValue_[BackIndex_] = NextFenceValue_;
		NextFenceValue_++;
	}
}
