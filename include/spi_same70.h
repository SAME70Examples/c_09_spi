#ifndef _SPI_SAME70_H
#define _SPI_SAME70_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void spi0_init(void);
void spi0_send16(uint16_t data);

#ifdef __cplusplus
}
#endif

#endif /* _SPI_SAME70_H */
