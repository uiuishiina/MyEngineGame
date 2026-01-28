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
		//終了条件…ファクトリーのアダプターが見つからなかったとき
		while (DXGIFactory_->EnumAdapters1(count_, &DXGIAdapter_) != DXGI_ERROR_NOT_FOUND) {
			//アダプター調査
			DXGI_ADAPTER_DESC1 desc_{};
			ProvisionalAdapter_->GetDesc1(&desc_);

			//ソフトウェアアダプター
			if (desc_.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
				ProvisionalAdapter_->Release();
				continue;
			}
			//動作チェック
			if (FAILED(D3D12CreateDevice(ProvisionalAdapter_, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) {
				DXGIAdapter_ = ProvisionalAdapter_;
				break;
			}
		}

		//チェック
		assert(!DXGIAdapter_ && "Unable to seted DXGIAdapter");

		return true;
	}

	//@brief	//…　DXGIファクトリー取得関数　…//
	//@return	DXGIファクトリーアドレス
	[[nodiscard]] IDXGIFactory4* DXGI :: GetFactory()const noexcept {
		//check
		assert(!DXGIFactory_ && "Not Found DXGIFactory_. Possibly it has not been created or has been deleted.");
		return DXGIFactory_.Get();
	}

	//@brief	//…　ディスプレイアダプター取得関数　…//
	//@return	ディスプレイアダプターアドレス
	[[nodiscard]] IDXGIAdapter1* DXGI :: GetAdapter()const noexcept {
		//check
		assert(!DXGIAdapter_ && "Not Found DXGIAdapter_. Possibly it has not been created or has been deleted.");
		return DXGIAdapter_.Get();
	}
}