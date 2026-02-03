#pragma once
//------  Fence.h  ------  //…　フェンス作成ヘッダーファイル　…//
//---  参照  ---
#include"Device.h"

namespace MyEngineGame::RenderingPipline {

	//@brief	//…　DirectX12_Device作成クラス　…//
	class Fence final
	{
	public:
		Fence() = default;
		~Fence() = default;

		//@brief	//…　Fence作成関数　…//
		//@return	作成の成否
		[[nodiscard]] bool Create()noexcept;

		//@brief	//…　Fence取得関数　…//
		//@return	Fenceのポインター
		[[nodiscard]] ID3D12Fence* Get()const noexcept;

		//@brief	//…　Fence待機関数　…//
		void WaitFunction(UINT value)const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D12Fence> Fence_{};	//フェンス
		HANDLE WaitEvent_{};
	};
}