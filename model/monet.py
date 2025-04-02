import torch
import torch.nn as nn
from PIL import Image
from torchvision import transforms
class ResidualBlock(nn.Module):
    def __init__(self, channels):
        super(ResidualBlock, self).__init__()
        self.conv_block = nn.Sequential(
            nn.ReflectionPad2d(1),
            nn.Conv2d(channels, channels, 3),
            nn.InstanceNorm2d(channels),
            nn.ReLU(True),
            nn.ReflectionPad2d(1),
            nn.Conv2d(channels, channels, 3),
            nn.InstanceNorm2d(channels)
        )

    def forward(self, x):
        return x + self.conv_block(x)

class Generator(nn.Module):
    def __init__(self, input_channels=3, output_channels=3, n_residual_blocks=9):
        super(Generator, self).__init__()

        # 初始卷积块
        model = [
            nn.ReflectionPad2d(3),
            nn.Conv2d(input_channels, 64, 7),
            nn.InstanceNorm2d(64),
            nn.ReLU(True)
        ]

        # 下采样
        in_channels = 64
        for _ in range(2):
            out_channels = in_channels * 2
            model += [
                nn.Conv2d(in_channels, out_channels, 3, stride=2, padding=1),
                nn.InstanceNorm2d(out_channels),
                nn.ReLU(True)
            ]
            in_channels = out_channels

        # 残差块
        for _ in range(n_residual_blocks):
            model += [ResidualBlock(in_channels)]

        # 上采样
        for _ in range(2):
            out_channels = in_channels // 2
            model += [
                nn.ConvTranspose2d(in_channels, out_channels, 3, stride=2, padding=1, output_padding=1),
                nn.InstanceNorm2d(out_channels),
                nn.ReLU(True)
            ]
            in_channels = out_channels

        # 输出层
        model += [
            nn.ReflectionPad2d(3),
            nn.Conv2d(64, output_channels, 7),
            nn.Tanh()
        ]

        self.model = nn.Sequential(*model)

    def forward(self, x):
        return self.model(x)


def tensor_to_image(tensor, denormalize=True):
    # 转换到CPU
    tensor = tensor.detach().cpu()

    # 逆归一化（训练时用了(0.5,0.5,0.5)均值和标准差）
    if denormalize:
        tensor = tensor * 0.5 + 0.5  # 从[-1,1]转换到[0,1]

    # 调整维度顺序：(C, H, W) -> (H, W, C)
    image = tensor.squeeze()

    # 转换为PIL图像
    return transforms.ToPILImage()(image)

generator = Generator()
generator.load_state_dict(torch.load('monet.pth'), strict=False)
generator.eval()
# 输入预处理
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5)),  # 归一化到[-1,1]
])

# 加载输入图像
input_image = Image.open('imgs/input2.png').convert('RGB')
input_tensor = transform(input_image).unsqueeze(0)

# 生成输出
with torch.no_grad():
    output_tensor = generator(input_tensor)

# 保存jit traced 模型
trace_model = torch.jit.trace(generator, input_tensor)
trace_model.save("monet.pt")

# 转换为图像
output_image = tensor_to_image(output_tensor, denormalize=True)
output_image.save('imgs/output2.jpg')
