/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AcrylicorTypedefs.h
Purpose: A list of commonly used typedefs.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/13/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef ACRYLICOR_TYPEDEFS_H
#define ACRYLICOR_TYPEDEFS_H

#define TEST_MODE 0
#define EPSILON 0.0001
#define PASS "PASS"
#define FAIL "!!!!! FAIL !!!!!"
#define PI       3.14159265358979323846f   // pi
#define PI_2     1.57079632679489661923f   // pi/2
#define PI_4     0.785398163397448309616f  // pi/4

const float DEG_TO_RAD = 3.14159265358979323846f / 180.0f;

#include <cstdint>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef uintmax_t uMax;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef intmax_t iMax;

#endif