target extended-remote localhost:3333
monitor reset halt        # 复位并暂停芯片
load                      # 加载程序到Flash
break main                # 在main函数设置断点
continue                  # 开始运行
