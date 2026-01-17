//
// Created by i4N on 2025/10/13.
//
/* *Avoid re-definition */
#pragma once
/* No headers, in case reading C++ codes from C */
#ifdef __cplusplus
extern "C"{
#endif
	/* This function is to be called in main.c and cppmain.cpp */
	/* So the linkage must be C */
	void cppmain();

#ifdef __cplusplus
}
#endif

