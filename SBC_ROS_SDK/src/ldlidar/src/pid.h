/**
* @file         pid.h
* @author       LD Robot
* @version      V01

* @brief         
* @note          
* @attention    COPYRIGHT LDROBOT
**/

#ifndef __PID_H__
#define __PID_H__
#include <stdint.h>
#include <vector>
#include <array>
#include <iostream>
#include "lipkg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	LIDAR_PWM	1

struct PIDObjTyp {
	int32_t kp;
	int32_t ki;
	int32_t kd;
	int64_t ki_plus;
	int32_t outabslimit;
	int32_t remainder;
	int32_t lasterr[2];
	int64_t max_ki_plus;

	PIDObjTyp()
	{
		memset(this, 0, sizeof(PIDObjTyp));
	}

	PIDObjTyp(int32_t kp, int32_t ki, int32_t kd, int32_t ki_plus,
		int32_t outabslimit, int64_t max_ki_plus)
	{
		memset(this, 0, sizeof(PIDObjTyp));

		this->kp = kp;
		this->ki = ki;
		this->kd = kd;
		this->ki_plus = ki_plus;
		this->outabslimit = outabslimit;
		this->max_ki_plus = max_ki_plus;
	}

	void Reset()
	{
		lasterr[0] = 0;
		lasterr[1] = 0;
		ki_plus = 0;
		remainder = 0;
	}

	int32_t PIDRegulatorS32(int32_t aim, int32_t cur, int32_t out)
	{
		int64_t out_value = 0;
		int32_t err = 0, ret = 0;

		err = aim - cur;

		out_value = (int64_t)kp * (int64_t)(err - lasterr[0]);
		out_value += (int64_t)ki * (int64_t)(err);	
		out_value += (int64_t)kd * (int64_t)(err - 2 * lasterr[0] + lasterr[1]);

		lasterr[1] = lasterr[0];
		lasterr[0] = err;

		out_value += remainder;	

		if (out_value < 0)
		{
			ret = (out_value >> 16) + 1 + out;
			remainder = (int32_t)out_value | 0xffff0000;
		}
		else
		{
			ret = (out_value >> 16) + out;
			remainder = (int32_t)out_value & 0x0000ffff;
		}

		
		if (ret > outabslimit)
		{
			return outabslimit;
		}
		else if (ret < -outabslimit) 
		{
			return -outabslimit;
		}
		else
		{
			return ret;
		}
    }
};

#endif
