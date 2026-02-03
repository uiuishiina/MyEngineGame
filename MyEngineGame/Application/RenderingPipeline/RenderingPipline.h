#pragma once
//------  RenderingPipline.h  ------  //…　レンダリングパイプライン作成ヘッダーファイル　…//
//---  参照まとめ  ---
//…　Windows　…//
#include "../Windows/Window.h"
//…　DirectX　…//
#include"DirectX/Device.h"
#include"DirectX/DrawingCommandRelated/DrawingCommandRelated.h"
#include"DirectX/DescriptorHeap/DescriptorHeap_Administrator.h"
#include"DirectX/SwapChain.h"
#include"DirectX/RenderTarget.h"
#include"DirectX/Fence.h"


namespace MyEngineGame::RenderingPipline {

	//@brief	//…　レンダリングパイプラインインスタンス作成クラス　…//
	class MEGRP final
	{
	public:
		//@brief	//…　レンダリングパイプラインインスタンス取得関数　…//
		//@return	レンダリングパイプラインインスタンス
		static MEGRP& Instance() noexcept {
			static MEGRP instance;
			return instance;
		}

		//@brief	//…　レンダリングパイプライン作成関数　…//
		//@return	作成の成否
		[[nodiscard]] bool Initialization()noexcept;

		//@brief	//…　Update前関数　…//
		void BeforeUpdate()noexcept;

		//@brief	//…　Update後関数　…//
		void LateUpdate()noexcept;
		
	private:
	
		//@brief	//…　リソースバリア設定関数　…//
		//@param	commandList	コマンドリスト
		//@param	resource	バリアを張るリソース
		//@param	from		変更前のリソースステート
		//@param	to			変更後のリソースステート
		void ResourceBarrier(const CommandList& List_,ID3D12Resource* resource, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to) noexcept {
			
			//リソースバリア設定
			D3D12_RESOURCE_BARRIER barrier{};
			barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			barrier.Transition.pResource = resource;
			barrier.Transition.StateBefore = from;
			barrier.Transition.StateAfter = to;
			barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

			//リソースバリア反映
			List_.Get()->ResourceBarrier(1, &barrier);
		}

		//…　クラス変数　…//

		DrawingCommandRelated CommandRelate_{}; //描画コマンドまとめ
		SwapChain Swap_{};
		RenderTarget RenderTarget_{};
		Fence Fence_{};

		UINT FenceValue_[2]{};
		UINT NextFenceValue_ = 1;
		UINT BackIndex_{};
	};
}