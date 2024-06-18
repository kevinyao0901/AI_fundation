from grabscreen import grab_screen
import cv2
import win32gui
import win32con
from cs_model import load_csmodel
import pynput
from mouse_control import lock
from pynput import keyboard
import time

lock_mode=False

x,y=(1920,1080)
re_x,re_y=(1920,1080)
model=load_csmodel()
mouse =pynput.mouse.Controller()

print("which team are you on ? (input t or ct)")
team=input()

# 非阻塞版本
def on_press(key):
    global lock_mode
    if key == keyboard.Key.shift:
        lock_mode = not lock_mode
        print('lock mode ','on' if lock_mode else 'off')

def on_release(key):
    pass

# 创建键盘监听器
listener = keyboard.Listener(
    on_press=on_press,
    on_release=on_release)

# 启动监听器
listener.start()

while True:
    img0 =grab_screen(region=(0,0,x,y))
    img_w, img_h = img0.shape[2], img0.shape[1]
    cv2.namedWindow('csgo-detect',cv2.WINDOW_NORMAL)
    cv2.resizeWindow('csgo-detect',re_x//3,re_y //3)

    hwnd = win32gui.FindWindow(None,"csgo-detect")
    CVRECT =cv2.getWindowImageRect('csgo-detect')
    win32gui.SetWindowPos(hwnd, win32con.HWND_TOPMOST,0,0,0,0, win32con.SWP_NOMOVE | win32con.SWP_NOSIZE)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        cv2.destroyAllWindows()
        break

    results = model.predict(source=img0, save=False, save_txt=False)
    
    # 处理结果列表
    for result in results:
        #print((result.boxes.xywhn).cpu().numpy())
        #print((result.boxes.cls).cpu().numpy())
        xywh=(result.boxes.xywhn).cpu().numpy().tolist()
        cls=(result.boxes.cls).cpu().numpy().tolist()
        combined_list = [([int(c)], x) for c, x in zip(cls, xywh)]
        if len(combined_list) and lock_mode:
            lock(combined_list,mouse,x,y,team)
            #time.sleep(0.5)

        for aim in combined_list:
            #print(aim)
            if len(aim):

                i=aim[0]
                det=aim[1]
                x_center, y_center, width, height=det
                x_center, width =re_x * float(x_center) , re_x * float(width)
                y_center, height =re_y * float(y_center) , re_y * float(height)
                top_left = (int(x_center - width / 2) ,int(y_center - height / 2))
                bottom_right = (int(x_center + width / 2) ,int(y_center + height / 2))
                color =(0,255,0)

                # code for test to remove hand start

                my_hand=(720 <= x_center <= 1800 and 512 <= y_center <= 1080  and y_center+height/2>=1000)
                print(x_center,y_center)
                print(width,height)

                if not (480 <= x_center <= 1440 and 270 <= y_center <= 810) or my_hand:
                    continue

                # end

                cv2.rectangle(img0,top_left,bottom_right,color,thickness=5)
                cv2.imshow('csgo-detect',img0)


# with pynput.mouse.Events() as events:
#     while True:
#         it = next(events)
#         while it is not None and not isinstance(it, pynput.mouse.Events.Click):
#             it =next(events)
#         if it is not None and it.button == it.button.right and it.pressed:
#             lock_mode = not lock_mode
#             print('lock mode ','on' if lock_mode else 'off')


#         img0 =grab_screen(region=(0,0,x,y))
#         cv2.namedWindow('csgo-detect',cv2.WINDOW_NORMAL)
#         cv2.resizeWindow('csgo-detect',re_x//3,re_y //3)

#         hwnd = win32gui.FindWindow(None,"csgo-detect")
#         CVRECT =cv2.getWindowImageRect('csgo-detect')
#         win32gui.SetWindowPos(hwnd, win32con.HWND_TOPMOST,0,0,0,0, win32con.SWP_NOMOVE | win32con.SWP_NOSIZE)

#         if cv2.waitKey(1) & 0xFF == ord('q'):
#             cv2.destroyAllWindows()
#             break

#         results = model.predict(source=img0, save=False, save_txt=False)
        
#         # 处理结果列表
#         for result in results:
#             #print((result.boxes.xywhn).cpu().numpy())
#             #print((result.boxes.cls).cpu().numpy())
#             xywh=(result.boxes.xywhn).cpu().numpy().tolist()
#             cls=(result.boxes.cls).cpu().numpy().tolist()
#             combined_list = [([int(c)], x) for c, x in zip(cls, xywh)]
#             if len(combined_list) and lock_mode:
#                 lock(combined_list,mouse,x,y)
#             for aim in combined_list:
#                 #print(aim)
#                 if len(aim):
#                     i=aim[0]
#                     det=aim[1]
#                     x_center, y_center, width, height=det
#                     x_center, width =re_x * float(x_center) , re_x * float(width)
#                     y_center, height =re_y * float(y_center) , re_y * float(height)
#                     top_left = (int(x_center - width / 2) ,int(y_center - height / 2))
#                     bottom_right = (int(x_center + width / 2) ,int(y_center + height / 2))
#                     color =(0,255,0)
#                     cv2.rectangle(img0,top_left,bottom_right,color,thickness=5)
#                     cv2.imshow('csgo-detect',img0)