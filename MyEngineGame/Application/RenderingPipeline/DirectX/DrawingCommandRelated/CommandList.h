#pragma once
//------  CommandList.h  ------  //…　CommandList作成ヘッダーファイル　…//
//---  参照  ---
#include"../Device.h"

//@brief	//…　CommandList作成クラス　…//
class CommandList final
{
public:
	CommandList() = default;
	~CommandList() = default;

	//@brief	//…　CommandList作成関数　…//
	//@return	作成の成否
	[[nodiscard]] bool Create()noexcept;
private:
};