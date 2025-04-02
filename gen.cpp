#include <torch/torch.h>
#include <torch/script.h>
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 检查CUDA可用性
    if (!torch::cuda::is_available()) {
        std::cerr << "CUDA not available! Using CPU." << std::endl;
        return -1;
    }
    torch::Device device(torch::kCUDA);

    // 加载模型并移动到GPU
    torch::jit::script::Module module;
    module = torch::jit::load("monet.pt");
    module.to(device);

    // 输入预处理
    cv::Mat input_image = cv::imread("input.jpg");
    cv::cvtColor(input_image, input_image, cv::COLOR_BGR2RGB);

    // 创建张量并移动到GPU
    torch::Tensor input_tensor = torch::from_blob(input_image.data,{1, input_image.rows, input_image.cols, 3},torch::kByte);
    input_tensor = input_tensor.permute({0, 3, 1, 2}).to(torch::kFloat32).div(255);
    input_tensor = input_tensor.sub(0.5).div(0.5);
    input_tensor = input_tensor.to(device);  //数据移至GPU

    // 执行推理
    std::vector<torch::jit::IValue> inputs{input_tensor};
    at::Tensor output_tensor = module.forward(inputs).toTensor().cpu();

    // 后处理
    output_tensor = output_tensor.squeeze().permute({1, 2, 0}).contiguous();        // 确保内存连续
    output_tensor = output_tensor.mul(0.5).add(0.5);
    output_tensor = output_tensor.mul(255).clamp(0, 255).to(torch::kU8);

    // 转换为OpenCV Mat
    cv::Mat output_image(output_tensor.size(0),output_tensor.size(1),CV_8UC3,output_tensor.data_ptr());
    cv::cvtColor(output_image, output_image, cv::COLOR_RGB2BGR);
    cv::imwrite("output.jpg", output_image);

    return 0;
}