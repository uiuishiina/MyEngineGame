//------  DescriptorHeap_Administrator.cpp  ------  //…　ディスクリプタヒープ管理オブジェクト作成ソースファイル　…//
//---  参照まとめ  ---
#include"DescriptorHeap_Administrator.h"
#include<cassert>

namespace MyEngineGame::RenderingPipline {

	//@brief	//…　ディスクリプタヒープ作成命令関数　…//
	//@return	ディスクリプタヒープからの返信
	[[nodiscard]] bool DescriptorHeap_Administrator::CreateOrder(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT NumberOfDescriptor, bool UseShader)noexcept {

		//作成済みか
		if (HeapMap_.find(type) != HeapMap_.end()) {
			return false;
		}

		//ディスクリプタヒープ作成
		auto p = std::make_unique<DescriptorHeap>();
		if (p->Create(type, NumberOfDescriptor, UseShader)) {
			HeapMap_.emplace(type, std::move(p));
		}

		return true;
	}

	//@brief	//…　ディスクリプタヒープインデックス確保命令関数　…//
	//@return	確保したインデックス番号(無いならnull)
	[[nodiscard]] std::optional<UINT> DescriptorHeap_Administrator :: SecureOrder(D3D12_DESCRIPTOR_HEAP_TYPE type)const noexcept {

		//作成済みか
		if (HeapMap_.find(type) == HeapMap_.end()) {
			assert(false && "Not Found DescriptorHeap(type) in HeapMap_.");
		}
		
		//確保
		return HeapMap_.find(type)->second->SecureDescriptor();
	}

	//@brief	//…　ディスクリプタヒープインデックス解放命令受付関数　…//
	void DescriptorHeap_Administrator :: ReleaseOrder(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT DescriptorIndex)noexcept {

		//作成済みか
		if (HeapMap_.find(type) == HeapMap_.end()) {
			assert(false && "Not Found DescriptorHeap(type) in HeapMap_.");
		}

		//重複してないか
		auto range = ReleaseMap_.equal_range(type);
		for (auto it = range.first; it != range.second; ++it) {
			if (it->second == DescriptorIndex) {
				return;
			}
		}

		//解放命令登録
		ReleaseMap_.emplace(type, DescriptorIndex);
	}

	//@brief	//…　ディスクリプタヒープインデックス解放命令実行関数　…//
	void DescriptorHeap_Administrator :: ReleaseExecute()noexcept {

		//解放
		for (auto& map : ReleaseMap_) {
			HeapMap_.find(map.first)->second->ReleaseDescriptor(map.second);
		}
		ReleaseMap_.clear();
	}

	//@brief	//…　ディスクリプタヒープアドレス取得関数　…//
	//@return	ディスクリプタヒープのアドレス
	[[nodiscard]] ID3D12DescriptorHeap* DescriptorHeap_Administrator :: GetDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type)const noexcept {

		//作成済みか
		if (HeapMap_.find(type) == HeapMap_.end()) {
			assert(false && "Not Found DescriptorHeap(type) in HeapMap_.");
		}

		//タイプ確認
		const auto it = HeapMap_.find(type);
		if (it->second->GetType() != type) {
			assert(false && "type dose not match DescriptorHeap(type) in HeapMap_.");
		}

		//取得
		return it->second->Get();
	}
}