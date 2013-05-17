/* video.c g++ -o ffmpeg_test ffmpeg_test.cpp video.cpp -lavformat -lavcodec -lavutil -lswscale -Wall

 * (C) Copyright 2010 Michael Meeuwisse
 *
 * Adapted from avcodec_sample.0.5.0.c, license unknown
 *
 * ffmpeg_test is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ffmpeg_test is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ffmpeg_test. If not, see <http://www.gnu.org/licenses/>.
 */

#include "video.h"

#include <stdio.h>
#include <string.h>


/* Init video source 
 * file: path to open
 * width: destination frame width in pixels - use 0 for source
 * height: destination frame height in pixels - use 0 for source
 * format: PIX_FMT_GRAY8 or PIX_FMT_RGB24
 * Returns video context on succes, NULL otherwise
 */
video *video_init(char *file, int width, int height, int format)
{
    int i = 0;
	
    video *ret = (video*)malloc(sizeof(video));
    memset(ret, 0, sizeof(video));
    ret->format = format;
	
    /* Init ffmpeg */
    av_register_all();
	
    /* Open file, check usability */
    if(av_open_input_file(&ret->pFormatCtx, file, NULL, 0, NULL) ||
       av_find_stream_info(ret->pFormatCtx) < 0)
	return video_quit(ret);
	
    /* Find the first video stream */
    ret->videoStream = -1;
    for(i = 0; i < ret->pFormatCtx->nb_streams; i++)
	if(ret->pFormatCtx->streams[i]->codec->codec_type == CODEC_TYPE_VIDEO) {
	    ret->videoStream = i;
	    break;
	}
	
    if(ret->videoStream == -1)
	return video_quit(ret);
	
    /* Get context for codec, pin down target width/height, find codec */
    ret->pCtx = ret->pFormatCtx->streams[ret->videoStream]->codec;
    ret->width = width? width: ret->pCtx->width;
    ret->height = height? height: ret->pCtx->height;
    ret->pCodec = avcodec_find_decoder(ret->pCtx->codec_id);
	
    if(!ret->pCodec ||
       avcodec_open(ret->pCtx, ret->pCodec) < 0)
	return video_quit(ret);
	
    /* Frame rate fix for some codecs */
    if(ret->pCtx->time_base.num > 1000 && ret->pCtx->time_base.den == 1)
	ret->pCtx->time_base.den = 1000;
	
    /* Get framebuffers */
    ret->pRaw = avcodec_alloc_frame();
    ret->pDat = avcodec_alloc_frame();
	
    if(!ret->pRaw || !ret->pDat)
	return video_quit(ret);
	
    /* Create data buffer */
    ret->buffer = (uint8_t*)malloc(avpicture_get_size(ret->format, 
					    ret->pCtx->width, ret->pCtx->height));
	
    /* Init buffers */
    avpicture_fill((AVPicture *) ret->pDat, ret->buffer, ret->format, 
		   ret->pCtx->width, ret->pCtx->height);
	
    /* Init scale & convert */
    ret->Sctx = sws_getContext(ret->pCtx->width, ret->pCtx->height, ret->pCtx->pix_fmt,
			       ret->width, ret->height, (PixelFormat)ret->format, SWS_BICUBIC, NULL, NULL, NULL);
	
    if(!ret->Sctx)
	return video_quit(ret);
	
    /* Give some info on stderr about the file & stream */
    //dump_format(ret->pFormatCtx, 0, file, 0);
	
    return ret;
}

/* Parse next packet from cur video
 * Returns 0 on succes, -1 on read error,
 * -2 when not a video packet (ignore these) and -3 for invalid frames (skip these)
 */
int video_next(video *cur)
{
    AVPacket packet;
    int finished = 0;
	
    /* Can we read a frame? */
    if(av_read_frame(cur->pFormatCtx, &packet) < 0)
	return -1;
	
    /* Is it what we're trying to parse? */
    if(packet.stream_index != cur->videoStream) {
	av_free_packet(&packet);
	return -2;
    }
	
    /* Decode it! */
    //avcodec_decode_video2(cur->pCtx, cur->pRaw, &finished, &packet);
    #if LIBAVCODEC_VERSION_MAJOR < 53
       avcodec_decode_video(cur->pCtx, cur->pRaw, &finished, packet.data, packet.size);
    #else
       avcodec_decode_video2(cur->pCtx, cur->pRaw, &finished, &packet);
    #endif
	
    /* Succes? If not, drop packet. */
    if(!finished) {
	av_free_packet(&packet);
	return -3;
    }
	
    /* gcc gets trippy because of the double const usage in argument 2 - hard cast 
     * Scale & convert decoded frame to correct size & colorspace
     */
    sws_scale(cur->Sctx, cur->pRaw->data, cur->pRaw->linesize, 
	      0, cur->pCtx->height, cur->pDat->data, cur->pDat->linesize);
    av_free_packet(&packet);
	
    return 0;
}

/* Close & Free cur video context 
 * This function is also called on failed init, so check existence before de-init
 */
video *video_quit(video *cur)
{
    if(cur->Sctx)
	sws_freeContext(cur->Sctx);
	
    if(cur->pRaw)
	av_free(cur->pRaw);
    if(cur->pDat)
	av_free(cur->pDat);
	
    if(cur->pCtx)
	avcodec_close(cur->pCtx);
    if(cur->pFormatCtx)
	av_close_input_file(cur->pFormatCtx);
	
    free(cur->buffer);
    free(cur);
	
    return NULL;
}

/* Output frame to file in PPM format */
void video_debug_ppm(video *cur, char *file)
{
    int i = 0;
    FILE *out = fopen(file, "wb");
	
    if(!out)
	return;
	
    /* PPM header */
    fprintf(out, "P%d\n%d %d\n255\n", cur->format == PIX_FMT_GRAY8? 5: 6, 
	    cur->width, cur->height);
	
    /* Spit out raw data */
    for(i = 0; i < cur->height; i++)
	fwrite(cur->pDat->data[0] + i * cur->pDat->linesize[0], 1,
	       cur->width * (cur->format == PIX_FMT_GRAY8? 1: 3), out);
	
    fclose(out);
}

