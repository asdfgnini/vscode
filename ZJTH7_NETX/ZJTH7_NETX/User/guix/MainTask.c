/*
*********************************************************************************************************
*	                                  
*	ģ������ : GUI����������
*	�ļ����� : MainTask.c
*	��    �� : V1.0
*	˵    �� : LCD����
*              
*	�޸ļ�¼ :
*		�汾��   ����         ����          ˵��
*		V1.0    2020-09-13   Eric2013  	    �װ�    
*                                     
*	Copyright (C), 2018-2030, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "MainTask.h"



/*
*********************************************************************************************************
*                                               ����
*********************************************************************************************************
*/
GX_WINDOW 		*pScreen;
GX_WINDOW_ROOT  *root;


/*
*********************************************************************************************************
*	�� �� ��: _cbWindow0
*	����˵��: ���ڻص�����
*	��    ��: widget ���ھ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
VOID _cbWindow0(GX_WINDOW *widget)
{
    GX_RECTANGLE drawto;
    GX_RECTANGLE tempdraw;     
    GX_CANVAS *mycanvas; 
    GX_POINT my_polygon[3] = { { 150, 210 }, { 250, 210 }, { 200, 260 } };
    

    /* Ĭ�ϵĴ��ڻ��ƻص���������Ĭ�Ͻ���Ч������ */
    gx_window_draw(widget);

    /* ����һ�����ο򣬺�����2D���ƺ���������������η�Χ�ڻ��Ƶ� */
    gx_utility_rectangle_define(&drawto,
                                10, 
                                100,
                                400, 
                                265);
 
    /* ���ش��ڶ�Ӧ��canvas���� */
    gx_widget_canvas_get(widget, &mycanvas);
    
    /* 
      ��ָ���Ļ�����������ͼ���˹������ڲ����ӳٻ�ͼ�㷨���ã�GUIX����Ҫ����ʱ�Զ�ִ�и��¡� 
      ��������Ӧ�ó����ƹ����ڻ�ͼ�㷨������ִ�С�
      ���ȵ���gx_canvas_drawing_inititate�ڻ����ϻ滭��
      Ȼ���������Ļ�ͼ���������Ȼ�����gx_canvas_drawing_complete���ɡ�
    */
    gx_canvas_drawing_initiate(mycanvas, widget, &drawto);

    /* ���ñ�ˢ���ߵ���ɫֵ */
    gx_context_raw_line_color_set(0xffff0000);

    /* ���ñ�ˢ������ɫֵ */   
    gx_context_raw_fill_color_set(0xff00ff00);

    /* ͨ��GX_BRUSH_SOLID_FILLʹ��ԲȦ�����Σ�����εȻ���Ϊ���Ч�� */
    gx_context_brush_style_set(GX_BRUSH_SOLID_FILL);

    /* ���ñ�ˢ�߿� */
    gx_context_brush_width_set(1);

    /* ����ֱ�� */
    gx_canvas_line_draw(10, 100, 50, 150);
 
    /* ����ԲȦ */
    gx_canvas_circle_draw(120, 150, 50);

    /* ������Բ */
    gx_canvas_ellipse_draw(300, 150, 100, 50);

    /* ���ƶ���� */
    gx_canvas_polygon_draw(my_polygon, 3); 

    /* ���ƾ��� */
    tempdraw.gx_rectangle_left = 30; 
    tempdraw.gx_rectangle_top = 210; 
    tempdraw.gx_rectangle_right = 100; 
    tempdraw.gx_rectangle_bottom = 260;
    gx_canvas_rectangle_draw(&tempdraw);

    /* ����ǿ���������ƣ�ע�⣬��غ�gx_canvas_drawing_initiate�ɶԵ��� */
    gx_canvas_drawing_complete(mycanvas, GX_TRUE);
}


//UINT _cbEventWindow(GX_WINDOW *widget, GX_EVENT *event_ptr)
//{
//	GX_CHAR *buffer_address;
//	UINT buffer_size;
//	UINT content_size;

//    switch (event_ptr->gx_event_type)
//    {
//        /* �ؼ���ʾ�¼� */
//        case GX_EVENT_SHOW:
//     
//            /* Ĭ���¼����� */
//            gx_window_event_process(widget, event_ptr);
//            break;
//			
//        /* ��ť1 */
//        case GX_SIGNAL(GUI_ID_BUTTON0, GX_EVENT_CLICKED):
//            gx_single_line_text_input_character_insert(&(window_1.window_1_text_input), (GX_UBYTE *)"1", 1);
//            break;
//		
//        /* ��ť2 */
//        case GX_SIGNAL(GUI_ID_BUTTON1, GX_EVENT_CLICKED):
//            gx_single_line_text_input_character_insert(&(window_1.window_1_text_input), (GX_UBYTE *)"2", 1);
//            break;
//		
//        /* ��ť3 */
//        case GX_SIGNAL(GUI_ID_BUTTON2, GX_EVENT_CLICKED):
//            gx_single_line_text_input_character_insert(&(window_1.window_1_text_input), (GX_UBYTE *)"3", 1);
//            break;

//        /* �������� */
//        case GX_SIGNAL(GUI_ID_BUTTON3, GX_EVENT_CLICKED):
//            gx_single_line_text_input_buffer_clear(&(window_1.window_1_text_input));
//            break;	

//        /* ��ť4 */
//        case GX_SIGNAL(GUI_ID_BUTTON4, GX_EVENT_CLICKED):
//            gx_single_line_text_input_character_insert(&(window_1.window_1_text_input), (GX_UBYTE *)"4", 1);
//            break;	

//        /* ��ť5 */
//        case GX_SIGNAL(GUI_ID_BUTTON5, GX_EVENT_CLICKED):
//            gx_single_line_text_input_character_insert(&(window_1.window_1_text_input), (GX_UBYTE *)"5", 1);
//            break;

//        /* ��ť6 */
//        case GX_SIGNAL(GUI_ID_BUTTON6, GX_EVENT_CLICKED):
//            gx_single_line_text_input_character_insert(&(window_1.window_1_text_input), (GX_UBYTE *)"6", 1);
//            break;	

//        /* ��ťC */
//        case GX_SIGNAL(GUI_ID_BUTTON7, GX_EVENT_CLICKED):
//			gx_single_line_text_input_left_arrow(&(window_1.window_1_text_input));
//			gx_single_line_text_input_character_delete(&(window_1.window_1_text_input));
//            break;			
//		
//        /* ��ť7 */
//        case GX_SIGNAL(GUI_ID_BUTTON8, GX_EVENT_CLICKED):
//            gx_single_line_text_input_character_insert(&(window_1.window_1_text_input), (GX_UBYTE *)"7", 1);
//            break;

//        /* ��ť8 */
//        case GX_SIGNAL(GUI_ID_BUTTON9, GX_EVENT_CLICKED):
//            gx_single_line_text_input_character_insert(&(window_1.window_1_text_input), (GX_UBYTE *)"8", 1);
//            break;	

//        /* ��ť9 */
//        case GX_SIGNAL(GUI_ID_BUTTON10, GX_EVENT_CLICKED):
//            gx_single_line_text_input_character_insert(&(window_1.window_1_text_input), (GX_UBYTE *)"9", 1);
//            break;	

//        /* δʹ��*/
//        case GX_SIGNAL(GUI_ID_BUTTON11, GX_EVENT_CLICKED):
//            break;

//        /* δʹ��*/
//        case GX_SIGNAL(GUI_ID_BUTTON12, GX_EVENT_CLICKED):
//            break;	

//        /* ��ť0 */
//        case GX_SIGNAL(GUI_ID_BUTTON13, GX_EVENT_CLICKED):
//			gx_single_line_text_input_character_insert(&(window_1.window_1_text_input), (GX_UBYTE *)"0", 1);
//            break;	

//        /* δʹ�� */
//        case GX_SIGNAL(GUI_ID_BUTTON14, GX_EVENT_CLICKED):
//            break;

//        /* ��ťOK */
//        case GX_SIGNAL(GUI_ID_BUTTON15, GX_EVENT_CLICKED):
//			/* ��ȡ�ı� */
//			gx_single_line_text_input_buffer_get(&(window_1.window_1_text_input), &buffer_address, &content_size, &buffer_size);
//			gx_prompt_text_set(&(window.window_prompt_1), buffer_address);
//		
//			/* Ĭ���¼����� */
//            gx_window_event_process(widget, event_ptr);
//            break;			

//        default:
//            return gx_window_event_process(widget, event_ptr);
//    }

//    return 0;
//}


/*
*********************************************************************************************************
*	�� �� ��: MainTask
*	����˵��: GUI������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MainTask(void) 
{
	/*
       ����У׼����Ĭ����ע�͵��ģ���������ҪУ׼������������У׼������û���ҪУ׼�������Ļ���ִ��
	   �˺������ɣ��Ὣ����У׼�������浽EEPROM���棬�Ժ�ϵͳ�ϵ���Զ���EEPROM������ء�
	*/
#if 0
	LCD_SetBackLight(255);
	LCD_InitHard();
    TOUCH_Calibration(2);
#endif
	
	/*��ʼ������ */
	gx_initconfig();

	/* ������ʾ�� */
    gx_studio_display_configure(DISPLAY_1, stm32h7_graphics_driver_setup_565rgb,
        LANGUAGE_ENGLISH, DISPLAY_1_THEME_1, &root);
	
    /* �������� */
//	gx_studio_named_widget_create("window_1", (GX_WIDGET *)root, (GX_WIDGET **)&pScreen);

    gx_studio_named_widget_create("window", (GX_WIDGET *)root, (GX_WIDGET **)&pScreen);

	/* ��ʾ������ */
    gx_widget_show(root);

    /* ����GUIX */
    gx_system_start();
	
	tx_thread_sleep(100);
	LCD_SetBackLight(255);
	
	while(1)
	{
		tx_thread_sleep(20);
	}
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
