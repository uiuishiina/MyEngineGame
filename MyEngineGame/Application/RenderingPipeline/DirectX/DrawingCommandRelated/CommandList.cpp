//------  CommandList.cpp  ------  //…　CommandList作成ソースファイル　…//
//---  参照  ---
#include"CommandList.h"
#include<cassert>

//@brief	//…　CommandList作成関数　…//
//@return	作成の成否
[[nodiscard]] bool CommandList :: Create(const D3D12_COMMAND_LIST_TYPE type, const CommandAllocator& Allocator_)noexcept {

	//コマンドリスト作成
	const auto hr = MyEngineGame::RenderingPipline::Device::Instance().GetDevice()->CreateCommandList(0, type, Allocator_.Get(), nullptr, IID_PPV_ARGS(&CommandList_));
	if (FAILED(hr)) {
		assert(false && "CommandList Creation Failed.");
		return false;
	}
	// コマンドリストを初期化状態に設定
	CommandList_->Close();

	return true;
}

//@brief	//…　CommandList取得関数　…//
//@return	CommandListのポインター
[[nodiscard]] ID3D12GraphicsCommandList* CommandList :: Get()const noexcept {
	assert(CommandList_ && "Not Found CommandList.");
	return CommandList_.Get();
}