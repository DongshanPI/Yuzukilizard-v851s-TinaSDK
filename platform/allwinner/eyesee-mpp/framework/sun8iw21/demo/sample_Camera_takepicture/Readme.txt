sample_Camera_takepicture�������̣�


1������˵����
��1��sample֧�ֵ�����ȡRaw��������ȡJPEG��ͬʱԤ����֧�ֻ�ȡJPEG����ȡRAW��ͬʱԤ����
��2����·�ֱ�ʹ�ò�ͬ��VIPP��ʹ������ISP����Ӧ��ϵ���£�
    - ISP0��ISP1�����ӵ�CSI1��
    - VIPP1��VIPP3���ӵ�ISP0��VIPP0��VIPP2���ӵ�ISP1��
��3��VIPPͨ��ʹ���Ƽ�������
    - Raw data is get by ScalerOutChns 0
    - JPEG data is get by ScalerOutChns 1
    - Preview data is  get by ScalerOutChns 3

2��ʹ�÷���
��1���޸� ipc-v5/lichee/tools/pack/chips/sun8iw12p1/configs/����/sys_config.fex �У�
    - sys_config.fex���òο�

        vinc0_used      = 1
        vinc0_csi_sel       = 1
        vinc0_mipi_sel      = 1
        vinc0_isp_sel       = 1
        vinc0_isp_tx_ch     = 0
        vinc0_rear_sensor_sel   = 1
        vinc0_front_sensor_sel  = 1
        vinc0_sensor_list   = 0
        
        [vind0/vinc1]
        vinc1_used      = 1
        vinc1_csi_sel       = 1
        vinc1_mipi_sel      = 1
        vinc1_isp_sel       = 0
        vinc1_isp_tx_ch     = 0
        vinc1_rear_sensor_sel   = 1
        vinc1_front_sensor_sel  = 1
        vinc1_sensor_list   = 0
        
        [vind0/vinc2]
        vinc2_used      = 1
        vinc2_csi_sel       = 1
        vinc2_mipi_sel      = 1
        vinc2_isp_sel       = 1
        vinc2_isp_tx_ch     = 0
        vinc2_rear_sensor_sel   = 1
        vinc2_front_sensor_sel  = 1
        vinc2_sensor_list   = 0
        
        [vind0/vinc3]
        vinc3_used      = 1
        vinc3_csi_sel       = 1
        vinc3_mipi_sel      = 1
        vinc3_isp_sel       = 0
        vinc3_isp_tx_ch     = 0
        vinc3_rear_sensor_sel   = 1
        vinc3_front_sensor_sel  = 1
        vinc3_sensor_list   = 0

��2����ȡ4K(3840*2160) Raw��ʽ�������޸��������ã�ȡ��isp�����еĹ�����ƣ�patch���£�
    - �޸��ļ� ipc-v5/lichee/linux-4.4/drivers/media/platform/sunxi-vin/vin-isp/sunxi_isp.c

        diff --git a/drivers/media/platform/sunxi-vin/vin-isp/sunxi_isp.c b/drivers/media/platform/sunxi-vin/vin-isp/sunxi_isp.c
        index eb3c0e6..b818075 100755
        --- a/drivers/media/platform/sunxi-vin/vin-isp/sunxi_isp.c
        +++ b/drivers/media/platform/sunxi-vin/vin-isp/sunxi_isp.c
        @@ -433,8 +433,8 @@ static struct isp_pix_fmt *__isp_try_format(struct isp_dev *isp,
        
                if (!isp->large_image) {
                        if (isp->id == 1) {
        -                       mf->width = clamp_t(u32, mf->width, MIN_IN_WIDTH, 3264);
        -                       mf->height = clamp_t(u32, mf->height, MIN_IN_HEIGHT, 3264);
        +                       mf->width = clamp_t(u32, mf->width, MIN_IN_WIDTH, 4224);
        +                       mf->height = clamp_t(u32, mf->height, MIN_IN_HEIGHT, 4224);
                        } else {
                                mf->width = clamp_t(u32, mf->width, MIN_IN_WIDTH, 4224);
                                mf->height = clamp_t(u32, mf->height, MIN_IN_HEIGHT, 4224);

