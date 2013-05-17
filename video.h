/* video.h
 * (C) Copyright 2010 Michael Meeuwisse
 *
 * ffmpeg_test is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ffmpeg_test is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ffmpeg_test. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VIDEOH
#define VIDEOH
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
typedef struct _video {
    AVFormatContext *pFormatCtx;
    AVCodecContext *pCtx;
    AVCodec *pCodec;
    AVFrame *pRaw;
    AVFrame *pDat;
    uint8_t *buffer;
    struct SwsContext *Sctx;
    int videoStream, width, height, format;
} video;

video *video_init(char *file, int width, int height, int format);
int video_next(video *cur);
video *video_quit(video *cur);
void video_debug_ppm(video *cur, char *file);

#endif 
