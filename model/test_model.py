import torch
import torch.nn as nn
from PIL import Image
from torchvision import transforms
from monet import tensor_to_image

model = torch.load("monet.pt", weights_only=False)
model.eval()

# 输入预处理
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5)),  # 归一化到[-1,1]
])

# 加载输入图像
input_image = Image.open('imgs/test.jpg').convert('RGB')
input_tensor = transform(input_image).unsqueeze(0)

# 生成输出
with torch.no_grad():
    output_tensor = model(input_tensor)

# 转换为图像
output_image = tensor_to_image(output_tensor, denormalize=True)
output_image.save('imgs/test_output.jpg')
