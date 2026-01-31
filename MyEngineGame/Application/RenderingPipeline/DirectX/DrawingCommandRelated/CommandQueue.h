#pragma once
//------  CommandQueue.h  ------  //…　CommandQueue作成ヘッダーファイル　…//
//---  参照  ---
#include"../Device.h"

/*
	・コマンドキューはコマンドアロケーターに保存された描画処理を実際に行うもの
	・DirectX12の描画実行役
*/

//@brief	//…　CommandQueue作成クラス　…//
class CommandQueue final
{
public:
	CommandQueue() = default;
	~CommandQueue() = default;

	//@brief	//…　CommandQueue作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool Create(const D3D12_COMMAND_LIST_TYPE type)noexcept;

	//@brief	//…　CommandQueue取得関数　…//
	//@return	CommandQueueのポインター
	[[nodiscard]] ID3D12CommandQueue* Get()const noexcept;
private:
	//…　クラス変数　…//
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> CommandQueue_{};	//CommandQueueインスタンス
};