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

		//タイプ別まとめ構造体
		struct CommandRelate {
			CommandQueue		CommandQueue_{};		//CommandQueueクラスインスタンス
			CommandAllocator	CommandAllocator_{};	//CommandAllocatorクラスインスタンス
		};

		//@brief	//…　描画コマンド関係作成関数　…//
		[[nodiscard]] bool Create(const D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT)noexcept;
	private:
		std::unordered_map<D3D12_COMMAND_LIST_TYPE, CommandRelate>	Listbytype_{};	//タイプ別まとめ構造体マップ
	};
}