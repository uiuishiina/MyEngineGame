//------  DrawingCommandRelated.cpp  ------  //…　描画コマンド関係まとめソースファイル　…//
//---  参照  ---
#include"DrawingCommandRelated.h"
#include<cassert>

namespace MyEngineGame::RenderingPipline {

	//@brief	//…　描画コマンド関係作成関数　…//
	[[nodiscard]] bool DrawingCommandRelated :: Create(const D3D12_COMMAND_LIST_TYPE type)noexcept {

		//コマンドキュー作成
		if (!CommandQueue_.Create(type)) {
			assert(false && "CommandQueue_ Creation Failed. (Drawing Command Related)");
			return false;
		}
		//コマンドアロケーター作成
		if (!CommandAllocator_.Create(type)) {
			assert(false && "CommandAllocator_ Creation Failed. (Drawing Command Related)");
			return false;
		}
		//コマンドリスト作成
		if (!CommandList_.Create(type, CommandAllocator_)) {
			assert(false && "CommandList_ Creation Failed. (Drawing Command Related)");
			return false;
		}

		//タイプ保存
		Type_ = type;
		
		return true;
	}

	//@brief	//…　描画コマンド関係作成関数　…//
	//@return	描画コマンドタイプ
	[[nodiscard]] const D3D12_COMMAND_LIST_TYPE DrawingCommandRelated :: GetType()const noexcept {
		return Type_;
	}

	//…　タイプ別描画コマンドオブジェクトアクセス & 取得関数　…//

	//@brief	//…　CommandQueue取得関数　…//
	//@return	CommandQueueのポインター
	[[nodiscard]] ID3D12CommandQueue* DrawingCommandRelated :: GetCommandQueue()const noexcept {
		return CommandQueue_.Get();
	}

	//@brief	//…　CommandAllocator取得関数　…//
	//@return	CommandAllocatorのポインター
	[[nodiscard]] ID3D12CommandAllocator* DrawingCommandRelated :: GetCommandAllocator()const noexcept {
		return CommandAllocator_.Get();
	}

	//@brief	//…　CommandList取得関数　…//
	//@return	CommandListのポインター
	[[nodiscard]] ID3D12CommandList* DrawingCommandRelated :: GetCommandList()const noexcept {
		return CommandList_.Get();
	}
}