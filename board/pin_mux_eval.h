#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/* SPIFI_CLK (coord M13), J13[2]/U27[6]/P0_26-SPIFI_CLK */
#define BOARD_INITSPIFIPINS_SPIFI_CLK_PERIPHERAL                          SPIFI0   /*!< Device name: SPIFI0 */
#define BOARD_INITSPIFIPINS_SPIFI_CLK_SIGNAL                           SPIFI_SCK   /*!< SPIFI0 signal: SPIFI_SCK */
#define BOARD_INITSPIFIPINS_SPIFI_CLK_PIN_NAME                         SPIFI_CLK   /*!< Pin name */
#define BOARD_INITSPIFIPINS_SPIFI_CLK_LABEL      "J13[2]/U27[6]/P0_26-SPIFI_CLK"   /*!< Label */
#define BOARD_INITSPIFIPINS_SPIFI_CLK_NAME                           "SPIFI_CLK"   /*!< Identifier name */

/* SPIFI_IO(0) (coord M7), J13[6]/U27[5]/P0_24-SPIFI_IO0 */
#define BOARD_INITSPIFIPINS_SPIFI_IO0_PERIPHERAL                          SPIFI0   /*!< Device name: SPIFI0 */
#define BOARD_INITSPIFIPINS_SPIFI_IO0_SIGNAL                SPIFI_IO0/SPIFI_MOSI   /*!< SPIFI0 signal: SPIFI_IO0/SPIFI_MOSI */
#define BOARD_INITSPIFIPINS_SPIFI_IO0_PIN_NAME                       SPIFI_IO(0)   /*!< Pin name */
#define BOARD_INITSPIFIPINS_SPIFI_IO0_LABEL      "J13[6]/U27[5]/P0_24-SPIFI_IO0"   /*!< Label */
#define BOARD_INITSPIFIPINS_SPIFI_IO0_NAME                           "SPIFI_IO0"   /*!< Identifier name */

/* SPIFI_IO(1) (coord K8), J13[4]/U27[2]/P0_25-SPIFI_IO1 */
#define BOARD_INITSPIFIPINS_SPIFI_IO1_PERIPHERAL                          SPIFI0   /*!< Device name: SPIFI0 */
#define BOARD_INITSPIFIPINS_SPIFI_IO1_SIGNAL                SPIFI_IO1/SPIFI_MISO   /*!< SPIFI0 signal: SPIFI_IO1/SPIFI_MISO */
#define BOARD_INITSPIFIPINS_SPIFI_IO1_PIN_NAME                       SPIFI_IO(1)   /*!< Pin name */
#define BOARD_INITSPIFIPINS_SPIFI_IO1_LABEL      "J13[4]/U27[2]/P0_25-SPIFI_IO1"   /*!< Label */
#define BOARD_INITSPIFIPINS_SPIFI_IO1_NAME                           "SPIFI_IO1"   /*!< Identifier name */

/* SPIFI_IO(3) (coord L9), J13[12]/U27[7]/P0_27-SPIFI_IO3 */
#define BOARD_INITSPIFIPINS_SPIFI_IO3_PERIPHERAL                          SPIFI0   /*!< Device name: SPIFI0 */
#define BOARD_INITSPIFIPINS_SPIFI_IO3_SIGNAL                            SPIFI_IO   /*!< SPIFI0 signal: SPIFI_IO */
#define BOARD_INITSPIFIPINS_SPIFI_IO3_CHANNEL                                  3   /*!< SPIFI0 SPIFI_IO channel: 3 */
#define BOARD_INITSPIFIPINS_SPIFI_IO3_PIN_NAME                       SPIFI_IO(3)   /*!< Pin name */
#define BOARD_INITSPIFIPINS_SPIFI_IO3_LABEL     "J13[12]/U27[7]/P0_27-SPIFI_IO3"   /*!< Label */
#define BOARD_INITSPIFIPINS_SPIFI_IO3_NAME                           "SPIFI_IO3"   /*!< Identifier name */

/* SPIFI_IO(2) (coord M9), J13[10]/U27[3]/P0_28-SPIFI_IO2-USB0_OCURRn */
#define BOARD_INITSPIFIPINS_SPIFI_IO2_PERIPHERAL                          SPIFI0   /*!< Device name: SPIFI0 */
#define BOARD_INITSPIFIPINS_SPIFI_IO2_SIGNAL                            SPIFI_IO   /*!< SPIFI0 signal: SPIFI_IO */
#define BOARD_INITSPIFIPINS_SPIFI_IO2_CHANNEL                                  2   /*!< SPIFI0 SPIFI_IO channel: 2 */
#define BOARD_INITSPIFIPINS_SPIFI_IO2_PIN_NAME                       SPIFI_IO(2)   /*!< Pin name */
#define BOARD_INITSPIFIPINS_SPIFI_IO2_LABEL "J13[10]/U27[3]/P0_28-SPIFI_IO2-USB0_OCURRn" /*!< Label */
#define BOARD_INITSPIFIPINS_SPIFI_IO2_NAME                           "SPIFI_IO2"   /*!< Identifier name */

/* SPIFI_CSN (coord N7), J13[8]/U27[1]/P0_23-SPIFI_CSn-MCLK */
#define BOARD_INITSPIFIPINS_SPIFI_CSn_PERIPHERAL                          SPIFI0   /*!< Device name: SPIFI0 */
#define BOARD_INITSPIFIPINS_SPIFI_CSn_SIGNAL                           SPIFI_CSN   /*!< SPIFI0 signal: SPIFI_CSN */
#define BOARD_INITSPIFIPINS_SPIFI_CSn_PIN_NAME                         SPIFI_CSN   /*!< Pin name */
#define BOARD_INITSPIFIPINS_SPIFI_CSn_LABEL "J13[8]/U27[1]/P0_23-SPIFI_CSn-MCLK"   /*!< Label */
#define BOARD_INITSPIFIPINS_SPIFI_CSn_NAME                           "SPIFI_CSn"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSPIFIPins(void); /* Function assigned for the Cortex-M4F */

/* EMC_A(14) (coord P9), U28[G8]/P3_25-EMC_A14 */
#define BOARD_INITSDRAMPINS_EMC_A14_PERIPHERAL                               EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A14_SIGNAL                                 EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A14_CHANNEL                                   14   /*!< EMC EMC_A channel: 14 */
#define BOARD_INITSDRAMPINS_EMC_A14_PIN_NAME                           EMC_A(14)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A14_LABEL                "U28[G8]/P3_25-EMC_A14"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A14_NAME                               "EMC_A14"   /*!< Identifier name */

/* EMC_A(13) (coord M12), U28[G7]/P1_25-EMC_A13 */
#define BOARD_INITSDRAMPINS_EMC_A13_PERIPHERAL                               EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A13_SIGNAL                                 EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A13_CHANNEL                                   13   /*!< EMC EMC_A channel: 13 */
#define BOARD_INITSDRAMPINS_EMC_A13_PIN_NAME                           EMC_A(13)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A13_LABEL                "U28[G7]/P1_25-EMC_A13"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A13_NAME                               "EMC_A13"   /*!< Identifier name */

/* EMC_A(11) (coord M10), U28[G2]/P1_23-EMC_A11 */
#define BOARD_INITSDRAMPINS_EMC_A11_PERIPHERAL                               EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A11_SIGNAL                                 EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A11_CHANNEL                                   11   /*!< EMC EMC_A channel: 11 */
#define BOARD_INITSDRAMPINS_EMC_A11_PIN_NAME                           EMC_A(11)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A11_LABEL                "U28[G2]/P1_23-EMC_A11"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A11_NAME                               "EMC_A11"   /*!< Identifier name */

/* EMC_A(10) (coord B7), U28[H9]/P1_16-EMC_A10 */
#define BOARD_INITSDRAMPINS_EMC_A10_PERIPHERAL                               EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A10_SIGNAL                                 EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A10_CHANNEL                                   10   /*!< EMC EMC_A channel: 10 */
#define BOARD_INITSDRAMPINS_EMC_A10_PIN_NAME                           EMC_A(10)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A10_LABEL                "U28[H9]/P1_16-EMC_A10"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A10_NAME                               "EMC_A10"   /*!< Identifier name */

/* EMC_A(9) (coord F10), U28[G3]/P1_27-EMC_A9 */
#define BOARD_INITSDRAMPINS_EMC_A9_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A9_SIGNAL                                  EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A9_CHANNEL                                     9   /*!< EMC EMC_A channel: 9 */
#define BOARD_INITSDRAMPINS_EMC_A9_PIN_NAME                             EMC_A(9)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A9_LABEL                  "U28[G3]/P1_27-EMC_A9"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A9_NAME                                 "EMC_A9"   /*!< Identifier name */

/* EMC_A(8) (coord J10), U28[H1]/P1_26-EMC_A8 */
#define BOARD_INITSDRAMPINS_EMC_A8_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A8_SIGNAL                                  EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A8_CHANNEL                                     8   /*!< EMC EMC_A channel: 8 */
#define BOARD_INITSDRAMPINS_EMC_A8_PIN_NAME                             EMC_A(8)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A8_LABEL                  "U28[H1]/P1_26-EMC_A8"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A8_NAME                                 "EMC_A8"   /*!< Identifier name */

/* EMC_A(7) (coord P8), U28[H2]/P1_8-EMC_A7 */
#define BOARD_INITSDRAMPINS_EMC_A7_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A7_SIGNAL                                  EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A7_CHANNEL                                     7   /*!< EMC EMC_A channel: 7 */
#define BOARD_INITSDRAMPINS_EMC_A7_PIN_NAME                             EMC_A(7)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A7_LABEL                   "U28[H2]/P1_8-EMC_A7"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A7_NAME                                 "EMC_A7"   /*!< Identifier name */

/* EMC_A(6) (coord N1), U28[H3]/P1_7-EMC_A6 */
#define BOARD_INITSDRAMPINS_EMC_A6_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A6_SIGNAL                                  EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A6_CHANNEL                                     6   /*!< EMC EMC_A channel: 6 */
#define BOARD_INITSDRAMPINS_EMC_A6_PIN_NAME                             EMC_A(6)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A6_LABEL                   "U28[H3]/P1_7-EMC_A6"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A6_NAME                                 "EMC_A6"   /*!< Identifier name */

/* EMC_A(5) (coord G4), U28[J2]/P1_6-EMC_A5 */
#define BOARD_INITSDRAMPINS_EMC_A5_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A5_SIGNAL                                  EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A5_CHANNEL                                     5   /*!< EMC EMC_A channel: 5 */
#define BOARD_INITSDRAMPINS_EMC_A5_PIN_NAME                             EMC_A(5)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A5_LABEL                   "U28[J2]/P1_6-EMC_A5"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A5_NAME                                 "EMC_A5"   /*!< Identifier name */

/* EMC_A(4) (coord E4), U28[J3]/P1_5-EMC_A4 */
#define BOARD_INITSDRAMPINS_EMC_A4_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A4_SIGNAL                                  EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A4_CHANNEL                                     4   /*!< EMC EMC_A channel: 4 */
#define BOARD_INITSDRAMPINS_EMC_A4_PIN_NAME                             EMC_A(4)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A4_LABEL                   "U28[J3]/P1_5-EMC_A4"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A4_NAME                                 "EMC_A4"   /*!< Identifier name */

/* EMC_A(3) (coord C13), U28[J7]/P0_21-EMC_A3 */
#define BOARD_INITSDRAMPINS_EMC_A3_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A3_SIGNAL                                  EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A3_CHANNEL                                     3   /*!< EMC EMC_A channel: 3 */
#define BOARD_INITSDRAMPINS_EMC_A3_PIN_NAME                             EMC_A(3)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A3_LABEL                  "U28[J7]/P0_21-EMC_A3"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A3_NAME                                 "EMC_A3"   /*!< Identifier name */

/* EMC_A(2) (coord D13), U28[J8]/P0_20-EMC_A2 */
#define BOARD_INITSDRAMPINS_EMC_A2_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A2_SIGNAL                                  EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A2_CHANNEL                                     2   /*!< EMC EMC_A channel: 2 */
#define BOARD_INITSDRAMPINS_EMC_A2_PIN_NAME                             EMC_A(2)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A2_LABEL                  "U28[J8]/P0_20-EMC_A2"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A2_NAME                                 "EMC_A2"   /*!< Identifier name */

/* EMC_A(1) (coord C6), U28[H8]/P0_19-EMC_A1 */
#define BOARD_INITSDRAMPINS_EMC_A1_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A1_SIGNAL                                  EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A1_CHANNEL                                     1   /*!< EMC EMC_A channel: 1 */
#define BOARD_INITSDRAMPINS_EMC_A1_PIN_NAME                             EMC_A(1)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A1_LABEL                  "U28[H8]/P0_19-EMC_A1"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A1_NAME                                 "EMC_A1"   /*!< Identifier name */

/* EMC_A(0) (coord C14), U28[H7]/P0_18-EMC_A0 */
#define BOARD_INITSDRAMPINS_EMC_A0_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_A0_SIGNAL                                  EMC_A   /*!< EMC signal: EMC_A */
#define BOARD_INITSDRAMPINS_EMC_A0_CHANNEL                                     0   /*!< EMC EMC_A channel: 0 */
#define BOARD_INITSDRAMPINS_EMC_A0_PIN_NAME                             EMC_A(0)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_A0_LABEL                  "U28[H7]/P0_18-EMC_A0"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_A0_NAME                                 "EMC_A0"   /*!< Identifier name */

/* EMC_WEN (coord L4), U28[F9]/P0_15-EMC_WEn */
#define BOARD_INITSDRAMPINS_EMC_WEn_PERIPHERAL                               EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_WEn_SIGNAL                                EMC_WE   /*!< EMC signal: EMC_WE */
#define BOARD_INITSDRAMPINS_EMC_WEn_PIN_NAME                             EMC_WEN   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_WEn_LABEL                "U28[F9]/P0_15-EMC_WEn"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_WEn_NAME                               "EMC_WEn"   /*!< Identifier name */

/* EMC_CASN (coord K6), U28[F7]/P1_9-EMC_CASn */
#define BOARD_INITSDRAMPINS_EMC_CASn_PERIPHERAL                              EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_CASn_SIGNAL                              EMC_CAS   /*!< EMC signal: EMC_CAS */
#define BOARD_INITSDRAMPINS_EMC_CASn_PIN_NAME                           EMC_CASN   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_CASn_LABEL               "U28[F7]/P1_9-EMC_CASn"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_CASn_NAME                             "EMC_CASn"   /*!< Identifier name */

/* EMC_RASN (coord N9), U28[F8]/P1_10-EMC_RASn */
#define BOARD_INITSDRAMPINS_EMC_RASn_PERIPHERAL                              EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_RASn_SIGNAL                              EMC_RAS   /*!< EMC signal: EMC_RAS */
#define BOARD_INITSDRAMPINS_EMC_RASn_PIN_NAME                           EMC_RASN   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_RASn_LABEL              "U28[F8]/P1_10-EMC_RASn"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_RASn_NAME                             "EMC_RASn"   /*!< Identifier name */

/* EMC_DYCSN(0) (coord K9), U28[G9]/P1_12-EMC_DYCSn0 */
#define BOARD_INITSDRAMPINS_EMC_DYCSn0_PERIPHERAL                            EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_DYCSn0_SIGNAL                           EMC_DYCS   /*!< EMC signal: EMC_DYCS */
#define BOARD_INITSDRAMPINS_EMC_DYCSn0_CHANNEL                                 0   /*!< EMC EMC_DYCS channel: 0 */
#define BOARD_INITSDRAMPINS_EMC_DYCSn0_PIN_NAME                     EMC_DYCSN(0)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_DYCSn0_LABEL          "U28[G9]/P1_12-EMC_DYCSn0"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_DYCSn0_NAME                         "EMC_DYCSn0"   /*!< Identifier name */

/* EMC_D(15) (coord C5), U28[A2]/RP2[1]/P1_31-EMC_D15 */
#define BOARD_INITSDRAMPINS_EMC_D15_PERIPHERAL                               EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D15_SIGNAL                                 EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D15_CHANNEL                                   15   /*!< EMC EMC_D channel: 15 */
#define BOARD_INITSDRAMPINS_EMC_D15_PIN_NAME                           EMC_D(15)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D15_LABEL         "U28[A2]/RP2[1]/P1_31-EMC_D15"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D15_NAME                               "EMC_D15"   /*!< Identifier name */

/* EMC_D(14) (coord A8), U28[B1]/RP2[2]/P1_30-EMC_D14 */
#define BOARD_INITSDRAMPINS_EMC_D14_PERIPHERAL                               EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D14_SIGNAL                                 EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D14_CHANNEL                                   14   /*!< EMC EMC_D channel: 14 */
#define BOARD_INITSDRAMPINS_EMC_D14_PIN_NAME                           EMC_D(14)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D14_LABEL         "U28[B1]/RP2[2]/P1_30-EMC_D14"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D14_NAME                               "EMC_D14"   /*!< Identifier name */

/* EMC_D(13) (coord C11), U28[B2]/RP2[3]/P1_29-EMC_D13 */
#define BOARD_INITSDRAMPINS_EMC_D13_PERIPHERAL                               EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D13_SIGNAL                                 EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D13_CHANNEL                                   13   /*!< EMC EMC_D channel: 13 */
#define BOARD_INITSDRAMPINS_EMC_D13_PIN_NAME                           EMC_D(13)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D13_LABEL         "U28[B2]/RP2[3]/P1_29-EMC_D13"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D13_NAME                               "EMC_D13"   /*!< Identifier name */

/* EMC_D(12) (coord E12), U28[C1]/RP2[4]/P1_28-EMC_D12 */
#define BOARD_INITSDRAMPINS_EMC_D12_PERIPHERAL                               EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D12_SIGNAL                                 EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D12_CHANNEL                                   12   /*!< EMC EMC_D channel: 12 */
#define BOARD_INITSDRAMPINS_EMC_D12_PIN_NAME                           EMC_D(12)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D12_LABEL         "U28[C1]/RP2[4]/P1_28-EMC_D12"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D12_NAME                               "EMC_D12"   /*!< Identifier name */

/* EMC_D(11) (coord D4), U28[C2]/RP4[1]/P1_4-EMC_D11 */
#define BOARD_INITSDRAMPINS_EMC_D11_PERIPHERAL                               EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D11_SIGNAL                                 EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D11_CHANNEL                                   11   /*!< EMC EMC_D channel: 11 */
#define BOARD_INITSDRAMPINS_EMC_D11_PIN_NAME                           EMC_D(11)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D11_LABEL          "U28[C2]/RP4[1]/P1_4-EMC_D11"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D11_NAME                               "EMC_D11"   /*!< Identifier name */

/* EMC_D(10) (coord N8), U28[D1]/RP4[2]/P1_21-EMC_D10 */
#define BOARD_INITSDRAMPINS_EMC_D10_PERIPHERAL                               EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D10_SIGNAL                                 EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D10_CHANNEL                                   10   /*!< EMC EMC_D channel: 10 */
#define BOARD_INITSDRAMPINS_EMC_D10_PIN_NAME                           EMC_D(10)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D10_LABEL         "U28[D1]/RP4[2]/P1_21-EMC_D10"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D10_NAME                               "EMC_D10"   /*!< Identifier name */

/* EMC_D(9) (coord M1), U28[D2]/RP4[3]/P1_20-EMC_D9 */
#define BOARD_INITSDRAMPINS_EMC_D9_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D9_SIGNAL                                  EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D9_CHANNEL                                     9   /*!< EMC EMC_D channel: 9 */
#define BOARD_INITSDRAMPINS_EMC_D9_PIN_NAME                             EMC_D(9)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D9_LABEL           "U28[D2]/RP4[3]/P1_20-EMC_D9"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D9_NAME                                 "EMC_D9"   /*!< Identifier name */

/* EMC_D(8) (coord L1), U28[E1]/RP4[4]/P1_19-EMC_D8 */
#define BOARD_INITSDRAMPINS_EMC_D8_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D8_SIGNAL                                  EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D8_CHANNEL                                     8   /*!< EMC EMC_D channel: 8 */
#define BOARD_INITSDRAMPINS_EMC_D8_PIN_NAME                             EMC_D(8)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D8_LABEL           "U28[E1]/RP4[4]/P1_19-EMC_D8"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D8_NAME                                 "EMC_D8"   /*!< Identifier name */

/* EMC_D(7) (coord G12), U28[E9]/RP5[1]/P0_9-EMC_D7 */
#define BOARD_INITSDRAMPINS_EMC_D7_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D7_SIGNAL                                  EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D7_CHANNEL                                     7   /*!< EMC EMC_D channel: 7 */
#define BOARD_INITSDRAMPINS_EMC_D7_PIN_NAME                             EMC_D(7)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D7_LABEL            "U28[E9]/RP5[1]/P0_9-EMC_D7"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D7_NAME                                 "EMC_D7"   /*!< Identifier name */

/* EMC_D(6) (coord H10), U28[D8]/RP5[2]/P0_8-EMC_D6 */
#define BOARD_INITSDRAMPINS_EMC_D6_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D6_SIGNAL                                  EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D6_CHANNEL                                     6   /*!< EMC EMC_D channel: 6 */
#define BOARD_INITSDRAMPINS_EMC_D6_PIN_NAME                             EMC_D(6)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D6_LABEL            "U28[D8]/RP5[2]/P0_8-EMC_D6"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D6_NAME                                 "EMC_D6"   /*!< Identifier name */

/* EMC_D(5) (coord H12), U28[D9]/RP5[3]/P0_7-EMC_D5 */
#define BOARD_INITSDRAMPINS_EMC_D5_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D5_SIGNAL                                  EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D5_CHANNEL                                     5   /*!< EMC EMC_D channel: 5 */
#define BOARD_INITSDRAMPINS_EMC_D5_PIN_NAME                             EMC_D(5)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D5_LABEL            "U28[D9]/RP5[3]/P0_7-EMC_D5"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D5_NAME                                 "EMC_D5"   /*!< Identifier name */

/* EMC_D(4) (coord A5), U28[C8]/RP5[4]/SW2/P0_6-ISP2/P0_6-EMC_D4 */
#define BOARD_INITSDRAMPINS_EMC_D4_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D4_SIGNAL                                  EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D4_CHANNEL                                     4   /*!< EMC EMC_D channel: 4 */
#define BOARD_INITSDRAMPINS_EMC_D4_PIN_NAME                             EMC_D(4)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D4_LABEL "U28[C8]/RP5[4]/SW2/P0_6-ISP2/P0_6-EMC_D4" /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D4_NAME                                 "EMC_D4"   /*!< Identifier name */

/* EMC_D(3) (coord E7), U28[C9]/RP3[1]/JS32[1]/SW3/P0_5-ISP1/P0_5-EMC_D3 */
#define BOARD_INITSDRAMPINS_EMC_D3_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D3_SIGNAL                                  EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D3_CHANNEL                                     3   /*!< EMC EMC_D channel: 3 */
#define BOARD_INITSDRAMPINS_EMC_D3_PIN_NAME                             EMC_D(3)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D3_LABEL "U28[C9]/RP3[1]/JS32[1]/SW3/P0_5-ISP1/P0_5-EMC_D3" /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D3_NAME                                 "EMC_D3"   /*!< Identifier name */

/* EMC_D(2) (coord C8), U28[B8]/RP3[2]/JS32[3]/SW4/P0_4-ISP0/P0_4-EMC_D2 */
#define BOARD_INITSDRAMPINS_EMC_D2_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D2_SIGNAL                                  EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D2_CHANNEL                                     2   /*!< EMC EMC_D channel: 2 */
#define BOARD_INITSDRAMPINS_EMC_D2_PIN_NAME                             EMC_D(2)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D2_LABEL "U28[B8]/RP3[2]/JS32[3]/SW4/P0_4-ISP0/P0_4-EMC_D2" /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D2_NAME                                 "EMC_D2"   /*!< Identifier name */

/* EMC_D(1) (coord A10), U28[B9]/RP3[3]/JS34[1]/U26[11]/J14[2]/P0_3-ISP_FC3_MOSI/P0_3-EMC_D1 */
#define BOARD_INITSDRAMPINS_EMC_D1_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D1_SIGNAL                                  EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D1_CHANNEL                                     1   /*!< EMC EMC_D channel: 1 */
#define BOARD_INITSDRAMPINS_EMC_D1_PIN_NAME                             EMC_D(1)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D1_LABEL "U28[B9]/RP3[3]/JS34[1]/U26[11]/J14[2]/P0_3-ISP_FC3_MOSI/P0_3-EMC_D1" /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D1_NAME                                 "EMC_D1"   /*!< Identifier name */

/* EMC_D(0) (coord E9), U28[A8]/RP3[4]/JS35[1]/U24[11]/J14[3]/P0_2-ISP_FC3_MISO/P0_2-EMC_D0 */
#define BOARD_INITSDRAMPINS_EMC_D0_PERIPHERAL                                EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_D0_SIGNAL                                  EMC_D   /*!< EMC signal: EMC_D */
#define BOARD_INITSDRAMPINS_EMC_D0_CHANNEL                                     0   /*!< EMC EMC_D channel: 0 */
#define BOARD_INITSDRAMPINS_EMC_D0_PIN_NAME                             EMC_D(0)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_D0_LABEL "U28[A8]/RP3[4]/JS35[1]/U24[11]/J14[3]/P0_2-ISP_FC3_MISO/P0_2-EMC_D0" /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_D0_NAME                                 "EMC_D0"   /*!< Identifier name */

/* EMC_DQM(1) (coord C12), U28[F1]/P1_14-EMC_DQM1 */
#define BOARD_INITSDRAMPINS_EMC_DQM1_PERIPHERAL                              EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_DQM1_SIGNAL                              EMC_DQM   /*!< EMC signal: EMC_DQM */
#define BOARD_INITSDRAMPINS_EMC_DQM1_CHANNEL                                   1   /*!< EMC EMC_DQM channel: 1 */
#define BOARD_INITSDRAMPINS_EMC_DQM1_PIN_NAME                         EMC_DQM(1)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_DQM1_LABEL              "U28[F1]/P1_14-EMC_DQM1"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_DQM1_NAME                             "EMC_DQM1"   /*!< Identifier name */

/* EMC_DQM(0) (coord G10), U28[E8]/P1_13-EMC_DQM0 */
#define BOARD_INITSDRAMPINS_EMC_DQM0_PERIPHERAL                              EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_DQM0_SIGNAL                              EMC_DQM   /*!< EMC signal: EMC_DQM */
#define BOARD_INITSDRAMPINS_EMC_DQM0_CHANNEL                                   0   /*!< EMC EMC_DQM channel: 0 */
#define BOARD_INITSDRAMPINS_EMC_DQM0_PIN_NAME                         EMC_DQM(0)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_DQM0_LABEL              "U28[E8]/P1_13-EMC_DQM0"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_DQM0_NAME                             "EMC_DQM0"   /*!< Identifier name */

/* EMC_CLK(0) (coord B4), U28[F2]/P1_11-EMC_CLK0 */
#define BOARD_INITSDRAMPINS_EMC_CLK0_PERIPHERAL                              EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_CLK0_SIGNAL                              EMC_CLK   /*!< EMC signal: EMC_CLK */
#define BOARD_INITSDRAMPINS_EMC_CLK0_CHANNEL                                   0   /*!< EMC EMC_CLK channel: 0 */
#define BOARD_INITSDRAMPINS_EMC_CLK0_PIN_NAME                         EMC_CLK(0)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_CLK0_LABEL              "U28[F2]/P1_11-EMC_CLK0"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_CLK0_NAME                             "EMC_CLK0"   /*!< Identifier name */

/* EMC_CKE(0) (coord A11), U28[F3]/P1_15-EMC_CKE0 */
#define BOARD_INITSDRAMPINS_EMC_CKE0_PERIPHERAL                              EMC   /*!< Device name: EMC */
#define BOARD_INITSDRAMPINS_EMC_CKE0_SIGNAL                              EMC_CKE   /*!< EMC signal: EMC_CKE */
#define BOARD_INITSDRAMPINS_EMC_CKE0_CHANNEL                                   0   /*!< EMC EMC_CKE channel: 0 */
#define BOARD_INITSDRAMPINS_EMC_CKE0_PIN_NAME                         EMC_CKE(0)   /*!< Pin name */
#define BOARD_INITSDRAMPINS_EMC_CKE0_LABEL              "U28[F3]/P1_15-EMC_CKE0"   /*!< Label */
#define BOARD_INITSDRAMPINS_EMC_CKE0_NAME                             "EMC_CKE0"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSDRAMPins(void); /* Function assigned for the Cortex-M4F */

/* USB1_DP (coord H3), J2[3]/U2[2]/U25[H3]/USB1_DP_TRGT */
#define BOARD_INITUSBPINS_USB1_DP_PERIPHERAL                              USBHSH   /*!< Device name: USBHSH */
#define BOARD_INITUSBPINS_USB1_DP_SIGNAL                                  USB_DP   /*!< USBHSH signal: USB_DP */
#define BOARD_INITUSBPINS_USB1_DP_PIN_NAME                               USB1_DP   /*!< Pin name */
#define BOARD_INITUSBPINS_USB1_DP_LABEL       "J2[3]/U2[2]/U25[H3]/USB1_DP_TRGT"   /*!< Label */
#define BOARD_INITUSBPINS_USB1_DP_NAME                                 "USB1_DP"   /*!< Identifier name */

/* USB1_DM (coord H2), J2[2]/U2[3]/U25[H2]/USB1_DM_TRGT */
#define BOARD_INITUSBPINS_USB1_DM_PERIPHERAL                              USBHSH   /*!< Device name: USBHSH */
#define BOARD_INITUSBPINS_USB1_DM_SIGNAL                                  USB_DM   /*!< USBHSH signal: USB_DM */
#define BOARD_INITUSBPINS_USB1_DM_PIN_NAME                               USB1_DM   /*!< Pin name */
#define BOARD_INITUSBPINS_USB1_DM_LABEL       "J2[2]/U2[3]/U25[H2]/USB1_DM_TRGT"   /*!< Label */
#define BOARD_INITUSBPINS_USB1_DM_NAME                                 "USB1_DM"   /*!< Identifier name */

/* USB1_VBUS (coord G2), J2[1]/U2[4]/VBUS1_TARGET */
#define BOARD_INITUSBPINS_USB1_VBUS_PERIPHERAL                            USBHSH   /*!< Device name: USBHSH */
#define BOARD_INITUSBPINS_USB1_VBUS_SIGNAL                              USB_VBUS   /*!< USBHSH signal: USB_VBUS */
#define BOARD_INITUSBPINS_USB1_VBUS_PIN_NAME                           USB1_VBUS   /*!< Pin name */
#define BOARD_INITUSBPINS_USB1_VBUS_LABEL             "J2[1]/U2[4]/VBUS1_TARGET"   /*!< Label */
#define BOARD_INITUSBPINS_USB1_VBUS_NAME                             "USB1_VBUS"   /*!< Identifier name */

/* USB1_ID (coord G1), J2[4]/USB1_ID_TARGET */
#define BOARD_INITUSBPINS_USB1_ID_PERIPHERAL                              USBHSH   /*!< Device name: USBHSH */
#define BOARD_INITUSBPINS_USB1_ID_SIGNAL                             USB_IDVALUE   /*!< USBHSH signal: USB_IDVALUE */
#define BOARD_INITUSBPINS_USB1_ID_PIN_NAME                               USB1_ID   /*!< Pin name */
#define BOARD_INITUSBPINS_USB1_ID_LABEL                   "J2[4]/USB1_ID_TARGET"   /*!< Label */
#define BOARD_INITUSBPINS_USB1_ID_NAME                                 "USB1_ID"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitUSBPins(void); /* Function assigned for the Cortex-M4F */

/* SWDIO (coord M3), P1[2]/U22[4]/D5[5]/IF_SWDIO */
#define BOARD_INITSWDPINS_IF_SWDIO_PERIPHERAL                                SWD   /*!< Device name: SWD */
#define BOARD_INITSWDPINS_IF_SWDIO_SIGNAL                                  SWDIO   /*!< SWD signal: SWDIO */
#define BOARD_INITSWDPINS_IF_SWDIO_PIN_NAME                                SWDIO   /*!< Pin name */
#define BOARD_INITSWDPINS_IF_SWDIO_LABEL           "P1[2]/U22[4]/D5[5]/IF_SWDIO"   /*!< Label */
#define BOARD_INITSWDPINS_IF_SWDIO_NAME                               "IF_SWDIO"   /*!< Identifier name */

/* SWCLK (coord L3), U16[4]/SWDCLK_TRGT */
#define BOARD_INITSWDPINS_SWDCLK_TRGT_PERIPHERAL                             SWD   /*!< Device name: SWD */
#define BOARD_INITSWDPINS_SWDCLK_TRGT_SIGNAL                               SWCLK   /*!< SWD signal: SWCLK */
#define BOARD_INITSWDPINS_SWDCLK_TRGT_PIN_NAME                             SWCLK   /*!< Pin name */
#define BOARD_INITSWDPINS_SWDCLK_TRGT_LABEL                 "U16[4]/SWDCLK_TRGT"   /*!< Label */
#define BOARD_INITSWDPINS_SWDCLK_TRGT_NAME                         "SWDCLK_TRGT"   /*!< Identifier name */

/* SWO (coord P2), U16[12]/SWO_TRGT */
#define BOARD_INITSWDPINS_SWO_TRGT_PERIPHERAL                                SWD   /*!< Device name: SWD */
#define BOARD_INITSWDPINS_SWO_TRGT_SIGNAL                                    SWO   /*!< SWD signal: SWO */
#define BOARD_INITSWDPINS_SWO_TRGT_PIN_NAME                                  SWO   /*!< Pin name */
#define BOARD_INITSWDPINS_SWO_TRGT_LABEL                      "U16[12]/SWO_TRGT"   /*!< Label */
#define BOARD_INITSWDPINS_SWO_TRGT_NAME                               "SWO_TRGT"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSWDPins(void); /* Function assigned for the Cortex-M4F */

/* LCD_FP (coord L7), J16[33]/P2_14-LCD_FP */
#define BOARD_INITLCDPINS_LCD_FP_PERIPHERAL                                  LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_FP_SIGNAL                                   LCD_FP   /*!< LCD signal: LCD_FP */
#define BOARD_INITLCDPINS_LCD_FP_PIN_NAME                                 LCD_FP   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_FP_LABEL                    "J16[33]/P2_14-LCD_FP"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_FP_NAME                                   "LCD_FP"   /*!< Identifier name */

/* LCD_DCLK (coord P7), J16[30]/P2_13-LCD_DCLK */
#define BOARD_INITLCDPINS_LCD_DCLK_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_DCLK_SIGNAL                               LCD_DCLK   /*!< LCD signal: LCD_DCLK */
#define BOARD_INITLCDPINS_LCD_DCLK_PIN_NAME                             LCD_DCLK   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_DCLK_LABEL                "J16[30]/P2_13-LCD_DCLK"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_DCLK_NAME                               "LCD_DCLK"   /*!< Identifier name */

/* LCD_LP (coord L8), J16[32]/P2_16-LCD_LP */
#define BOARD_INITLCDPINS_LCD_LP_PERIPHERAL                                  LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_LP_SIGNAL                                   LCD_LP   /*!< LCD signal: LCD_LP */
#define BOARD_INITLCDPINS_LCD_LP_PIN_NAME                                 LCD_LP   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_LP_LABEL                    "J16[32]/P2_16-LCD_LP"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_LP_NAME                                   "LCD_LP"   /*!< Identifier name */

/* LCD_AC (coord M8), J16[34]/P2_15-LCD_AC_ENAB_M */
#define BOARD_INITLCDPINS_LCD_AC_ENAB_M_PERIPHERAL                           LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_AC_ENAB_M_SIGNAL                            LCD_AC   /*!< LCD signal: LCD_AC */
#define BOARD_INITLCDPINS_LCD_AC_ENAB_M_PIN_NAME                          LCD_AC   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_AC_ENAB_M_LABEL      "J16[34]/P2_15-LCD_AC_ENAB_M"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_AC_ENAB_M_NAME                     "LCD_AC_ENAB_M"   /*!< Identifier name */

/* LCD_VD(4) (coord K10), J16[9]/P2_22-LCD_VD4 */
#define BOARD_INITLCDPINS_LCD_VD4_PERIPHERAL                                 LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD4_SIGNAL                                  LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD4_CHANNEL                                      4   /*!< LCD LCD_VD channel: 4 */
#define BOARD_INITLCDPINS_LCD_VD4_PIN_NAME                             LCD_VD(4)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD4_LABEL                   "J16[9]/P2_22-LCD_VD4"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD4_NAME                                 "LCD_VD4"   /*!< Identifier name */

/* LCD_VD(3) (coord L10), J16[8]/P2_21-LCD_VD3 */
#define BOARD_INITLCDPINS_LCD_VD3_PERIPHERAL                                 LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD3_SIGNAL                                  LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD3_CHANNEL                                      3   /*!< LCD LCD_VD channel: 3 */
#define BOARD_INITLCDPINS_LCD_VD3_PIN_NAME                             LCD_VD(3)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD3_LABEL                   "J16[8]/P2_21-LCD_VD3"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD3_NAME                                 "LCD_VD3"   /*!< Identifier name */

/* LCD_VD(11) (coord G11), J16[16]/P2_29-LCD_VD11 */
#define BOARD_INITLCDPINS_LCD_VD11_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD11_SIGNAL                                 LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD11_CHANNEL                                    11   /*!< LCD LCD_VD channel: 11 */
#define BOARD_INITLCDPINS_LCD_VD11_PIN_NAME                           LCD_VD(11)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD11_LABEL                "J16[16]/P2_29-LCD_VD11"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD11_NAME                               "LCD_VD11"   /*!< Identifier name */

/* LCD_VD(7) (coord J11), J16[12]/P2_25-LCD_VD7 */
#define BOARD_INITLCDPINS_LCD_VD7_PERIPHERAL                                 LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD7_SIGNAL                                  LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD7_CHANNEL                                      7   /*!< LCD LCD_VD channel: 7 */
#define BOARD_INITLCDPINS_LCD_VD7_PIN_NAME                             LCD_VD(7)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD7_LABEL                  "J16[12]/P2_25-LCD_VD7"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD7_NAME                                 "LCD_VD7"   /*!< Identifier name */

/* LCD_VD(12) (coord F12), J16[17]/P2_30-LCD_VD12 */
#define BOARD_INITLCDPINS_LCD_VD12_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD12_SIGNAL                                 LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD12_CHANNEL                                    12   /*!< LCD LCD_VD channel: 12 */
#define BOARD_INITLCDPINS_LCD_VD12_PIN_NAME                           LCD_VD(12)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD12_LABEL                "J16[17]/P2_30-LCD_VD12"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD12_NAME                               "LCD_VD12"   /*!< Identifier name */

/* LCD_VD(10) (coord G13), J16[15]/P2_28-LCD_VD10 */
#define BOARD_INITLCDPINS_LCD_VD10_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD10_SIGNAL                                 LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD10_CHANNEL                                    10   /*!< LCD LCD_VD channel: 10 */
#define BOARD_INITLCDPINS_LCD_VD10_PIN_NAME                           LCD_VD(10)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD10_LABEL                "J16[15]/P2_28-LCD_VD10"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD10_NAME                               "LCD_VD10"   /*!< Identifier name */

/* LCD_VD(13) (coord D14), J16[18]/P2_31-LCD_VD13 */
#define BOARD_INITLCDPINS_LCD_VD13_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD13_SIGNAL                                 LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD13_CHANNEL                                    13   /*!< LCD LCD_VD channel: 13 */
#define BOARD_INITLCDPINS_LCD_VD13_PIN_NAME                           LCD_VD(13)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD13_LABEL                "J16[18]/P2_31-LCD_VD13"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD13_NAME                               "LCD_VD13"   /*!< Identifier name */

/* LCD_VD(6) (coord K14), J16[11]/P2_24-LCD_VD6 */
#define BOARD_INITLCDPINS_LCD_VD6_PERIPHERAL                                 LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD6_SIGNAL                                  LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD6_CHANNEL                                      6   /*!< LCD LCD_VD channel: 6 */
#define BOARD_INITLCDPINS_LCD_VD6_PIN_NAME                             LCD_VD(6)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD6_LABEL                  "J16[11]/P2_24-LCD_VD6"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD6_NAME                                 "LCD_VD6"   /*!< Identifier name */

/* LCD_VD(5) (coord M14), J16[10]/P2_23-LCD_VD5 */
#define BOARD_INITLCDPINS_LCD_VD5_PERIPHERAL                                 LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD5_SIGNAL                                  LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD5_CHANNEL                                      5   /*!< LCD LCD_VD channel: 5 */
#define BOARD_INITLCDPINS_LCD_VD5_PIN_NAME                             LCD_VD(5)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD5_LABEL                  "J16[10]/P2_23-LCD_VD5"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD5_NAME                                 "LCD_VD5"   /*!< Identifier name */

/* LCD_VD(14) (coord D12), J16[19]/JS36[1]/P3_0-LCD_VD14 */
#define BOARD_INITLCDPINS_LCD_VD14_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD14_SIGNAL                                 LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD14_CHANNEL                                    14   /*!< LCD LCD_VD channel: 14 */
#define BOARD_INITLCDPINS_LCD_VD14_PIN_NAME                           LCD_VD(14)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD14_LABEL         "J16[19]/JS36[1]/P3_0-LCD_VD14"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD14_NAME                               "LCD_VD14"   /*!< Identifier name */

/* LCD_VD(15) (coord D11), J16[20]/JS33[1]/P3_1-LCD_VD15 */
#define BOARD_INITLCDPINS_LCD_VD15_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD15_SIGNAL                                 LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD15_CHANNEL                                    15   /*!< LCD LCD_VD channel: 15 */
#define BOARD_INITLCDPINS_LCD_VD15_PIN_NAME                           LCD_VD(15)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD15_LABEL         "J16[20]/JS33[1]/P3_1-LCD_VD15"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD15_NAME                               "LCD_VD15"   /*!< Identifier name */

/* LCD_VD(19) (coord B10), J16[24]/P3_5-LCD_VD19 */
#define BOARD_INITLCDPINS_LCD_VD19_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD19_SIGNAL                                 LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD19_CHANNEL                                    19   /*!< LCD LCD_VD channel: 19 */
#define BOARD_INITLCDPINS_LCD_VD19_PIN_NAME                           LCD_VD(19)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD19_LABEL                 "J16[24]/P3_5-LCD_VD19"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD19_NAME                               "LCD_VD19"   /*!< Identifier name */

/* LCD_VD(20) (coord C9), J16[25]/P3_6-LCD_VD20 */
#define BOARD_INITLCDPINS_LCD_VD20_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD20_SIGNAL                                 LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD20_CHANNEL                                    20   /*!< LCD LCD_VD channel: 20 */
#define BOARD_INITLCDPINS_LCD_VD20_PIN_NAME                           LCD_VD(20)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD20_LABEL                 "J16[25]/P3_6-LCD_VD20"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD20_NAME                               "LCD_VD20"   /*!< Identifier name */

/* LCD_VD(21) (coord B8), J16[26]/P3_7-LCD_VD21 */
#define BOARD_INITLCDPINS_LCD_VD21_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD21_SIGNAL                                 LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD21_CHANNEL                                    21   /*!< LCD LCD_VD channel: 21 */
#define BOARD_INITLCDPINS_LCD_VD21_PIN_NAME                           LCD_VD(21)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD21_LABEL                 "J16[26]/P3_7-LCD_VD21"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD21_NAME                               "LCD_VD21"   /*!< Identifier name */

/* LCD_VD(22) (coord A7), J16[27]/P3_8-LCD_VD22 */
#define BOARD_INITLCDPINS_LCD_VD22_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD22_SIGNAL                                 LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD22_CHANNEL                                    22   /*!< LCD LCD_VD channel: 22 */
#define BOARD_INITLCDPINS_LCD_VD22_PIN_NAME                           LCD_VD(22)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD22_LABEL                 "J16[27]/P3_8-LCD_VD22"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD22_NAME                               "LCD_VD22"   /*!< Identifier name */

/* LCD_VD(23) (coord C7), J16[28]/P3_9-LCD_VD23 */
#define BOARD_INITLCDPINS_LCD_VD23_PERIPHERAL                                LCD   /*!< Device name: LCD */
#define BOARD_INITLCDPINS_LCD_VD23_SIGNAL                                 LCD_VD   /*!< LCD signal: LCD_VD */
#define BOARD_INITLCDPINS_LCD_VD23_CHANNEL                                    23   /*!< LCD LCD_VD channel: 23 */
#define BOARD_INITLCDPINS_LCD_VD23_PIN_NAME                           LCD_VD(23)   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_VD23_LABEL                 "J16[28]/P3_9-LCD_VD23"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_VD23_NAME                               "LCD_VD23"   /*!< Identifier name */

/* PIO3_3 (coord A13), J9[8]/LED2/P3_3-USR_LED2 */
#define BOARD_INITLCDPINS_LED2_GPIO                                         GPIO   /*!< GPIO device name: GPIO */
#define BOARD_INITLCDPINS_LED2_PORT                                           3U   /*!< PORT device index: 3 */
#define BOARD_INITLCDPINS_LED2_GPIO_PIN                                       3U   /*!< PIO3 pin index: 3 */
#define BOARD_INITLCDPINS_LED2_PIN_NAME                                   PIO3_3   /*!< Pin name */
#define BOARD_INITLCDPINS_LED2_LABEL                  "J9[8]/LED2/P3_3-USR_LED2"   /*!< Label */
#define BOARD_INITLCDPINS_LED2_NAME                                       "LED2"   /*!< Identifier name */

/* PIO2_11 (coord K3), J16[31]/P2_11-LCD_PWR */
#define BOARD_INITLCDPINS_LCD_PWR_GPIO                                      GPIO   /*!< GPIO device name: GPIO */
#define BOARD_INITLCDPINS_LCD_PWR_PORT                                        2U   /*!< PORT device index: 2 */
#define BOARD_INITLCDPINS_LCD_PWR_GPIO_PIN                                   11U   /*!< PIO2 pin index: 11 */
#define BOARD_INITLCDPINS_LCD_PWR_PIN_NAME                               PIO2_11   /*!< Pin name */
#define BOARD_INITLCDPINS_LCD_PWR_LABEL                  "J16[31]/P2_11-LCD_PWR"   /*!< Label */
#define BOARD_INITLCDPINS_LCD_PWR_NAME                                 "LCD_PWR"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLCDPins(void); /* Function assigned for the Cortex-M4F */

/* PDM1_CLK (coord L14), J13[18]/JS25[3]/DMIC1[4]/P1_2-PDM1_CLK */
#define BOARD_INITAUDIOPINS_PDM1_CLK_PERIPHERAL                            DMIC0   /*!< Device name: DMIC0 */
#define BOARD_INITAUDIOPINS_PDM1_CLK_SIGNAL                                  CLK   /*!< DMIC0 signal: CLK */
#define BOARD_INITAUDIOPINS_PDM1_CLK_CHANNEL                                   1   /*!< DMIC0 CLK channel: 1 */
#define BOARD_INITAUDIOPINS_PDM1_CLK_PIN_NAME                           PDM1_CLK   /*!< Pin name */
#define BOARD_INITAUDIOPINS_PDM1_CLK_LABEL "J13[18]/JS25[3]/DMIC1[4]/P1_2-PDM1_CLK" /*!< Label */
#define BOARD_INITAUDIOPINS_PDM1_CLK_NAME                             "PDM1_CLK"   /*!< Identifier name */

/* PDM1_DATA (coord J13), JS26[3]/DMIC1[1]/P1_3-PDM1_DATA */
#define BOARD_INITAUDIOPINS_PDM1_DATA_PERIPHERAL                           DMIC0   /*!< Device name: DMIC0 */
#define BOARD_INITAUDIOPINS_PDM1_DATA_SIGNAL                                DATA   /*!< DMIC0 signal: DATA */
#define BOARD_INITAUDIOPINS_PDM1_DATA_CHANNEL                                  1   /*!< DMIC0 DATA channel: 1 */
#define BOARD_INITAUDIOPINS_PDM1_DATA_PIN_NAME                         PDM1_DATA   /*!< Pin name */
#define BOARD_INITAUDIOPINS_PDM1_DATA_LABEL    "JS26[3]/DMIC1[1]/P1_3-PDM1_DATA"   /*!< Label */
#define BOARD_INITAUDIOPINS_PDM1_DATA_NAME                           "PDM1_DATA"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitAudioPins(void); /* Function assigned for the Cortex-M4F */

/* SCT0_GPI0 (coord D6), U26[13]/J14[4]/P0_0-ISP_FC3_SCK */
#define BOARD_INITIRDAPINS_ISP_FC3_SCK_PERIPHERAL                           SCT0   /*!< Device name: SCT0 */
#define BOARD_INITIRDAPINS_ISP_FC3_SCK_SIGNAL                                 IN   /*!< SCT0 signal: IN */
#define BOARD_INITIRDAPINS_ISP_FC3_SCK_CHANNEL                                 0   /*!< SCT0 IN channel: 0 */
#define BOARD_INITIRDAPINS_ISP_FC3_SCK_PIN_NAME                        SCT0_GPI0   /*!< Pin name */
#define BOARD_INITIRDAPINS_ISP_FC3_SCK_LABEL   "U26[13]/J14[4]/P0_0-ISP_FC3_SCK"   /*!< Label */
#define BOARD_INITIRDAPINS_ISP_FC3_SCK_NAME                        "ISP_FC3_SCK"   /*!< Identifier name */

/* FC0_RXD_SDA_MOSI (coord B13), U24[13]/P0_29-ISP_FC0_RXD */
#define BOARD_INITIRDAPINS_ISP_FC0_RXD_PERIPHERAL                      FLEXCOMM0   /*!< Device name: FLEXCOMM0 */
#define BOARD_INITIRDAPINS_ISP_FC0_RXD_SIGNAL                       RXD_SDA_MOSI   /*!< FLEXCOMM0 signal: RXD_SDA_MOSI */
#define BOARD_INITIRDAPINS_ISP_FC0_RXD_PIN_NAME                 FC0_RXD_SDA_MOSI   /*!< Pin name */
#define BOARD_INITIRDAPINS_ISP_FC0_RXD_LABEL         "U24[13]/P0_29-ISP_FC0_RXD"   /*!< Label */
#define BOARD_INITIRDAPINS_ISP_FC0_RXD_NAME                        "ISP_FC0_RXD"   /*!< Identifier name */

/* FC0_TXD_SCL_MISO (coord A2), U24[12]/P0_30-ISP_FC0_TXD */
#define BOARD_INITIRDAPINS_ISP_FC0_TXD_PERIPHERAL                      FLEXCOMM0   /*!< Device name: FLEXCOMM0 */
#define BOARD_INITIRDAPINS_ISP_FC0_TXD_SIGNAL                       TXD_SCL_MISO   /*!< FLEXCOMM0 signal: TXD_SCL_MISO */
#define BOARD_INITIRDAPINS_ISP_FC0_TXD_PIN_NAME                 FC0_TXD_SCL_MISO   /*!< Pin name */
#define BOARD_INITIRDAPINS_ISP_FC0_TXD_LABEL         "U24[12]/P0_30-ISP_FC0_TXD"   /*!< Label */
#define BOARD_INITIRDAPINS_ISP_FC0_TXD_NAME                        "ISP_FC0_TXD"   /*!< Identifier name */

/* PIO2_26 (coord H11), U12[15]/P2_26-ENET_PHY_RSTn */
#define BOARD_INITIRDAPINS_ENET_PHY_RSTn_GPIO                               GPIO   /*!< GPIO device name: GPIO */
#define BOARD_INITIRDAPINS_ENET_PHY_RSTn_PORT                                 2U   /*!< PORT device index: 2 */
#define BOARD_INITIRDAPINS_ENET_PHY_RSTn_GPIO_PIN                            26U   /*!< PIO2 pin index: 26 */
#define BOARD_INITIRDAPINS_ENET_PHY_RSTn_PIN_NAME                        PIO2_26   /*!< Pin name */
#define BOARD_INITIRDAPINS_ENET_PHY_RSTn_LABEL     "U12[15]/P2_26-ENET_PHY_RSTn"   /*!< Label */
#define BOARD_INITIRDAPINS_ENET_PHY_RSTn_NAME                    "ENET_PHY_RSTn"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitIrDAPins(void); /* Function assigned for the Cortex-M4F */

/* PIO0_22 (coord B12), U3[4]/J3[1]/P0_22-USB0_VBUS */
#define BOARD_INITKEYBOARDPINS_USB0_VBUS_GPIO                               GPIO   /*!< GPIO device name: GPIO */
#define BOARD_INITKEYBOARDPINS_USB0_VBUS_PORT                                 0U   /*!< PORT device index: 0 */
#define BOARD_INITKEYBOARDPINS_USB0_VBUS_GPIO_PIN                            22U   /*!< PIO0 pin index: 22 */
#define BOARD_INITKEYBOARDPINS_USB0_VBUS_PIN_NAME                        PIO0_22   /*!< Pin name */
#define BOARD_INITKEYBOARDPINS_USB0_VBUS_LABEL     "U3[4]/J3[1]/P0_22-USB0_VBUS"   /*!< Label */
#define BOARD_INITKEYBOARDPINS_USB0_VBUS_NAME                        "USB0_VBUS"   /*!< Identifier name */

/* PIO3_11 (coord B2), J11[8]/J12[7]/P3_11-MCLK-PMOD2_GPIO */
#define BOARD_INITKEYBOARDPINS_MCLK_GPIO                                    GPIO   /*!< GPIO device name: GPIO */
#define BOARD_INITKEYBOARDPINS_MCLK_PORT                                      3U   /*!< PORT device index: 3 */
#define BOARD_INITKEYBOARDPINS_MCLK_GPIO_PIN                                 11U   /*!< PIO3 pin index: 11 */
#define BOARD_INITKEYBOARDPINS_MCLK_PIN_NAME                             PIO3_11   /*!< Pin name */
#define BOARD_INITKEYBOARDPINS_MCLK_LABEL  "J11[8]/J12[7]/P3_11-MCLK-PMOD2_GPIO"   /*!< Label */
#define BOARD_INITKEYBOARDPINS_MCLK_NAME                                  "MCLK"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitKeyboardPins(void); /* Function assigned for the Cortex-M4F */

/* FC6_RXD_SDA_MOSI_DATA (coord F14), U10[32]/J9[10]/P4_2-FC6_I2S_TX_DATA */
#define BOARD_INITCHARGEPINS_FC6_I2S_TX_DATA_PERIPHERAL                FLEXCOMM6   /*!< Device name: FLEXCOMM6 */
#define BOARD_INITCHARGEPINS_FC6_I2S_TX_DATA_SIGNAL            RXD_SDA_MOSI_DATA   /*!< FLEXCOMM6 signal: RXD_SDA_MOSI_DATA */
#define BOARD_INITCHARGEPINS_FC6_I2S_TX_DATA_PIN_NAME      FC6_RXD_SDA_MOSI_DATA   /*!< Pin name */
#define BOARD_INITCHARGEPINS_FC6_I2S_TX_DATA_LABEL "U10[32]/J9[10]/P4_2-FC6_I2S_TX_DATA" /*!< Label */
#define BOARD_INITCHARGEPINS_FC6_I2S_TX_DATA_NAME              "FC6_I2S_TX_DATA"   /*!< Identifier name */

/* FC6_TXD_SCL_MISO_WS (coord F13), U10[30]/J9[12]/P4_3-FC6_I2S_TX_WS */
#define BOARD_INITCHARGEPINS_FC6_I2S_TX_WS_PERIPHERAL                  FLEXCOMM6   /*!< Device name: FLEXCOMM6 */
#define BOARD_INITCHARGEPINS_FC6_I2S_TX_WS_SIGNAL                TXD_SCL_MISO_WS   /*!< FLEXCOMM6 signal: TXD_SCL_MISO_WS */
#define BOARD_INITCHARGEPINS_FC6_I2S_TX_WS_PIN_NAME          FC6_TXD_SCL_MISO_WS   /*!< Pin name */
#define BOARD_INITCHARGEPINS_FC6_I2S_TX_WS_LABEL "U10[30]/J9[12]/P4_3-FC6_I2S_TX_WS" /*!< Label */
#define BOARD_INITCHARGEPINS_FC6_I2S_TX_WS_NAME                  "FC6_I2S_TX_WS"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitChargePins(void); /* Function assigned for the Cortex-M4F */

/* PIO0_17 (coord E14), U12[18]/P0_17-ENET_TXD1 */
#define BOARD_INITWIFIPINS_ENET_TXD1_GPIO                                   GPIO   /*!< GPIO device name: GPIO */
#define BOARD_INITWIFIPINS_ENET_TXD1_PORT                                     0U   /*!< PORT device index: 0 */
#define BOARD_INITWIFIPINS_ENET_TXD1_GPIO_PIN                                17U   /*!< PIO0 pin index: 17 */
#define BOARD_INITWIFIPINS_ENET_TXD1_PIN_NAME                            PIO0_17   /*!< Pin name */
#define BOARD_INITWIFIPINS_ENET_TXD1_LABEL             "U12[18]/P0_17-ENET_TXD1"   /*!< Label */
#define BOARD_INITWIFIPINS_ENET_TXD1_NAME                            "ENET_TXD1"   /*!< Identifier name */

/* PIO0_29 (coord B13), U24[13]/P0_29-ISP_FC0_RXD */
#define BOARD_INITWIFIPINS_ISP_FC0_RXD_GPIO                                 GPIO   /*!< GPIO device name: GPIO */
#define BOARD_INITWIFIPINS_ISP_FC0_RXD_PORT                                   0U   /*!< PORT device index: 0 */
#define BOARD_INITWIFIPINS_ISP_FC0_RXD_GPIO_PIN                              29U   /*!< PIO0 pin index: 29 */
#define BOARD_INITWIFIPINS_ISP_FC0_RXD_PIN_NAME                          PIO0_29   /*!< Pin name */
#define BOARD_INITWIFIPINS_ISP_FC0_RXD_LABEL         "U24[13]/P0_29-ISP_FC0_RXD"   /*!< Label */
#define BOARD_INITWIFIPINS_ISP_FC0_RXD_NAME                        "ISP_FC0_RXD"   /*!< Identifier name */

/* PIO0_30 (coord A2), U24[12]/P0_30-ISP_FC0_TXD */
#define BOARD_INITWIFIPINS_ISP_FC0_TXD_GPIO                                 GPIO   /*!< GPIO device name: GPIO */
#define BOARD_INITWIFIPINS_ISP_FC0_TXD_PORT                                   0U   /*!< PORT device index: 0 */
#define BOARD_INITWIFIPINS_ISP_FC0_TXD_GPIO_PIN                              30U   /*!< PIO0 pin index: 30 */
#define BOARD_INITWIFIPINS_ISP_FC0_TXD_PIN_NAME                          PIO0_30   /*!< Pin name */
#define BOARD_INITWIFIPINS_ISP_FC0_TXD_LABEL         "U24[12]/P0_30-ISP_FC0_TXD"   /*!< Label */
#define BOARD_INITWIFIPINS_ISP_FC0_TXD_NAME                        "ISP_FC0_TXD"   /*!< Identifier name */

/* FC3_RXD_SDA_MOSI (coord K12), J12[12]/U29[4]/SW5/P1_1-USER_PB-USB1_OVRCURn */
#define BOARD_INITWIFIPINS_SW5_PERIPHERAL                              FLEXCOMM3   /*!< Device name: FLEXCOMM3 */
#define BOARD_INITWIFIPINS_SW5_SIGNAL                               RXD_SDA_MOSI   /*!< FLEXCOMM3 signal: RXD_SDA_MOSI */
#define BOARD_INITWIFIPINS_SW5_PIN_NAME                         FC3_RXD_SDA_MOSI   /*!< Pin name */
#define BOARD_INITWIFIPINS_SW5_LABEL "J12[12]/U29[4]/SW5/P1_1-USER_PB-USB1_OVRCURn" /*!< Label */
#define BOARD_INITWIFIPINS_SW5_NAME                                        "SW5"   /*!< Identifier name */

/* FC3_SSEL3 (coord N14), U28[G1]/P1_24-EMC_A12 */
#define BOARD_INITWIFIPINS_EMC_A12_PERIPHERAL                          FLEXCOMM3   /*!< Device name: FLEXCOMM3 */
#define BOARD_INITWIFIPINS_EMC_A12_SIGNAL                                  SSEL3   /*!< FLEXCOMM3 signal: SSEL3 */
#define BOARD_INITWIFIPINS_EMC_A12_PIN_NAME                            FC3_SSEL3   /*!< Pin name */
#define BOARD_INITWIFIPINS_EMC_A12_LABEL                 "U28[G1]/P1_24-EMC_A12"   /*!< Label */
#define BOARD_INITWIFIPINS_EMC_A12_NAME                                "EMC_A12"   /*!< Identifier name */

/* FC3_TXD_SCL_MISO (coord P12), U10[31]/J9[20]/P2_19-FC7_I2S_RX_DAT */
#define BOARD_INITWIFIPINS_FC7_I2S_RX_DAT_PERIPHERAL                   FLEXCOMM3   /*!< Device name: FLEXCOMM3 */
#define BOARD_INITWIFIPINS_FC7_I2S_RX_DAT_SIGNAL                    TXD_SCL_MISO   /*!< FLEXCOMM3 signal: TXD_SCL_MISO */
#define BOARD_INITWIFIPINS_FC7_I2S_RX_DAT_PIN_NAME              FC3_TXD_SCL_MISO   /*!< Pin name */
#define BOARD_INITWIFIPINS_FC7_I2S_RX_DAT_LABEL "U10[31]/J9[20]/P2_19-FC7_I2S_RX_DAT" /*!< Label */
#define BOARD_INITWIFIPINS_FC7_I2S_RX_DAT_NAME                  "FC7_I2S_RX_DAT"   /*!< Identifier name */

/* FC3_SCK (coord H11), U12[15]/P2_26-ENET_PHY_RSTn */
#define BOARD_INITWIFIPINS_ENET_PHY_RSTn_PERIPHERAL                    FLEXCOMM3   /*!< Device name: FLEXCOMM3 */
#define BOARD_INITWIFIPINS_ENET_PHY_RSTn_SIGNAL                              SCK   /*!< FLEXCOMM3 signal: SCK */
#define BOARD_INITWIFIPINS_ENET_PHY_RSTn_PIN_NAME                        FC3_SCK   /*!< Pin name */
#define BOARD_INITWIFIPINS_ENET_PHY_RSTn_LABEL     "U12[15]/P2_26-ENET_PHY_RSTn"   /*!< Label */
#define BOARD_INITWIFIPINS_ENET_PHY_RSTn_NAME                    "ENET_PHY_RSTn"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitWiFiPins(void); /* Function assigned for the Cortex-M4F */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitBlePins(void); /* Function assigned for the Cortex-M4F */

/* FC2_CTS_SDA_SSEL0 (coord C2), J11[10]/J9[3]/U10[3]/J17[5]/U19[10]/P3_23-FC2_SDAX */
#define BOARD_INITTOUCHPANELPINS_FC2_SDAX_PERIPHERAL                   FLEXCOMM2   /*!< Device name: FLEXCOMM2 */
#define BOARD_INITTOUCHPANELPINS_FC2_SDAX_SIGNAL                   CTS_SDA_SSEL0   /*!< FLEXCOMM2 signal: CTS_SDA_SSEL0 */
#define BOARD_INITTOUCHPANELPINS_FC2_SDAX_PIN_NAME             FC2_CTS_SDA_SSEL0   /*!< Pin name */
#define BOARD_INITTOUCHPANELPINS_FC2_SDAX_LABEL "J11[10]/J9[3]/U10[3]/J17[5]/U19[10]/P3_23-FC2_SDAX" /*!< Label */
#define BOARD_INITTOUCHPANELPINS_FC2_SDAX_NAME                        "FC2_SDAX"   /*!< Identifier name */

/* FC2_RTS_SCL_SSEL1 (coord E2), J11[9]/J9[1]/U10[2]/J17[4]/U19[2]/P3_24-FC2_SCLX */
#define BOARD_INITTOUCHPANELPINS_FC2_SCLX_PERIPHERAL                   FLEXCOMM2   /*!< Device name: FLEXCOMM2 */
#define BOARD_INITTOUCHPANELPINS_FC2_SCLX_SIGNAL                   RTS_SCL_SSEL1   /*!< FLEXCOMM2 signal: RTS_SCL_SSEL1 */
#define BOARD_INITTOUCHPANELPINS_FC2_SCLX_PIN_NAME             FC2_RTS_SCL_SSEL1   /*!< Pin name */
#define BOARD_INITTOUCHPANELPINS_FC2_SCLX_LABEL "J11[9]/J9[1]/U10[2]/J17[4]/U19[2]/P3_24-FC2_SCLX" /*!< Label */
#define BOARD_INITTOUCHPANELPINS_FC2_SCLX_NAME                        "FC2_SCLX"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitTouchpanelPins(void); /* Function assigned for the Cortex-M4F */

/* PIO2_2 (coord C3), J9[6]/LED3/P2_2-CT1MAT1-USR_LED3 */
#define BOARD_INITZIGBEEPINS_LED3_GPIO                                      GPIO   /*!< GPIO device name: GPIO */
#define BOARD_INITZIGBEEPINS_LED3_PORT                                        2U   /*!< PORT device index: 2 */
#define BOARD_INITZIGBEEPINS_LED3_GPIO_PIN                                    2U   /*!< PIO2 pin index: 2 */
#define BOARD_INITZIGBEEPINS_LED3_PIN_NAME                                PIO2_2   /*!< Pin name */
#define BOARD_INITZIGBEEPINS_LED3_LABEL       "J9[6]/LED3/P2_2-CT1MAT1-USR_LED3"   /*!< Label */
#define BOARD_INITZIGBEEPINS_LED3_NAME                                    "LED3"   /*!< Identifier name */

/* FC1_RXD_SDA_MOSI (coord B1), U9[3]/P2_3-SD_CLK */
#define BOARD_INITZIGBEEPINS_SD_CLK_PERIPHERAL                         FLEXCOMM1   /*!< Device name: FLEXCOMM1 */
#define BOARD_INITZIGBEEPINS_SD_CLK_SIGNAL                          RXD_SDA_MOSI   /*!< FLEXCOMM1 signal: RXD_SDA_MOSI */
#define BOARD_INITZIGBEEPINS_SD_CLK_PIN_NAME                    FC1_RXD_SDA_MOSI   /*!< Pin name */
#define BOARD_INITZIGBEEPINS_SD_CLK_LABEL                    "U9[3]/P2_3-SD_CLK"   /*!< Label */
#define BOARD_INITZIGBEEPINS_SD_CLK_NAME                                "SD_CLK"   /*!< Identifier name */

/* FC1_TXD_SCL_MISO (coord D3), RP1[6]/U9[2]/P2_4-SD_CMD */
#define BOARD_INITZIGBEEPINS_SD_CMD_PERIPHERAL                         FLEXCOMM1   /*!< Device name: FLEXCOMM1 */
#define BOARD_INITZIGBEEPINS_SD_CMD_SIGNAL                          TXD_SCL_MISO   /*!< FLEXCOMM1 signal: TXD_SCL_MISO */
#define BOARD_INITZIGBEEPINS_SD_CMD_PIN_NAME                    FC1_TXD_SCL_MISO   /*!< Pin name */
#define BOARD_INITZIGBEEPINS_SD_CMD_LABEL             "RP1[6]/U9[2]/P2_4-SD_CMD"   /*!< Label */
#define BOARD_INITZIGBEEPINS_SD_CMD_NAME                                "SD_CMD"   /*!< Identifier name */

/* FC1_CTS_SDA_SSEL0 (coord C1), Q3[1]/P2_5-SD_POW_EN */
#define BOARD_INITZIGBEEPINS_SD_POW_EN_PERIPHERAL                      FLEXCOMM1   /*!< Device name: FLEXCOMM1 */
#define BOARD_INITZIGBEEPINS_SD_POW_EN_SIGNAL                      CTS_SDA_SSEL0   /*!< FLEXCOMM1 signal: CTS_SDA_SSEL0 */
#define BOARD_INITZIGBEEPINS_SD_POW_EN_PIN_NAME                FC1_CTS_SDA_SSEL0   /*!< Pin name */
#define BOARD_INITZIGBEEPINS_SD_POW_EN_LABEL              "Q3[1]/P2_5-SD_POW_EN"   /*!< Label */
#define BOARD_INITZIGBEEPINS_SD_POW_EN_NAME                          "SD_POW_EN"   /*!< Identifier name */

/* FC1_RTS_SCL_SSEL1 (coord F3), RP1[5]/U9[4]/P2_6-SD_D0 */
#define BOARD_INITZIGBEEPINS_SD_D0_PERIPHERAL                          FLEXCOMM1   /*!< Device name: FLEXCOMM1 */
#define BOARD_INITZIGBEEPINS_SD_D0_SIGNAL                          RTS_SCL_SSEL1   /*!< FLEXCOMM1 signal: RTS_SCL_SSEL1 */
#define BOARD_INITZIGBEEPINS_SD_D0_PIN_NAME                    FC1_RTS_SCL_SSEL1   /*!< Pin name */
#define BOARD_INITZIGBEEPINS_SD_D0_LABEL               "RP1[5]/U9[4]/P2_6-SD_D0"   /*!< Label */
#define BOARD_INITZIGBEEPINS_SD_D0_NAME                                  "SD_D0"   /*!< Identifier name */

/* PIO2_10 (coord P1), RP1[2]/U9[7]/P2_10-SD_CDn */
#define BOARD_INITZIGBEEPINS_SD_CDn_GPIO                                    GPIO   /*!< GPIO device name: GPIO */
#define BOARD_INITZIGBEEPINS_SD_CDn_PORT                                      2U   /*!< PORT device index: 2 */
#define BOARD_INITZIGBEEPINS_SD_CDn_GPIO_PIN                                 10U   /*!< PIO2 pin index: 10 */
#define BOARD_INITZIGBEEPINS_SD_CDn_PIN_NAME                             PIO2_10   /*!< Pin name */
#define BOARD_INITZIGBEEPINS_SD_CDn_LABEL            "RP1[2]/U9[7]/P2_10-SD_CDn"   /*!< Label */
#define BOARD_INITZIGBEEPINS_SD_CDn_NAME                                "SD_CDn"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitZigbeePins(void); /* Function assigned for the Cortex-M4F */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
