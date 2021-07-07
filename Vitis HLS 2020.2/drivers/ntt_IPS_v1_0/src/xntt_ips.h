// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XNTT_IPS_H
#define XNTT_IPS_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xntt_ips_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Ctrl_BaseAddress;
} XNtt_ips_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XNtt_ips;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XNtt_ips_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XNtt_ips_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XNtt_ips_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XNtt_ips_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XNtt_ips_Initialize(XNtt_ips *InstancePtr, u16 DeviceId);
XNtt_ips_Config* XNtt_ips_LookupConfig(u16 DeviceId);
int XNtt_ips_CfgInitialize(XNtt_ips *InstancePtr, XNtt_ips_Config *ConfigPtr);
#else
int XNtt_ips_Initialize(XNtt_ips *InstancePtr, const char* InstanceName);
int XNtt_ips_Release(XNtt_ips *InstancePtr);
#endif

void XNtt_ips_Start(XNtt_ips *InstancePtr);
u32 XNtt_ips_IsDone(XNtt_ips *InstancePtr);
u32 XNtt_ips_IsIdle(XNtt_ips *InstancePtr);
u32 XNtt_ips_IsReady(XNtt_ips *InstancePtr);
void XNtt_ips_EnableAutoRestart(XNtt_ips *InstancePtr);
void XNtt_ips_DisableAutoRestart(XNtt_ips *InstancePtr);

void XNtt_ips_Set_cont(XNtt_ips *InstancePtr, u32 Data);
u32 XNtt_ips_Get_cont(XNtt_ips *InstancePtr);

void XNtt_ips_InterruptGlobalEnable(XNtt_ips *InstancePtr);
void XNtt_ips_InterruptGlobalDisable(XNtt_ips *InstancePtr);
void XNtt_ips_InterruptEnable(XNtt_ips *InstancePtr, u32 Mask);
void XNtt_ips_InterruptDisable(XNtt_ips *InstancePtr, u32 Mask);
void XNtt_ips_InterruptClear(XNtt_ips *InstancePtr, u32 Mask);
u32 XNtt_ips_InterruptGetEnabled(XNtt_ips *InstancePtr);
u32 XNtt_ips_InterruptGetStatus(XNtt_ips *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
