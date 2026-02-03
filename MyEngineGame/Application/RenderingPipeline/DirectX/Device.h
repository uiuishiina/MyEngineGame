#pragma once
//------  Device.h  ------  //…　DirectX12_Device作成ヘッダーファイル　…//
//---  参照  ---
#include"DXGI.h"

namespace MyEngineGame::RenderingPipline {
	//@brief	//…　DirectX12_Device作成クラス　…//
	class Device final
	{
	public:
		//@brief	//…　Deviceクラスインスタンス取得関数　…//
		//@return	Deviceクラスインスタンス
		static Device& Instance() noexcept {

			//シングルトンパターンによりプロジェクト内で１つだけに限定
			static Device instance;
			return instance;
		}

		//@brief	//…　Device作成関数　…//
		//@return	作成の成否
		[[nodiscard]] bool Create()noexcept;

		//@brief	//…　Device取得関数　…//
		//@return	Deviceのポインター
		[[nodiscard]] ID3D12Device* GetDevice()const noexcept;

		//@brief	//…　DXGIインスタンス取得関数　…//
		//@return	DXGIインスタンス
		[[nodiscard]] const DXGI& GetDXGI()const noexcept;

	private:
		Device() = default;
		~Device() = default;

		//…　クラス変数　…//
		DXGI									DXGI_{};		//DXGIクラスインスタンス
		Microsoft::WRL::ComPtr<ID3D12Device>	Device_{};		//デバイス
	};
}