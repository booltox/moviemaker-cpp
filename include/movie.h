// Adapted from
// https://stackoverflow.com/questions/34511312/how-to-encode-a-video-from-several-images-generated-in-a-c-program-without-wri

#ifndef MOVIE_H
#define MOVIE_H

#ifdef USE_CAIRO
#include <cairo/cairo.h>
#endif
#include <stdint.h>
#include <string>
#include <vector>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/mathematics.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
#include <x264.h>
}

class MovieWriter {
  const unsigned int width, height;
  unsigned int iframe;
  int frameRate;

  SwsContext *swsCtx;
  AVOutputFormat *fmt;
  AVStream *stream;
  AVFormatContext *fc;
  AVCodecContext *c;
  AVPacket pkt;

  AVFrame *rgbpic, *yuvpic;

  std::vector<uint8_t> pixels;

#ifdef USE_CAIRO
  cairo_surface_t *cairo_surface;
#endif

public:
  MovieWriter(const std::string &filename, const unsigned int width,
              const unsigned int height, const int frameRate = 25);

#ifdef USE_CAIRO
  void addFrame(const std::string &filename);
#endif

  void addFrame(const uint8_t *pixels);

  ~MovieWriter();
};

class MovieReader {
  const unsigned int width, height;

  SwsContext *swsCtx;
  AVOutputFormat *fmt;
  AVStream *stream;
  AVFormatContext *fc;
  AVCodecContext *c;
  AVFrame *pFrame;
  AVFrame *pFrameRGB;

  // The index of video stream.
  int ivstream;

public:
  MovieReader(const std::string &filename, const unsigned int width,
              const unsigned int height);

  bool getFrame(std::vector<uint8_t> &pixels);
  int getFrameRate() const;

  ~MovieReader();
};

#endif // MOVIE_H
