#include <chrono>
#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

using namespace std::chrono_literals;

class FirstPublisher : public rclcpp::Node
{
public:
  FirstPublisher()
  : Node("first_publisher")
  {
    publisher = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
    timer_ = this->create_wall_timer(
      500ms, std::bind(&FirstPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = example_interfaces::msg::Int64();
    message.data = count_++; 
    RCLCPP_INFO(this->get_logger(), "Publishing: %ld", message.data);
    publisher->publish(message);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher;

  size_t count_ = 0; 
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FirstPublisher>());
  rclcpp::shutdown();
  return 0;
}