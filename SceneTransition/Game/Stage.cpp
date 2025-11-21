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
	//生データ(データをひっくり返すために一時的に用意
	std::vector<uint8_t> rawData;
	rawData.resize(header.size);

	FileRead_read(rawData.data(), data_.size() * sizeof(uint8_t), handle);

	//データが上から下になっているが、縦シューは下から上に進むために
	//データを上下逆にする
	//データを上下逆にする目的
	//作ったマップと実際のゲーム進行をシンクロさせるため
	//そのままのデータだと、ゲーム開始地点のデータが一番下にあるため
	//データ先頭から遠い状態になってしまう
	//これは扱いづらいし、メモリ効率的にも良くない
	for (int y = 0; y < header.height; ++y)
	{
		int reverseY = header.height - y;//これだと範囲がh～1であるためさらに1を引きます
		reverseY -= 1;
		//copy_nについて
		//algorithmの1つなのでalgorithmをincludeする必要がある
		//copy_n(コピー元の開始イテレータ(アドレス),何個コピーするか,
		// コピー先の開始テレータ(アドレス)
		//イテレータ(反復子)とは
		//データ集合の要素に順番にアクセスするための仕組み
		//無印のcopyは範囲を指定、copy_nはその数を指定
		std::copy_n(&rawData[y * header.width],
		header.width,
		//vectorは[]オペレータオーバーロードによって、実データのn番目の要素の値を返してきます。
		//今回はそのアドレスが欲しいので　帰ってきた値に&をつけて、n番目の要素のアドレスを
		//取得します。この時に
		//先頭アドレスを y * header.widthとしているがこれは　、目的の「行の先頭」を返す
		//１行下のデータはどこにあるかというと、今の
		//行数を今のアドレスに足したものになる。
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

const std::vector<uint8_t>& Stage::GetAllData() const
{
	return data_;
}
