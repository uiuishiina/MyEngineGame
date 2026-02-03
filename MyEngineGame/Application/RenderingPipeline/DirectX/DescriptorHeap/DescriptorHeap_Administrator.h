#pragma once
//------  DescriptorHeap_Administrator.h  ------  //…　ディスクリプタヒープ管理オブジェクト作成ヘッダーファイル　…//
//---  参照まとめ  ---
#include"DescriptorHeap.h"
#include<unordered_map>
#include<map>
#include<memory>
namespace MyEngineGame::RenderingPipline {

	//@brief	//…　ディスクリプタヒープ管理オブジェクト作成クラス　…//
	class DescriptorHeap_Administrator final
	{
	public:

		//@brief	//…　ディスクリプタヒープ管理オブジェクトインスタンス取得関数　…//
		//@return	ディスクリプタヒープ管理オブジェクトインスタンス
		static DescriptorHeap_Administrator& Instance() noexcept {

			//シングルトンパターンによりプロジェクト内で１つだけに限定
			static DescriptorHeap_Administrator instance;
			return instance;
		}

		//@brief	//…　ディスクリプタヒープ作成命令関数　…//
		//@return	ディスクリプタヒープからの返信
		[[nodiscard]] bool CreateOrder(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT NumberOfDescriptor, bool UseShader = false)noexcept;

		//@brief	//…　ディスクリプタヒープインデックス確保命令関数　…//
		//@return	確保したインデックス番号(無いならnull)
		[[nodiscard]] std::optional<UINT> SecureOrder(D3D12_DESCRIPTOR_HEAP_TYPE type)const noexcept;

		//@brief	//…　ディスクリプタヒープインデックス解放命令受付関数　…//
		void ReleaseOrder(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT DescriptorIndex)noexcept;

		//@brief	//…　ディスクリプタヒープインデックス解放命令実行関数　…//
		void ReleaseExecute()noexcept;

		//@brief	//…　ディスクリプタヒープアドレス取得関数　…//
		//@return	ディスクリプタヒープのアドレス
		[[nodiscard]] ID3D12DescriptorHeap* GetDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type)const noexcept;
	private:
		DescriptorHeap_Administrator() = default;
		~DescriptorHeap_Administrator() = default;

		//…　クラス変数　…//
		std::unordered_map<D3D12_DESCRIPTOR_HEAP_TYPE, std::unique_ptr<DescriptorHeap>> HeapMap_{};	//ディスクリプタタイプ別まとめ
		std::multimap<D3D12_DESCRIPTOR_HEAP_TYPE, UINT>									ReleaseMap_;//解放命令登録マップ
	};
}