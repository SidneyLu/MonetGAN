#include "generator.h"

torch::Device device(torch::kCUDA);

cv::Mat Generate(const cv::Mat& input_image) {
    // Load the model and move it to GPU
    torch::jit::script::Module module;
    module = torch::jit::load("monet.pt");
    module.to(device);

    // Create the input tensor and move it to GPU
    torch::Tensor input_tensor = torch::from_blob(input_image.data,{1, input_image.rows, input_image.cols, 3},torch::kByte);
    // Preprocessing
    input_tensor = input_tensor.permute({0, 3, 1, 2}).to(torch::kFloat32).div(255);
    input_tensor = input_tensor.sub(0.5).div(0.5);
    input_tensor = input_tensor.to(device);

    // Inference
    std::vector<torch::jit::IValue> inputs{input_tensor};
    at::Tensor output_tensor = module.forward(inputs).toTensor().cpu();

    // Postprocessing
    output_tensor = output_tensor.squeeze().permute({1, 2, 0}).contiguous();        // 确保内存连续
    output_tensor = output_tensor.mul(0.5).add(0.5);
    output_tensor = output_tensor.mul(255).clamp(0, 255).to(torch::kU8);

    // Convert to OpenCV Mat
    static cv::Mat output_image(output_tensor.size(0),output_tensor.size(1),CV_8UC3,output_tensor.data_ptr());
    return output_image;

}