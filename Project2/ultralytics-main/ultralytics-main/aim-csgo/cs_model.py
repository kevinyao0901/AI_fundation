import torch
from ultralytics import YOLO 

device = 'cuda' if torch.cuda.is_available() else 'cpu'

model_path=r'D:\courseware\AI基础\Lab\proj2\ultralytics-main\ultralytics-main\aim-csgo\models\best.pt'

imgsz=640

def load_csmodel():
    model = YOLO(model_path)  # 加载一个预训练的YOLOv8n模型

    return model

