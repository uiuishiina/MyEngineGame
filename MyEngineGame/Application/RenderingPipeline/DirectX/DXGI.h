#pragma once
//------  DXGI.h  ------  //…　DXGIファクトリー & ディスプレイアダプター作成ヘッダーファイル　…//
//---  参照  ---
#include<d3d12.h>
#include<dxgi1_4.h>
#include <wrl/client.h>

namespace MyEngineGame::RenderingPipline {
	//@brief	//…　DXGIファクトリー & ディスプレイアダプター作成クラス　…//
	class DXGI final
	{
	public:
		DXGI() = default;
		~DXGI() = default;

		//@brief	//…　DXGIファクトリー & ディスプレイアダプター作成関数　…//
		//@return	作成の成否
		[[nodiscard]] bool Create()noexcept;

		//@brief	//…　DXGIファクトリー取得関数　…//
		//@return	DXGIファクトリーアドレス
		[[nodiscard]] IDXGIFactory4* GetFactory()const noexcept;

		//@brief	//…　ディスプレイアダプター取得関数　…//
		//@return	ディスプレイアダプターアドレス
		[[nodiscard]] IDXGIAdapter1* GetAdapter()const noexcept;

	private:
		//@brief	//…　DXGIファクトリー作成関数　…//
		//@return	作成の成否
		[[nodiscard]] bool CreateFactory() noexcept;

		//@brief	//…　ディスプレイアダプター作成関数　…//
		//@return	作成の成否
		[[nodiscard]] bool CreateAdapter() noexcept;

	private:
		//…　クラス変数　…//
		Microsoft::WRL::ComPtr<IDXGIFactory4> DXGIFactory_{};	//DXGIファクトリー
		Microsoft::WRL::ComPtr<IDXGIAdapter1> DXGIAdapter_{};	//ディスプレイアダプター
	};
}