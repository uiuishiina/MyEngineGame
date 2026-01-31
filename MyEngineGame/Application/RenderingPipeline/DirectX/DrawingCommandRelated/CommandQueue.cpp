//------  CommandQueue.cpp  ------  //…　CommandQueue作成ソースファイル　…//
//---  参照  ---
#include"CommandQueue.h"
#include<cassert>

//@brief	//…　CommandQueue作成関数　…//
//@return	作成の成否
[[nodiscard]] bool CommandQueue :: Create(const D3D12_COMMAND_LIST_TYPE type)noexcept {

	//コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type			= type;
	desc.Priority		= D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags			= D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask		= 0;

	//コマンドキュー作成
	const auto hr = MyEngineGame::RenderingPipline::Device::Instance().GetDevice()->CreateCommandQueue(&desc, IID_PPV_ARGS(&CommandQueue_));
	if (FAILED(hr)) {
		assert(false && "CommandQueue Creation Failed.");
		return false;
	}

	return true;
}

//@brief	//…　CommandQueue取得関数　…//
//@return	CommandQueueのポインター
[[nodiscard]] ID3D12CommandQueue* CommandQueue :: Get()const noexcept {
	assert(CommandQueue_ && "Not Found CommandQueue.");
	return CommandQueue_.Get();
}