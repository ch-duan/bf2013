#include "BF2013.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BF2013.h"
#include "BF2013_config.h"
#include "sensor.h"
#if defined(USE_BF2013) && USE_BF2013 == 1
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "i2c.h"
#include "main.h"

#define dcmi_width  320
#define dcmi_height 240

// #define dcmi_buf_size 320 * 240
#define dcmi_buf_size 1

#pragma pack(4)
uint16_t dcmi_line_buf[dcmi_buf_size] __attribute__((section(".sram")));
#pragma pack()

BF2013_IDTypeDef BF2013ID;
uint16_t BF2013_ADDR = 0x6e;
I2C_HandleTypeDef *mI2C;
UART_HandleTypeDef *mHuart;
DCMI_HandleTypeDef *DCMI_hdcmi;

static char *hal_status_msg[] = {"HAL_OK", "HAL_ERROR", "HAL_BUSY", "HAL_TIMEOUT"};
void i2c_sent(uint8_t reg, uint8_t data) {
  uint8_t sent_data[2];
  sent_data[0] = reg;
  sent_data[1] = data;
  HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(mI2C, (uint16_t) BF2013_ADDR << 1 | 0x00, (uint8_t *) sent_data, 2, 10000);
  if (status != HAL_OK) {
    printf("\033[0;31m i2c_sent[%02X] is %s\r\n", reg, hal_status_msg[status]);
  }
}

uint8_t i2c_receive(uint8_t reg) {
  uint8_t data = 0;
  HAL_StatusTypeDef status = HAL_I2C_Mem_Read(mI2C, (uint16_t) BF2013_ADDR << 1 | 0x01, reg, 1, (uint8_t *) &data, 1, 10000);
  if (status != HAL_OK) {
    printf("\033[0;31m i2c_receive[%02X] is %s\r\n", reg, hal_status_msg[status]);
  }
  return data;
}

uint8_t SCCB_Read(uint8_t slv_addr, uint8_t reg) {
  uint8_t data = 0;
  HAL_StatusTypeDef status = HAL_I2C_Mem_Read(mI2C, (uint16_t) BF2013_ADDR << 1 | 0x01, reg, 1, (uint8_t *) &data, 1, 10000);
  if (status != HAL_OK) {
    printf("\033[0;31m i2c_receive[%02X] is %s\r\n", reg, hal_status_msg[status]);
  }
  return data;
}

int SCCB_Write(uint8_t reg, uint8_t data) {
  uint8_t sent_data[2];
  sent_data[0] = reg;
  sent_data[1] = data;
  HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(mI2C, (uint16_t) BF2013_ADDR << 1 | 0x00, (uint8_t *) sent_data, 2, 10000);
  return status;
}

static const uint8_t default_regs[][2] = {
    {0x12, 0x80}, // COM7 Resets all registers to default values
    {0x09, 0x03}, // COM2 0x20==1 4x data out drive capability
    {0x15, 0x02}, // COM10  HSYNC:active high, VSYNC:active high
    {0x3a, 0x00}, // TSLB   IF YUV422 IS selected YUYV else RGB565 R5G3H,G3LB5
    {0x12, 0x00}, // COM7
    {0x1e, 0x00},
    {0x13, 0x00},
    {0x01, 0x14},
    {0x02, 0x21},
    {0x8c, 0x01},
    {0x8d, 0xcb},
    {0x87, 0x20},
    {0x1b, 0x80},
    {0x11, 0x80},
    {0x2b, 0x20},
    {0x92, 0x40},
    {0x06, 0xe0},
    {0x29, 0x54},
    {0xeb, 0x30},
    {0xbb, 0x20},
    {0xf5, 0x21},
    {0xe1, 0x3c},
    {0x16, 0x01},
    {0xe0, 0x0b},
    {0x2f, 0xf6},
    {0x1f, 0x20},
    {0x22, 0x20},
    {0x26, 0x20},
    {0x33, 0x20},
    {0x34, 0x08},
    {0x35, 0x50},
    {0x65, 0x4a},
    {0x66, 0x48},
    {0x36, 0x05},
    {0x37, 0xf6},
    {0x38, 0x46},
    {0x9b, 0xf6},
    {0x9c, 0x46},
    {0xbc, 0x01},
    {0xbd, 0xf6},
    {0xbe, 0x46},
    {0x70, 0x6f},
    {0x72, 0x3f},
    {0x73, 0x3f},
    {0x74, 0x27},
    {0x77, 0x90},
    {0x79, 0x48},
    {0x7a, 0x1e},
    {0x7b, 0x30},
    {0x24, 0x70},
    {0x25, 0x80},
    {0x80, 0x55},
    {0x81, 0x02},
    {0x82, 0x14},
    {0x83, 0x23},
    {0x9a, 0x23},
    {0x84, 0x1a},
    {0x85, 0x20},
    {0x86, 0x30},
    {0x89, 0x02},
    {0x8a, 0x64},
    {0x8b, 0x02},
    {0x8e, 0x07},
    {0x8f, 0x79},
    {0x94, 0x0a},
    {0x96, 0xa6},
    {0x97, 0x0c},
    {0x98, 0x18},
    {0x9d, 0x93},
    {0x9e, 0x7a},
    {0x3b, 0x60},
    {0x3c, 0x20},
    {0x39, 0x80},
    {0x3f, 0xb0},
    {0x40, 0x9b},
    {0x41, 0x88},
    {0x42, 0x6e},
    {0x43, 0x59},
    {0x44, 0x4d},
    {0x45, 0x45},
    {0x46, 0x3e},
    {0x47, 0x39},
    {0x48, 0x35},
    {0x49, 0x31},
    {0x4b, 0x2e},
    {0x4c, 0x2b},
    {0x4e, 0x26},
    {0x4f, 0x22},
    {0x50, 0x1f},
    {0x51, 0x05},
    {0x52, 0x10},
    {0x53, 0x0b},
    {0x54, 0x15},
    {0x57, 0x87},
    {0x58, 0x72},
    {0x59, 0x5f},
    {0x5a, 0x7e},
    {0x5b, 0x1f},
    {0x5c, 0x0e},
    {0x5d, 0x95},
    {0x60, 0x24},
    {0x6a, 0x01},
    {0x23, 0x66},
    {0xa0, 0x03},
    {0xa1, 0x31},
    {0xa2, 0x0e},
    {0xa3, 0x27},
    {0xa4, 0x08},
    {0xa5, 0x25},
    {0xa6, 0x06},
    {0xa7, 0x80},
    {0xa8, 0x7e},
    {0xa9, 0x20},
    {0xaa, 0x20},
    {0xab, 0x20},
    {0xac, 0x3c},
    {0xad, 0xf0},
    {0xae, 0x80},
    {0xaf, 0x00},
    {0xc5, 0x18},
    {0xc6, 0x00},
    {0xc7, 0x20},
    {0xc8, 0x18},
    {0xc9, 0x20},
    {0xca, 0x17},
    {0xcb, 0x1f},
    {0xcc, 0x40},
    {0xcd, 0x58},
    {0xee, 0x4c},
    {0xb0, 0xe0},
    {0xb1, 0xc0},
    {0xb2, 0xb0},
    {0xb3, 0x88},
    {0x56, 0x40},
    {0x13, 0x07}
};

static int get_reg(int reg, int mask) {
  int ret = SCCB_Read(BF2013_ADDR << 1 | 0x01, reg & 0xFF);
  if (ret > 0) {
    ret &= mask;
  }
  return ret;
}

static int set_reg(int reg, int mask, int value) {
  int ret = 0;
  ret = SCCB_Read(BF2013_ADDR << 1 | 0x01, reg & 0xFF);
  if (ret < 0) {
    return ret;
  }
  value = (ret & ~mask) | (value & mask);
  ret = SCCB_Write(reg & 0xFF, value);
  return ret;
}

static int set_reg_bits(uint8_t reg, uint8_t offset, uint8_t length, uint8_t value) {
  int ret = 0;
  ret = SCCB_Read(BF2013_ADDR << 1 | 0x01, reg);
  //  if (ret < 0) {
  //    return ret;
  //  }
  uint8_t mask = ((1 << length) - 1) << offset;
  value = (ret & ~mask) | ((value << offset) & mask);
  printf("set_reg_bits regs:[%02X] is mask:%d,length:%d,offset:%d,value:%d \r\n", reg, mask, length, offset, value);
  ret = SCCB_Write(reg & 0xFF, value);
  return ret;
}

static int get_reg_bits(uint8_t reg, uint8_t offset, uint8_t length) {
  int ret = 0;
  ret = SCCB_Read(BF2013_ADDR << 1 | 0x01, reg);
  if (ret < 0) {
    return ret;
  }
  uint8_t mask = ((1 << length) - 1) << offset;
  return (ret & mask) >> offset;
}

static int reset(void) {
  uint32_t i = 0;
  const uint8_t(*regs)[2];

  // Reset all registers

  //   int ret = SCCB_Write(BF2013_ADDR<<1|0x01, COM7, COM7_RESET);
  int ret = SCCB_Write(0x09, 0x03);
  if (!ret) {
    printf("bf2013 reset failure.");
  }

  // Delay 10 ms
  osDelay(10 / portTICK_PERIOD_MS);

  // Write default regsiters
  uint8_t value = 0;
  for (i = 1, regs = default_regs; i < sizeof(default_regs) / 2; i++) {
    SCCB_Write(regs[i][0], regs[i][1]);
    value = 0;
    value = SCCB_Read(BF2013_ADDR << 1 | 0x01, regs[i][0]);
    if (value != regs[i][1]) {
      printf("regs:[%02X] write: %02X,read:%02X", regs[i][0], regs[i][1], value);
    } else {
      printf("regs:[%02X] write: %02X,read:%02X", regs[i][0], regs[i][1], value);
    }
  }

  // Delay
  osDelay(30 / portTICK_PERIOD_MS);

  return 0;
}

static int set_pixformat(pixformat_t pixformat) {
  int ret = 0;
  switch (pixformat) {
    case PIXFORMAT_RGB565:
      set_reg_bits(COM7, 2, 1, 1);
      //      ret = SCCB_Write( COM7, 0x14);
      //      i2c_sent(COM7, 0x14);

      printf("set pixformat:%d,read:%02x\r\n", ret, SCCB_Read(BF2013_ADDR << 1 | 0x01, COM7));

      break;
    case PIXFORMAT_RAW:
      set_reg_bits(COM7, 0, 3, 0x4);
      break;
    case PIXFORMAT_YUV422:
    case PIXFORMAT_GRAYSCALE:
      set_reg_bits(0x12, 2, 1, 0);
      break;
    default:
      return -1;
  }
  // Delay
  osDelay(30 / portTICK_PERIOD_MS);

  return ret;
}

static int set_framesize(framesize_t framesize) {
  int ret = 0;
  if (framesize > FRAMESIZE_VGA) {
    return -1;
  }
  uint16_t w = resolution[framesize].width;
  uint16_t h = resolution[framesize].height;
  //  if ((w <= 320) && (h <= 240)) {
  //    // Enable auto-scaling/zooming factors
  //    set_reg_bits(0x12, 4, 1, 1);
  //
  //  } else if ((w <= 640) && (h <= 480)) {
  //    // Enable auto-scaling/zooming factors
  //    set_reg_bits(0x12, 4, 1, 0);
  //  }
  //
  ////  int hstart = (648 - w) / 2 / 4;
  ////  int hstop = ((648 - w) / 2 + w) / 4;
  ////  int vstart = (486 - h) / 2 / 4;
  ////  int vstop = ((486 - h) / 2 + h) / 4;
  //  int hstart = 0;
  //  int hstop = w / 4;
  //  int vstart = 0;
  //  int vstop = h/ 4;
  //
  //  ret |= SCCB_Write( HSTART, hstart);
  //  ret |= SCCB_Write( HSTOP, hstop);
  //
  //  ret |= SCCB_Write( VSTART, vstart);
  //  ret |= SCCB_Write( VSTOP, vstop);
  //
  //  ret |= SCCB_Write( VHREF, 0);
  //  printf("set_framesize: w:%d,h:%d,hstart:%d,hstop:%d,vstart:%d,vstop:%d\r\n", w, h, hstart, hstop, vstart, vstop);
  //  // Delay
  //  osDelay(30 / portTICK_PERIOD_MS);
  //
  ret |= SCCB_Write(HSTART, 0);
  ret |= SCCB_Write(HSTOP, w >> 2);

  ret |= SCCB_Write(VSTART, 0);
  ret |= SCCB_Write(VSTOP, h >> 2);

  // Write LSBs
  ret |= SCCB_Write(VHREF, 0);
  if ((w <= 320) && (h <= 240)) {
    // Enable auto-scaling/zooming factors
    // ret |= SCCB_Write(0x12, 0x50);
    set_reg_bits(0x12, 4, 1, 1);

    ret |= SCCB_Write(HSTART, (80 - w / 4));
    ret |= SCCB_Write(HSTOP, (80 + w / 4));

    ret |= SCCB_Write(VSTART, (60 - h / 4));
    ret |= SCCB_Write(VSTOP, (60 + h / 4));

    ret |= SCCB_Write(VHREF, 0);

  } else if ((w <= 640) && (h <= 480)) {
    // Enable auto-scaling/zooming factors
    // ret |= SCCB_Write(0x12, 0x40);
    set_reg_bits(0x12, 4, 1, 0);

    ret |= SCCB_Write(HSTART, (80 - w / 8));
    ret |= SCCB_Write(HSTOP, (80 + w / 8));

    ret |= SCCB_Write(VSTART, (60 - h / 8));
    ret |= SCCB_Write(VSTOP, (60 + h / 8));

    ret |= SCCB_Write(VHREF, 0);
  }

  return ret;
}

static int set_colorbar(int value) {
  int ret = 0;

  ret |= SCCB_Write(TEST_MODE, value);

  return ret;
}

static int set_whitebal(int enable) {
  if (set_reg_bits(COM8, 1, 1, enable) >= 0) {
  }
  return enable;
}

static int set_gain_ctrl(int enable) {
  if (set_reg_bits(COM8, 2, 1, enable) >= 0) {
  }
  return enable;
}

static int set_exposure_ctrl(int enable) {
  if (set_reg_bits(COM8, 0, 1, enable) >= 0) {
  }
  return enable;
}

static int set_hmirror(int enable) {
  if (set_reg_bits(MVFP, 5, 1, enable) >= 0) {
  }
  return enable;
}

static int set_vflip(int enable) {
  if (set_reg_bits(MVFP, 4, 1, enable) >= 0) {
  }
  return enable;
}

static int set_raw_gma_dsp(int enable) {
  int ret = 0;
  ret = set_reg_bits(0xf1, 1, 1, !enable);
  if (ret == 0) {
    printf("Set raw_gma to: %d", !enable);
  }
  return ret;
}

static int set_lenc_dsp(int enable) {
  int ret = 0;
  ret = set_reg_bits(0xf1, 0, 1, !enable);
  if (ret == 0) {
    printf("Set lenc to: %d", !enable);
  }
  return ret;
}

static int set_agc_gain(int option) {
  int ret = 0;
  ret = set_reg_bits(0x13, 4, 1, !!option);
  if (ret == 0) {
    printf("Set gain to: %d", !!option);
  }
  return ret;
}

static int set_awb_gain_dsp(int value) {
  int ret = 0;
  ret = SCCB_Write(0xa6, value);
  if (ret == 0) {
    printf("Set awb gain threthold to: %d", value);
  }
  return ret;
}

static int set_brightness(int level) {
  int ret = 0;
  ret = SCCB_Write(0x55, level);
  if (ret == 0) {
    printf("Set brightness to: %d", level);
  }
  return ret;
}

static int set_contrast(int level) {
  int ret = 0;
  ret = SCCB_Write(0x56, level);
  if (ret == 0) {
    printf("Set contrast to: %d", level);
  }
  return ret;
}

static int set_sharpness(int level) {
  int ret = 0;
  ret = SCCB_Write(INTCTR, level);
  if (ret == 0) {
    printf("Set sharpness to: %d", level);
  }
  return ret;
}

int BF2013_Init(I2C_HandleTypeDef *hi2c2, DCMI_HandleTypeDef *hdcmi, UART_HandleTypeDef *huart) {
  mI2C = hi2c2;
  //  mHuart = huart;
  uint8_t mid_h = i2c_receive(REG_MIDH), mid_l = i2c_receive(REG_MIDL);
  printf("BF2013 MIDH:%02X\tMIDL:%02X\r\n", mid_h, mid_l);
  if (mid_h != VALUE_MIDH || mid_l != VALUE_MIDL) {
    printf("not found bf2013\r\n");
    return -1;
  }
  i2c_sent(COM7, 0x80);
  osDelay(1000);
  int i = 0;
  const uint8_t(*regs)[2] = BF2013_YUV_INIT;
  //  uint8_t value = 0;

  for (i = 1; regs[i][0]; i++) {
    i2c_sent(regs[i][0], regs[i][1]);
    osDelay(10);
    //    value = i2c_receive(regs[i][0]);
    //    if (value != regs[i][1]) {
    //      printf("\033[0;31m regs:[%02X] write: %02X,read:%02X\r\n", regs[i][0], regs[i][1], value);
    //    } else {
    //      printf("\033[0;32m regs:[%02X] write: %02X,read:%02X\r\n", regs[i][0], regs[i][1], value);
    //    }
  }
  osDelay(100);
  set_framesize(FRAMESIZE_QVGA);
  osDelay(100);
  set_pixformat(PIXFORMAT_RGB565);
  osDelay(100);
  //  printf("regs:[COM7]:%02x,[HSTART]:%02x,[HSTOP]:%02x,[VSTART]:%02x,[VSTOP]:%02x,[VHREF]:%02x\r\n", i2c_receive(COM7), i2c_receive(HSTART),
  //  i2c_receive(HSTOP),
  //         i2c_receive(VSTART), i2c_receive(VSTOP), i2c_receive(VHREF));

  //  for (i = 0; i <= 0xfd; i++) {
  //    value = i2c_receive(i);
  //    printf("\033[0;32m regs:[%02X],read:%02X\r\n", i, value);
  //  }
  return 0;
}

void start_ov2640(void) {
  memset((void *) dcmi_line_buf, 0, dcmi_buf_size * 2);
  HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t) dcmi_line_buf, dcmi_buf_size);
  __HAL_DCMI_ENABLE_IT(&hdcmi, DCMI_IT_FRAME);
  __HAL_DCMI_ENABLE(&hdcmi);
  DCMI->CR |= DCMI_CR_CAPTURE;
}

static volatile int dcmi_frame = 0;
extern DMA_HandleTypeDef hdma_dcmi;
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi) {
  HAL_DCMI_Stop(hdcmi);
  dcmi_frame = 1;
}
#endif