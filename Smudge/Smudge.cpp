#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>


const uint32_t HEIGHT {600};
const uint32_t WIDTH {800};

GLFWwindow* window;
VkInstance instance;

    class SmudgeMain{
    public:
        void run(){
            initVulkan();
            initWindow();
            mainLoop();
            cleanup();
        }
    private:
        
        void initVulkan(){
            createInstance();
        }
        void initWindow(){
            glfwInit();
                
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            
                
            window = glfwCreateWindow(WIDTH, HEIGHT, "SILVER CHARIOT", nullptr, nullptr);
        }
        void mainLoop(){
            while (!glfwWindowShouldClose(window)){
                glfwPollEvents();
            }
        }
        void cleanup(){
            vkDestroyInstance(instance, nullptr);
        
            glfwDestroyWindow(window);
            
            glfwTerminate();
        }
        void createInstance(){
        VkApplicationInfo appinfo{};
        appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appinfo.pApplicationName = "Smudge";
        appinfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        appinfo.pEngineName = "SILVER CHARIOT";
        appinfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
        appinfo.apiVersion = VK_API_VERSION_1_3;
        
        VkInstanceCreateInfo createinfo{};
        createinfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createinfo.pApplicationInfo = &appinfo;
        
        uint32_t glfwExtensionCount {0};
        const char** glfwExtensions;
        
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        
        createinfo.enabledExtensionCount = glfwExtensionCount;
        createinfo.ppEnabledExtensionNames = glfwExtensions;
        createinfo.enabledLayerCount = 0;
        
        VkResult result = vkCreateInstance(&createinfo, nullptr, &instance);
        if (result != VK_SUCCESS){
        throw std::runtime_error("failed to create an instance IODIOT IDIOT IDIOT");
        }
        uint32_t extensionCount {0};
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        
        std::cout << "available extensions:\n";
        for (const auto& extension : extensions){
            std::cout << '\t' << extension.extensionName << '\n';
        }
        std::cout << extensionCount ;
        }
        


    };

    int main(){
    
        SmudgeMain app;
        try{
            app.run();
        }catch (const std::exception& e){
            std::cerr << e.what() << '\n';
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
