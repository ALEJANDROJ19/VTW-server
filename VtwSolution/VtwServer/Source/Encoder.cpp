/*
* Copyright (c) 2001 Fabrice Bellard
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

/**
* @file
* libavcodec API use example.
*
* @example decoding_encoding.c
* Note that libavcodec only handles codecs (MPEG, MPEG-4, etc...),
* not file formats (AVI, VOB, MP4, MOV, MKV, MXF, FLV, MPEG-TS, MPEG-PS, etc...).
* See library 'libavformat' for the format handling
*/

#include "../Encoder.h"

/*Global pointers for the encoder data*/
AVCodec *&codec;
AVCodec *codec;
AVCodecContext *c = NULL;
FILE *f;
/*global video containers*/
AVFrame *frame;
AVPacket pkt;

/*do no call, call init insetad*/
void Encoder::find_and_register_video_codec(int codec_id) {
	try
	{
		codec = avcodec_find_encoder((AVCodecID)codec_id);
	}
	catch (const std::exception &e)
	{
		fprintf(stderr, "Codec not found with exeption: %s \n", e.what());
		exit(1);
	}
	avcodec_register(codec);
}

/*do no call, call init insetad*/
void Encoder::allocate_codec_context() {
	try
	{
		c = avcodec_alloc_context3(codec);
	}
	catch (const std::exception &e)
	{
		fprintf(stderr, "Could not allocate video codec context with exeption: %s \n", e.what());
		exit(1);
	}
}

/*do no call, call init insetad*/
void Encoder::put_video_parameters() {
	/* put sample parameters */
	c->bit_rate = 400000;
	/* resolution must be a multiple of two */
	c->width = 352;
	c->height = 288;
	/* frames per second */
	c->time_base = AVRational{ 1, 25 };
	/* emit one intra frame every ten frames
	* check frame pict_type before passing frame
	* to encoder, if frame->pict_type is AV_PICTURE_TYPE_I
	* then gop_size is ignored and the output of encoder
	* will always be I frame irrespective to gop_size
	*/
	c->gop_size = 10;
	c->max_b_frames = 1;
	c->pix_fmt = AV_PIX_FMT_YUV420P;
}

/*do no call, call init insetad*/
void Encoder::open_video_codec(){
	try
	{
		avcodec_open2(c, codec, NULL);
	}
	catch (const std::exception &e)
	{
		fprintf(stderr, "Could not open codec with exeption: %s \n", e.what());
		exit(1);
	}
}

/*do no call, call init insetad*/
void Encoder::open_input_file(const char *filename) {
	try
	{
		f = fopen(filename, "wb"); /*wb 'write' + 'binary mode' */
	}
	catch (const std::exception &e)
	{
		fprintf(stderr, "Could not open %s, with exeption: %s \n", filename, e.what());
		exit(1);
	}
}

/*do no call, call init insetad*/
FILE* Encoder::create_and_open_output_file() {
	try
	{
		std::ofstream outfile("C:/Users/recra/Source/Repos/VTW-server/VtwSolution/x64/Debug/output.webm");
		printf("Created new file output.webm \n");
		exit(1);
	}
	catch (const std::exception &e)
	{
		fprintf(stderr, "Failed to create output file with exeption: %s \n", e.what());
		exit(1);
	}

	//open the output file
	const char *file = "C:/Users/recra/Source/Repos/VTW-server/VtwSolution/x64/Debug/output.webm";
	FILE *output;
	try
	{
		output = fopen(file, "wb"); /*wb 'write' + 'binary mode' */
	}
	catch (const std::exception &e)
	{
		fprintf(stderr, "Failed to open output file with exeption: %s \n", e.what());
	}
}

/*do no call, call init insetad*/
void Encoder::allocate_video_frame() {
	try
	{
		frame = av_frame_alloc();
	}
	catch (const std::exception &e)
	{
		fprintf(stderr, "Could not allocate video frame with exeption: %s \n", e.what());
		exit(1);
	}

	frame->format = c->pix_fmt;
	frame->width = c->width;
	frame->height = c->height;
}

/*do no call call init insetad*/
void Encoder::allocate_sample_image() {
	/* the image can be allocated by any means and av_image_alloc() is
	* just the most convenient way if av_malloc() is to be used */
	try
	{
		av_image_alloc(frame->data, frame->linesize, c->width, c->height, 
			c->pix_fmt, 32);
	}
	catch (const std::exception &e)
	{
		fprintf(stderr, "Could not allocate raw picture buffer with exeption: %s \n", 
			e.what());
		exit(1);
	}
}

FILE* Encoder::init(const char *filename, int codec_id)
{
	/*Open codec*/
	find_and_register_video_codec(codec_id);
	/*Allocate codec context*/
	allocate_codec_context();
	/* put sample parameters */
	put_video_parameters();
	/* open the codec*/
	open_video_codec();
	/*open input file*/
	open_input_file(filename);
	/*create new output file to write the video*/
	FILE *output = create_and_open_output_file();
	/*alloc video frame*/
	allocate_video_frame();
	return output;
}

/*call the last to free memory and close files*/
void Encoder::free_memory_and_close(FILE* output) {
	/*clode the files and free the memory*/
	fclose(output);
	fclose(f);
	avcodec_close(c);
	av_free(c);
	av_freep(&frame->data[0]);
	av_frame_free(&frame);
}

AVFrame* create_dummy_frame(int i) {
	int x, y;
	/* Y */
	for (y = 0; y < c->height; y++) {
		for (x = 0; x < c->width; x++) {
			frame->data[0][y * frame->linesize[0] + x] = x + y + i * 3;
		}
	}

	/* Cb and Cr */
	for (y = 0; y < c->height / 2; y++) {
		for (x = 0; x < c->width / 2; x++) {
			frame->data[1][y * frame->linesize[1] + x] = 128 + y + i * 2;
			frame->data[2][y * frame->linesize[2] + x] = 64 + x + i * 5;
		}
	}
}

/*
* Video encoding example 10 seconds
*/
void Encoder::video_encode_example(const char *filename, int codec_id) {
	int i, x, y, got_output;
	uint8_t endcode[] = { 0, 0, 1, 0xb7 };
	/*video containers*/

	printf("Encode video file %s\n", filename);

	/*init*/
	FILE *output = init(filename, codec_id);

	/* encode 10 second of video */
	for (i = 0; i < 250; i++) {
		av_init_packet(&pkt);
		pkt.data = NULL;    // packet data will be allocated by the encoder
		pkt.size = 0;
		
		fflush(stdout);
		/* prepare a dummy image */
		create_dummy_frame(i);
		frame->pts = i;

		/* encode the image */
		try
		{
			avcodec_encode_video2(c, &pkt, frame, &got_output);
		}
		catch (const std::exception &e)
		{
			fprintf(stderr, "Error encoding frame with exeption: %s \n", e.what());
			exit(1);
		}

		if (got_output) {
			printf("Write frame %3d (size=%5d)\n", i, pkt.size);
			fwrite(pkt.data, 1, pkt.size, f);
			av_packet_unref(&pkt);
		}
	}

	/* get the delayed frames */
	for (got_output = 1; got_output; i++) {
		fflush(stdout);

		try
		{
			avcodec_encode_video2(c, &pkt, NULL, &got_output);
		}
		catch (const std::exception &e)
		{
			fprintf(stderr, "Error encoding frame with exeption: %s \n", e.what());
			exit(1);
		}

		if (got_output) {
			printf("Write frame %3d (size=%5d)\n", i, pkt.size);
			fwrite(pkt.data, 1, pkt.size, output);
			av_packet_unref(&pkt);
		}
	}

	/* add sequence end code to have a real file */
	fwrite(endcode, 1, sizeof(endcode), output);

	free_memory_and_close(output);

	printf("Done \n");

}

/*
* Video encoding example 10 seconds
*/
void Encoder::video_encode_example1(const char *filename, int codec_id) {
	int i, x, y, got_output;
	uint8_t endcode[] = { 0, 0, 1, 0xb7 };
	/*video containers*/

	printf("Encode video file %s\n", filename);

	/*init*/
	FILE *output = init(filename, codec_id);

	/* encode 10 second of video */
	for (i = 0; i < 250; i++) {
		av_init_packet(&pkt);
		pkt.data = NULL;    // packet data will be allocated by the encoder
		pkt.size = 0;

		fflush(stdout);
		/* prepare a dummy image */
		create_dummy_frame(i);
		frame->pts = i;

		/* encode the image */
		try
		{
			avcodec_encode_video2(c, &pkt, frame, &got_output);
			//int avcodec_send_frame(AVCodecContext * avctx, const AVFrame * frame);

		}
		catch (const std::exception &e)
		{
			fprintf(stderr, "Error encoding frame with exeption: %s \n", e.what());
			exit(1);
		}

		if (got_output) {
			printf("Write frame %3d (size=%5d)\n", i, pkt.size);
			fwrite(pkt.data, 1, pkt.size, f);
			av_packet_unref(&pkt);
		}
	}

	/* get the delayed frames */
	for (got_output = 1; got_output; i++) {
		fflush(stdout);

		try
		{
			avcodec_encode_video2(c, &pkt, NULL, &got_output);
		}
		catch (const std::exception &e)
		{
			fprintf(stderr, "Error encoding frame with exeption: %s \n", e.what());
			exit(1);
		}

		if (got_output) {
			printf("Write frame %3d (size=%5d)\n", i, pkt.size);
			fwrite(pkt.data, 1, pkt.size, output);
			av_packet_unref(&pkt);
		}
	}

	/* add sequence end code to have a real file */
	fwrite(endcode, 1, sizeof(endcode), output);

	free_memory_and_close(output);

	printf("Done \n");

}

void Encoder::Encode(const char * str)
{
	
}

void Encoder::Encode_Example10(const char *str)
{
	/* register all the codecs */
	video_encode_example1(str, AV_CODEC_ID_VP8);
}
