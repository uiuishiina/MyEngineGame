#pragma once
//------  DrawingCommandRelated.h  ------  //…　描画コマンド関係まとめヘッダーファイル　…//
//---  参照  ---
#include"CommandQueue.h"
#include"CommandAllocator.h"
#include"CommandList.h"

namespace MyEngineGame::RenderingPipline {

	//@brief	//…　描画コマンド関係まとめクラス　…//
	class DrawingCommandRelated final
	{
	public:
		DrawingCommandRelated() = default;
		~DrawingCommandRelated() = default;

		//@brief	//…　描画コマンド関係作成関数　…//
		//@return	作成の成否
		[[nodiscard]] bool Create(const D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT)noexcept;

		//@brief	//…　描画コマンド関係作成関数　…//
		//@return	描画コマンドタイプ
		[[nodiscard]] const D3D12_COMMAND_LIST_TYPE GetType()const noexcept;

		//…　タイプ別描画コマンドオブジェクトアクセス & 取得関数　…//

		//@brief	//…　CommandQueue取得関数　…//
		//@return	CommandQueueインスタンス
		[[nodiscard]] CommandQueue& GetCommandQueue()noexcept;

		//@brief	//…　CommandAllocator取得関数　…//
		//@return	CommandAllocatorインスタンス
		[[nodiscard]] CommandAllocator& GetCommandAllocator(UINT index)noexcept;

		//@brief	//…　CommandList取得関数　…//
		//@return	CommandListインスタンス
		[[nodiscard]] CommandList& GetCommandList()noexcept;

		//@brief	//…　リセット関数　…//
		void Reset(UINT index)noexcept;

	private:

		//…　クラス変数　…//

		D3D12_COMMAND_LIST_TYPE Type_{};			//描画コマンドタイプ
		CommandQueue		CommandQueue_{};		//CommandQueueクラスインスタンス
		CommandAllocator	CommandAllocator_[2]{};	//CommandAllocatorクラスインスタンス
		CommandList			CommandList_{};			//CommandListクラスインスタンス
	};
}