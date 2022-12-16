#ifndef _EISE_LIB_H_
#define _EISE_LIB_H_

#include "IEGcommon.h"

typedef struct _EISE_CFG_PARA_{
	int       in_h; //����ͼ��߶�,4�ı���
	int       in_w;//����ͼ����,4�ı���
	int       in_luma_pitch;//��������pitch
	int       in_chroma_pitch;//���ɫ��pitch
	int       in_yuv_type;//����yuv����,Ĭ��0
	int       out_h;//����߶�
	int       out_w;//������
	int       out_luma_pitch;//�������pitch
	int       out_chroma_pitch;//���ɫ��pitch
	int       out_yuv_type;//���yuv����
	int       fps;//����֡��
	float     rt; // ISP��ȡSensor���������������ʱ��
	float     ts; // ��Ƶ֡���һ�����һ��֮���ʱ���
	float     td; // ���ڲü��߶���ɵ���ʱ
	float     k_matrix[9]; // ����ڲα궨K����
	float     k_matrix_inv[9]; // ����ڲα궨K���������
	float     stable_anglev[3]; // ������ת�ӹ̶���ת���ٶ�
	float     angle_th[3]; // ����֡����ת����ֵ
	int       radius[3]; // �˲��뾶
	int       xy_exchange_en; // ����������ϵ���������ϵ��XY���Ƿ�Ի�,0:���Ի�;1:�Ի�
	int       rolling_shutter; // rolling shutter˳��,0:���ϵ���;1:���µ���
	int       rs_correction_en;//rolling_shutter ��������
	int       frame_rotation_en;//֡����ת��������
	int       filter_type; // �˲���ʽ,0:��ͨ;1:��ֵ
	int       src_width; // Sensor���ֱ��ʿ��
	int       src_height; // Sensor���ֱ��ʸ߶�
	int       cut_height; // ����ͼ�ü���߶�
	int       hor_off;
	int       ver_off;
	int       fast_mode;
	int       g_en_angle_filter;
	int       g_interlace;
	int       max_frm_buf; // ����ͺ󻺴�֡��  max_frm_buf >= radius[1] + radius[2]
	int       max_next_frm; // �˲������ұ����֡��  max_next_frm = max_frm_buf - radius[1] - radius[2]
	int       old_radius_th0; // Old2New�����õ��˲��뾶��ֵ
	int       old_radius_th1; // Old2Newǰһ֡�뵱ǰ֡���˲��뾶֮����ֵ
	char      reserved[32];
}EISE_CFG_PARA;

typedef struct _EIS_PROCIN_PARA_{
	unsigned int		in_luma_phy_Addr;
	void*				in_luma_mmu_Addr;
	unsigned int		in_chroma_phy_Addr;
	void*				in_chroma_mmu_Addr;
	char				reserved[32];
}EIS_PROCIN_PARA;

typedef struct _EIS_PROCOUT_PARA_{
	unsigned int		out_luma_phy_Addr;
	void*				out_luma_mmu_Addr;
	unsigned int		out_chroma_u_phy_Addr;
	void*				out_chroma_u_mmu_Addr;
	char				reserved[32];
}EIS_PROCOUT_PARA;

typedef struct {
	unsigned long long time;
	float  ax;
	float  ay;
	float  az;
	float  vx;
	float  vy;
	float  vz;
} sGyroData;

typedef struct FrameData_EIS {
	int                fid;//֡ID
	int                gyro_num; // ��ǰ֡�������Ŀ���gyro_data����
	sGyroData          gyro_data[100];//Ŀǰ��൥֡65������
	unsigned long long frame_stamp;//ʱ���
	float              texp; // ��ǰ֡�ĵ������ص��ع�ʱ��
	EIS_PROCIN_PARA    in_addr;//����������BUFFER
	char               reserved[32];
}EISE_FrameData;

// �ӿں���
int EIS_Create(EISE_CFG_PARA *ise_cfg, EISE_HANDLE *handle);

void EIS_SetFrq(int freMHz, EISE_HANDLE *handle);

int EIS_setOutputAddr(EISE_HANDLE *handle, EIS_PROCOUT_PARA *fd);

int EIS_setFrameData(EISE_HANDLE *handle, EISE_FrameData *fd);

int EIS_Proc(EISE_HANDLE *handle, int *proc_id);

int EIS_Destroy(EISE_HANDLE *handle);

int EIS_Reset_Soft(EISE_HANDLE *handle);

int EIS_Set_UnitMatrix_Flag(EISE_HANDLE *handle, int flag);

#endif
