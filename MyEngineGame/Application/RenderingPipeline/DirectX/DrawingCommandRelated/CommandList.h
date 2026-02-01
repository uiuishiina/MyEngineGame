#pragma once
//------  CommandList.h  ------  //…　CommandList作成ヘッダーファイル　…//
//---  参照  ---
#include"../Device.h"
#include"CommandAllocator.h"

//@brief	//…　CommandList作成クラス　…//
class CommandList final
{
public:
	CommandList() = default;
	~CommandList() = default;

	//@brief	//…　CommandList作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool Create(const D3D12_COMMAND_LIST_TYPE type,const CommandAllocator& Allocator_)noexcept;

	//@brief	//…　CommandList取得関数　…//
	//@return	CommandListのポインター
	[[nodiscard]] ID3D12CommandList* Get()const noexcept;
private:
	Microsoft::WRL::ComPtr<ID3D12CommandList> CommandList_{};	//コマンドリストインスタンス
};