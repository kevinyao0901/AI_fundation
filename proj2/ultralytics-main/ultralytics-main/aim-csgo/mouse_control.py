import pynput
import pyautogui
import pydirectinput
import win32api
import win32con
import time

# def move_mouse(x, y):
#     cur_x, cur_y = win32api.GetCursorPos()
    

#     dx = x - cur_x
#     dy = y - cur_y

#     win32api.mouse_event(win32con.MOUSEEVENTF_MOVE, dx, dy, 0, 0)

def lock(combined_list,mouse,x,y,team):

    mouse_pos_x,mouse_pos_y=mouse.position
    dist_list=[]
    for aim in combined_list:
        i=aim[0]
        det=aim[1]
        x_c, y_c, w, h = det
        dist =(x*float(x_c) - mouse_pos_x) ** 2 + (y*float(y_c) - mouse_pos_y) ** 2
        dist_list.append(dist)

    # following code can work
    # target=combined_list[dist_list.index(min(dist_list))]

    # tag=target[0][0]
    # x_center, y_center, width, height=target[1]
    # x_center, width =x * float(x_center) , x * float(width)
    # y_center, height =y * float(y_center) , y * float(height)

    while dist_list:
        target = combined_list[dist_list.index(min(dist_list))]
        x_center, y_center, width, height = target[1]
        x_center, width = x * float(x_center), x * float(width)
        y_center, height = y * float(y_center), y * float(height)

        my_hand=(720 <= x_center <= 1800 and 512 <= y_center <= 1080  and y_center+height/2>=1000)
        print(x_center,y_center)
        print(width,height)
        # print("box")
        # print(width,height)

        # print("center")
        # print(x_center,y_center)
        if ((480 <= x_center <= 1440 and 270 <= y_center <= 810) and (not my_hand)):
            break
        else:
            del dist_list[dist_list.index(min(dist_list))]

    if not dist_list:
        return

# names:
#   0: ct_body
#   1: ct_head
#   2: t_body
#   3: t_head
    # if tag == 0 or tag == 2:
    #     pydirectinput.moveTo(int(x_center), int(y_center))
    # elif tag == 1 or tag == 3:
    #     pydirectinput.moveTo(int(x_center), int(y_center - 1/6 * height))

    screenWidth, screenHeight = pyautogui.size()
    px, py = pyautogui.position()

    # print(' 移动前鼠标坐标 : (%s, %s)' % ( px, py))
    win32api.mouse_event(win32con.MOUSEEVENTF_MOVE,int(x_center-px),int(y_center-py-height/8), 0, 0)

    # factor_x = (x_center - mouse_pos_x) / (x - mouse_pos_x)
    # factor_y = (y_center - mouse_pos_y) / (y - mouse_pos_y)
    # print(' factor : (%s, %s)' % ( factor_x, factor_y))

    # x, y = pyautogui.position()
    # #返回鼠标的坐标
    # print(' 移动后鼠标坐标 : (%s, %s) ,目标坐标：(%s, %s) , 期望移动距离：(%s, %s) ，真实移动距离：(%s, %s), 实际移动距离/期望移动距离：(%s, %s)' % ( x, y ,x_center ,y_center ,x_center-px, y_center-py ,x-px ,y-py, (x-px)/(x_center-px),(y-py)/(y_center-py)))
    # # 每个1s中打印一次 , 并执行清屏
    # win32api.mouse_event(win32con.MOUSEEVENTF_MOVE,-int(x_center-px),-int(y_center-py), 0, 0)
    
    # if(x!=px and y!=py):
    #     factor_x = (x_center-px)/(x-px)
    #     factor_y = (y_center-py)/(y-py)
    #     print(' 当前鼠标坐标 : (%s, %s)' % ( px, py))
    #     win32api.mouse_event(win32con.MOUSEEVENTF_MOVE,int((x_center-px)*factor_x),int((y_center-py)*factor_y), 0, 0)
    #     time.sleep(2)

    x, y = pyautogui.position()
    # print(' 当前鼠标坐标 : (%s, %s)' % ( px, py))
    win32api.mouse_event(win32con.MOUSEEVENTF_MOVE,1,1, 0, 0)
    x, y = pyautogui.position()
    # print(' 当前鼠标坐标 : (%s, %s)' % ( px, py))


