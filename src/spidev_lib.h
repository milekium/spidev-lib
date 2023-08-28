/*
 *
 * This file is part of pyA20.
 * spi_lib.c is python SPI extension.
 *
 * Copyright (c) 2014 Stefan Mavrodiev @ OLIMEX LTD, <support@olimex.com>
 *
 * pyA20 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef _SPI_LIB_H
#define _SPI_LIB_H
#endif 

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t mode;
    uint8_t bits_per_word;
    uint32_t speed;
    uint16_t delay;
} spi_config_t;

int spi_open(char *device, spi_config_t config);
int spi_close(int fd);
int spi_xfer(int fd, uint8_t *tx_buffer, uint32_t tx_len, uint8_t *rx_buffer, uint32_t rx_len);
int spi_read(int fd, uint8_t *rx_buffer, uint32_t rx_len);
int spi_write(int fd, uint8_t *tx_buffer, uint32_t tx_len);
#ifdef __cplusplus
}
#endif




