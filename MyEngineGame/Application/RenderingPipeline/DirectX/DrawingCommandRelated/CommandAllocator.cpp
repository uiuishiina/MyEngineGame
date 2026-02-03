//------  CommandAllocator.cpp  ------  //…　CommandAllocator作成ソースファイル　…//
//---  参照  ---
#include"CommandAllocator.h"
#include<cassert>

//@brief	//…　CommandAllocator作成関数　…//
//@return	作成の成否
[[nodiscard]] bool CommandAllocator :: Create(const D3D12_COMMAND_LIST_TYPE type)noexcept {

    // コマンドアロケータの生成
    const auto hr = MyEngineGame::RenderingPipline::Device::Instance().GetDevice()->CreateCommandAllocator(type, IID_PPV_ARGS(&CommandAllocator_));
    if (FAILED(hr)) {
        assert(false && "CommandAllocator Creation Failed.");
        return false;
    }
    return true;
}

//@brief	//…　CommandAllocator取得関数　…//
//@return	CommandAllocatorのポインター
[[nodiscard]] ID3D12CommandAllocator* CommandAllocator :: Get()const noexcept {
    assert(CommandAllocator_ && "Not Found CommandAllocator.");
    return CommandAllocator_.Get();
}

//@brief	//…　CommandAllocatorリセット関数　…//
void CommandAllocator :: Reset()noexcept {
    assert(CommandAllocator_ && "Not Found CommandAllocator.");
    CommandAllocator_->Reset();
}