#pragma once
//------  CommandAllocator.h  ------  //…　CommandAllocator作成ヘッダーファイル　…//
//---  参照  ---
#include"../Device.h"

/*
	・コマンドアロケーターは描画処理を保存するためのもの
	・DirectX12の描画命令役
*/

//@brief	//…　CommandAllocator作成クラス　…//
class CommandAllocator final
{
public:
	CommandAllocator() = default;
	~CommandAllocator() = default;

	//@brief	//…　CommandAllocator作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool Create(const D3D12_COMMAND_LIST_TYPE type)noexcept;

	//@brief	//…　CommandAllocator取得関数　…//
	//@return	CommandAllocatorのポインター
	[[nodiscard]] ID3D12CommandAllocator* Get()const noexcept;

	//@brief	//…　CommandAllocatorリセット関数　…//
	void Reset()noexcept;
private:
	Microsoft::WRL::ComPtr <ID3D12CommandAllocator> CommandAllocator_{};	//コマンドアロケーターインスタンス
};