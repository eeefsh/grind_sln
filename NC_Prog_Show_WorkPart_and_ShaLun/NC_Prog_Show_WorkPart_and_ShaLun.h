/*
*	******************使用模板的说明*****************
* 
*	1、替换解决方案中所有的 “NC_Prog_Show_WorkPart_and_ShaLun” 为 自定义的项目名
*	2、替换要最终输出的头文件为 自定义的项目名
*	3、本项目最终输出的dll、lib文件已设置成以 项目名 命名
*	4、模板设置了环境变量 xt_import_vc_dir 指向总的库目录（需要按照制定的结构存放库）
*	5、 参照 引用额外的库的说明 引用库
*  
*/

#ifdef NC_Prog_Show_WorkPart_and_ShaLun_EXPORTS
#define NC_Prog_Show_WorkPart_and_ShaLun_API __declspec(dllexport)
#else
#define NC_Prog_Show_WorkPart_and_ShaLun_API __declspec(dllimport)
#endif

/*  ****************** 引用额外的库的说明 ******************
*	
*	1、本项目模板默认包含NC_Prog_Show_WorkPart_and_ShaLun的设置作为实例，如下
*	2、请参照NC_Prog_Show_WorkPart_and_ShaLun_settings.h文件内容和安置路径设置其他库
*	3、可能还需要进行一些手动操作，详情见xt_armadillo_settings.h中说明
*	4、将上一层相关库关联信息代码复制到 生成后事件
*/

//#include "maneger_h/NC_Prog_Show_WorkPart_and_ShaLun_settings.h"
