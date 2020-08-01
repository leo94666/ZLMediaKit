﻿/*
 * Copyright (c) 2016 The ZLMediaKit project authors. All Rights Reserved.
 *
 * This file is part of ZLMediaKit(https://github.com/xiongziliang/ZLMediaKit).
 *
 * Use of this source code is governed by MIT license that can be found in the
 * LICENSE file in the root of the source tree. All contributing project authors
 * may be found in the AUTHORS file in the root of the source tree.
 */

#ifndef ZLMEDIAKIT_COMMONRTMP_H
#define ZLMEDIAKIT_COMMONRTMP_H

#include "Frame.h"
#include "Rtmp/RtmpCodec.h"

namespace mediakit{

/**
 * 通用 rtmp解码类
 */
class CommonRtmpDecoder : public RtmpCodec , public ResourcePoolHelper<FrameImp> {
public:
    typedef std::shared_ptr<CommonRtmpDecoder> Ptr;

    ~CommonRtmpDecoder() override {}

    /**
     * 构造函数
     * @param codec 编码id
     */
    CommonRtmpDecoder(CodecId codec);

    /**
     * 返回编码类型ID
     */
    CodecId getCodecId() const override;

    /**
     * 输入Rtmp并解码
     * @param rtmp Rtmp数据包
     * @param key_pos 此参数内部强制转换为false,请忽略之
     */
    bool inputRtmp(const RtmpPacket::Ptr &rtmp, bool key_pos = false) override;

private:
    void obtainFrame();

private:
    CodecId _codec;
    FrameImp::Ptr _frame;
};

/**
 * 通用 rtmp编码类
 */
class CommonRtmpEncoder : public CommonRtmpDecoder , public ResourcePoolHelper<RtmpPacket> {
public:
    typedef std::shared_ptr<CommonRtmpEncoder> Ptr;

    CommonRtmpEncoder(const Track::Ptr &track);
    ~CommonRtmpEncoder() override{}

    /**
     * 输入帧数据
     */
    void inputFrame(const Frame::Ptr &frame) override;

private:
    uint8_t _audio_flv_flags = 0;
};

}//namespace mediakit
#endif //ZLMEDIAKIT_COMMONRTMP_H