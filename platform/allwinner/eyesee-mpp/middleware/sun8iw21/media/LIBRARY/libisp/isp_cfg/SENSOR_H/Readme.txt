һ����װ������
1.��creat_bin.sh �ű��ŵ�Ŀ¼��softwinner/eyesee-mpp/middleware/sun8iw19p1/media/LIBRARY/libisp/isp_cfg/SENSOR_H
2.�����ִ��Ȩ�ޣ� chmod +x creat_bin.sh

����ʹ�÷���
1. cd softwinner/eyesee-mpp/middleware/sun8iw19p1/media/LIBRARY/libisp/isp_cfg/SENSOR_H
2. ��ȡ������ ./creat_bin.sh -h
3. ת������Ч��ͷ�ļ� ./creat_bin.sh -t sp2305/sp2305_20fps_ini_ipc_day.h 
���ɵ�Ч���ļ���(4��)��
sp2305/sp2305_mipi_day_isp_3a_settings.bin
sp2305/sp2305_mipi_day_isp_iso_settings.bin
sp2305/sp2305_mipi_day_isp_test_settings.bin
sp2305/sp2305_mipi_day_isp_tuning_settings.bin
4.����Ҫ������sp2305 ��ͷ�ļ���ת������ ./creat_bin.sh -t sp2305/
����sp2305Ŀ¼��������ÿ��ͷ�ļ���bin�ļ���

�����޸�Mpp���룬������Щͷ�ļ���
��load_extern_isp.diff ��mppĿ¼�¡�
�����������ISP�����ʱ�򣬼���Ƿ��������ļ���
+#define ISP_TEST_PATH    "/mnt/extsd/isp/isp_test_settings.bin"
+#define ISP_3A_PATH      "/mnt/extsd/isp/isp_3a_settings.bin"
+#define ISP_ISO_PATH     "/mnt/extsd/isp/isp_iso_settings.bin"
+#define ISP_TUNNING_PATH "/mnt/extsd/isp/isp_tuning_settings.bin"

����У����ȡ��������Ŀ¼��ͷ�ļ�����û�У���ʹ��app�ڲ���ͷ�ļ���




�ġ�ת��ԭ��
��ν�ͷ�ļ��Ĳ����ṹ��ת���ɶ��������ݣ�
�ٽ�ͷ�ļ������ c��obj�ļ�����.o�ļ�

��ͨ��readelf -s ��ȡ .o�ļ��ģ��������ʵ���ķ��ű�չʾ������
   Num:    Value  Size Type    Bind   Vis      Ndx Name
    10: 00000000   216 OBJECT  GLOBAL DEFAULT    2 sc2232_mipi_isp_20fps_night_test_settings
    11: 000000d8  5832 OBJECT  GLOBAL DEFAULT    2 sc2232_mipi_isp_20fps_night_3a_settings
    12: 000017a0  8468 OBJECT  GLOBAL DEFAULT    2 sc2232_mipi_isp_20fps_night_iso_settings
    13: 000038b4 0x1ced0 OBJECT  GLOBAL DEFAULT    2 sc2232_mipi_isp_20fps_night_tuning_settings
�Ӵ˴ο�֪�� ȫ�ֱ��� sc2232_mipi_isp_20fps_night_test_settings �ĵ�ַΪ0x00000000  ��СΪ��216

��ͨ��readelf -S ��ȡ .o�ļ��� file's section headers ����֪��.data ����λ���ļ���� ȫ�ֱ����Ǵ洢��.data�ε���������ģ�
 [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
[ 2] .data             PROGBITS        00000000 00004c 020794 00  WA  0   0  4
������֪ .data����ƫ���ļ�0x00004c  λ�á�

��sc2232_mipi_isp_20fps_night_test_settings �ⲿ���������� .o �ļ��� 0x00004c + 0x00000000 ��λ�á� ���СΪ��216����ddȡ�������ɡ�

��ͨ��������������Խ�ʣ���3��ȫ�ֱ����Ķ�������ȫ��ȡ�������档