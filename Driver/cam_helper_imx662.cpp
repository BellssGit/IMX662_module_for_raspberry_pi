/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2021, Raspberry Pi Ltd
 *
 * cam_helper_imx662.cpp - camera helper for imx662 sensor
 */

#include <math.h>

#include "cam_helper.h"

using namespace RPiController;

class CamHelperImx662 : public CamHelper
{
public:
	CamHelperImx662();
	uint32_t gainCode(double gain) const override;
	double gain(uint32_t gainCode) const override;
	void getDelays(int &exposureDelay, int &gainDelay,
		       int &vblankDelay, int &hblankDelay) const override;
	unsigned int hideFramesModeSwitch() const override;

private:
	/*
	 * Smallest difference between the frame length and integration time,
	 * in units of lines.
	 */
	static constexpr int frameIntegrationDiff = 2;
};

CamHelperImx662::CamHelperImx662()
	: CamHelper({}, frameIntegrationDiff)
{
}

uint32_t CamHelperImx662::gainCode(double gain) const
{
	int code = 66.6667 * log10(gain);
	return std::max(0, std::min(code, 0xf0));
}

double CamHelperImx662::gain(uint32_t gainCode) const
{
	return pow(10, 0.015 * gainCode);
}

void CamHelperImx662::getDelays(int &exposureDelay, int &gainDelay,
				int &vblankDelay, int &hblankDelay) const
{
	exposureDelay = 2;
	gainDelay = 2;
	vblankDelay = 2;
	hblankDelay = 2;
}

unsigned int CamHelperImx662::hideFramesModeSwitch() const
{
	/* After a mode switch, we seem to get 1 bad frame. */
	return 1;
}

static CamHelper *create()
{
	return new CamHelperImx662();
}

static RegisterCamHelper reg("imx662", &create);
