#pragma once

#define INBUF_SIZE 4096
#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096


#include <math.h>
#include <fstream>

//include c files to visual c++
extern "C" {
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
}

class Encoder
{
public:
	/*Encodes the video into vp8-*/
	void Encode(const char *);

	/*Encodes 10s of video into vp8-
	falta pasar un punter a memoria del video per a codificar en temps real
	Actualment nomes obre arxius per nom*/
	void Encode_Example10(const char *);

private:
	void allocate_codec_context();
	void put_video_parameters();
	void open_video_codec();
	void open_input_file(const char *filename);
	FILE* create_and_open_output_file();
	void allocate_video_frame();
	void allocate_sample_image();
	FILE* init(const char*, int);
	void find_and_register_video_codec(int);
	void free_memory_and_close(FILE*);
	void video_encode_example(const char *, int);
	void Encoder::video_encode_example1(const char *filename, int codec_id);
	

};