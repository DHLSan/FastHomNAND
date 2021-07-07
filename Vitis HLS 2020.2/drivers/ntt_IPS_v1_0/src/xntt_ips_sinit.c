// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xntt_ips.h"

extern XNtt_ips_Config XNtt_ips_ConfigTable[];

XNtt_ips_Config *XNtt_ips_LookupConfig(u16 DeviceId) {
	XNtt_ips_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XNTT_IPS_NUM_INSTANCES; Index++) {
		if (XNtt_ips_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XNtt_ips_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XNtt_ips_Initialize(XNtt_ips *InstancePtr, u16 DeviceId) {
	XNtt_ips_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XNtt_ips_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XNtt_ips_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

