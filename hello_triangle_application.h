#ifndef TRIANGLE_APP_CLASS_H
#define TRIANGLE_APP_CLASS_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

class HelloTriangleApplication {
 public:
  void runMainLoop();
  HelloTriangleApplication(GLFWwindow* w) : window(w) { initVulkan(); }
  HelloTriangleApplication() = delete;

  ~HelloTriangleApplication();

 private:
  void initVulkan();
  void createInstance();  
  void setupDebugCallback();
  void pickPhysicalDevice();
  void createLogicalDevice();
  void createSwapChain();

  void createImageViews();
  void createRenderPass();
  void createGraphicsPipeline();
  void createFramebuffers();
  void createCommandPool();
  void createCommandBuffers();
  void createSyncObjects();

  void drawFrame();
  void recreateSwapChain();
  void cleanupSwapChain();

  GLFWwindow* window;
  VkInstance instance;
  VkDebugUtilsMessengerEXT validation_callback;
  VkSurfaceKHR surface;
  VkPhysicalDevice physical_device;
  VkDevice logical_device;
  VkQueue graphics_queue;
  VkQueue present_queue;

  VkSwapchainKHR swap_chain;
  std::vector<VkImage> swap_chain_images; // Presentable images
  VkFormat swap_chain_image_format; // Colour depth
  VkExtent2D swap_chain_extent;  // Resolution of images
  std::vector<VkImageView> swap_chain_image_views; // Swapchain view

  VkRenderPass render_pass;
  VkPipelineLayout pipeline_layout;
  VkPipeline graphics_pipeline;
  std::vector<VkFramebuffer> swap_chain_framebuffers;
  VkCommandPool command_pool;
  std::vector<VkCommandBuffer> command_buffers;

  std::vector<VkSemaphore> image_available_semaphores; // signal that an image has been acquired and is ready for rendering
  std::vector<VkSemaphore> render_finished_semaphores; // signal that rendering has finished and presentation can happen
  std::vector<VkFence> in_flight_fences; // Performs CPU-GPU synchronization
  size_t current_frame = 0; // Used to index semaphores, so correct pair is used. TODO: improve by wrapping synchro in struct

 public:
  bool framebuffer_resized = false;
};
#endif  // TRIANGLE_APP_CLASS_H