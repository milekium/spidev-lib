 /*
 * Copyright (c) 2014 Philippe Van Hecke  <lemouchon@gmail.com >
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

#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>

#include <linux/spi/spidev.h>

#include "spidev_lib++.h"


bool SPI::setBitPerWord(uint8_t p_bit){

    /* Set bits per word*/
    if (ioctl(m_spifd, SPI_IOC_WR_BITS_PER_WORD, &p_bit) < 0) {
        return false;
    }
    if (ioctl(m_spifd, SPI_IOC_RD_BITS_PER_WORD, &p_bit) < 0) {
        return false;
    }

    m_spiconfig.bits_per_word = p_bit;
   return true;
   
}
bool SPI::setSpeed(uint32_t p_speed){
    /* Set SPI speed*/
    if (ioctl(m_spifd, SPI_IOC_WR_MAX_SPEED_HZ, &p_speed) < 0) {
        return false;
    }
    if (ioctl(m_spifd, SPI_IOC_RD_MAX_SPEED_HZ, &p_speed) < 0) {
        return false;
    }

   m_spiconfig.speed = p_speed;

  return true;


}

bool SPI::setMode(uint8_t p_mode){
    /* Set SPI_POL and SPI_PHA */
    if (ioctl(m_spifd, SPI_IOC_WR_MODE, &p_mode) < 0) {
        return false;
    }
    if (ioctl(m_spifd, SPI_IOC_RD_MODE, &p_mode) < 0) {
        return false;
    }

    m_spiconfig.mode = p_mode;
    return true;


}

int SPI::xfer(uint8_t *p_txbuffer, uint8_t p_txlen, uint8_t *p_rxbuffer, uint8_t p_rxlen){
    struct spi_ioc_transfer spi_message[1];
    memset(spi_message, 0, sizeof(spi_message));
    
    spi_message[0].rx_buf = (unsigned long)p_rxbuffer;
    spi_message[0].tx_buf = (unsigned long)p_txbuffer;
    spi_message[0].len = p_txlen;
    return ioctl(m_spifd, SPI_IOC_MESSAGE(1), spi_message);
}

int SPI::write(uint8_t *p_txbuffer,uint8_t p_txlen){
    struct spi_ioc_transfer spi_message[1];
    memset(spi_message, 0, sizeof(spi_message));
    spi_message[0].tx_buf = (unsigned long)p_txbuffer;
    spi_message[0].len = p_txlen;

    return ioctl(m_spifd, SPI_IOC_MESSAGE(1), spi_message);

}

int SPI::read(uint8_t *p_rxbuffer,uint8_t p_rxlen){
    struct spi_ioc_transfer spi_message[1];
    memset(spi_message, 0, sizeof(spi_message));
    
    spi_message[0].rx_buf = (unsigned long)p_rxbuffer;
    spi_message[0].len = p_rxlen;
    return ioctl(m_spifd, SPI_IOC_MESSAGE(1), spi_message);
}

bool SPI::begin(){
    /* open spidev device */
    if (m_open == true )
       return true;
    if (m_spidev == NULL)
       return false;
    m_spifd = open(m_spidev, O_RDWR);
  
    if (m_spifd < 0) {
        return false;
    }
    /* Set SPI_POL and SPI_PHA */
    if (ioctl(m_spifd, SPI_IOC_WR_MODE, &m_spiconfig.mode) < 0) {
        close(m_spifd);
        return false;
    }
    if (ioctl(m_spifd, SPI_IOC_RD_MODE, &m_spiconfig.mode) < 0) {
        close(m_spifd);
        return false;
    }

    /* Set bits per word*/
    if (ioctl(m_spifd, SPI_IOC_WR_BITS_PER_WORD, &m_spiconfig.bits_per_word) < 0) {
        close(m_spifd);
        return false;
    }
    if (ioctl(m_spifd, SPI_IOC_RD_BITS_PER_WORD, &m_spiconfig.bits_per_word) < 0) {
        close(m_spifd);
        return false;
    }

    /* Set SPI speed*/
    if (ioctl(m_spifd, SPI_IOC_WR_MAX_SPEED_HZ, &m_spiconfig.speed) < 0) {
        close(m_spifd);
        return false;
    }
    if (ioctl(m_spifd, SPI_IOC_RD_MAX_SPEED_HZ, &m_spiconfig.speed) < 0) {
        close(m_spifd);
        return false;
    }

    m_open = true;

    return true;

  
}
SPI::SPI(const char * p_spidev){
  m_spidev = NULL;
  if (p_spidev != NULL ){
      m_spidev = (char *)malloc(strlen(p_spidev)+1);
      if (m_spidev != NULL) 
         strcpy(m_spidev,p_spidev);
  }
   m_open = false;

}
SPI::SPI(const char * p_spidev, spi_config_t *p_spi_config){
  m_spidev = NULL;
  if (p_spidev != NULL ){
      m_spidev = (char *)malloc(strlen(p_spidev)+1);
      if (m_spidev != NULL) 
         strcpy(m_spidev,p_spidev);
  }
  if (p_spi_config != NULL){
	memcpy(&m_spiconfig,p_spi_config,sizeof(spi_config_t));
     }
  else {
	m_spiconfig.mode = 0;
	m_spiconfig.speed = 1000000;
	m_spiconfig.bits_per_word = 8;
	m_spiconfig.delay = 0;
		
  }
 m_open = false;
}

SPI::~SPI(){
  if (m_spidev != NULL ) {
	free(m_spidev);
	m_spidev = NULL;
  }
  if (m_open)
      close(m_spifd);
}


bool SPI::setConfig(spi_config_t *p_spi_config){
  if (p_spi_config != NULL){
	memcpy(&m_spiconfig,p_spi_config,sizeof(spi_config_t));
        if (m_open){
         /* Set SPI_POL and SPI_PHA */
          if (ioctl(m_spifd, SPI_IOC_WR_MODE, &m_spiconfig.mode) < 0) {
            close(m_spifd);
           return false;
          }
          if (ioctl(m_spifd, SPI_IOC_RD_MODE, &m_spiconfig.mode) < 0) {
             close(m_spifd);
          return false;
          }

        /* Set bits per word*/
          if (ioctl(m_spifd, SPI_IOC_WR_BITS_PER_WORD, &m_spiconfig.bits_per_word) < 0) {
             close(m_spifd);
          return false;
          }
          if (ioctl(m_spifd, SPI_IOC_RD_BITS_PER_WORD, &m_spiconfig.bits_per_word) < 0) {
             close(m_spifd);
          return false;
          }
  
        /* Set SPI speed*/
          if (ioctl(m_spifd, SPI_IOC_WR_MAX_SPEED_HZ, &m_spiconfig.speed) < 0) {
             close(m_spifd);
          return false;
          } 
          if (ioctl(m_spifd, SPI_IOC_RD_MAX_SPEED_HZ, &m_spiconfig.speed) < 0) {
             close(m_spifd);
          return false;
          }
        return true;
        }
   }
  return false;

}



