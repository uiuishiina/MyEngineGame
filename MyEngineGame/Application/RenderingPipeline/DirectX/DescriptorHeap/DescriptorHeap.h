#pragma once
//------  DescriptorHeap.h  ------  //…　ディスクリプタヒープ作成ヘッダーファイル　…//
//---  参照まとめ  ---
#include"../Device.h"
#include<vector>
#include <optional>

/*
	ディスクリプタヒープとは "メモリの塊" を "配列のようにまとめる" もの
*/

//@brief	//…　ディスクリプタヒープ作成クラス　…//
class DescriptorHeap final
{
public:
	DescriptorHeap() = default;
	~DescriptorHeap() = default;

	//@brief	//…　ディスクリプタヒープ作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool Create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT NumberOfDescriptor, bool UseShader)noexcept;

	//@brief	//…　ディスクリプタヒープ取得関数　…//
	//@return	ディスクリプタヒープのポインター
	[[nodiscard]] ID3D12DescriptorHeap* Get()const noexcept;

	//@brief	//…　ディスクリプタヒープタイプ取得関数　…//
	//@return	ディスクリプタヒープのタイプ
	[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE GetType()const noexcept;

	//@brief	//…　ディスクリプタヒープインデックス確保関数　…//
	//@return	確保したインデックス番号(無いならnull)
	[[nodiscard]] std::optional<UINT> SecureDescriptor()noexcept;

	//@brief	//…　ディスクリプタヒープ解放関数　…//
	void ReleaseDescriptor(UINT index)noexcept;
private:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DescriptorHeap_{};	//ディスクリプタヒープ
	D3D12_DESCRIPTOR_HEAP_TYPE Type_{};	//ディスクリプタタイプ
	std::vector<UINT> UnusedIndex_{};	//未使用のディスクリプタ番号
	//std::vector<UINT> ComebackIndex_{};	//使用しなくなったディスクリプタ番号
};