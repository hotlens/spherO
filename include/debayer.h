#ifndef SPHERO_DEBAYER_H
#define SPHERO_DEBAYER_H

#ifdef __cplusplus
extern "C" {
#endif
#include <unicap.h>
#ifdef __cplusplus
}
#endif

struct _debayer_data {
  int use_ccm;
  int use_rbgain;

  // color correction matrix
  int ccm[3][3];

  // red/blue gain
  int rgain;
  int bgain;
};

typedef struct _debayer_data debayer_data_t;

void debayer_ccm_rgb24_nn(unicap_data_buffer_t *destbuf, unicap_data_buffer_t *srcbuf,
                          debayer_data_t *data);
void debayer_ccm_rgb24_edge(unicap_data_buffer_t *destbuf, unicap_data_buffer_t *srcbuf,
                            debayer_data_t *data);
void debayer_ccm_uyvy(unicap_data_buffer_t *destbuf, unicap_data_buffer_t *srcbuf,
                      debayer_data_t *data);
void debayer_calculate_rbgain(unicap_data_buffer_t *buffer, int *rgain, int *bgain);

#endif  // SPHERO_DEBAYER_H
