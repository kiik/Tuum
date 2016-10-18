/** @file tuum_http.hpp
 *  @brief Dirty implementation of http protocols.
 *
 * @authors Meelik Kiik
 * @date 18. October 2016
 * @version 0.1
 */

#ifndef TUUM_HTTP_H
#define TUUM_HTTP_H

#include "tuum_streams.hpp"

namespace tuum { namespace http {

  size_t read_data_stream(size_t lid, image_t& out);

  void mjpeg_headers(lws *wsi);
  void mjpeg_frame(lws *wsi, size_t len);
  void mjpeg_stream(lws *wsi);

}}

#endif
