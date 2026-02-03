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
		if (!CommandAllocator_[0].Create(type)) {
			assert(false && "CommandAllocator_ Creation Failed. (Drawing Command Related)");
			return false;
		}
		if (!CommandAllocator_[1].Create(type)) {
			assert(false && "CommandAllocator_ Creation Failed. (Drawing Command Related)");
			return false;
		}

		//コマンドリスト作成
		if (!CommandList_.Create(type, CommandAllocator_[0])) {
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
	//@return	CommandQueueインスタンス
	[[nodiscard]] CommandQueue& DrawingCommandRelated :: GetCommandQueue()noexcept {
		return CommandQueue_;
	}

	//@brief	//…　CommandAllocator取得関数　…//
	//@return	CommandAllocatorインスタンス
	[[nodiscard]] CommandAllocator& DrawingCommandRelated :: GetCommandAllocator(UINT index)noexcept {
		return CommandAllocator_[index];
	}

	//@brief	//…　CommandList取得関数　…//
	//@return	CommandListインスタンス
	[[nodiscard]] CommandList& DrawingCommandRelated :: GetCommandList()noexcept {
		return CommandList_;
	}

	//@brief	//…　リセット関数　…//
	void DrawingCommandRelated :: Reset(UINT index)noexcept {
		CommandAllocator_[index].Reset();
		CommandList_.Get()->Reset(CommandAllocator_[index].Get(), nullptr);
	}
}