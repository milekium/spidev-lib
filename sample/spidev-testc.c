#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spidev_lib.h>

spi_config_t spi_config;
uint8_t tx_buffer[32];
uint8_t rx_buffer[32];


void main( void)
{
  int spifd;
  spi_config.mode=0;
  spi_config.speed=1000000;
  spi_config.delay=0;
  spi_config.bits_per_word=8;

  spifd=spi_open("/dev/spidev2.0",spi_config);

  memset(tx_buffer,0,32);
  memset(rx_buffer,0,32);
  sprintf(tx_buffer,"hello world");
  printf("sending %s, to spidev2.0 in full duplex \n ",tx_buffer); 
  spi_xfer(spifd,tx_buffer,strlen(tx_buffer),rx_buffer,strlen(tx_buffer));
  printf("rx_buffer=%s\n",rx_buffer);
  spi_close(spifd); 
  }
