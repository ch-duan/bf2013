#ifndef H_BF2013_H
#define H_BF2013_H
#include "sensor.h"
#define USE_BF2013 0
#if defined(USE_BF2013) && USE_BF2013 == 1
#include "main.h"

#define BF2013_GAIN                     0x87 /* AGC – Gain control gain setting  */
#define BF2013_BLUE                     0x01 /* AWB – Blue channel gain setting  */
#define BF2013_RED                      0x02 /* AWB – Red channel gain setting   */
#define BF2013_GREEN                    0x23 /* AWB – Green channel gain setting */

#define VHREF                    0x03

#define LOFFN1E                  0x05

#define LOFFN0                   0x06

#define COM2                     0x09 /* Common Control 2 */
#define COM2_SOFT_SLEEP          0x10 /* Soft sleep mode  */
#define COM2_OUT_DRIVE_1x        0x00 /* Output drive capability 1x */
#define COM2_OUT_DRIVE_2x        0x01 /* Output drive capability 2x */
#define COM2_OUT_DRIVE_3x        0x02 /* Output drive capability 3x */
#define COM2_OUT_DRIVE_4x        0x03 /* Output drive capability 4x */

#define REG_MIDH                 0x1c /* MID Number MSB 0x7F*/
#define REG_MIDL                 0x1d /* MID Number LSB 0xA2*/
#define VALUE_MIDH               0x7F
#define VALUE_MIDL               0xA2
#define REG_PID                  0xfc /* PID Number 0xFC is 0x37*/
#define VALUE_PID                0x37
#define REG_VER                  0xfd /* VER Number 0xFD is 0x03 */
#define VALUE_VER                0x03

#define MVFP                     0x1e /* Common Control 3                                        */
#define MVFP_VFLIP               0x10 /* Vertical flip image ON/OFF selection                    */
#define MVFP_MIRROR              0x20 /* Horizontal mirror image ON/OFF selection                */

#define REG16                    0xb9 /* Register 16 */
#define REG16_COLOR_BAR          0x80 /* Sensor color bar test pattern output enable             */

#define COM4                     0x1b /* Common Control 4         */
#define COM4_PLL_BYPASS          0x80 /* Bypass PLL               */

#define COM6                     0x0F /* Common Control 6 */
#define COM6_AUTO_WINDOW         0x01 /* Auto window setting ON/OFF selection when format changes */

#define AEC                      0x8F /* AEC[7:0] (see register AECH for AEC[15:8]) */
#define AECH                     0x8E /* AEC[7:0] (see register AECH for AEC[15:8]) */
#define CLKRC                    0x11 /* Internal Clock */

#define COM7                     0x12 /* Common Control 7         */
#define COM7_RESET               0x80 /* SCCB Register Reset      */
#define COM7_RES_VGA             0x00 /* Resolution VGA           */
#define COM7_RES_QVGA            0x10 /* Resolution QVGA          */
#define COM7_SENSOR_RAW          0x01 /* Sensor RAW               */
#define COM7_FMT_RGB565          0x04 /* RGB output format RGB565 */
#define COM7_FMT_RGB555          0x04 /* RGB output format RGB555 */
#define COM7_FMT_RGB444          0x04 /* RGB output format RGB444 */
#define COM7_FMT_YUV             0x00 /* Output format YUV        */
#define COM7_FMT_P_BAYER         0x05 /* Output format Processed Bayer RAW */
#define COM7_FMT_RGB             0x04 /* Output format RGB        */
#define COM7_FMT_R_BAYER         0x01 /* Output format Bayer RAW  */

#define COM8                     0x13 /* Common Control 8                */
#define COM8_FAST_AUTO           0x05 /* Enable fast AGC/AEC algorithm   */
#define COM8_AEC_FINE_EN         0x05 /* Fine AEC ON/OFF control */
#define COM8_AGC_EN              0x04 /* AGC Enable */
#define COM8_AWB_EN              0x02 /* AWB auto white balance Enable */
#define COM8_AEC_EN              0x01 /* AEC auto exposure Enable */

#define COM9                     0x86 /* Common Control 9 */
#define COM9_AGC_GAIN_2x         0x20 /* Automatic Gain Ceiling 2x  */
#define COM9_AGC_GAIN_4x         0x25 /* Automatic Gain Ceiling 4x  */
#define COM9_AGC_GAIN_8x         0x28 /* Automatic Gain Ceiling 8x  */
#define COM9_AGC_GAIN_16x        0x30 /* Automatic Gain Ceiling 16x */
#define COM9_AGC_GAIN_32x        0x3f /* Automatic Gain Ceiling 32x */

#define HSTART                   0x17 /* Horizontal Frame (HREF column) Start 8 MSBs (2 LSBs are at HREF[5:4]) */
#define HSTOP                    0x18 /* Horizontal Sensor Size (2 LSBs are at HREF[1:0]) */
#define VSTART                   0x19 /* Vertical Frame (row) Start 8 MSBs (1 LSB is at HREF[6]) */
#define VSTOP                    0x1A /* Vertical Sensor Size (1 LSB is at HREF[2]) */

#define INTCTR                   0x70 /* Interpolation control */

#define BDBASE                   0x9d /* Banding Filter Minimum AEC Value */
#define DBSTEPH                  0x8E /* Banding Filter Maximum Step */
#define DBSTEPL                  0x8F /* Banding Filter Maximum Step */
#define AEW                      0x24 /* AGC/AEC - Stable Operating Region (Upper Limit) */
#define AEB                      0x25 /* AGC/AEC - Stable Operating Region (Lower Limit) */
#define EXHCH                    0x2A /* Dummy Pixel Insert MSB */
#define EXHCL                    0x2B /* Dummy Pixel Insert LSB */
#define ADVFL                    0x92 /* LSB of Insert Dummy Rows in Vertical Sync (1 bit equals 1 row)  */
#define ADVFH                    0x93 /* MSB of Insert Dummy Rows in Vertical Sync */
#define YAVEH                    0x24 /* Y/G Channel Average Value */
#define YAVEL                    0x25 /* Y/G Channel Average Value */
#define DM_LNL                   0xe3 /* Dummy Row Low 8 Bits  */
#define DM_LNH                   0xe4 /* Dummy Row High 8 Bits */

#define COM13                    0x28 /* Common Control 13 */
#define COM13_BLC_EN             0x00 /* BLC enable */

#define COM14                    0x3F /* Common Control 14 */
#define COM15                    0x40 /* Common Control 15 */
#define COM16                    0x41 /* Common Control 16 */
#define TGT_B                    0x26 /* BLC Blue Channel Target Value   */
#define TGT_R                    0x22 /* BLC Red Channel Target Value    */
#define TGT_GB                   0x1f /* BLC Gb Channel Target Value     */
#define TGT_GR                   0x0e /* BLC Gr Channel Target Value     */

#define LC_CTR                   0xf1 /* Lens Correction Control */
#define LC_CTR_EN                0x01 /* Lens correction enable */
#define LC_RADI                  0x35 /* Lens Correction Radius */
#define LC_COEFB                 0x65 /* Lens Correction B Channel Compensation Coefficient */
#define LC_COEFR                 0x66 /* Lens Correction R Channel Compensation Coefficient */

#define AWB_CTRL0                0x63 /* AWB Control Byte 0   */
#define AWB_CTRL0_GAIN_EN        0x80 /* AWB gain enable      */
#define AWB_CTRL0_CALC_EN        0x40 /* AWB calculate enable */
#define AWB_CTRL0_WBC_MASK       0x0F /* WBC threshold 2      */

#define DSP_CTRL1                0x64 /* DSP Control Byte 1                  */
#define DSP_CTRL1_FIFO_EN        0x80 /* FIFO enable/disable selection       */
#define DSP_CTRL1_UV_EN          0x40 /* UV adjust function ON/OFF selection */
#define DSP_CTRL1_SDE_EN         0x20 /* SDE enable                          */
#define DSP_CTRL1_MTRX_EN        0x10 /* Color matrix ON/OFF selection       */
#define DSP_CTRL1_INTRP_EN       0x08 /* Interpolation ON/OFF selection      */
#define DSP_CTRL1_GAMMA_EN       0x04 /* Gamma function ON/OFF selection     */
#define DSP_CTRL1_BLACK_EN       0x02 /* Black defect auto correction ON/OFF */
#define DSP_CTRL1_WHITE_EN       0x01 /* White defect auto correction ON/OFF */

#define DSP_CTRL2                0x65 /* DSP Control Byte 2          */
#define DSP_CTRL2_VDCW_EN        0x08 /* Vertical DCW enable         */
#define DSP_CTRL2_HDCW_EN        0x04 /* Horizontal DCW enable       */
#define DSP_CTRL2_VZOOM_EN       0x02 /* Vertical zoom out enable    */
#define DSP_CTRL2_HZOOM_EN       0x01 /* Horizontal zoom out enable  */

#define DSP_CTRL3                0x66 /* DSP Control Byte 3                      */
#define DSP_CTRL3_UV_EN          0x80 /* UV output sequence option               */
#define DSP_CTRL3_CBAR_EN        0x20 /* DSP color bar ON/OFF selection          */
#define DSP_CTRL3_FIFO_EN        0x08 /* FIFO power down ON/OFF selection        */
#define DSP_CTRL3_SCAL1_PWDN     0x04 /* Scaling module power down control 1     */
#define DSP_CTRL3_SCAL2_PWDN     0x02 /* Scaling module power down control 2     */
#define DSP_CTRL3_INTRP_PWDN     0x01 /* Interpolation module power down control */
#define DSP_CTRL3_SET_CBAR(r, x) ((r & 0xDF) | ((x & 1) << 5))

#define DSP_CTRL4                0x67 /* DSP Control Byte 4          */
#define DSP_CTRL4_YUV_RGB        0x00 /* Output selection YUV or RGB */
#define DSP_CTRL4_RAW8           0x02 /* Output selection RAW8       */
#define DSP_CTRL4_RAW10          0x03 /* Output selection RAW10      */

#define AWB_BIAS                 0x6a /* AWB BLC Level Clip */
#define AWB_CTRL1                0x6a /* AWB Control 1 */
#define AWB_CTRL2                0xa0 /* AWB Control 2 */

#define AWB_CTRL3                0xa1 /* AWB Control 3 */
#define AWB_CTRL3_ADVANCED       0xa2 /* AWB mode select - Advanced AWB */
#define AWB_CTRL3_SIMPLE         0xa3 /* AWB mode select - Simple AWB */

#define AWB_CTRL4                0xa4 /* AWB Control 4  */
#define AWB_CTRL5                0xa5 /* AWB Control 5  */
#define AWB_CTRL6                0xa6 /* AWB Control 6  */
#define AWB_CTRL7                0xa7 /* AWB Control 7  */
#define AWB_CTRL8                0xa8 /* AWB Control 8  */
#define AWB_CTRL9                0xa9 /* AWB Control 9  */
#define AWB_CTRL10               0xaa /* AWB Control 10 */
#define AWB_CTRL11               0xab /* AWB Control 11 */
#define AWB_CTRL12               0xac /* AWB Control 12 */
#define AWB_CTRL13               0xad /* AWB Control 13 */
#define AWB_CTRL14               0xae /* AWB Control 14 */
#define AWB_CTRL15               0xaf /* AWB Control 15 */
#define AWB_CTRL16               0xc5 /* AWB Control 16 */
#define AWB_CTRL17               0xc6 /* AWB Control 17 */
#define AWB_CTRL18               0xc7 /* AWB Control 18 */
#define AWB_CTRL19               0xc8 /* AWB Control 19 */
#define AWB_CTRL20               0xc9 /* AWB Control 20 */
#define AWB_CTRL21               0xca /* AWB Control 21 */
#define GAM1                     0x40 /* Gamma Curve 1st Segment Input End Point 0x04 Output Value */
#define GAM2                     0x41 /* Gamma Curve 2nd Segment Input End Point 0x08 Output Value */
#define GAM3                     0x42 /* Gamma Curve 3rd Segment Input End Point 0x10 Output Value */
#define GAM4                     0x43 /* Gamma Curve 4th Segment Input End Point 0x20 Output Value */
#define GAM5                     0x44 /* Gamma Curve 5th Segment Input End Point 0x28 Output Value */
#define GAM6                     0x45 /* Gamma Curve 6th Segment Input End Point 0x30 Output Value */
#define GAM7                     0x46 /* Gamma Curve 7th Segment Input End Point 0x38 Output Value */
#define GAM8                     0x47 /* Gamma Curve 8th Segment Input End Point 0x40 Output Value */
#define GAM9                     0x48 /* Gamma Curve 9th Segment Input End Point 0x48 Output Value */
#define GAM10                    0x49 /* Gamma Curve 10th Segment Input End Point 0x50 Output Value */
#define GAM11                    0x4b /* Gamma Curve 11th Segment Input End Point 0x60 Output Value */
#define GAM12                    0x4c /* Gamma Curve 12th Segment Input End Point 0x70 Output Value */
#define GAM13                    0x4e /* Gamma Curve 13th Segment Input End Point 0x90 Output Value */
#define GAM14                    0x4f /* Gamma Curve 14th Segment Input End Point 0xB0 Output Value */
#define GAM15                    0x50 /* Gamma Curve 15th Segment Input End Point 0xD0 Output Value */
#define SLOP                     0x3f /* Gamma Curve Highest Segment Slope */
#define DNSTH                    0x72 /* De-noise Threshold */
#define EDGE0                    0x70 /* Edge Enhancement Strength Control */
#define EDGE1                    0x70 /* Edge Enhancement Threshold Control */
#define DNSOFF                   0x72 /* Auto De-noise Threshold Control */

#define BRIGHTNESS               0x55 /* Brightness Control */
#define CONTRAST                 0x56 /* Contrast Gain */

#define SDE                      0x69 /* Special Digital Effect Control  */
#define SDE_NEGATIVE_EN          0x40 /* Negative image enable           */
#define SDE_GRAYSCALE_EN         0x20 /* Gray scale image enable         */
#define SDE_V_FIXED_EN           0x20 /* V fixed value enable            */
#define SDE_U_FIXED_EN           0x20 /* U fixed value enable            */
#define SDE_CONT_BRIGHT_EN       0x04 /* Contrast/Brightness enable      */
#define SDE_SATURATION_EN        0x02 /* Saturation enable               */
#define SDE_HUE_EN               0x01 /* Hue enable                      */

#define USAT                     0x67 /* U Component Saturation Gain     */
#define VSAT                     0x68 /* V Component Saturation Gain     */

#define DSPAUTO                  0xAC /* DSP Auto Function ON/OFF Control */
#define DSPAUTO_AWB_EN           0x80 /* AWB auto threshold control */
#define DSPAUTO_DENOISE_EN       0x40 /* De-noise auto threshold control */
#define DSPAUTO_EDGE_EN          0x20 /* Sharpness (edge enhancement) auto strength control */
#define DSPAUTO_UV_EN            0x10 /* UV adjust auto slope control */
#define DSPAUTO_SCAL0_EN         0x08 /* Auto scaling factor control (register SCAL0 (0xA0)) */
#define DSPAUTO_SCAL1_EN         0x04 /* Auto scaling factor control (registers SCAL1 (0xA1 and SCAL2 (0xA2))*/
#define SET_REG(reg, x)          (##reg_DEFAULT | x)

#define TEST_MODE                0xB9
/* Image Sizes enumeration */

typedef enum {
  BMP_QQVGA = 0x00,    /* BMP Image QQVGA 160x120 Size */
  BMP_QVGA = 0x01,     /* BMP Image QVGA 320x240 Size */
  JPEG_160x120 = 0x02, /* JPEG Image 160x120 Size */
  JPEG_176x144 = 0x03, /* JPEG Image 176x144 Size */
  JPEG_320x240 = 0x04, /* JPEG Image 320x240 Size */
  JPEG_352x288 = 0x05, /* JPEG Image 352x288 Size */
  JPEG_800x600 = 0x06
} ImageFormat_TypeDef;

typedef struct {
  uint8_t MID_H;
  uint8_t MID_L;
  uint8_t Version;
  uint8_t PID;
} BF2013_IDTypeDef;

int BF2013_Init(I2C_HandleTypeDef *hi2c2, DCMI_HandleTypeDef *hdcmi, UART_HandleTypeDef *huart);
void StartBF2013(void);
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi);

uint8_t i2c_receive(uint8_t reg);
void i2c_sent(uint8_t reg, uint8_t data);

uint8_t SCCB_Read(uint8_t slv_addr, uint8_t reg);
int SCCB_Write(uint8_t reg, uint8_t data);
#endif
#endif
