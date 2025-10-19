#include <chrono>
#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

using namespace std::chrono_literals;

class NumberPublisher : public rclcpp::Node
{
public:
  NumberPublisher()
  : Node("number_publisher")
  {
    publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
    timer_ = this->create_wall_timer(
      500ms, std::bind(&NumberPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = example_interfaces::msg::Int64();
    message.data = 2;
    RCLCPP_INFO(this->get_logger(), "Publishing: %ld", message.data);
    publisher_->publish(message);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NumberPublisher>());
  rclcpp::shutdown();
  return 0;
}
