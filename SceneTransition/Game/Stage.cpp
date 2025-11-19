#include "Stage.h"
#include <DxLib.h>
#include <cassert>
#include <algorithm>

namespace
{
	//  + 0	identifier[U4]	// ファイル識別子 'FMF_' (0x5F464D46)
	//	+ 4	size[U4]	// ヘッダを除いたデータサイズ
	//	+ 8	mapWidth[U4]	// マップの横幅
	//	+ 12	mapHeight[U4]	// マップの縦幅
	//	+ 16	chipHeight[U1]	// パーツの横幅
	//	+ 17	chipHeight[U1]	// パーツの縦幅
	//	+ 18	layerCount[U1]	// レイヤー数
	//	+ 19	bitCount[U1]	// レイヤーデータのビットカウント(8/16)
	//配置に必要な情報
	struct DataSetting
	{
		uint8_t chipW;//チップ幅(いらない)
		uint8_t chipH;//チップ高さ(いらない)
		uint8_t lyaerCount;//レイヤー数
		uint8_t bitCount;//1チップに何ビットしようしているのか
	};
	//マップデータのヘッダ
	struct DataHeader
	{
		char identifier[4];//正しければ'FMF_'になっている
		uint32_t size;//データのサイズ
		uint32_t width;//データの幅
		uint32_t height;//データの高さ
		DataSetting setting;//データ配置に必要な情報
	};
}

void Stage::Load(int stageNo)
{
	wchar_t filePath[32];
	wsprintf(filePath, L"data/stage%d.fmf", stageNo);
	auto handle = FileRead_open(filePath);
	assert(handle >= 0);
	DataHeader header;
	FileRead_read(&header, sizeof(header), handle);

	dataSize_.w = header.width;
	dataSize_.h = header.height;

	//データを受けとる準備をします
	data_.resize(header.size);
	std::vector<uint8_t> rawData;//生データ
	rawData.resize(header.size);

	FileRead_read(rawData.data(), data_.size() * sizeof(uint8_t), handle);

	//データが上から下になっているが、縦シューは下から上に進むために
	//データを上下逆にする
	for (int y = 0; y < header.height; ++y)
	{
		int reverseY = header.height - y;//これだと範囲がh～1であるためさらに1を引きます
		reverseY -= 1;
		std::copy_n(&rawData[y * header.width],
		header.width,
		&data_[reverseY * header.width]);
	}

	FileRead_close(handle);
}

Size Stage::MapSize() const
{
	return dataSize_;
}

uint8_t Stage::GetData(int xidx, int yidx)
{
	return data_[yidx * dataSize_.w + xidx];
}
