//------  Device.cpp  ------  //…　DirectX12_Device作成ソースファイル　…//
//---  参照  ---
#include"Device.h"
#include<cassert>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")

namespace MyEngineGame::RenderingPipline {

	//@brief	//…　Device作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool Device :: Create()noexcept {

		//DXGI作成
		assert(DXGI_.Create() && "Device::DXGI.Create() failed.");

		//デバイス作成
		const auto hr = D3D12CreateDevice(DXGI_.GetAdapter(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&Device_));
		if (FAILED(hr)) {
			assert(false && "D3D12Device creation failed.");
			return false;
		}

		return true;
	}

	//@brief	//…　Device取得関数　…//
	//@return	Deviceのポインター
	[[nodiscard]] ID3D12Device* Device :: GetDevice()const noexcept {
		assert(Device_ && "Not Found Device_.");
		return Device_.Get();
	}

	//@brief	//…　DXGIインスタンス取得関数　…//
	//@return	DXGIインスタンス
	[[nodiscard]] const DXGI& Device :: GetDXGI()const noexcept {
		return DXGI_;
	}
}