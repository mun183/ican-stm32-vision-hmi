from maix import camera, display, image, nn, app
from maix import uart
from struct import pack

# 加载YOLOv5模型
detector = nn.YOLOv5(model="/root/models/maixhub/188743/model_188743.mud")

# 初始化摄像头和显示器
cam = camera.Camera(detector.input_width(), detector.input_height(), detector.input_format())
dis = display.Display()

# 初始化串口
device = "/dev/ttyS0"
serial = uart.UART(device, 9600)

while not app.need_exit():
    img = cam.read()
    objs = detector.detect(img, conf_th=0.5, iou_th=0.45)
    
    # 检测到物体时发送0x55
    if len(objs) > 0:
        bytes_content = b'\x55'
        serial.write(bytes_content)
        print(f'Sent: {bytes_content.hex()}')
    
    for obj in objs:
        img.draw_rect(obj.x, obj.y, obj.w, obj.h, color=image.COLOR_RED)
        msg = f'{detector.labels[obj.class_id]}: {obj.score:.2f}'
        img.draw_string(obj.x, obj.y, msg, color=image.COLOR_RED)
    
    # 显示图像
    dis.show(img)