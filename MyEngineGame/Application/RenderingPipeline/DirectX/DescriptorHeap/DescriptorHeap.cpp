//------  DescriptorHeap.cpp  ------  //…　ディスクリプターヒープ作成ソースファイル　…//
//---  参照まとめ  ---
#include"DescriptorHeap.h"
#include<cassert>

//@brief	//…　ディスクリプタヒープ作成関数　…//
//@return	作成の成否
[[nodiscard]] bool DescriptorHeap :: Create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT NumberOfDescriptor, bool UseShader)noexcept {
	
	//ヒープ(配列)の設定
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type				= type;
	desc.NumDescriptors		= NumberOfDescriptor;
	desc.Flags				= UseShader ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	//タイプ設定
	Type_ = type;

	//ディスクリプタヒープ作成
	const auto hr = MyEngineGame::RenderingPipline::Device::Instance().GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&DescriptorHeap_));
	if (FAILED(hr)) {
		assert(false && "DescriptorHeap Creation Failed.");
		return false;
	}

	//未使用インデックス配列に登録
	for (UINT i = 0; i < NumberOfDescriptor; i++) {
		UnusedIndex_.push_back(i);
	}

	return true;
}

//@brief	//…　ディスクリプタヒープ取得関数　…//
//@return	ディスクリプタヒープのポインター
[[nodiscard]] ID3D12DescriptorHeap* DescriptorHeap :: Get()const noexcept {
	assert(DescriptorHeap_ && "Not Found DescriptorHeap_.");
	return DescriptorHeap_.Get();
}

//@brief	//…　ディスクリプタヒープタイプ取得関数　…//
//@return	ディスクリプタヒープのタイプ
[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeap :: GetType()const noexcept {
	//取得時に設定したタイプであるか確認するために作成
	assert(DescriptorHeap_ && "Not Found DescriptorHeap_.");
	return Type_;
}

//@brief	//…　ディスクリプタヒープインデックス確保関数　…//
//@return	確保したインデックス番号(無いならnull)
[[nodiscard]] std::optional<UINT> DescriptorHeap :: SecureDescriptor()noexcept {

	//空きがあるか確認
	if (UnusedIndex_.empty()) {
		return std::nullopt;
	}

	//後ろから確保していく
	const auto index = UnusedIndex_.back();
	UnusedIndex_.pop_back();
	return index;
}

//@brief	//…　ディスクリプタヒープ解放関数　…//
void DescriptorHeap :: ReleaseDescriptor(UINT index)noexcept {
	//未使用ディスクリプタに追加
	UnusedIndex_.push_back(index);
}