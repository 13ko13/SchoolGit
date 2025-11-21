#pragma once
#include "../Geometry.h"
#include <vector>

/// <summary>
/// ステージデータを管理する
/// </summary>
class Stage
{
	Size dataSize_;//データサイズ
	std::vector<uint8_t> data_;	//データ本体(8ビット)


public:
	void Load(int stageNo);
	Size MapSize() const;
	uint8_t GetData(int xidx, int yidx);
	const std::vector<uint8_t>& GetAllData() const;
};

