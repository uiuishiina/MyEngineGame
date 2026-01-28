//------  DXGI.cp@  ------  //…　DXGIファクトリー & ディスプレイアダプター作成ソースファイル　…//
//---  参照  ---
#include"DXGI.h"
#include<cassert>

#pragma comment(lib, "dxgi.lib")

namespace MyEngineGame::RenderingPipline {
	//@brief	//…　DXGIファクトリー & ディスプレイアダプター作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool DXGI :: Create()noexcept {

		//DXGIファクトリー作成
		assert(CreateFactory() && "DXGI::CreateFactory() failed.");

		//ディスプレイアダプター作成
		assert(CreateAdapter() && "DXGI::CreateAdapter() failed.");

		return true;
	}

	//@brief	//…　DXGIファクトリー作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool DXGI :: CreateFactory()noexcept {

#if _DEBUG
        // デバッグレイヤーON
        ID3D12Debug* Debug_;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&Debug_)))) {
            Debug_->EnableDebugLayer();
        }
#endif

        // DXGIファクトリー作成
        UINT Creat4eFlags_ = 0;
#if _DEBUG
        Creat4eFlags_ |= DXGI_CREATE_FACTORY_DEBUG;
#endif
        const auto hr = CreateDXGIFactory2(Creat4eFlags_, IID_PPV_ARGS(&DXGIFactory_));
        if (FAILED(hr)) {
            assert(false && "DXGIFactory creation failed.");
            return false;
        }

        return true;
	}

	//@brief	//…　ディスプレイアダプター作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool DXGI :: CreateAdapter() noexcept {

		//アダプター取得
		auto count_ = 0;
		IDXGIAdapter1* ProvisionalAdapter_{};

		//アダプター選択

	}
}