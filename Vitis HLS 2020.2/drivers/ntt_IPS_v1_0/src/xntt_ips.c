// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xntt_ips.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XNtt_ips_CfgInitialize(XNtt_ips *InstancePtr, XNtt_ips_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XNtt_ips_Start(XNtt_ips *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XNtt_ips_ReadReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_AP_CTRL) & 0x80;
    XNtt_ips_WriteReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XNtt_ips_IsDone(XNtt_ips *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XNtt_ips_ReadReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XNtt_ips_IsIdle(XNtt_ips *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XNtt_ips_ReadReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XNtt_ips_IsReady(XNtt_ips *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XNtt_ips_ReadReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XNtt_ips_EnableAutoRestart(XNtt_ips *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XNtt_ips_WriteReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_AP_CTRL, 0x80);
}

void XNtt_ips_DisableAutoRestart(XNtt_ips *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XNtt_ips_WriteReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_AP_CTRL, 0);
}

void XNtt_ips_Set_cont(XNtt_ips *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XNtt_ips_WriteReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_CONT_DATA, Data);
}

u32 XNtt_ips_Get_cont(XNtt_ips *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XNtt_ips_ReadReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_CONT_DATA);
    return Data;
}

void XNtt_ips_InterruptGlobalEnable(XNtt_ips *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XNtt_ips_WriteReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_GIE, 1);
}

void XNtt_ips_InterruptGlobalDisable(XNtt_ips *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XNtt_ips_WriteReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_GIE, 0);
}

void XNtt_ips_InterruptEnable(XNtt_ips *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XNtt_ips_ReadReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_IER);
    XNtt_ips_WriteReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_IER, Register | Mask);
}

void XNtt_ips_InterruptDisable(XNtt_ips *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XNtt_ips_ReadReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_IER);
    XNtt_ips_WriteReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_IER, Register & (~Mask));
}

void XNtt_ips_InterruptClear(XNtt_ips *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XNtt_ips_WriteReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_ISR, Mask);
}

u32 XNtt_ips_InterruptGetEnabled(XNtt_ips *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XNtt_ips_ReadReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_IER);
}

u32 XNtt_ips_InterruptGetStatus(XNtt_ips *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XNtt_ips_ReadReg(InstancePtr->Ctrl_BaseAddress, XNTT_IPS_CTRL_ADDR_ISR);
}

