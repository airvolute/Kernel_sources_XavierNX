/*
 * ov9281.c - ov9281 sensor driver
 *
 * Copyright (c) 2016-2017, NVIDIA CORPORATION, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <media/camera_common.h>

#ifndef __OV9281_I2C_TABLES__
#define __OV9281_I2C_TABLES__

#define OV9281_TABLE_WAIT_MS	0
#define OV9281_TABLE_END	1

#define ov9281_reg struct reg_8

enum {	
	OV9281_MODE_1280X800,
	OV9281_MODE_1280X720,	
	OV9281_MODE_640X400,	
	OV9281_START_STREAM,
	OV9281_STOP_STREAM,
};

enum {
	OV9281_FSYNC_NONE,
	OV9281_FSYNC_MASTER,
	OV9281_FSYNC_SLAVE,
	OV9281_FSYNC_SLAVE_TRIGGER,
};

static const ov9281_reg ov9281_start_stream[] = {
	{ 0x0100, 0x01 },
	{ OV9281_TABLE_END, 0x00 }
};

static const ov9281_reg ov9281_stop_stream[] = {
	{ 0x0100, 0x00 },
	{ OV9281_TABLE_END, 0x00 }
};

/*static const ov9281_reg ov9281_fsync_master[] = {
	{ 0x3006, 0x02 }, // fsin pin out 
	{ 0x3823, 0x00 },
	{ OV9281_TABLE_WAIT_MS, 66 },
	{ OV9281_TABLE_END, 0x00 }
};*/
static const u16 fps_lookup_table[] = {
	28609,
	28609,
	28609,
	28609,
	28609,
	28609,
	23837,
	20429,
	17874,
	15886,
	14285,
	12996,
	11912,
	10995,
	10209,
	9528,
	8932,
	8406,
	7939,
	7521,
	7144,
	6804,
	6494,
	6212,
	5953,
	5714,
	5494,
	5291,
	5102,
	4926,
	4761,
	4608,
	4463,
	4328,
	4201,
	4081,
	3967,
	3860,
	3758,
	3662,
	3570,
	3483,
	3400,
	3321,
	3245,
	3173,
	3104,
	3038,
	2975,
	2914,
	2856,
	2800,
	2746,
	2694,
	2644,
	2596,
	2549,
	2505,
	2461,
	2420,
	2379,
	2340,
	2302,
	2266,
	2230,
	2196,
	2163,
	2131,
	2099,
	2069,
	2039,
	2010,
	1982,
	1955,
	1929,
	1903,
	1878,
	1854,
	1830,
	1807,
	1784,
	1762,
	1741,
	1720,
	1699,
	1679,
	1659,
	1640,
	1622,
	1604,
	1586,
	1568,
	1551,
	1534,
	1518,
	1502,
	1486,
	1471,
	1456,
	1441,
	1427,
	1413,
	1399,
	1385,
	1372,
	1359,
	1346,
	1334,
	1321,
	1309,
	1297,
	1285,
	1274,
	1263,
	1252,
	1241,
	1230,
	1219,
	1209,
	1199,
	1189,
	1179,
	1169,
	1160,
	1151,
	1141,
	1132,
	1123,
	1115,
	1106,
	1097,
	1089,
	1081,
	1073,
	1065,
	1057,
	1049,
	1041,
	1034,
	1026,
	1019,
	1012,
	1005,
	998,
	991,
	984,
	977,
	970,
	964,
	957,
	951,
	945,
	938,
	932,
	926,
	920,
	914,
	909,
	903,
	897,
	892,
	886,
	881,
	875,
	870,
	864,
	859,
	854,
	849,
	844,
	839,
	834,
	829,
	824,
	820,
	815,
	810,
	806,
	801,
	797,
	792,
	788,
	784,
	779,
	775,
	771,
	767,
	763,
	759,
	755,
	751,
	747,
	743,
	739,
	735,
	731,
	728,
	724,
	720,
	717,
	713,
	710,
	706,
	703,
	699,
	696,
	692,
	689,
	686,
	682,
	679,
	676,
	673,
	670,
	666,
	663,
	660,
	657,
	654,
	651,
	648,
	645,
	642,
	639,
	637,
	634,
	631,
	628,
	625,
	623,
	620,
	617,
	615,
	612,
	609,
	607,
	604,
	602,
	599,
	597,
	594,
	592,
	589,
	587,
	584,
	582,
	580,
	577,
	575,
	573,
	570,
	568,
	566,
	564,
	561,
	559,
	557,
	555,
	553,
	551,
	548,
	546,
	544,
	542,
	540,
	538,
	536,
	534,
	532,
	530,
	528,
	526,
	524,
	522,
	520
}; 


/*In this mode rising edge on fsin wakes sensor up and streams number of frames*/
static const ov9281_reg ov9281_slave_trigger_mode[] = {
	//{ 0x0100, 0x00 }, // SC_MODE_SELECT, Bit[0] 1:streaming, 0:software_standby (Default: 0x00)
	//{ 0x4F00, 0x01 },//LOW POWER TRIGGER MODE
	//{ 0x3030, 0x04 }, // bit[4] repeating the sequence of streaming, bit[2] rising edge wakes sensor and streams out 0x303F number of frames
	//{ 0x303F, 0x01 }, //number of frames after wake up
	//{ 0x3006, 0x00 }, // fsin pin in 
	//{ 0x3823, 0x30}, // ext_vs_en, r_init_man		
	//{ 0x302C, 0x00}, // SC_LP_CTRL0, r_sleep_period[31:24] (All bits are set by 0x302F - 0x302C) (Default: 0x01)
    //{ 0x302F, 0x7F}, // SC_LP_CTRL4, r_sleep_period[7:0] (Default: 0x10)
	//{ 0x3023, 0x00 }, //MIPI power down enable during sleep period	
	//{ 0x0100, 0x00 },
	//{ 0x0103, 0x01 }, ->mode0  // SC_SOFTWARE_RESET 0x00 = def
    //{ 0xFFFE, 0x64 }, ->mode0
	//{ 0x380c, 0x05 },  // TIMING_HTS  DUPLICITA - pravdepodobne povodca problemu 80fps
	//{ 0x380d, 0x2a },  // TIMING_HTS  DUPLICITA - pravdepodobne povodca problemu 80fps
	//{ 0x5000, 0x87 },   // ISP CTRL 0x9F = default
	//{ 0x4f00, 0x04 },   //PSV_CTRL
	//{ 0x0100, 0x00 },   //stop streaming  
	//{ 0x320c, 0x8f },	//SRAM TEST 0x0F = def
	//{ 0x302c, 0x00 },   //0x01 //302c-302f numb. of lines sleep
	//{ 0x302d, 0x00 },   //0x00
	//{ 0x302e, 0x50 },   //0x00
	//{ 0x302f, 0x00 },   //0x00
	//{ 0x303F, 0x01 },   //number of frames after wake up
	//{ 0x4242, 0x00 },   //FRAME OFF NUM  0x00 = def
	//{ 0x3030, 0x84 },   //rising edge streams out + r_auto_sleep_en

	{ 0x4f00, 0x04 },	
	{ 0x0100, 0x00 },	
	{ 0x320c, 0x8f },	
	{ 0x302c, 0x00 },	
	{ 0x302d, 0x00 },	
	{ 0x302e, 0x50 },	
	{ 0x302f, 0x00 },	
	{ 0x303f, 0x01 },	
	{ 0x4242, 0x00 },	
	{ 0x3030, 0x80 },	
	{ 0x3030, 0x84 },
	{ OV9281_TABLE_WAIT_MS, 66 },
	{ OV9281_TABLE_END, 0x00 }
};

static const ov9281_reg ov9281_mode_1280x800_26MhzMCLK[] = {
    { 0x0103, 0x01 },   // SC_SOFTWARE_RESET 0x00 = def
    { 0xFFFE, 0x64 }, 

	/* PLL control */
	{ 0x0302, 0x32 },
	{ 0x030d, 0x60 },
	{ 0x030e, 0x02 },

	/* system control */
	{ 0x3001, 0x00 },
	{ 0x3004, 0x00 },
	{ 0x3005, 0x00 },
	{ 0x3006, 0x04 },
	{ 0x3011, 0x0a },
	{ 0x3013, 0x18 },
	{ 0x301c, 0xf0 }, //add
	{ 0x3022, 0x01 },
	{ 0x3030, 0x10 },
	{ 0x3039, 0x32 },
	{ 0x303a, 0x00 },

	/* manual AEC/AGC */
	{ 0x3500, 0x00 },
	{ 0x3501, 0x2a },
	{ 0x3502, 0x90 },
	{ 0x3503, 0x08 }, 
	{ 0x3505, 0x8c },
	{ 0x3507, 0x03 },
	{ 0x3508, 0x00 },
	{ 0x3509, 0x10 },

	/* analog control */
	{ 0x3610, 0x80 },
	{ 0x3611, 0xa0 },
	{ 0x3620, 0x6e },
	{ 0x3632, 0x56 },
	{ 0x3633, 0x78 },
	{ 0x3662, 0x07 }, //zmena
	{ 0x3666, 0x00 },
	{ 0x366f, 0x5a },
	{ 0x3680, 0x84 },

	/* sensor control */
	{ 0x3712, 0x80 },
	{ 0x372d, 0x22 },
	{ 0x3731, 0x80 },
	{ 0x3732, 0x30 },
	{ 0x3778, 0x00 },
	{ 0x377d, 0x22 },
	{ 0x3788, 0x02 },
	{ 0x3789, 0xa4 },
	{ 0x378a, 0x00 },
	{ 0x378b, 0x4a },
	{ 0x3799, 0x20 },

	/* timing control */
	{ 0x3800, 0x00 },
	{ 0x3801, 0x00 },
	{ 0x3802, 0x00 },
	{ 0x3803, 0x00 },
	{ 0x3804, 0x05 },
	{ 0x3805, 0x0f },
	{ 0x3806, 0x03 },
	{ 0x3807, 0x2f },
	{ 0x3808, 0x05 },
	{ 0x3809, 0x00 },
	{ 0x380a, 0x03 },
	{ 0x380b, 0x20 },
	{ 0x380c, 0x02 },
	{ 0x380d, 0xd8 },
	{ 0x380e, 0x03 },
	{ 0x380f, 0x8e },
	{ 0x3810, 0x00 },
	{ 0x3811, 0x08 },
	{ 0x3812, 0x00 },
	{ 0x3813, 0x08 },
	{ 0x3814, 0x11 },
	{ 0x3815, 0x11 },
	{ 0x3820, 0x40 },
	{ 0x3821, 0x00 },
	{ 0x382c, 0x05 },	//add
	{ 0x382d, 0xb0 },	//add
	{ 0x389d, 0x00 },   //add
	{ 0x3881, 0x42 },
	{ 0x3882, 0x01 },	//add
	{ 0x3883, 0x00 },	//add
	{ 0x3885, 0x02 },	//add
	{ 0x38a8, 0x02 },
	{ 0x38a9, 0x80 },
	{ 0x38b1, 0x00 },
	{ 0x38b3, 0x02 },	//add
	{ 0x38c4, 0x00 },
	{ 0x38c5, 0xc0 },
	{ 0x38c6, 0x04 },
	{ 0x38c7, 0x80 },

	/* PWM and strobe control */
	{ 0x3920, 0xff },

	/* BLC control */
	{ 0x4003, 0x40 },
	{ 0x4008, 0x04 },
	{ 0x4009, 0x0b },
	{ 0x400c, 0x00 },
	{ 0x400d, 0x07 },
	{ 0x4010, 0x40 },
	{ 0x4043, 0x40 },

	/* format control */
	{ 0x4307, 0x30 },
	{ 0x4317, 0x00 },

	/* ???? */
	{ 0x4501, 0x00 },
	{ 0x4507, 0x00 },
	{ 0x4509, 0x00 },
	{ 0x450a, 0x08 },

	/* VFIFO control */
	{ 0x4601, 0x04 },

	/* DVP control */
	{ 0x470f, 0x00 },

	/* low power mode control */
	{ 0x4f07, 0x00 },

	/* MIPI top control */
	{ 0x4800, 0x00 }, /* bit 5: discontinuous clk */

	/* ISP top control */
	{ 0x5000, 0x9f },
	{ 0x5001, 0x00 },
	{ 0x5e00, 0x00 },

	/* ???? */
	{ 0x5d00, 0x07 },
	{ 0x5d01, 0x00 },
	{ OV9281_TABLE_END, 0x00}
};

/*static const ov9281_reg ov9281_mode_1280x800_26MhzMCLK_fsync_slave[] = {
	{ 0x3826, 0x03 }, // R reset value on fsin.  VTS - 4 
	{ 0x3827, 0x8a },
	{ OV9281_TABLE_END, 0x00 }
};*/

static const ov9281_reg ov9281_mode_1280x720_26MhzMCLK[] = {
	{ 0x0103, 0x01 }, 
    { 0xFFFE, 0x64 }, 
	{ 0x0302, 0x32 },
	{ 0x030d, 0x60 },
	{ 0x030e, 0x02 },
	{ 0x3001, 0x00 },
	{ 0x3004, 0x00 },
	{ 0x3005, 0x00 },
	{ 0x3006, 0x04 },
	{ 0x3011, 0x0a },
	{ 0x3013, 0x18 },
	{ 0x3022, 0x01 },
	{ 0x3030, 0x10 },
	{ 0x3039, 0x32 },
	{ 0x303a, 0x00 },
	{ 0x3500, 0x00 },
	{ 0x3501, 0x2a },
	{ 0x3502, 0x90 },
	{ 0x3503, 0x08 },
	{ 0x3505, 0x8c },
	{ 0x3507, 0x03 },
	{ 0x3508, 0x00 },
	{ 0x3509, 0x10 },
	{ 0x3610, 0x80 },
	{ 0x3611, 0xa0 },
	{ 0x3620, 0x6e },
	{ 0x3632, 0x56 },
	{ 0x3633, 0x78 },
	{ 0x3662, 0x07 },
	{ 0x3666, 0x00 },
	{ 0x366f, 0x5a },
	{ 0x3680, 0x84 },
	{ 0x3712, 0x80 },
	{ 0x372d, 0x22 },
	{ 0x3731, 0x80 },
	{ 0x3732, 0x30 },
	{ 0x3778, 0x00 },
	{ 0x377d, 0x22 },
	{ 0x3788, 0x02 },
	{ 0x3789, 0xa4 },
	{ 0x378a, 0x00 },
	{ 0x378b, 0x4a },
	{ 0x3799, 0x20 },
	{ 0x3800, 0x00 },
	{ 0x3801, 0x00 },
	{ 0x3802, 0x00 },
	{ 0x3803, 0x28 },
	{ 0x3804, 0x05 },
	{ 0x3805, 0x0f },
	{ 0x3806, 0x03 },
	{ 0x3807, 0x07 },
	{ 0x3808, 0x05 },
	{ 0x3809, 0x00 },
	{ 0x380a, 0x02 },
	{ 0x380b, 0xd0 },
	{ 0x380c, 0x02 },
	{ 0x380d, 0xd8 },
	{ 0x380e, 0x03 },
	{ 0x380f, 0x8e },
	{ 0x3810, 0x00 },
	{ 0x3811, 0x08 },
	{ 0x3812, 0x00 },
	{ 0x3813, 0x08 },
	{ 0x3814, 0x11 },
	{ 0x3815, 0x11 },
	{ 0x3820, 0x40 },
	{ 0x3821, 0x00 },
	{ 0x3881, 0x42 },
	{ 0x38a8, 0x02 },
	{ 0x38a9, 0x80 },
	{ 0x38b1, 0x00 },
	{ 0x38c4, 0x00 },
	{ 0x38c5, 0xc0 },
	{ 0x38c6, 0x04 },
	{ 0x38c7, 0x80 },
	{ 0x3920, 0xff },
	{ 0x4003, 0x40 },
	{ 0x4008, 0x04 },
	{ 0x4009, 0x0b },
	{ 0x400c, 0x00 },
	{ 0x400d, 0x07 },
	{ 0x4010, 0x40 },
	{ 0x4043, 0x40 },
	{ 0x4307, 0x30 },
	{ 0x4317, 0x00 },
	{ 0x4501, 0x00 },
	{ 0x4507, 0x00 },
	{ 0x4509, 0x00 },
	{ 0x450a, 0x08 },
	{ 0x4601, 0x04 },
	{ 0x470f, 0x00 },
	{ 0x4f07, 0x00 },
	{ 0x4800, 0x00 },
	{ 0x5000, 0x9f },
	{ 0x5001, 0x00 },
	{ 0x5e00, 0x00 },
	{ 0x5d00, 0x07 },
	{ 0x5d01, 0x00 },
	{ OV9281_TABLE_END, 0x00}
};

static const ov9281_reg ov9281_mode_640x400_26MhzMCLK[] = {
	{ 0x0103, 0x01 },   
    { 0xFFFE, 0x64 }, 
	{ 0x0302, 0x32 },
	{ 0x030d, 0x60 },
	{ 0x030e, 0x02 },
	{ 0x3001, 0x00 },
	{ 0x3004, 0x00 },
	{ 0x3005, 0x00 },
	{ 0x3006, 0x04 },
	{ 0x3011, 0x0a },
	{ 0x3013, 0x18 },
	{ 0x3022, 0x01 },
	{ 0x3030, 0x10 },
	{ 0x3039, 0x32 },
	{ 0x303a, 0x00 },
	{ 0x3500, 0x00 },
	{ 0x3501, 0x18 },
	{ 0x3502, 0x2d },
	{ 0x3503, 0x08 },
	{ 0x3505, 0x8c },
	{ 0x3507, 0x03 },
	{ 0x3508, 0x00 },
	{ 0x3509, 0x10 },
	{ 0x3610, 0x80 },
	{ 0x3611, 0xa0 },
	{ 0x3620, 0x6e },
	{ 0x3632, 0x56 },
	{ 0x3633, 0x78 },
	{ 0x3662, 0x07 },
	{ 0x3666, 0x00 },
	{ 0x366f, 0x5a },
	{ 0x3680, 0x84 },
	{ 0x3712, 0x80 },
	{ 0x372d, 0x22 },
	{ 0x3731, 0x80 },
	{ 0x3732, 0x30 },
	{ 0x3778, 0x10 },
	{ 0x377d, 0x22 },
	{ 0x3788, 0x02 },
	{ 0x3789, 0xa4 },
	{ 0x378a, 0x00 },
	{ 0x378b, 0x4a },
	{ 0x3799, 0x20 },
	{ 0x3800, 0x00 },
	{ 0x3801, 0x00 },
	{ 0x3802, 0x00 },
	{ 0x3803, 0x00 },
	{ 0x3804, 0x05 },
	{ 0x3805, 0x0f },
	{ 0x3806, 0x03 },
	{ 0x3807, 0x2f },
	{ 0x3808, 0x02 },
	{ 0x3809, 0x80 },
	{ 0x380a, 0x01 },
	{ 0x380b, 0x90 },
	{ 0x380c, 0x02 },
	{ 0x380d, 0xd8 },
	{ 0x380e, 0x02 },
	{ 0x380f, 0x08 },
	{ 0x3810, 0x00 },
	{ 0x3811, 0x04 },
	{ 0x3812, 0x00 },
	{ 0x3813, 0x04 },
	{ 0x3814, 0x31 },
	{ 0x3815, 0x22 },
	{ 0x3820, 0x60 },
	{ 0x3821, 0x01 },
	{ 0x3881, 0x42 },
	{ 0x38a8, 0x02 },
	{ 0x38a9, 0x80 },
	{ 0x38b1, 0x00 },
	{ 0x38c4, 0x00 },
	{ 0x38c5, 0xc0 },
	{ 0x38c6, 0x04 },
	{ 0x38c7, 0x80 },
	{ 0x3920, 0xff },
	{ 0x4003, 0x40 },
	{ 0x4008, 0x02 },
	{ 0x4009, 0x05 },
	{ 0x400c, 0x00 },
	{ 0x400d, 0x03 },
	{ 0x4010, 0x40 },
	{ 0x4043, 0x40 },
	{ 0x4307, 0x30 },
	{ 0x4317, 0x00 },
	{ 0x4501, 0x00 },
	{ 0x4507, 0x03 },
	{ 0x4509, 0x80 },
	{ 0x450a, 0x08 },
	{ 0x4601, 0x04 },
	{ 0x470f, 0x00 },
	{ 0x4f07, 0x00 },
	{ 0x4800, 0x00 },
	{ 0x5000, 0x9f },
	{ 0x5001, 0x00 },
	{ 0x5e00, 0x00 },
	{ 0x5d00, 0x07 },
	{ 0x5d01, 0x00 },
	{ OV9281_TABLE_END, 0x00 }
};

static const ov9281_reg *mode_table[] = {	
	[OV9281_MODE_1280X800] = ov9281_mode_1280x800_26MhzMCLK,
	[OV9281_MODE_1280X720] = ov9281_mode_1280x720_26MhzMCLK,
	[OV9281_MODE_640X400] = ov9281_mode_640x400_26MhzMCLK,	
	[OV9281_START_STREAM] = ov9281_start_stream,
	[OV9281_STOP_STREAM] = ov9281_stop_stream,
};


static const ov9281_reg *ov9281_fsync_table[] = {
	[OV9281_FSYNC_NONE] = NULL,
	[OV9281_FSYNC_MASTER] = NULL, 
	[OV9281_FSYNC_SLAVE] = NULL, 
	[OV9281_FSYNC_SLAVE_TRIGGER] = ov9281_slave_trigger_mode,
};

static const int ov9281_mode0_fps[] = {
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	156,
};

static const int ov9281_mode2_fps[] = {
	20,
	40,
	60,
	80,
	100,
	120,
	140,
	274,	
};

/*
 * WARNING: frmfmt ordering need to match mode definition in
 * device tree!
 */
static const struct camera_common_frmfmt ov9281_frmfmt[] = {
	{ { 1280, 800 }, ov9281_mode0_fps, ARRAY_SIZE(ov9281_mode0_fps), 0, OV9281_MODE_1280X800 },  
	{ { 1280, 720 }, ov9281_mode0_fps, ARRAY_SIZE(ov9281_mode0_fps), 0, OV9281_MODE_1280X720 },
	{ { 640, 400 }, ov9281_mode2_fps, ARRAY_SIZE(ov9281_mode2_fps), 0, OV9281_MODE_640X400 },
};

#endif  /* __OV9281_I2C_TABLES__ */

